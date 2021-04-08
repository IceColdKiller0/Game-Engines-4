#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_)
{
	VAO = 0;
	VBO = 0;
	//vertexList = std::vector<Vertex>(); //sets vertex list to equal an empty vector
	//textureID = 0;
	shaderProgram = 0;
	modelLoc = 0;
	viewLoc = 0;
	projectionLoc = 0;
	//textureLoc = 0;
	diffuseMapLoc = 0;
	ambientLoc = 0;
	diffuseLoc = 0;
	specularLoc = 0;
	shininessLoc = 0;
	transparencyLoc = 0;
	diffuseLoc = 0;
	viewPos = 0;
	lightPos = 0;
	ambValue = 0;
	diffValue = 0;
	specValue = 0;
	lightColour = 0;
	//vertexList = vertexList_; //sets the class vertex list vector equal to the vertex list passed in as a param 
	//textureID = textureID_;
	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO); //Deletes VAO - opengl has its own way of deleting
	glDeleteBuffers(1, &VBO); //Deletes VBO

	//vertexList.clear();
	
	if (subMesh.vertexList.size() > 0)
	{
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0)
	{
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_)
{
	glUniform1i(diffuseMapLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniform3fv(viewPos, 1, glm::value_ptr(camera_->GetPosition()));
	glUniform3fv(lightPos, 1, glm::value_ptr(camera_->GetLightSource()[0]->GetPosition()));
	glUniform1f(ambValue, camera_->GetLightSource()[0]->GetAmbValue());
	glUniform1f(diffValue, camera_->GetLightSource()[0]->GetDiffValue());
	glUniform1f(specValue, camera_->GetLightSource()[0]->GetSpecValue());
	glUniform3fv(lightColour, 1, glm::value_ptr(camera_->GetLightSource()[0]->GetLightColour()));

	glUniform1f(shininessLoc, subMesh.material.shininess);
	glUniform1f(transparencyLoc, subMesh.material.transparency);
	glUniform3f(ambientLoc, subMesh.material.ambient.x, subMesh.material.ambient.y, subMesh.material.ambient.z);
	glUniform3f(diffuseLoc, subMesh.material.diffuse.x, subMesh.material.diffuse.y, subMesh.material.diffuse.z);
	glUniform3f(specularLoc, subMesh.material.specular.x, subMesh.material.specular.y, subMesh.material.specular.z);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	

	glBindVertexArray(VAO); //BIND VAO

	glEnable(GL_DEPTH_TEST); // when objects are rendered their z values will be taken into consideration

	for (int i = 0; i < instances_.size(); i++)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));

		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size()); //draw
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO); //Generate VAO
	glGenBuffers(1, &VBO); //Generate VBO
	glBindVertexArray(VAO); //Bind to the GPU as an array
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind to the GPU 
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

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
	/*glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));*/

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	//textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	viewPos = glGetUniformLocation(shaderProgram, "viewPos");
	lightPos = glGetUniformLocation(shaderProgram, "light.lightPos");
	ambValue = glGetUniformLocation(shaderProgram, "light.ambValue");
	diffValue = glGetUniformLocation(shaderProgram, "light.diffValue");
	specValue = glGetUniformLocation(shaderProgram, "light.specValue");
	lightColour = glGetUniformLocation(shaderProgram, "light.lightColour");

	diffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	shininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	ambientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	diffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	specularLoc = glGetUniformLocation(shaderProgram, "material.specular");
}
