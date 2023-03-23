#include <iostream>
#include <fstream>

#include "MeshLoader.h"

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColors(ifstream& inFile, Mesh& mesh);
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

	void LoadColors(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.numColors;

		if (mesh.numColors > 0)
		{
			mesh.indexedColors = new Color[mesh.numColors];

			for (int i = 0; i < mesh.numColors; i++)
			{
				inFile >> mesh.indexedColors[i].r;
				inFile >> mesh.indexedColors[i].g;
				inFile >> mesh.indexedColors[i].b;
			}
		}
	}

	void LoadUVs(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.numTexCoords;

		if (mesh.numTexCoords > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.numTexCoords];

			for (int i = 0; i < mesh.numTexCoords; i++)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
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
		LoadColors(inFile, *mesh);
		LoadUVs(inFile, *mesh);
		LoadIndices(inFile, *mesh);


		return mesh;
	}
}