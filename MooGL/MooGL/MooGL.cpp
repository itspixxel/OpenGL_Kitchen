#include "MooGL.h"

MooGL::MooGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

// Commence the DESTRUCTION!
MooGL::~MooGL(void)
{
	
}

void MooGL::Display()
{

}


int main(int argc, char* argv[])
{
	//Creates an instance of our game
	MooGL* game = new MooGL(argc, argv);

	//Assumes a successful exit if our game exits
	return 0;
}