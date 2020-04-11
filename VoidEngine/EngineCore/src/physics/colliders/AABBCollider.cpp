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
			minExtent.X, minExtent.Y, minExtent.Z, //min
			maxExtent.X, minExtent.Y, minExtent.Z,
			maxExtent.X, maxExtent.Y, minExtent.Z,
			minExtent.X, maxExtent.Y, minExtent.Z, //4
			minExtent.X, minExtent.Y, maxExtent.Z,
			maxExtent.X, minExtent.Y, maxExtent.Z,
			maxExtent.X, maxExtent.Y, maxExtent.Z, //max
			minExtent.X, maxExtent.Y, maxExtent.Z, //8
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
		
		vertexArray = VertexArray::Create();

		vertexArray->LinkVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);

	}

	void AABBCollider::Initialize() {
		minExtent.X = configData["min"][0].get<float>();
		minExtent.Y = configData["min"][1].get<float>();
		minExtent.Z = configData["min"][2].get<float>();

		maxExtent.X = configData["max"][0].get<float>();
		maxExtent.Y = configData["max"][1].get<float>();
		maxExtent.Z = configData["max"][2].get<float>();
	}

	void AABBCollider::Draw(std::shared_ptr<ShaderProgram> shader, const glm::mat4& transform) {
		shader->SetUniform("material.base_diffuse", {1, 0, 1, 1});
		
		// draw mesh
		//Renderer::Submit(shader, vertexArray, transform, DrawMode::LINE);
	}

	math::Vector3 AABBCollider::GetMin() const {
		return minExtent;
	}

	math::Vector3 AABBCollider::GetMax() const {
		return maxExtent;
	}

}
