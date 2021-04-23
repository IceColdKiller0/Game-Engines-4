#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel()
{
	vertices = std::vector<glm::vec3>();
	normals = std::vector<glm::vec3>();
	textureCoords = std::vector<glm::vec2>();
	indices = std::vector<unsigned int>();
	normalIndices = std::vector<unsigned int>();
	textureIndices = std::vector<unsigned int>();
	meshVertices = std::vector<Vertex>();
	subMeshes = std::vector<SubMesh>();
	currentMaterial = Material();

	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() const
{
	return boundingBox;
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.position = vertices[indices[i]-1];
		vert.normal = normals[normalIndices[i]-1];
		vert.textureCoordinates = textureCoords[textureIndices[i]-1];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in)
	{
		Debugger::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}

	std::string line;

	boundingBox.minVert = glm::vec3(1000000.0f);
	boundingBox.maxVert = glm::vec3(-1000000.0f);

	while (std::getline(in, line))
	{
		//VERTEX DATA
		if (line.substr(0, 2) == "v ")
		{
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));

			
				//min vertices
				if (x < boundingBox.minVert.x)
					boundingBox.minVert.x = x;
				if (y < boundingBox.minVert.y)
					boundingBox.minVert.y = y;
				if (z < boundingBox.minVert.z)
					boundingBox.minVert.z = z;

				//max vertices
				if (x > boundingBox.maxVert.x)
					boundingBox.maxVert.x = x;
				if (y > boundingBox.maxVert.y)
					boundingBox.maxVert.y = y;
				if (z > boundingBox.maxVert.z)
					boundingBox.maxVert.z = z;
			
		}
		//VERTEX TEXTURE
		else if (line.substr(0, 3) == "vt ")
		{
			std::stringstream vt(line.substr(3));
			float x, y;
			vt >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}
		//VERTEX NORMAL
		else if (line.substr(0, 3) == "vn ")
		{
			std::stringstream vn(line.substr(3));
			float x, y, z;
			vn >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		
		//FACE DATA
		else if (line.substr(0, 2) == "f ")
		{
			std::stringstream f(line.substr(2));

			int count = 0;
			int temp = 0;

			while (f >> temp)
			{
				if (count == 0)
				{
					indices.push_back(temp);
				}
				else if (count == 1)
				{
					textureIndices.push_back(temp);
				}
				else if (count == 2)
				{
					normalIndices.push_back(temp);
				}

				if (f.peek() == '/')
				{
					++count;
					f.ignore(1, '/');
				}
				else if (f.peek() == ' ')
				{
					++count;
					f.ignore(1, ' ');
				}

				if (count > 2)
				{
					count = 0;
				}

			}

		}
			
		//NEW MESH
		else if (line.substr(0, 7) == "usemtl ")
		{
			if (indices.size() > 0)
			{
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}

	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
	
	/*if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(matName_, "Resources/Textures/" + matName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	}*/
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
	/*std::ifstream in(matFilePath_.c_str(), std::ios::in);

	if (!in)
	{
		Debugger::Error("Cannot open MTL file: " + matFilePath_, "LoadOBJModel.cpp", __LINE__);
	}
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			LoadMaterial(line.substr(7));
		}
	}*/
}
