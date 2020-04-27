//STD Headers

//Library Headers
#include <glad/glad.h>

//Void Engine Headers
#include "platform/OpenGL/OpenGLIndexBuffer.h"

namespace core {

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	}

	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const {
		return indexCount;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, uint32_t count) : indexCount(count) {
		glCreateBuffers(1, &handle);
		
		// Set to ARRAY_BUFFER to avoid VAO binding issues.
		glBindBuffer(GL_ARRAY_BUFFER, handle);
		glBufferData(GL_ARRAY_BUFFER, indexCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &handle);
	}
}