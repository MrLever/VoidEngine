//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Vector.h"

#include "utils/Logger.h"

#include "rendering/Model.h"
#include "rendering/ShaderProgram.h"

namespace core {

	Model::Model(const std::string& filePath) : utils::Resource(filePath) {
		modelDirectory = ResourcePath.parent_path();
		textureCache = std::make_shared<utils::ResourceAllocator<Texture>>();
		IsThreadSafe = false;
	}

	Model::~Model() {
	
	}

	bool Model::Load() {
		importer = std::make_unique<Assimp::Importer>();
		auto modelData = importer->ReadFile(ResourcePath.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!modelData || modelData->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !modelData->mRootNode) {
			utils::Logger::LogError("ASSIMP File Load error [" + ResourcePath.string() + "] was invalid");
			return false;
		}
		return true;
	}

	bool Model::LoadErrorResource() {
		return false;
	}

	void Model::Initialize() {
		if (importer == nullptr) {
			//Model already initialized
			return;
		}

		ProcessAssimpNode(importer->GetScene()->mRootNode, importer->GetScene());
		
		for (auto& mesh : meshes) {
			mesh.Initialize();
		}
		importer.reset(nullptr);
	}

	void Model::Draw(std::shared_ptr<ShaderProgram> shader, glm::mat4 transform) const {
		for (auto& mesh : meshes) {
			mesh.Draw(shader, transform);
		}
	}
	
	void Model::ProcessAssimpNode(aiNode* node, const aiScene* scene) {
		auto numMeshes = node->mNumMeshes;
		auto numChildren = node->mNumChildren;
		//Extract and process Mesh Data from Assimp
		for (auto i = 0u; i < numMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.emplace_back(ProcessAssimpMesh(mesh, scene));
		}

		//Recursively perform this operation for all of this node's children
		for (auto i = 0u; i < numChildren; i++) {
			ProcessAssimpNode(node->mChildren[i], scene);
		}

	}
	
	Mesh Model::ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene) {
		std::vector<float> vertices;
		std::vector<uint32_t> indices;
		std::vector<TexturePtr> textures;

		auto numVerts = mesh->mNumVertices;

		//Load vertex data
		for (auto i = 0u; i < numVerts; i++) {
			vertices.push_back(mesh->mVertices[i].x);
			vertices.push_back(mesh->mVertices[i].y);
			vertices.push_back(mesh->mVertices[i].z);

			vertices.push_back(mesh->mNormals[i].x);
			vertices.push_back(mesh->mNormals[i].y);
			vertices.push_back(mesh->mNormals[i].z);

			if (mesh->mTextureCoords[0] != nullptr) {
				vertices.push_back(mesh->mTextureCoords[0][i].x);
				vertices.push_back(mesh->mTextureCoords[0][i].y);
			}
			else {
				vertices.push_back(0);
				vertices.push_back(0);
			}
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

			auto texturePath = modelDirectory.string() + "/" + str.C_Str();

			textureHandles.push_back(textureCache->LoadResource(texturePath));
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