//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Logger.h"

#include "platform/OpenGL/OpenGLVertexBuffer.h"

#include "rendering/VertexBuffer.h"
#include "rendering/Renderer.h"

namespace core {
	
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(const float* vertices, uint32_t size) {
		switch (Renderer::GetRendererAPI()) {
			case RenderDevice::API::OPENGL:
				return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		VE_ASSERT(false, "VertexBuffer does not support selected rendering API.");
		return nullptr;
	}

}