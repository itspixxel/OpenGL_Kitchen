#pragma once

#ifndef _SceneObject
#define _SceneObject

#ifndef _hStructs
#include "Structures.h"
#endif

#ifndef _texture2D.h
#include "Texture2D.h"
#endif

class SceneObject
{
	protected:
		Mesh* _mesh;
		OBJMesh* _objMesh;
		Texture2D* _texture;

	public:
		SceneObject(Mesh* mesh, Texture2D* texture);
		SceneObject(OBJMesh* mesh, Texture2D* texture);
		virtual ~SceneObject();

		virtual void Update();
		virtual void Draw();
};
#endif // !_SceneObject