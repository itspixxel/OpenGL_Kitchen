#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"

class Cube
{
	public:
		Cube(Mesh* mesh, float x, float y, float z);
		~Cube();

		void Draw();
		void Update();

	private:
		Mesh* m_mesh;

		static int numVertices, numColors, numIndices;

		GLfloat rotation = 0.0f;
		Vector3 position;
};