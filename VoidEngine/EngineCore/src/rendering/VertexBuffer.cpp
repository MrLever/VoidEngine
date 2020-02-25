//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Logger.h"

#include "platform/OpenGL/OpenGLVertexBuffer.h"

#include "rendering/VertexBuffer.h"
#include "rendering/Renderer.h"

namespace core {
	
	VertexBuffer* VertexBuffer::Create(const float* vertices, uint32_t size) {
		switch (Renderer::GetRendererAPI()) {
			case RenderDevice::API::OPENGL:
				return new OpenGLVertexBuffer(vertices, size);
		}

		utils::Logger::LogError("VertexBuffer does not support selected rendering API.");
		return nullptr;
	}

}