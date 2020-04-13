#pragma once
//STD Headers
#include <vector>
#include <filesystem>

//Library Headers
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//Void Engine Headers
#include "utils/resource/Resource.h"
#include "utils/resource/ResourceAllocator.h"

#include "core/rendering/Texture.h"
#include "core/rendering/Mesh.h"
#include "core/rendering/ShaderProgram.h"

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
		 * @param shader The shader to use when drawing this model
		 */
		void Draw(std::shared_ptr<ShaderProgram> shader, glm::mat4 transform) const;

	private:
		/**
		 * Recursive function to process the Assimp data structures for model loading
		 * @param node The current node being processed
		 * @param scene The model's current scene
		 */
		void ProcessAssimpNode(aiNode* node, const aiScene* scene);

		/**
		 * Helper function for ProcessAssimpNode that constructs and populates a mesh
		 * @param mesh The Assimp mesh data to process
		 * @param scene The model's current scene
		 */
		Mesh ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene);

		/**
		 * Helper function for ProcessAssimpMesh that loads all the textures referenced by the mesh being loaded
		 * @param mat The material specifying the textures to load
		 * @param type The type of texture being loaded
		 * @param typeName the string literal representing the type name
		 * @param textures The texture list to insert into
		 */
		void LoadTextures(
			aiMaterial* mat, 
			aiTextureType type, 
			const std::string& typeName,
			std::vector<TexturePtr>& textures
		);

		/** The directory this model was loaded from */
		std::filesystem::path modelDirectory;

		/** The set of meshes that make up this model */
		std::vector<Mesh> meshes;

		/** Cache of textures used to draw this model */
		ResourceAllocatorPtr<Texture> textureCache;

		/** A static scene importer that holds a reference to the last scene loaded */
		Assimp::Importer importer;
	};

}
