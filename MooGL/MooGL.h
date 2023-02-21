#pragma once
#pragma once
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "GLUTCallbacks.h" //GLUTCallbacks

#define REFRESHRATE 16

class MooGL
{
public:

	//contructor definition
	MooGL(int argc, char* argv[]);

	//destructor
	~MooGL(void);

	void Display();

	void Update();

private:
	float rotation;
};