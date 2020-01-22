#pragma once
//STD Headers
#include <vector>

//Library Headers
#include "EngineMath/Vector.h"

//Void Engine Headers
#include "Vertex.h"
#include "Texture.h"
#include "ShaderProgram.h"

namespace core {

	class Mesh {
	public:
		/**
		 * Constructor 
		 */
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<TexturePtr> textures);

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

		/** The mesh's vertex data */
		std::vector<Vertex> Vertices;

		/** The mesh's indices used to draw faces from vertex data */
		std::vector<unsigned> Indices;

		/** Textures used to draw mesh */
		std::vector<std::shared_ptr<Texture>> Textures;

		/** Vertex Array Object used to render this mesh */
		unsigned VAO;

		/** Vertex Buffer Obect used to store this mesh's vertices */
		unsigned VBO;
		
		/** Element Buffer Object used to draw faces from VBO */
		unsigned EBO;
	};

}

