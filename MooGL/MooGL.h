#pragma once
#pragma once
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "GLUTCallbacks.h" //GLUTCallbacks
#include "Structures.h"

#define REFRESHRATE 16

class MooGL
{
	public:
		//constructor definition
		MooGL(int argc, char* argv[]);

		//destructor
		~MooGL(void);

		void Display();

		void Update();

		void Keyboard(unsigned char key, int x, int y);

		void DrawCube();

		void DrawCubeArray();

		void DrawIndexedCube();

	private:
		float rotation;

		Camera* camera;

		static Vertex vertices[];
		static Color colors[];

		static Vertex indexedVertices[];
		static Color indexedColors[];
		static GLushort indices[];

};