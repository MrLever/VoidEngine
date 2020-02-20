#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/rendering/VertexBuffer.h"

namespace core {

	class OpenGLVertexBuffer : public VertexBuffer {
		friend class VertexBuffer;
	public:
		/**
		 * Destructor
		 */
		virtual ~OpenGLVertexBuffer();

		/**
		 * Binds OpenGL IndexBuffer to active VAO
		 */
		void Bind() const;

		/**
		 * Unbinds OpenGL IndexBuffer to active VAO
		 */
		void Unbind() const;

		/**
		 * Allows calling code to specify vertex layout data in buffer
		 */
		void SetLayout(const BufferLayout& layout) override;

		/**
		 * Accessor for buffer layout
		 */
		const BufferLayout& GetLayout(const BufferLayout& layout) const override;

	private:
		/**
		 * Constructor
		 */
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		uint32_t RendererID;

		BufferLayout m_Layout;
	};

}