//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Vector.h"

#include "utils/Logger.h"

#include "rendering/Model.h"
#include "rendering/ShaderProgram.h"

namespace core {
	Model::Model(const std::string& filePath) : utils::Resource(filePath) {
		ModelDirectory = ResourcePath.parent_path();
		TextureCache = nullptr;
		IsThreadSafe = false;
	}

	bool Model::Load() {
		TextureCache = std::make_shared<utils::ResourceAllocator<Texture>>();
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(ResourcePath.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			utils::Logger::LogError("ASSIMP File Load error [" + ResourcePath.string() + "] was invalid");
			return false;
		}

		ProcessAssimpNode(scene->mRootNode, scene);

		return true;
	}

	bool Model::LoadErrorResource() {
		return false;
	}

	void Model::Initialize() {
		for (auto& mesh : Meshes) {
			mesh.Initialize();
		}
	}

	void Model::Draw(ShaderProgram* shader) const {
		for (auto& mesh : Meshes) {
			mesh.Draw(shader);
		}
	}
	
	void Model::ProcessAssimpNode(aiNode* node, const aiScene* scene) {
		auto numMeshes = node->mNumMeshes;
		auto numChildren = node->mNumChildren;
		//Extract and process Mesh Data from Assimp
		for (auto i = 0u; i < numMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			Meshes.emplace_back(ProcessAssimpMesh(mesh, scene));
		}

		//Recursively perform this operation for all of this node's children
		for (auto i = 0u; i < numChildren; i++) {
			ProcessAssimpNode(node->mChildren[i], scene);
		}

	}
	
	Mesh Model::ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene) {
		std::vector<Vertex> vertices;
		std::vector<unsigned> indices;
		std::vector<TexturePtr> textures;

		auto numVerts = mesh->mNumVertices;

		//Load vertex data
		for (auto i = 0u; i < numVerts; i++) {
			Vertex vert;
			vert.Position = glm::vec3(
				mesh->mVertices[i].x, 
				mesh->mVertices[i].y, 
				mesh->mVertices[i].z
			);

			vert.Normal = glm::vec3(
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z
			);

			if (mesh->mTextureCoords[0] != nullptr) {
				vert.UV = glm::vec2(
					mesh->mTextureCoords[0][i].x,
					mesh->mTextureCoords[0][i].y
				);
			}

			vertices.push_back(vert);
		}

		//Load Index data
		auto numFaces = mesh->mNumFaces;
		for (auto i = 0u; i < numFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (auto j = 0u; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		math::Color matDiffuseColor;
		bool isBasicMaterial = false;
		//Load Material data
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

			aiColor4D diffuseColor;

			auto hasBasicColor = aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
			if (hasBasicColor == aiReturn_SUCCESS) {
				isBasicMaterial = true;
				matDiffuseColor.X = diffuseColor.r;
				matDiffuseColor.Y = diffuseColor.g;
				matDiffuseColor.Z = diffuseColor.b;
				matDiffuseColor.W = diffuseColor.a;
			}

			//Load diffuse maps
			LoadTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse", textures);

			//Load specular maps
			LoadTextures(mat, aiTextureType_SPECULAR, "texture_specular", textures);

		}

		Mesh finalMesh(vertices, indices, textures);
		
		if (isBasicMaterial) {
			finalMesh.SetMaterialDiffuse(matDiffuseColor);
		}

		return finalMesh;
	}

	void Model::LoadTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName, std::vector<TexturePtr>& textures) {
		auto textureCount = mat->GetTextureCount(type);
		TextureType t = (typeName == "texture_diffuse") ? TextureType::DIFFUSE : TextureType::SPECULAR;

		std::vector<utils::ResourceHandle<Texture>> textureHandles;

		//Load all the textures for the model in parrallel (SCATTER)
		for (auto i = 0u; i < textureCount; i++) {
			aiString str;
			mat->GetTexture(type, i, &str);

			auto texturePath = ModelDirectory.string() + "/" + str.C_Str();

			textureHandles.push_back(TextureCache->LoadResource(texturePath));
		}

		//Extract all texture data (GATHER)
		for (auto& handle : textureHandles) {
			//Extract texture from thread safe container
			auto texture = handle.GetResource();
			
			//Set pertinent texture data
			texture->SetType(t);

			//Send it off for rendering
			textures.push_back(std::move(texture));
		}
	}
}