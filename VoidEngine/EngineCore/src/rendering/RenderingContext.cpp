//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/RenderingContext.h"

namespace core {

	RenderingContext::RenderingContext() 
		: CurrentViewport(0,0,0,0), ClearColor(0.24f, 0.28f, 0.28f, 1.0f) {
	
	}

	void RenderingContext::SetViewport(int x, int y, int width, int height) {
		this->SetViewport(Viewport(x, y, width, height));
	}

	RenderingContext::Viewport RenderingContext::GetViewport() const {
		return CurrentViewport;
	}

}
