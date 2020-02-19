#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/rendering/IndexBuffer.h"

namespace core {

	class OpenGLIndexBuffer {
		friend class IndexBuffer;

	public:
		/**
		 * Destructor
		 */
		virtual ~OpenGLIndexBuffer() {}

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
		OpenGLIndexBuffer(float* indices, uint32_t size);

		uint32_t RendererID;
	};

}