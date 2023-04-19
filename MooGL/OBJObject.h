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

		Vector3 GetPosition() { return _position; }
		Vector3 SetPosition(Vector3 newPos) { _position = newPos; }
		Vector3 SetPosition(float x, float y, float z) { _position = Vector3(x,y,z); }

		void Update();
		void Draw();
};

#endif //!_OBJObject