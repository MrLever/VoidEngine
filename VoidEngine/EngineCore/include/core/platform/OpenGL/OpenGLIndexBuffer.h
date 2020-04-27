#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/rendering/IndexBuffer.h"

namespace core {

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		/**
		 * Constructor
		 */
		OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);

		/**
		 * Destructor
		 */
		virtual ~OpenGLIndexBuffer();

		/**
		 * Binds OpenGL IndexBuffer to active VAO
		 */
		void Bind() const override;

		/**
		 * Unbinds OpenGL IndexBuffer to active VAO
		 */
		void Unbind() const override;

		/**
		 * Returns number of indices in index buffer
		 */
		uint32_t GetCount() const override;

		uint32_t handle;
		uint32_t indexCount;
	};

}