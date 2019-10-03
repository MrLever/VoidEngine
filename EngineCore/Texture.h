#pragma once

//STD Headers
#include "Resource.h"

//Library Headers
#include <glad/glad.h>

//Void Engine Headers

namespace core {
	/**
	 * @class Texture
	 * @brief Class to define how to handle OpenGL Textures
	 */
	class Texture : public EngineUtils::Resource {
	public:
		/**
		 * Constructor
		 * @param texturePath Path to the texture's data
		 */
		Texture(const std::string& name, const std::string& texturePath);

		/**
		 * Constructor
		 * @param texturePath Path to the texture's data
		 */
		Texture(const std::string& name, const std::string& texturePath, GLint textureUnit);

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
		void Initialize() override;

		/**
		 * Instructs OpenGL we'd like to use this texture in our next draw call
		 */
		void Use();

		/**
		 * Getter for the Texture's name
		 */
		std::string GetName();

		/**
		 * Getter for the Texture's OpenGL Texture Unit
		 */
		GLint GetUnit();

	private:
		/** The texure's name, used for setting uniforms */
		std::string Name;

		/** Handle used by OpenGL to address this texture */
		GLuint TextureHandle;

		/** Defines this textures corresponding Texture Unit */
		GLint TextureUnit;

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