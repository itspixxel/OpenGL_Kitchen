#pragma once
class MooGL;

namespace GLUTCallbacks
{
	void Init(MooGL* gl);

	void Display();

	void Timer(int preferredRefresh);
}