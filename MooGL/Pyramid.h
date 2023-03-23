#pragma once

#ifndef _Pyramid
 
#define _Pyramid

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

	#ifndef _Texture2D
	#include "Texture2D.h"
	#endif

	#ifndef _hStructs
	#include "Structures.h"
	#endif

	class Pyramid : public SceneObject
	{
	private:
		GLfloat _rotation = 0;
		Vector3 _position;
		Texture2D* _texture;

	public:

		Pyramid(Mesh* mesh, Texture2D* text, float x, float y, float z);
		~Pyramid();

		void Draw();
		void Update();
	};

#endif // !_Cube