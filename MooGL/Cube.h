#pragma once

#ifndef _Cube
 
#define _Cube

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "GL\freeglut.h"

#ifndef _SceneObject
#include "SceneObject.h"
#endif

#ifndef _hStructs
#include "Structures.h"
#endif

#ifndef _Texture2D
#include "Texture2D.h"
#endif

class Cube : public SceneObject
{
	private:
		Material* _material;
		GLfloat _rotation = 0;
		Vector3 _position;
		bool _isSpinning;

	public:
		Cube(Mesh* mesh, bool isSpinning, Material* material, Texture2D* _texture, float x, float y, float z);
		~Cube();

		void Draw();
		void Update();
};

#endif // !_Cube