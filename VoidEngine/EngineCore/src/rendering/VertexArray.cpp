#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "platform/OpenGL/OpenGLVertexArray.h"

#include "rendering/VertexArray.h"
#include "rendering/Renderer.h"

namespace core {

	std::shared_ptr<VertexArray> VertexArray::Create() {
		switch (Renderer::GetRendererAPI()) {
			case RenderDevice::API::OPENGL: return std::make_shared<OpenGLVertexArray>();
		}

		VE_ASSERT(false, "VertexArray does not support selected RendererAPI");
		return nullptr;
	}

}