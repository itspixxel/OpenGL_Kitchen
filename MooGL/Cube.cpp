#pragma once
#include "Cube.h"

// Indexed Cube Data
Vertex Cube::indexedVertices[] = { 1, 1, 1,  -1, 1, 1,  // v0,v1,
				-1,-1, 1,   1,-1, 1,   // v2,v3
				1,-1,-1,   1, 1,-1,    // v4,v5
				-1, 1,-1,   -1,-1,-1 }; // v6,v7

Color Cube::indexedColors[] = { 1, 1, 1,   1, 1, 0,   // v0,v1,
				1, 0, 0,   1, 0, 1,   // v2,v3
				0, 0, 1,   0, 1, 1,   // v4,v5
				0, 1, 0,   0, 0, 0 }; //v6,v7

GLushort Cube::indices[] = { 0, 1, 2,  2, 3, 0,      // front
				0, 3, 4,  4, 5, 0,      // right
				0, 5, 6,  6, 1, 0,      // top
				1, 6, 7,  7, 2, 1,      // left
				7, 4, 3,  3, 2, 7,      // bottom
				4, 7, 6,  6, 5, 4 };    // back

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
	glPushMatrix();

		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation, 1.0f, 0.0f, 0.0f);
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

void Cube::Update()
{
	rotation += 0.1f;
}