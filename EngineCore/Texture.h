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
	class Texture : public utils::Resource {
	public:
		/**
		 * Constructor
		 * @param texturePath Path to the texture's data
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
		void Initialize() override;

		/**
		 * Instructs OpenGL we'd like to use this texture in our next draw call
		 */
		void Use();

		/**
		 * Sets this textures name for use in GLSL uniform assignment
		 */
		void SetName(const std::string& name);

		/**
		 * Getter for this Texture's name
		 */
		std::string GetName();

	private:
		/** The texure's name, used for setting uniforms */
		std::string TextureName;

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