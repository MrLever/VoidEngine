#pragma once
//STD Headers
#include <cstdint>
#include <memory>

//Library Headers

//Void Engine Headers
#include "core/rendering/BufferLayout.h"

namespace core {

	/**
	 * Pure virtual class to abstract rendering API
	 */
	class VertexBuffer {
	public:
		/**
		 * Factory method to create a vertex buffer appropriate for the current 
		 * rendering pipeline.
		 */
		static std::shared_ptr<VertexBuffer> Create(const float* vertices, uint32_t size);

		/**
		 * Destructor
		 */
		virtual ~VertexBuffer() {};
		
		/**
		 * Allows calling code to specify vertex layout data in buffer
		 */
		virtual void SetLayout(const BufferLayout& layout) = 0;
		
		/**
		 * BufferLayout accessor
		 */
		virtual const BufferLayout& GetLayout() const = 0;
		
		/**
		 * Binds VertexBuffer in rendering pipeline
		 */
		virtual void Bind() const = 0;

		/**
		 * Unbinds VertexBuffer in rendering pipeline
		 */
		virtual void Unbind() const = 0;
	};

}