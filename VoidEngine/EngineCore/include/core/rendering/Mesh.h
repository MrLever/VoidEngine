#pragma once
//STD Headers
#include <vector>
#include <memory>

//Library Headers
#include "math/Vector.h"

//Void Engine Headers
#include "core/rendering/Vertex.h"
#include "core/rendering/IndexBuffer.h"
#include "core/rendering/VertexArray.h"
#include "core/rendering/VertexBuffer.h"
#include "core/rendering/Texture.h"
#include "core/rendering/ShaderProgram.h"

namespace core {

	class Mesh {
	public:
		/**
		 * Constructor 
		 */
		Mesh(
			const std::vector<float>& vertices, 
			const std::vector<uint32_t>& indices, 
			const std::vector<TexturePtr>& textures
		);

		/**
		 * Destructor 
		 */
		~Mesh() = default;

		/**
		 * Function to draw mesh
		 * @param shader The shader to use when drawing this mesh
		 */
		void Draw(ShaderProgram* shader) const;

		/**
		 * Function to set up OpenGL draw data
		 */
		void Initialize();

		/**
		 * Function to set the material's diffuse color (in the case of a simple, untextured material)
		 * @param color The material's color
		 */
		void SetMaterialDiffuse(math::Color color);

	private:
		/**
		 * Helper function for Initialize to set up OpenGL buffer data
		 */
		void InitializeGeometryData();
		
		/** The material's untextured color */
		math::Color MaterialColor;

		/** Textures used to draw mesh */
		std::vector<std::shared_ptr<Texture>> Textures;

		/** Vertex Array Object used to render this mesh */
		std::shared_ptr<VertexArray> m_VertexArray;

		/** Vertex Buffer Obect used to store this mesh's vertices */
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		
		/** Element Buffer Object used to draw faces from VBO */
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}

