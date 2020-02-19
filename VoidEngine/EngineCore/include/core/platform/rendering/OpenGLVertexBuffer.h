#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/rendering/VertexBuffer.h"

namespace core {

	class OpenGLVertexBuffer {
		friend class VertexBuffer;
	public:
		/**
		 * Destructor
		 */
		virtual ~OpenGLVertexBuffer();

		/**
		 * Binds OpenGL IndexBuffer to active VAO
		 */
		virtual void Bind() const;

		/**
		 * Unbinds OpenGL IndexBuffer to active VAO
		 */
		virtual void Unbind() const;

	private:
		/**
		 * Constructor
		 */
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		
		uint32_t RendererID;
	};

}