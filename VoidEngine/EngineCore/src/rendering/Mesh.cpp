//STD Headers

//Library Headers
#include "glad/glad.h"

//Void Engine Headers
#include "rendering/Mesh.h"

namespace core {
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<TexturePtr> textures)
		: MaterialColor(192.0f/255, 190.0f/255, 191.0f/255), 
		  Vertices(std::move(vertices)), 
		  Indices(std::move(indices)), 
		  Textures(std::move(textures)) {
		
		VAO = VBO = EBO = 0;
	}

	void Mesh::Draw(ShaderProgram* shader) const {
		unsigned diffuseNr = 1;
		unsigned specularNr = 1;
		if (shader == nullptr) {
			return;
		}

		if (Textures.size() > 0) {
			for (unsigned int i = 0; i < Textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
				// retrieve texture number (the N in diffuse_textureN)
				std::string number;
				auto type = Textures[i]->GetType();
				std::string typeString;

				if (type == TextureType::DIFFUSE) {
					typeString = "texture_diffuse";
					number = std::to_string(diffuseNr++);
				}
				else if (type == TextureType::SPECULAR) {
					typeString = "texture_specular";
					number = std::to_string(specularNr++);
				}

				shader->SetUniform(("material." + typeString + number).c_str(), (int)i);
				glBindTexture(GL_TEXTURE_2D, Textures[i]->GetTextureID());
			}
			glActiveTexture(GL_TEXTURE0);
		}
		else {
			//Unbinds any texture from previous draw calls
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		
		//A diffuseNr of one after the loop above implies there were no diffuse textures
		if (diffuseNr == 1) {
			//Therefore we should set the shader's default diffuse color
			shader->SetUniform("material.base_diffuse", MaterialColor);
		}

		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, (GLuint)Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Mesh::Initialize() {
		InitializeGeometryData();

		for (auto& texture : Textures) {
			texture->Initialize();
		}
	}

	void Mesh::SetMaterialDiffuse(math::Color color) {
		MaterialColor = color;
	}

	void Mesh::InitializeGeometryData() {
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