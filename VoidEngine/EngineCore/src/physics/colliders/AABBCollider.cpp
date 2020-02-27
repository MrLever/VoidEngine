//STD Headers

//Library Headers

//Void Engine Headers
#include "physics/colliders/AABBCollider.h"
#include "physics/colliders/SphereCollider.h"

#include "rendering/Renderer.h"
#include "rendering/VertexBuffer.h"
#include "rendering/IndexBuffer.h"

namespace core {
	TYPE_INFO_IMPL(AABBCollider)

	ENABLE_FACTORY(AABBCollider, Collider)

	AABBCollider::AABBCollider() {
		std::vector<float> verts = {
			m_MinExtent.X, m_MinExtent.Y, m_MinExtent.Z, //min
			m_MaxExtent.X, m_MinExtent.Y, m_MinExtent.Z,
			m_MaxExtent.X, m_MaxExtent.Y, m_MinExtent.Z,
			m_MinExtent.X, m_MaxExtent.Y, m_MinExtent.Z, //4
			m_MinExtent.X, m_MinExtent.Y, m_MaxExtent.Z,
			m_MaxExtent.X, m_MinExtent.Y, m_MaxExtent.Z,
			m_MaxExtent.X, m_MaxExtent.Y, m_MaxExtent.Z, //max
			m_MinExtent.X, m_MaxExtent.Y, m_MaxExtent.Z, //8
		};

		std::vector<uint32_t> indices = {
			0, 1, 3, 3, 1, 2,
			1, 5, 2, 2, 5, 6,
			5, 4, 6, 6, 4, 7,
			4, 0, 7, 7, 0, 3,
			3, 2, 7, 7, 2, 6,
			4, 5, 0, 0, 5, 1
		};

		BufferLayout meshLayout = {
			{ShaderDataType::FLOAT_3, "a_Position"},
		};

		auto vertexBuffer = VertexBuffer::Create(verts.data(), (uint32_t)verts.size());
		auto indexBuffer = IndexBuffer::Create(indices.data(), (uint32_t)indices.size());

		vertexBuffer->SetLayout(meshLayout);
		
		m_VertexArray = VertexArray::Create();

		m_VertexArray->LinkVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

	}

	void AABBCollider::Initialize() {
		m_MinExtent.X = ConfigData["min"][0].get<float>();
		m_MinExtent.Y = ConfigData["min"][1].get<float>();
		m_MinExtent.Z = ConfigData["min"][2].get<float>();

		m_MaxExtent.X = ConfigData["max"][0].get<float>();
		m_MaxExtent.Y = ConfigData["max"][1].get<float>();
		m_MaxExtent.Z = ConfigData["max"][2].get<float>();
	}

	void AABBCollider::Draw(std::shared_ptr<ShaderProgram> shader, const glm::mat4& transform) {
		shader->SetUniform("material.base_diffuse", {1, 0, 1, 1});
		
		// draw mesh
		Renderer::Submit(shader, m_VertexArray, transform, DrawMode::LINE);
	}

	math::Vector3 AABBCollider::GetMin() const {
		return m_MinExtent;
	}

	math::Vector3 AABBCollider::GetMax() const {
		return m_MaxExtent;
	}

}
