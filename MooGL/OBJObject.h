#pragma once

#ifndef _OBJObject
#define _OBJObject

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

class OBJObject : public SceneObject
{
	private:
		Material* _material;
		GLfloat _rotation = 0;
		Vector3 _position;

	public:

		OBJObject(OBJMesh* objMesh, Texture2D* _texture, float x, float y, float z);
		~OBJObject();

		void Update();
		void Draw();
};

#endif //!_OBJObject