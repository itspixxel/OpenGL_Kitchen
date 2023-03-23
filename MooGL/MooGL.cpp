#include "MooGL.h"

int main(int argc, char* argv[])
{
	MooGL* game = new MooGL(argc, argv);

	return 0;
}

MooGL::MooGL(int argc, char* argv[])
{
	srand(time(NULL));
	InitGL(argc, argv);
	InitObjects();

	glutMainLoop();

}

void MooGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple OpenGL Program");

	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(1, 0);

	glMatrixMode(GL_MODELVIEW);

}

void MooGL::InitObjects()
{
	rotation = 0;
	camera = new Camera();
	camera->eye.z = 5.0f; camera->up.y = 1.0f;
	//camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;

	Mesh* cubeMesh = MeshLoader::Load((char *)"cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);


	for (int i = 0; i < 200; i++)
	{
		objects.push_back(new Pyramid(pyramidMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f));

	}

	srand(time(NULL) + 50);

	for (int i = 0; i < 200; i++)
	{
		objects.push_back(new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f));
	}

}

void MooGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	
	for (SceneObject* n : objects)
		n->Update();

	glutPostRedisplay();
}

void MooGL::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w': {
			camera->eye.y--;
			break;
		}

		case 'a': {
			camera->eye.x++;
			break;
		}

		case 's': {
			camera->eye.y++;
			break;
		}

		case 'd': {
			camera->eye.x--;
			break;
		}
	}
}

void MooGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (SceneObject* n : objects)
	{
		glPushMatrix();
			n->Draw();
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
}

MooGL::~MooGL(void)
{

}
