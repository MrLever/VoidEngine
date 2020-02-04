//STD Headers

//Library Headers
#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb/stb_image.h"

//Void Engine Headers
#include "Texture.h"
#include "utils/Logger.h"

namespace core {
	Texture::Texture(const std::string& texturePath)
		: Resource(texturePath), TextureHandle(-1), ImageData(nullptr), 
		  TextureWidth(-1), TextureHeight(-1), TextureColorChannels(-1), Type(TextureType::DIFFUSE) {

	}

	Texture::~Texture() {
		if (ImageData != nullptr) {
			stbi_image_free(ImageData);
		}
	}

	bool Texture::Load() {
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

	void Texture::Initialize() {
		if (IsInitialized) {
			utils::Logger::LogDebug("Texture [" + ResourceID.StringID + "] has already been initialized");
			return;
		}
		if (!ImageData) {
			utils::Logger::LogError("Texture not loaded. Cannot generate OpenGL texture info");
			return;
		}

		//Generate an OpenGL handle for this texture
		glGenTextures(1, &TextureHandle);
		glBindTexture(GL_TEXTURE_2D, TextureHandle);

		//Pass image data to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureWidth, TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ImageData);

		//Instruct OpenGL to generate a Mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
		
		//Set textures to repeat at edges
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
		//Set texture filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Once the image is bound by OpenGL, the raw data is no longer necessary
		stbi_image_free(ImageData);
		ImageData = nullptr;

		IsInitialized = true;
	}

	void Texture::Use() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureHandle);
	}

	GLuint Texture::GetTextureID() {
		return TextureHandle;
	}

	void Texture::SetName(const std::string& name) {
		TextureName = name;
	}

	void Texture::SetType(TextureType type) {
		Type = type;
	}

	TextureType Texture::GetType() {
		return Type;
	}

	std::string Texture::GetName() {
		return TextureName;
	}

}