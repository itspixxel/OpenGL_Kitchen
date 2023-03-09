#include "MooGL.h"

Vertex MooGL::vertices[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
				-1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

				1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
				1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

				1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
				-1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

				-1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
				-1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

				-1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
				1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

				1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
				-1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

Color MooGL::colors[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
				1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

				1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
				0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

				1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
				0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

				1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
				0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

				0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
				1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

				0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
				0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4

Vertex MooGL::indexedVertices[] = { 1, 1, 1,  -1, 1, 1,  // v0,v1,
				-1,-1, 1,   1,-1, 1,   // v2,v3
				1,-1,-1,   1, 1,-1,    // v4,v5
				-1, 1,-1,   -1,-1,-1 }; // v6,v7

Color MooGL::indexedColors[] = { 1, 1, 1,   1, 1, 0,   // v0,v1,
				1, 0, 0,   1, 0, 1,   // v2,v3
				0, 0, 1,   0, 1, 1,   // v4,v5
				0, 1, 0,   0, 0, 0 }; //v6,v7

GLushort MooGL::indices[] = { 0, 1, 2,  2, 3, 0,      // front
				0, 3, 4,  4, 5, 0,      // right
				0, 5, 6,  6, 1, 0,      // top
				1, 6, 7,  7, 2, 1,      // left
				7, 4, 3,  3, 2, 7,      // bottom
				4, 7, 6,  6, 5, 4 };    // back


#include <cmath>

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

	glutInitDisplayMode(GLUT_DOUBLE);
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
	glClear(GL_COLOR_BUFFER_BIT); //this clears the scene

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

	// DrawCube method call
	DrawIndexedCube();


	glFlush(); // Flushes the scene drawn to the graphics card
	glutSwapBuffers();
}

void MooGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	glutPostRedisplay();
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

void MooGL::DrawCube()
{
	glBegin(GL_TRIANGLES);
	// face v0-v1-v2
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	// face v2-v3-v0
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	// face v0-v3-v4
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	// face v4-v5-v0
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	// face v0-v5-v6
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	// face v6-v1-v0
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	// face  v1-v6-v7
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	// face v7-v2-v1
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	// face v7-v4-v3
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	// face v3-v2-v7
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);

	// face v4-v7-v6
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	// face v6-v5-v4
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);

	glEnd();
}

void MooGL::DrawCubeArray()
{
	glPushMatrix();

		glBegin(GL_TRIANGLES);
			for (int i = 0; i < 36; i++)
			{
				glColor3fv(&colors[i].r);
				glVertex3fv(&vertices[i].x);
			}
		glEnd();

	glPopMatrix();
}

void MooGL::DrawIndexedCube()
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++)
	{
		Vertex v = indexedVertices[indices[i]];
		Color c = indexedColors[indices[i]];
		glColor3f(c.r, c.g, c.b);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();

	glPopMatrix();
}


int main(int argc, char* argv[])
{
	// Creates an instance of our game
	MooGL* moo = new MooGL(argc, argv);

	// Assumes a successful exit if our game exits
	return 0;
}