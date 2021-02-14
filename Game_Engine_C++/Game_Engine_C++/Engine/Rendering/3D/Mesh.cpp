#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertexList_)
{
	VAO = 0;
	VBO = 0;
	vertexList = std::vector<Vertex>(); //sets vertex list to equal an empty vector
	vertexList = vertexList_; //sets the class vertex list vector equal to the vertex list passed in as a param 
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO); //Deletes VAO - opengl has its own way of deleting
	glDeleteBuffers(1, &VBO); //Deletes VBO

	vertexList.clear();
}

void Mesh::Render()
{
	glBindVertexArray(VAO); //BIND VAO

	glDrawArrays(GL_TRIANGLES, 0, vertexList.size()); //draw

	glBindVertexArray(0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO); //Generate VAO
	glGenBuffers(1, &VBO); //Generate VBO
	glBindVertexArray(VAO); //Bind to the GPU as an array
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind to the GPU 
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//TEX COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	//COLOUR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
