//STD Headers

//Library Headers
#include "glad/glad.h"

//Void Engine Headers
#include "Mesh.h"

namespace core {
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<TextureHandle> textures)
		: Vertices(std::move(vertices)), Indices(std::move(indices)), Textures(std::move(textures)) {
		VAO = VBO = EBO = 0;
	}

	void Mesh::Draw(ShaderProgram shader) const {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;


		for (unsigned int i = 0; i < Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = Textures[i].Type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

			shader.SetUniform(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, Textures[i].TextureID);
		}
		glActiveTexture(GL_TEXTURE0);

		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Mesh::Initialize() {
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