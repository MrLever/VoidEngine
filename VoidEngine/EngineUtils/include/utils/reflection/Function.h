#pragma once
//STD Headers
#include <functional>
#include <span>

//Library Headers

//Void Engine Headers
#include "utils/Name.h"
#include "utils/reflection/TypeDescriptor.h"

namespace utils {

	struct FunctionDataInterface {
		virtual const TypeDescriptor* GetReturnType() = 0;
		virtual std::span<TypeDescriptor> GetArgTypes() = 0;
		virtual size_t GetArgumentCount() = 0;
	};

	template<class retType, class ...Args>
	struct FunctionData {

		const TypeDescriptor* GetReturnType() override { return m_ReturnType; }
		
		std::span<TypeDescriptor> GetArgTypes() = 0;

		virtual size_t GetArgumentCount() 
	
	private:
		const TypeDescriptor& m_ReturnType;
		std::array<TypeDescriptor, sizeof...(Args)> m_Args;
	};

	struct Function {
		utils::Name m_Name;

	};

}