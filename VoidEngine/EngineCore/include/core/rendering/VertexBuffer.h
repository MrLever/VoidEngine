#pragma once
//STD Headers
#include <cstdint>

//Library Headers

//Void Engine Headers

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
		static VertexBuffer* Create(float* vertices, uint32_t size);

		/**
		 * Destructor
		 */
		virtual ~VertexBuffer() {};
		
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