#pragma once
#pragma once
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "GLUTCallbacks.h" //GLUTCallbacks

#define REFRESHRATE 16

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

class MooGL
{
public:

	//contructor definition
	MooGL(int argc, char* argv[]);

	//destructor
	~MooGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

private:
	float rotation;

	Camera* camera;
};