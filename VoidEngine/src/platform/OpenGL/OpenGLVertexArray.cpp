#pragma once
//STD Headers

//Library Headers
#include <glad/glad.h>

//Void Engine Headers
#include "platform/OpenGL/OpenGLVertexArray.h"

namespace core {
	
	static GLenum ShaderDataTypeToOpenGL(ShaderDataType type) {
		switch (type) {
		case core::ShaderDataType::FLOAT:    return GL_FLOAT;
		case core::ShaderDataType::FLOAT_2:  return GL_FLOAT;
		case core::ShaderDataType::FLOAT_3:  return GL_FLOAT;
		case core::ShaderDataType::FLOAT_4:  return GL_FLOAT;
		case core::ShaderDataType::INT:	     return GL_INT;
		case core::ShaderDataType::INT_2:	 return GL_INT;
		case core::ShaderDataType::INT_3:	 return GL_INT;
		case core::ShaderDataType::INT_4:	 return GL_INT;
		case core::ShaderDataType::MAT_3:	 return GL_FLOAT;
		case core::ShaderDataType::MAT_4:	 return GL_FLOAT;
		case core::ShaderDataType::BOOL:	 return GL_BOOL;
		}

		VE_ASSERT(false, "ShaderDataType cannot be converted to OpenGL type");
		return 0;
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(handle);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::LinkVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) {
		VE_ASSERT(buffer->GetLayout().GetNumElements(), "Vertex buffer has no layout :(((");

		glBindVertexArray(handle);
		buffer->Bind();

		GLuint i = 0;
		const auto& layout = buffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(
				i,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGL(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			i++;
		}

		glBindVertexArray(0);
		vertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) {
		glBindVertexArray(handle);
		buffer->Bind();

		glBindVertexArray(0);
		indexBuffer = buffer;
	}

	std::shared_ptr<const IndexBuffer> OpenGLVertexArray::GetIndexBuffer() const {
		return indexBuffer;
	}

	std::vector<std::shared_ptr<VertexBuffer>> OpenGLVertexArray::GetVertexBuffers() const {
		return vertexBuffers;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &handle);
	}
	
	OpenGLVertexArray::~OpenGLVertexArray(){
		glDeleteVertexArrays(1, &handle);
	};
}