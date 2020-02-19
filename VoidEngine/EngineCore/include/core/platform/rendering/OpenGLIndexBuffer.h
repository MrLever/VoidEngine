#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/rendering/IndexBuffer.h"

namespace core {

	class OpenGLIndexBuffer : public IndexBuffer{
		friend class IndexBuffer;

	public:
		/**
		 * Destructor
		 */
		virtual ~OpenGLIndexBuffer() {}

		/**
		 * Binds OpenGL IndexBuffer to active VAO
		 */
		virtual void Bind() const override;

		/**
		 * Unbinds OpenGL IndexBuffer to active VAO
		 */
		virtual void Unbind() const override;

	private:
		/**
		 * Constructor
		 */
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);

		uint32_t RendererID;
	};

}