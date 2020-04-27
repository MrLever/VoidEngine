//STD Headers

//Library Headers
#include <glad/glad.h>

//Void Engine Headers
#include "platform/OpenGL/OpenGLVertexBuffer.h"

namespace core {
	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &handle);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, handle);
	}

	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout) {
		bufferLayout = layout;
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const {
		return bufferLayout;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, uint32_t size) : bufferLayout({}) {
		glCreateBuffers(1, &handle);
		glBindBuffer(GL_ARRAY_BUFFER, handle);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(uint32_t), vertices, GL_STATIC_DRAW);
	}
}