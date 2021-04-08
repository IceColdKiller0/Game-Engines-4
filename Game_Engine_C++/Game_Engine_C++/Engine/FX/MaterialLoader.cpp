#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}

void MaterialLoader::LoadMaterial(std::string filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);

	if (!in)
	{
		Debugger::Error("Cannot open MTL file: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}

	Material m = Material();
	std::string matName = "";
	std::string line;

	while (std::getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			if (m.diffuseMap != 0)
			{
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}

		else if (line.substr(0, 4) == "\tNs ")
		{
			//matName = line.substr(3);
			std::stringstream Ns(line.substr(3));
			float x;
			Ns >> x;
			m.shininess = x;
			//m.name = matName;	
		}

		else if (line.substr(0, 3) == "\td ")
		{
			//matName = line.substr(2);
			std::stringstream d(line.substr(2));
			float x;
			d >> x;
			m.transparency = x;
			//m.name = matName;
		}

		else if (line.substr(0, 4) == "\tKa ")
		{
			//matName = line.substr(3);
			std::stringstream Ka(line.substr(3));
			float x, y, z;
			Ka >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
			//m.name = matName;
			
		}

		else if (line.substr(0, 4) == "\tKd ")
		{
			//matName = line.substr(3);
			std::stringstream Kd(line.substr(3));
			float x, y, z;
			Kd >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
			//m.name = matName;

		}

		else if (line.substr(0, 4) == "\tKs ")
		{
			//matName = line.substr(3);
			std::stringstream Ks(line.substr(3));
			float x, y, z;
			Ks >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
			//m.name = matName;
		}

	}

	if (m.diffuseMap != 0)
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);

	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(fileName_, "Resources/Textures/" + fileName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}

	return currentTexture;
}
