//STD Headers

//Library Headers
#include <glad/glad.h>

//Void Engine Headers
#include "platform/OpenGL/OpenGLIndexBuffer.h"

namespace core {

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const {
		return m_IndexCount;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_IndexCount(count) {
		glCreateBuffers(1, &m_RendererID);
		
		// Set to ARRAY_BUFFER to avoid VAO binding issues.
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, m_IndexCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

}