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
		GLfloat _rotation;
		Vector3 _position;
		bool _isSpinning;

	public:

		OBJObject(OBJMesh* objMesh, bool isSpinning, Material* material, Texture2D* _texture, float x, float y, float z);
		~OBJObject();

		GLfloat GetRotation() { return _rotation; }
		GLfloat SetRotation(GLfloat newRotation) { _rotation = newRotation; }
		void SetRotation(GLfloat x, GLfloat y, GLfloat z)
		{
			glRotatef(_rotation, x, y, z);
		}

		Vector3 GetPosition() { return _position; }
		void SetPosition(Vector3 newPos) { _position = newPos;}
		void SetPosition(float x, float y, float z) { _position = Vector3(x, y, z); }

		void Update();
		void Draw();
};

#endif //!_OBJObject