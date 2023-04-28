#pragma once
#include "GL\freeglut.h"
#include <iostream>
#include "SceneManager.h"

class MooGL;

namespace GLUTCallbacks
{

	void Init(MooGL* gl);
	void Init(SceneManager* gl);
	void Timer(int preferredRefresh);
	void Keyboard(unsigned char key, int x, int y);
	void SpecialInput(int key, int x, int y);
	void Display();
}
