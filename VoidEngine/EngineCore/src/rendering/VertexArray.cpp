#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "platform/OpenGL/OpenGLVertexArray.h"

#include "rendering/VertexArray.h"
#include "rendering/Renderer.h"

namespace core {

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetRendererAPI()) {
			case RendererAPI::OPENGL: return new OpenGLVertexArray();
		}

		VE_ASSERT(false, "VertexArray does not support selected RendererAPI");
		return nullptr;
	}

}