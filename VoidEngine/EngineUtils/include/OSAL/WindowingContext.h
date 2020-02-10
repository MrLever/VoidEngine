#pragma once
//STD Headers

//Library Headers

//Void Engine Headers

namespace OSAL {  

	/**
	 * @class WindowingContext
	 * @brief Abstraction interface used to swap windowing system
	 *        without interupting other engine systems. The windowing 
	 *        context is responsible for handling OS specific IO issues
	 *        like window creation, buffer swapping, and input handling
	 */
	class WindowingContext {
	public:
		WindowingContext();
	};
}