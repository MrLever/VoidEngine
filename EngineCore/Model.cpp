//STD Headers

//Library Headers


//Void Engine Headers
#include "Model.h"
#include "Logger.h"
#include "ShaderProgram.h"

namespace core {
	Model::Model(const std::string& filePath) : utils::Resource(filePath) {
		ModelDirectory = ResourcePath.parent_path();
		TextureCache = nullptr;
		IsThreadSafe = false;
		IsComposite = true;
	}

	bool Model::Load() {
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
		std::vector<TextureHandle> textures;

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

		//Load Textures
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

			//Load diffuse maps
			std::vector<TextureHandle> diffuseMaps = LoadTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			//Load specular maps
			std::vector<TextureHandle> specularMaps = LoadTextures(mat, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	std::vector<TextureHandle> Model::LoadTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName) {
		std::vector<TextureHandle> handles;
		auto textureCount = mat->GetTextureCount(type);

		for (auto i = 0u; i < textureCount; i++) {
			aiString str;
			mat->GetTexture(type, i, &str);

			auto texturePath = ModelDirectory.string() + str.C_Str();

			auto texture = TextureCache->GetResource(texturePath);

			if (!texture->GetIsInitialized()) {
				texture->Initialize();
			}

			TextureHandle handle(
				texture->GetTextureID(),
				typeName
			);
		}

		return handles;
	}
}