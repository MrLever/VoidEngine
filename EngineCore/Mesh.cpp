//STD Headers

//Library Headers
#include "glad/glad.h"

//Void Engine Headers
#include "Mesh.h"

namespace core {
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures)
		: Vertices(std::move(vertices)), Indices(std::move(indices)), Textures(std::move(textures)) {
		VAO = VBO = EBO = 0;
	}

	void Mesh::Draw() {

	}

	void Mesh::Intialize() {
		//Generate buffers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		//Bind VAO
		glBindVertexArray(VAO);

		//Fill Vertex Buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_DYNAMIC_DRAW);

		//Fill Element Buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned), &Indices[0], GL_DYNAMIC_DRAW);

		//Set up VAO attributes
		//Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		//Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		//UV Coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

		glBindVertexArray(0);
	}
}