#include "MooGL.h"
#include <cmath>

MooGL::MooGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
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
	glClearColor(0.094f, 0.094f, 0.094f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); //this clears the scene
	
	// Render first shape (rectangle)
	glBegin(GL_POLYGON);
	glColor4f(0.811f, 0.321f, 0.949f, 0.372f);
	glVertex2f(0.25, 0.75); 
	glColor4f(0.666f, 0.337f, 0.988f, 0.388f);
	glVertex2f(0.75, 0.75); 
	glColor4f(0.478f, 0.352f, 0.901f, 0.352f);
	glVertex2f(0.75, 0.25); 
	glColor4f(0.337f, 0.360f, 0.988f, 0.388f);
	glVertex2f(0.25, 0.25); 
	glEnd();

	// Render second shape (triangle)
	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(-0.5f, 0.625f);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex2f(-0.25f, 0.25f);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex2f(-0.75f, 0.25f);
	glEnd();

	// Render a circle with 64 sides
	const int num_segments = 64;
	const float radius = 0.25f;
	const float center_x = 0.0f;
	const float center_y = -0.5f;
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(0.0f, 0.560f, 0.549f, 0.219f); // Center color
	glVertex2f(center_x, center_y);
	for (int i = 0; i <= num_segments; ++i) {
		float angle = i * (2.0f * 3.1415926f / num_segments);
		float x = center_x + radius * cosf(angle);
		float y = center_y + radius * sinf(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glFlush(); //flushes the scene drawn to the graphics card
}


int main(int argc, char* argv[])
{
	//Creates an instance of our game
	MooGL* game = new MooGL(argc, argv);

	//Assumes a successful exit if our game exits
	return 0;
}