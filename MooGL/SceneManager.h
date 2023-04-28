#pragma once
#include "Scene.h"

#define REFRESHRATE 16

class Scene;
class SceneManager
{
	public:
		SceneManager(int argc, char* argv[]);
		~SceneManager(void);

		void Display();
		void Update();

		void ChangeScene(SCENES newScene, int argc, char* argv[]);
		void Keyboard(unsigned char key, int x, int y, int argc, char* argv[]);

	private:
		Scene* mCurrentScene;
};