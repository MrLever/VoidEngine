//STD Headers

//Library Headers
#include <glad/glad.h>

//Void Engine Headers
#include "platform/rendering/OpenGLIndexBuffer.h"

namespace core {

	void OpenGLIndexBuffer::Bind() const {
	
	}

	void OpenGLIndexBuffer::Unbind() const {

	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(float* indices, uint32_t size) {
		glCreateBuffers(1, &RendererID);
		glBufferData();
	}

}