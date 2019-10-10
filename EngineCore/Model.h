#pragma once
//STD Headers
#include <vector>
#include <filesystem>

//Library Headers

//Void Engine Headers
#include "Resource.h"
#include "ResourceAllocator.h"
#include "Texture.h"
#include "Mesh.h"
#include "ShaderProgram.h"

namespace core {

	class Model : public utils::Resource {
	public:
		/**
		 * Constructor
		 */
		Model(const std::string& filePath);

		/**
		 * Loads the model from main memory
		 */
		bool Load() override;

		/**
		 * Loads a default error cube
		 */
		bool LoadErrorResource() override;

		/**
		 * Generates OpenGL data for child meshes
		 */
		void Initialize() override;

		/**
		 * Draws model in scene
		 */
		void Draw(ShaderProgram shader) const;

	private:

		void ProcessAssimpNode(aiNode* node, const aiScene* scene);

		Mesh ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene);

		std::vector<TextureHandle> LoadTextures(
			aiMaterial* mat, 
			aiTextureType type, 
			const std::string& typeName
		);

		std::filesystem::path ModelDirectory;

		/** The set of meshes that make up this model */
		std::vector<Mesh> Meshes;

		/** Cache of textures used to draw this model */
		ResourceAllocatorPtr<Texture> TextureCache;
	};

}
