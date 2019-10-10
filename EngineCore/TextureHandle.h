#pragma once
//STD Headers
#include <string>

//Library Headers

//Void Engine Headers

namespace core {

	struct TextureHandle {

		/**
		 * Constructor
		 */
		TextureHandle(unsigned ID, const std::string& type) : TextureID(ID), Type(type) {

		}

		unsigned TextureID;
		std::string Type;

	};

}

