//STD Headers
#include <iostream>

//Library Headers
#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb/stb_image.h"

//Void Engine Headers
#include "Texture.h"

namespace EngineCore {
	Texture::Texture(const std::string& name, const std::string& texturePath)
		: Resource(texturePath), Name(std::move(name)), TextureHandle(-1), TextureUnit(0), ImageData(nullptr), 
		  TextureWidth(-1), TextureHeight(-1), TextureColorChannels(-1) {

	}

	Texture::Texture(const std::string& name, const std::string& texturePath, GLint textureUnit)
		: Resource(texturePath), Name(std::move(name)), TextureHandle(-1), TextureUnit(textureUnit), ImageData(nullptr),
		  TextureWidth(-1), TextureHeight(-1), TextureColorChannels(-1) {

	}

	Texture::~Texture() {
		if (ImageData != nullptr) {
			stbi_image_free(ImageData);
		}
	}

	bool Texture::Load() {
		//stbi is loading files upside down, so flip it back
		stbi_set_flip_vertically_on_load(true);

		//Load image data from file into heap
		ImageData = stbi_load(ResourcePath.string().c_str(), &TextureWidth, &TextureHeight, &TextureColorChannels, 0);
		
		if (ImageData) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Texture::LoadErrorResource() {
		return false;
	}

	void Texture::GenerateTextureInfo() {
		if (!ImageData) {
			std::cout << "Error: Texture not loaded. Cannot generate OpenGL texture info\n";
			return;
		}

		glGenTextures(1, &TextureHandle);
		glBindTexture(GL_TEXTURE_2D, TextureHandle);

		//Set textures to repeat at edges
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
		//Set texture filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Pass image data to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureWidth, TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ImageData);
		
		//Instruct OpenGL to generate a Mipmap
		glGenerateMipmap(GL_TEXTURE_2D);

		//Once the image is bound by OpenGL, the raw data is no longer necessary
		stbi_image_free(ImageData);
		ImageData = nullptr;
	}

	void Texture::Use() {
		glActiveTexture(GL_TEXTURE0 + TextureUnit);
		glBindTexture(GL_TEXTURE_2D, TextureHandle);
	}

	std::string Texture::GetName() {
		return Name;
	}

	GLint Texture::GetUnit() {
		return TextureUnit;
	}

}