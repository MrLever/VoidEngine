#pragma once
//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "core/rendering/IndexBuffer.h"
#include "core/rendering/VertexBuffer.h"

namespace core {
	
	class VertexArray {
	public:
		/**
		 * Factory method to create a index buffer appropriate for the current
		 * rendering pipeline.
		 */
		static std::shared_ptr<VertexArray> Create();

		/**
		 * Destructor
		 */
		virtual ~VertexArray() {};

		/**
		 * Binds VertexArray in rendering pipeline
		 */
		virtual void Bind() const = 0;

		/**
		 * Unbinds VertexArray in rendering pipeline
		 */
		virtual void Unbind() const = 0;

		/**
		 * Links a VertexBuffer to the VertexArray
		 */
		virtual void LinkVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;

		/**
		 * Links a IndexBuffer to the VertexArray
		 */
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

		/**
		 * Accessor for linked index buffer
		 */
		virtual std::shared_ptr<const IndexBuffer> GetIndexBuffer() const = 0;

		/**
		 * Accessor for linked vertex buffers
		 */
		virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const = 0;
	};

}