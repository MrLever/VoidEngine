//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/RenderingContext.h"

namespace core {

	RenderingContext::RenderingContext() : CurrentViewport(0,0,0,0) {
	
	}

	void RenderingContext::SetViewport(int x, int y, int width, int height) {
		this->SetViewport(Viewport(x, y, width, height));
	}

	RenderingContext::Viewport RenderingContext::GetViewport(int x, int y, int width, int height) {
		return CurrentViewport;
	}

}
