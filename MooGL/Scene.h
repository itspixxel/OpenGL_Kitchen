#pragma once
#include "Structures.h"

class Scene
{
	public:
		Scene();
		~Scene(void);

		virtual void InitGL();
		virtual void InitLighting();
		virtual void InitObjects();

		virtual void Display();
		virtual void Update();

		Camera* camera;
		Vector4* _lightPosition;
		Lighting* _lightData;
};