#pragma once
class MooGL;
#include "GL\freeglut.h"
#include <iostream>

namespace GLUTCallbacks
{

	void Init(MooGL* gl);
	void Timer(int preferredRefresh);
	void Keyboard(unsigned char key, int x, int y);
	void Display();

}
