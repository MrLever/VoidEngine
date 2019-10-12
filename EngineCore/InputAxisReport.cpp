//STD Headers

//Library Headers

//Void Engine Headers
#include "InputAxisReport.h"
#include "InputAxis.h"

namespace core {
	InputAxisReport::InputAxisReport(const utils::Name& name, float value) 
		: AxisName(name), Value(value) {
	
	}
	
	InputAxisReport::InputAxisReport(const std::string& name, float value)
		: InputAxisReport(utils::Name(name), value) {

	}

}