#pragma once
#include "GLUTCallbacks.h" //GLUTCallbacks
#include "Cube.h"
#include "Pyramid.h"
#include "MeshLoader.h" // MeshLoader class

// Refresh rate pre-processor
#define REFRESHRATE 16


class MooGL
{
	public:
		MooGL(int argc, char* argv[]);

		void InitObjects();
		void InitGL(int argc, char* argv[]);

		~MooGL(void);

		void Display();
		void Update();
		void Keyboard(unsigned char key, int x, int y);

	private:
		float rotation;

		Camera* camera;
		SceneObject* objects[200];
};