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
		virtual const TypeDescriptor& GetReturnType() = 0;
		virtual std::span<TypeDescriptor> GetArgTypes() = 0;
		virtual size_t GetArgumentCount() = 0;

		/*template<class ReturnType, class ...Args>
		ReturnType Invoke(Args&&... args) {
		
		}*/
	};

	template<class ReturnType, class ...Args>
	struct FunctionData : public FunctionDataInterface {
		
		FunctionData() : m_ReturnTypeDescriptor(reflection::GetType<ReturnType>()) {
			
		}

		const TypeDescriptor& GetReturnType() override { return m_ReturnTypeDescriptor; }
		
		std::span<TypeDescriptor> GetArgTypes() { return m_Args; };

		size_t GetArgumentCount() override { return sizeof...(Args); }
	
	private:
		const TypeDescriptor& m_ReturnTypeDescriptor;
		std::array<TypeDescriptor, sizeof...(Args)> m_Args;

		std::function<ReturnType(Args...)> m_Function;
	};

	struct Function {

		const utils::Name m_Name;

		//Function(const utils::Name& name/*, FunctionDataInterface& data*/) : m_Name(name) /*, m_Data(data)*/ {
		//
		//}

		utils::Name GetName() { return m_Name; }
	private:
		
		//VoidRefl Supplied invoke helper??
		//FunctionDataInterface& m_Data;
	};

}