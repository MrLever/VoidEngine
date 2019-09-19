#pragma once

//STD Headers
#include "Resource.h"

//Library Headers
#include <glad/glad.h>

//Void Engine Headers

namespace EngineCore {

	class Texture : public EngineUtils::Resource {
	public:
		/**
		 * Constructor
		 */
		Texture(const std::string& texturePath);

		/**
		 * Destructor
		 */
		~Texture();

		/**
		 * Loads texture from memory
		 */
		bool Load() override;

		/**
		 * Loads the resource's default value if the path provided is invalid
		 */
		bool LoadErrorResource() override;

		/**
		 * Generates OpenGL data needed to use this texture in rendering
		 */
		void GenerateTextureInfo();

		/**
		 * Instructs OpenGL we'd like to use this texture in our next draw call
		 */
		void Use();

	private:
		/** Handle used by OpenGL to address this texture */
		GLuint TextureHandle;

		/** The raw data of the image loaded for the texture */
		unsigned char* ImageData;

		/** Width of the texture in pixels */
		int TextureWidth;

		/** Height of the texture in pixels*/
		int TextureHeight;

		/** Number of color channels per pixel */
		int TextureColorChannels;
	};

}