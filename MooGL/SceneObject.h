#pragma once
#include "Structures.h"

class SceneObject
{
protected:
	Mesh* m_mesh;

public:
	SceneObject(Mesh* mesh);
	virtual ~SceneObject();

	virtual void Update();
	virtual void Draw();
};
