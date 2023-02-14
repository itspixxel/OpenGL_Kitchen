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
}
