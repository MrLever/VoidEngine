#pragma once
//STD Headers
#include <cstdint>
#include <memory>

//Library Headers

//Void Engine Headers

namespace core {

	class IndexBuffer {
	public:
		/**
		 * Factory method to create a index buffer appropriate for the current
		 * rendering pipeline.
		 */
		static std::shared_ptr<IndexBuffer> Create(const uint32_t* indices, uint32_t size);

		/**
		 * Destructor
		 */
		virtual ~IndexBuffer() {};

		/**
		 * Binds VertexBuffer in rendering pipeline
		 */
		virtual void Bind() const = 0;

		/**
		 * Unbinds VertexBuffer in rendering pipeline
		 */
		virtual void Unbind() const = 0;

		/**
		 * Returns number of indices in index buffer
		 */
		virtual uint32_t GetCount() const = 0;

	};

}