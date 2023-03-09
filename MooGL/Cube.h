#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"

class Cube
{
private:
	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];

public:
	Cube();
	~Cube();

	void Draw();
	void Update();
};
