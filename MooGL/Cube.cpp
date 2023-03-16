#pragma once
#include "Cube.h"
#include <fstream>
#include <iostream>

// Indexed Cube Data
Vertex* Cube::indexedVertices = nullptr;
Color* Cube::indexedColors = nullptr;
GLushort* Cube::indices = nullptr;

int Cube::numVertices = 0;
int Cube::numColors = 0;
int Cube::numIndices = 0;

Cube::Cube(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

Cube::~Cube()
{

}

void Cube::Draw()
{
	if (indexedVertices != nullptr && indexedColors != nullptr && indices != nullptr)
	{
		glPushMatrix();

		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation, 1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLES);

		for (int i = 0; i < 36; i++)
		{
			Vertex v = indexedVertices[indices[i]];
			Color c = indexedColors[indices[i]];
			glColor3f(c.r, c.g, c.b);
			glVertex3f(v.x, v.y, v.z);
		}

		glEnd();

		glPopMatrix();
	}
}

void Cube::Update()
{
	rotation += 5.0f;
}

bool Cube::Load(char* path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		std::cerr << "Can't open text file " << path << std::endl;
		return false;
	}

	inFile >> numVertices;
	indexedVertices = new Vertex[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		inFile >> indexedVertices[i].x >> indexedVertices[i].y >> indexedVertices[i].z;
	}

	inFile >> numColors;
	indexedColors = new Color[numColors];
	for (int i = 0; i < numColors; i++)
	{
		inFile >> indexedColors[i].r >> indexedColors[i].g >> indexedColors[i].b;
	}

	inFile >> numIndices;
	indices = new GLushort[numIndices];
	for (int i = 0; i < numIndices; i++)
	{
		inFile >> indices[i];
	}

	inFile.close();

	return true;
}
