//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/RenderCommand.h"

namespace core {
	std::unique_ptr<RenderDevice> RenderCommand::s_RenderDevice = RenderDevice::Create();
	
	void RenderCommand::Initialize() {
		s_RenderDevice->Initialize();
	}

	void RenderCommand::SetViewport(Viewport viewport) {
		s_RenderDevice->SetViewport(viewport);
	}

	void RenderCommand::SetClearColor(math::Vector4 color) {
		s_RenderDevice->SetClearColor(color);
	}

	void RenderCommand::Clear() {
		s_RenderDevice->Clear();
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vao) {
		s_RenderDevice->DrawIndexed(vao);
	}
}