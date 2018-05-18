/*

Author: Daniel Fernández
Date:	18705/2018

*/

#include "Mesh.hpp"

using namespace std;

namespace example
{
	Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		//Setup Mesh

		glGenVertexArrays(1, &vao_id);
		glGenBuffers(1, &vbo_ids[COORDINATES_VBO]);
		glGenBuffers(1, &vbo_ids[INDICES_VBO]);

		glBindVertexArray(vao_id);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_VBO]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
			&indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}

	void Mesh::render(/*Shader shader*/)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		//for (unsigned int i = 0; i < textures.size(); i++)
		//{
		//	glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		//									  // retrieve texture number (the N in diffuse_textureN)
		//	string number;
		//	string name = textures[i].type;
		//	if (name == "texture_diffuse")
		//		number = std::to_string(diffuseNr++);
		//	else if (name == "texture_specular")
		//		number = std::to_string(specularNr++);

		//	//shader.setFloat(("material." + name + number).c_str(), i);
		//	glBindTexture(GL_TEXTURE_2D, textures[i].id);
		//}
		//glActiveTexture(GL_TEXTURE0);

		// draw mesh
		glBindVertexArray(vao_id);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}