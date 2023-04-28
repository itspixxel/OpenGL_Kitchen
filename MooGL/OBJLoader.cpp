#include "OBJLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace OBJLoader
{
	OBJMesh* OBJLoader::LoadOBJ(char* path)
	{
		std::fstream inFile;

		std::string line; // represents current line
		std::string prefix; // represents prefix of line

		stringstream ss;

		OBJMesh* mesh = new OBJMesh;

		inFile.open(path);

		// check if in file opened correctly
		if (!inFile.good())
		{
			std::cerr << "Can't open mesh file" << path << std::endl;
			return nullptr;
		}

		// loop though obj file
		while (std::getline(inFile, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;


			if (prefix == "v") // assign vertices
			{
				Vertex tempVertex;
				ss >> tempVertex.x >> tempVertex.y >> tempVertex.z;
				mesh->vertices.push_back(tempVertex);
			}
			else if (prefix == "vt") // assign UVs
			{
				TexCoord tempTexCoord;
				ss >> tempTexCoord.u >> tempTexCoord.v;
				mesh->texCoords.push_back(tempTexCoord);
			}
			else if (prefix == "vn") // assign normals
			{
				Vector3 tempNormal;
				ss >> tempNormal.x >> tempNormal.y >> tempNormal.z;
				mesh->normals.push_back(tempNormal);
			}
			else if (prefix == "f") // assign indices
			{
				Face tempFace;
				int tempInt = 0;
				int counter = 0;
				while (ss >> tempInt)
				{
					if (counter == 0)
						tempFace.vertexIndex = tempInt;
					else if (counter == 1)
						tempFace.texCoordIndex = tempInt;
					else if (counter == 2)
						tempFace.normalIndex = tempInt;

					if (ss.peek() == '/')
					{
						counter++;
						ss.ignore(1, '/');
					}
					else if (ss.peek() == ' ')
					{
						counter++;
						ss.ignore(1, ' ');
					}

					if (counter > 2)
					{
						counter = 0;
						mesh->indices.push_back(tempFace);
					}
				}
				mesh->indices.push_back(tempFace);
			}
		}

		inFile.close();
		return mesh;
	}
}