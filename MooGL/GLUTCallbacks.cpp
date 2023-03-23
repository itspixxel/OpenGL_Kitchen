// Includes
#include "GLUTCallbacks.h"
#include "MooGL.h"

// Namespace implementation
namespace GLUTCallbacks
{
	namespace
	{
		// Initialise to a null pointer before we do anything
		MooGL* mooGL = nullptr;
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
	}

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		mooGL->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		mooGL->Keyboard(key, x, y);
	}
}