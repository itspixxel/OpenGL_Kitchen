#pragma once
class MooGL;

namespace GLUTCallbacks
{
	void Init(MooGL* gl);

	void Display();

	void Timer(int preferredRefresh);

	void Keyboard(unsigned char key, int x, int y);
}