#pragma once
#include "Structures.h"
#include "SceneObject.h"

class Pyramid : public SceneObject
{
	public: 
		Pyramid(Mesh* mesh, float x, float y, float z);
		~Pyramid();

		void Draw();
		void Update();

	private:
		static int numVertices, numColors, numIndices;

		GLfloat rotation = 0.0f;
		Vector3 position;
};