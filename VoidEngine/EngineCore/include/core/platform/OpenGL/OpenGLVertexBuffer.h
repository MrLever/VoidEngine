#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/rendering/VertexBuffer.h"

namespace core {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		/**
		 * Constructor
		 */
		OpenGLVertexBuffer(const float* vertices, uint32_t size);

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
		const BufferLayout& GetLayout() const override;

	private:
		uint32_t RendererID;

		BufferLayout m_Layout;
	};

}