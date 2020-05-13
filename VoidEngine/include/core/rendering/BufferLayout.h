#pragma once
//STD Headers
#include <cstdint>
#include <string>
#include <vector>

//Library Headers

//Void Engine Headers
#include "utils/EngineUtilities.h"

namespace core {
	
	/**
	 * The types the buffer element will be bound to in the target shader
	 */
	enum class ShaderDataType : uint8_t {
		NONE,
		FLOAT,
		FLOAT_2,
		FLOAT_3,
		FLOAT_4,
		INT,
		INT_2,
		INT_3,
		INT_4,
		MAT_3,
		MAT_4,
		BOOL
	};

	static uint32_t SizeOfShaderType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::FLOAT:	  return 4;
			case ShaderDataType::FLOAT_2: return 4 * 2;
			case ShaderDataType::FLOAT_3: return 4 * 3;
			case ShaderDataType::FLOAT_4: return 4 * 4;
			case ShaderDataType::INT:	  return 4;
			case ShaderDataType::INT_2:   return 4 * 2;
			case ShaderDataType::INT_3:	  return 4 * 3;
			case ShaderDataType::INT_4:	  return 4 * 4;
			case ShaderDataType::MAT_3:	  return 4 * 3 * 3;
			case ShaderDataType::MAT_4:   return 4 * 4 * 4;
			case ShaderDataType::BOOL:	  return 1;
			case ShaderDataType::NONE:	  return 0;
		}

		VE_ASSERT(false, "Shader Data type not recognized by SizeOfShaderType");
		return 0;
	}

	/**
	 * Object used to store buffer layout data for a specific element of a 
	 * Vertex Buffer
	 */
	struct BufferElement {
		/** Buffer element name*/
		std::string Name;
		uint32_t Offset;
		uint32_t Size;
		ShaderDataType Type;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(SizeOfShaderType(type)), Offset(0), Normalized(normalized) {

		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::FLOAT:    return 1;
				case ShaderDataType::FLOAT_2:  return 2;
				case ShaderDataType::FLOAT_3:  return 3;
				case ShaderDataType::FLOAT_4:  return 4;
				case ShaderDataType::MAT_3:    return 3 * 3;
				case ShaderDataType::MAT_4:    return 4 * 4;
				case ShaderDataType::INT:      return 1;
				case ShaderDataType::INT_2:    return 2;
				case ShaderDataType::INT_3:    return 3;
				case ShaderDataType::INT_4:    return 4;
				case ShaderDataType::BOOL:     return 1;
			}

			VE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};


	class BufferLayout {
	public:
		/**
		 * Constructor
		 * @param elements An braced list of Buffer Elements
		 */
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		/** Accessor for BufferLayout's stride */
		uint32_t GetStride() const;

		/** Accessor for BufferLayout's element count */
		uint32_t GetNumElements() const;

		/** Functions to allow range based iteration of BufferLayouts */
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride();

		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

}