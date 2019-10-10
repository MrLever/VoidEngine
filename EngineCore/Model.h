#pragma once
//STD Headers
#include <vector>

//Library Headers

//Void Engine Headers
#include "Resource.h"
#include "ResourceAllocator.h"
#include "Mesh.h"


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

	private:
		/** The set of meshes that make up this model */
		std::vector<Mesh> Meshes;

		/** Cache of textures used to draw this model */
		ResourceAllocatorPtr<Texture> TextureCache;
	};

}
