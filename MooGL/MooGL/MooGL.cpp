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
	glClear(GL_COLOR_BUFFER_BIT); //this clears the scene
	glBegin(GL_POLYGON); //starts to draw a polygon
	// plotting the vertices
	glColor4f(0.811f, 0.321f, 0.949f, 0.372f);
	glVertex2f(-0.75, 0.5); 
	glColor4f(0.666f, 0.337f, 0.988f, 0.388f);
	glVertex2f(0.75, 0.5); 
	glColor4f(0.478f, 0.352f, 0.901f, 0.352f);
	glVertex2f(0.75, -0.5); 
	glColor4f(0.337f, 0.360f, 0.988f, 0.388f);
	glVertex2f(-0.75, -0.5); 
	glEnd(); // defines the end of the draw
	glFlush(); //flushes the scene drawn to the graphics card
}


int main(int argc, char* argv[])
{
	//Creates an instance of our game
	MooGL* game = new MooGL(argc, argv);

	//Assumes a successful exit if our game exits
	return 0;
}