#include "MooGL.h"
#include <math.h>

MooGL::MooGL(int argc, char* argv[])
{
	// Creates an instance of a camera
	camera = new Camera();
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	rotation = 0.0f;

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
	gluPerspective(45, 1, 0, 500);

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

	// Render first shape (square)
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -2.0f);
		glRotatef(rotation, 1.0f, 0.0f, 1.0f);
	
		
		glBegin(GL_POLYGON);
			glColor4f(0.811f, 0.321f, 0.949f, 0.372f);
			glVertex2f(0.25f, 0.5f);
			glColor4f(0.666f, 0.337f, 0.988f, 0.388f);
			glVertex2f(0.5f, 0.5f); 
			glColor4f(0.478f, 0.352f, 0.901f, 0.352f);
			glVertex2f(0.5f, 0.25f); 
			glColor4f(0.337f, 0.360f, 0.988f, 0.388f);
			glVertex2f(0.25f, 0.25f);
		glEnd();

	glPopMatrix();

	// Render second shape (triangle)
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(rotation, 0.0f, 1.0f, 1.0f);

		glBegin(GL_TRIANGLES);
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glVertex2f(-0.5f, 0.625f);
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			glVertex2f(-0.25f, 0.25f);
			glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			glVertex2f(-0.75f, 0.25f);
		glEnd();

	glPopMatrix();

	// Render a circle with 64 sides
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(rotation, 1.0f, 1.0f, 1.0f);

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

	glPopMatrix();

	cube->Draw();

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