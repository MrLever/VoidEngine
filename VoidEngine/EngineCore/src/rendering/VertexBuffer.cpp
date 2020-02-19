//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Logger.h"

#include "rendering/VertexBuffer.h"
#include "rendering/Renderer.h"

namespace core {
	
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetRendererAPI()) {
		default:
			utils::Logger::LogError("VertexBuffer does not support selected rendering API");
			return nullptr;
			break;
		}
	}

}