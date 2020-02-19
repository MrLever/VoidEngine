//STD Headers

//Library Headers
#include <glad/glad.h>

//Void Engine Headers
#include "platform/rendering/OpenGLIndexBuffer.h"

namespace core {

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t size) {
		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

}