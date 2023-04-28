// Includes
#include "GLUTCallbacks.h"
#include "MooGL.h"
#include "SceneManager.h"

// Namespace implementation
namespace GLUTCallbacks
{
	namespace
	{
		// Initialise to a null pointer before we do anything
		MooGL* mooGL = nullptr;
		SceneManager* sceneManager = nullptr;
	}

	void Init(SceneManager* gl)
	{
		sceneManager = gl;
	}

	void Init(MooGL* gl)
	{
		mooGL = gl;
	}

	void Display()
	{

		if (mooGL != nullptr)
		{
			mooGL->Display();
		}
		else if (sceneManager != nullptr)
		{
			sceneManager->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		if (mooGL != nullptr)
		{
			mooGL->Update();
		}
		else if (sceneManager != nullptr)
		{
			sceneManager->Update();
		}

		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		mooGL->Keyboard(key, x, y);
	}

	void SpecialInput(int key, int x, int y)
	{
		mooGL->SpecialInput(key, x, y);
	}
}