//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Logger.h"

#include "platform/OpenGL/OpenGLIndexBuffer.h"

#include "rendering/IndexBuffer.h"
#include "rendering/Renderer.h"

namespace core {
	
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetRendererAPI()) {
			case RendererAPI::NONE:
				utils::Logger::LogError("IndexBuffer does not support selected rendering API: NONE");
				return nullptr;
			case RendererAPI::OPENGL:
				return new OpenGLIndexBuffer(indices, size);
			case RendererAPI::DIRECT3D12:
				utils::Logger::LogError("Index does not support selected rendering API: DIRECT3D12");
				return nullptr;
		}

		utils::Logger::LogError("Index does not support selected rendering API: ERROR");
		return nullptr;
	}

}