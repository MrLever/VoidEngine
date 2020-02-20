//STD Headers

//Library Headers
#include <glad/glad.h>

//Void Engine Headers
#include "platform/OpenGL/OpenGLVertexBuffer.h"

namespace core {
	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &RendererID);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout) {
		m_Layout = layout;
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout(const BufferLayout& layout) const {
		return m_Layout;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) : m_Layout({}) {
		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
}