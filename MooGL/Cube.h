#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"

class Cube
{
	public:
		Cube(float x, float y, float z);
		~Cube();

		void Draw();
		void Update();

	private:
		static Vertex indexedVertices[];
		static Color indexedColors[];
		static GLushort indices[];

		GLfloat rotation = 0.0f;
		Vector3 position;
};