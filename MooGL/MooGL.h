#pragma once

#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "GLUTCallbacks.h" //GLUTCallbacks
#include "Structures.h" // Structs
#include "Cube.h" // Cube class

// Refresh rate pre-processor
#define REFRESHRATE 16

class MooGL
{
	public:
		MooGL(int argc, char* argv[]);

		~MooGL(void);

		void Display();
		void Update();
		void Keyboard(unsigned char key, int x, int y);

	private:
		float rotation;

		Camera* camera;
		Cube* cube[6000];
};