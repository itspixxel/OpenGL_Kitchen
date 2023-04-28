#include "SceneManager.h"
#include "GLUTCallbacks.h"

#include "Scene.h"
#include "SceneManager.h"
#include "MooGL.h"

#include <iostream>

SceneManager::SceneManager(int argc, char* argv[])
{
	mCurrentScene = NULL;

	GLUTCallbacks::Init(this);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	ChangeScene(SCENE_KITCHEN, argc, argv);
}

SceneManager::~SceneManager(void)
{
	delete mCurrentScene;
	mCurrentScene = NULL;
}

void SceneManager::Display()
{
	mCurrentScene->Display();
}

void SceneManager::Update()
{
	mCurrentScene->Update();
}

void SceneManager::ChangeScene(SCENES newScreen, int argc, char* argv[])
{
	MooGL* tempMoo;

	switch (newScreen)
	{
	case SCENE_KITCHEN:
		tempMoo = new MooGL(argc, argv);
		mCurrentScene = (Scene*)tempMoo;
		tempMoo = NULL;
		break;
	default:
		std::cout << "ERROR::Was not able to load any of the scenes!" << std::endl;
		break;
	}
	mCurrentScene->~Scene();
}

void SceneManager::Keyboard(unsigned char key, int x, int y, int argc, char* argv[])
{
	if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == 27)
	{
		delete mCurrentScene;
		mCurrentScene = NULL;
	}

	if (key == '0')
		ChangeScene(SCENE_KITCHEN, argc, argv);

	if (key == 27)
		exit(0);
}