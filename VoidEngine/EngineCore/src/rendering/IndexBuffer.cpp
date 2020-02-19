//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Logger.h"

#include "rendering/IndexBuffer.h"
#include "rendering/Renderer.h"

namespace core {
	
	IndexBuffer* IndexBuffer::Create(float* indices, uint32_t size) {
		switch (Renderer::GetRendererAPI()) {
		case RendererAPI::NONE:
			utils::Logger::LogError("Index does not support selected rendering API: NONE");
			return nullptr;
			break;

		case RendererAPI::OPENGL:
			return new 
		default:
			utils::Logger::LogError("Index does not support selected rendering API: ERROR");
			return nullptr;
			break;
		}
	}

}