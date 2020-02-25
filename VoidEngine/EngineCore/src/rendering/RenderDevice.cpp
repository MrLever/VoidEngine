//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/RenderDevice.h"

namespace core {

	RenderDevice::API RenderDevice::s_API = API::OPENGL;

	RenderDevice::RenderDevice() 
		: CurrentViewport(0,0,0,0), ClearColor(0.24f, 0.28f, 0.28f, 1.0f) {
	
	}

	void RenderDevice::SetViewport(int x, int y, int width, int height) {
		this->SetViewport(Viewport(x, y, width, height));
	}

	RenderDevice::Viewport RenderDevice::GetViewport() const {
		return CurrentViewport;
	}

	RenderDevice::API RenderDevice::GetRendererAPI() {
		return s_API;
	}

}
