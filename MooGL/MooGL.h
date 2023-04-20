#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL\freeglut.h"
#include "GLUTCallbacks.h"

#ifndef _Texture2D
#include "Texture2D.h"
#endif

#ifndef _Cube
#include "Cube.h"
#endif

#ifndef _OBJObject
#include "OBJObject.h"
#endif

#ifndef _MeshLoader
#include "MeshLoader.h"
#endif

#ifndef _OBJLoader
#include "OBJLoader.h"
#endif

#include <vector>
#include <map>

#define REFRESHRATE 16

class MooGL
{
	public:

		MooGL(int argc, char* argv[]);

		void Display();
		void Update();

		void Keyboard(unsigned char key, int x, int y);

		~MooGL(void);

		void InitObjects();
		void InitLighting();
		void InitGL(int argc, char* argv[]);

	private:
		Vector4* _lightPosition;
		Lighting* _lightData;
		float rotation;
		Camera* camera;
		std::map<std::string, OBJObject*> objects;
		std::vector<SceneObject*> primitives;

		int objectFocusID = 0;
};
