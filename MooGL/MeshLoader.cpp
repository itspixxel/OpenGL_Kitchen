#include <iostream>
#include <fstream>
#include <sstream>

#include "MeshLoader.h"

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadUVs(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.numVertices;

		if (mesh.numVertices > 0)
		{
			mesh.indexedVertices = new Vertex[mesh.numVertices];

			for (int i = 0; i < mesh.numVertices; i++)
			{
				inFile >> mesh.indexedVertices[i].x;
				inFile >> mesh.indexedVertices[i].y;
				inFile >> mesh.indexedVertices[i].z;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.numNormals;

		if (mesh.numNormals > 0)
		{
			mesh.indexedNormals = new Vector3[mesh.numNormals];

			for (int i = 0; i < mesh.numNormals; i++)
			{
				inFile >> mesh.indexedNormals[i].x;
				inFile >> mesh.indexedNormals[i].y;
				inFile >> mesh.indexedNormals[i].z;
			}
		}
	}

	void LoadUVs(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.numTexCoords;

		if (mesh.numTexCoords > 0)
		{
			mesh.texCoords = new TexCoord[mesh.numTexCoords];

			for (int i = 0; i < mesh.numTexCoords; i++)
			{
				inFile >> mesh.texCoords[i].u;
				inFile >> mesh.texCoords[i].v;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		//TODO: Load Indices
		inFile >> mesh.numIndices;

		if (mesh.numIndices > 0)
		{
			mesh.indices = new GLushort[mesh.numIndices];

			for (int i = 0; i < mesh.numIndices; i++)
			{
				inFile >> mesh.indices[i];
			}
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		//LOAD DATA USING METHODS ABOVE
		LoadVertices(inFile, *mesh);
		LoadUVs(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		return mesh;
	}

	Mesh* MeshLoader::LoadOBJ(char* path)
	{
		std::ifstream inFile(path);
		std::string line;

		if (!inFile.is_open()) {
			std::cout << "Couldn't open file" << std::endl;
			return nullptr;
		}

		std::vector<GLushort*> vertexIndices, uvIndices, normalIndices;
		std::vector<Vertex*> tempVertices;
		std::vector<Vector3*> tempNormals;
		std::vector<TexCoord*> tempTexCoords;

		//Fill vectors with data, loop through file line by line and process each line
		while (std::getline(inFile, line)) {
			//Create stringstream of current line
			stringstream curLine(line);
			//Current type of line it's on (represented by first characters of line)
			string curDataType;
			curLine >> curDataType;

			//Vertex
			if (curDataType == "v") {
				Vertex* vert = new Vertex();
				curLine >> vert->x >> vert->y >> vert->z;
				tempVertices.push_back(vert);
			}
			//Normal
			else if (curDataType == "vn") {
				Vector3* norm = new Vector3();
				curLine >> norm->x >> norm->y >> norm->z;
				tempNormals.push_back(norm);
			}
			//TexCoord
			else if (curDataType == "vt") {
				TexCoord* uv = new TexCoord();
				curLine >> uv->u >> uv->v;
				tempTexCoords.push_back(uv);
			}
			//Face
			else if (curDataType == "f") {
				unsigned int vertIndex[3], uvIndex[3], normIndex[3];

				//For loop through all 3 'sections' of data on each line
				for (int i = 0; i < 3; i++) {
					std::string data;
					curLine >> data;

					std::stringstream intStream[3];
					int intStreamIndex = 0;

					for (int i = 0; i < data.length(); i++) {
						if (data[i] == '/') {
							intStreamIndex++;
						}
						else {
							intStream[intStreamIndex] << data[i];
						}
					}

					intStream[0] >> vertIndex[i];
					intStream[1] >> uvIndex[i];
					intStream[2] >> normIndex[i];
				}

				vertexIndices.push_back(new GLushort(vertIndex[0]));
				vertexIndices.push_back(new GLushort(vertIndex[1]));
				vertexIndices.push_back(new GLushort(vertIndex[2]));
				uvIndices.push_back(new GLushort(uvIndex[0]));
				uvIndices.push_back(new GLushort(uvIndex[1]));
				uvIndices.push_back(new GLushort(uvIndex[2]));
				normalIndices.push_back(new GLushort(normIndex[0]));
				normalIndices.push_back(new GLushort(normIndex[1]));
				normalIndices.push_back(new GLushort(normIndex[2]));
			}
		}
	}
}