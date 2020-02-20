//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Logger.h"

#include "platform/rendering/OpenGLVertexBuffer.h"

#include "rendering/VertexBuffer.h"
#include "rendering/Renderer.h"

namespace core {
	
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetRendererAPI()) {
			case RendererAPI::NONE:
				utils::Logger::LogError("VertexBuffer does not support selected rendering API: NONE");
				return nullptr;
			case RendererAPI::OPENGL:
				return new OpenGLVertexBuffer(vertices, size);
			case RendererAPI::DIRECT3D12:
				utils::Logger::LogError("VertexBuffer does not support selected rendering API: NONE");
				return nullptr;
			default:
				utils::Logger::LogError("VertexBuffer does not support selected rendering API: ERROR");
				return nullptr;
				break;
		}
	}

}