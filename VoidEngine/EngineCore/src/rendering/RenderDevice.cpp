//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/EngineUtilities.h"
#include "rendering/RenderDevice.h"

#include "platform/OpenGL/OpenGLRenderDevice.h"

namespace core {

	RenderDevice::API RenderDevice::s_API = API::OPENGL;

	std::unique_ptr<RenderDevice> RenderDevice::Create() {
		switch (s_API) {
			case core::RenderDevice::API::OPENGL: return std::make_unique<OpenGLRenderDevice>();
		}

		VE_ASSERT(false, "RenderAPI not supported. Device creation failed");

		return nullptr;
	}

	void RenderDevice::SetViewport(int x, int y, int width, int height) {
		this->SetViewport(Viewport(x, y, width, height));
	}

	Viewport RenderDevice::GetViewport() const {
		return CurrentViewport;
	}

	RenderDevice::API RenderDevice::GetRendererAPI() {
		return s_API;
	}

}
