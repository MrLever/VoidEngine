//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/BufferLayout.h"

namespace core {
	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) 
		:m_Elements(elements) {
		CalculateOffsetsAndStride();
	}

	uint32_t BufferLayout::GetStride() const {
		return m_Stride;
	}

	void BufferLayout::CalculateOffsetsAndStride() {
		uint32_t offset = 0;
		m_Stride = 0;

		for (auto& element : m_Elements) {
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}
}