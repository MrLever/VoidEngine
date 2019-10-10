#pragma once
//STD Headers
#include <vector>

//Library Headers

//Void Engine Headers
#include "Vertex.h"
#include "TextureHandle.h"
#include "ShaderProgram.h"

namespace core {

	class Mesh {
	public:
		/**
		 * Constructor 
		 */
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<TextureHandle> textures);

		/**
		 * Destructor 
		 */
		~Mesh() = default;

		/**
		 * Function to draw mesh
		 */
		void Draw(ShaderProgram* shader) const;

		/**
		 * Function to set up OpenGL draw data
		 */
		void Initialize();

	private:
		/** The mesh's vertex data */
		std::vector<Vertex> Vertices;

		/** The mesh's indices used to draw faces from vertex data */
		std::vector<unsigned> Indices;

		/** Textures used to draw mesh */
		std::vector<TextureHandle> Textures;

		/** Vertex Array Object used to render this mesh */
		unsigned VAO;

		/** Vertex Buffer Obect used to store this mesh's vertices */
		unsigned VBO;
		
		/** Element Buffer Object used to draw faces from VBO */
		unsigned EBO;
	};

}
