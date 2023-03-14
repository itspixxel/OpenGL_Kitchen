#include "MooGL.h"
#include <math.h>

MooGL::MooGL(int argc, char* argv[])
{
	// Creates an instance of a camera
	camera = new Camera();
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = 5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	rotation = 0.0f;

	for (int i = 0; i < 6000; i++)
	{
		cube[i] = new Cube(((rand() % 400) / 10.0f) - 20.0f, ((rand() % 250) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}


	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MooGL");

	// Tell GLUT about funcs
	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	// Switch to Project mode to set up the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 1, 500);

	// Switch back to ModelView mode
	glMatrixMode(GL_MODELVIEW);

	// Enable backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}

// Commence the DESTRUCTION!
MooGL::~MooGL(void)
{
	delete camera;
}

void MooGL::Display()
{
	glClearColor(0.094f, 0.094f, 0.094f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //this clears the scene

	glPushMatrix();
		glRotatef(rotation, 0.0f, 1.0f, 0.0f);
		for (int i = 0; i < 200; i++)
		{
			cube[i]->Draw();
		}
	glPopMatrix();

	glFlush(); // Flushes the scene drawn to the graphics card
	glutSwapBuffers();
}

void MooGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	glutPostRedisplay();

	// Constant rotation
	//rotation += 0.5f;

	for (int i = 0; i < 200; i++)
	{
		cube[i]->Update();
	}

	if (rotation >= 360.0f)
	{
		rotation = 0.0f;
	}
}

void MooGL::Keyboard(unsigned char key, int x, int y)
{
	// If the D key is pressed
	if (key == 'd')
	{
		rotation += 1.0f;
	}
	// If the A key is pressed
	if (key == 'a')
	{
		rotation -= 1.0f;
	}
	// If the W key is pressed
	if (key == 'w')
	{
		camera->eye.z -= 1.0f;
	}
	// If the S key is pressed
	if (key == 's')
	{
		camera->eye.z += 1.0f;
	}
}

int main(int argc, char* argv[])
{
	// Creates an instance of our game
	MooGL* moo = new MooGL(argc, argv);

	// Assumes a successful exit if our game exits
	return 0;
}