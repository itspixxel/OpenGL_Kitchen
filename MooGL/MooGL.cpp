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
	InitLighting();

	glutMainLoop();
}

void MooGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MooGL");

	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 1, 1000);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GLUT_MULTISAMPLE);

	glCullFace(GL_BACK);

	glMatrixMode(GL_MODELVIEW);
}

void MooGL::InitObjects()
{
	rotation = 0;
	camera = new Camera();
	camera->eye.z = -5.0f; camera->up.y = 1.0f;
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;

	Mesh* cubeMesh = MeshLoader::Load((char *)"cube.txt");
	OBJMesh* monkeMesh = OBJLoader::LoadOBJ((char*)"objects/monke.obj");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"crate.bmp", 512, 512);
	Texture2D* monkeTexture = new Texture2D();
	monkeTexture->Load((char*)"Monke.bmp", 512, 512);

	objects.push_back(new Cube(cubeMesh, texture, 0.0f, 0.0f, 0.0f));
	for (int i = 0; i < 200; i++)
	{
		objects.push_back(new OBJObject(monkeMesh, monkeTexture, ((rand() % 600) / 10.0f) - 20.0f, ((rand() % 400) / 10.0f) - 10.0f, -(rand() % 2000) / 10.0f));
	}
}

void MooGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 1.0;
	_lightPosition->z = -0.5;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->ambient.x = 0.2;
	_lightData->ambient.y = 0.2;
	_lightData->ambient.z = 0.2;
	_lightData->ambient.w = 1.0;
	_lightData->diffuse.x = 0.8;
	_lightData->diffuse.y = 0.8;
	_lightData->diffuse.z = 0.8;
	_lightData->diffuse.w = 1.0;
	_lightData->specular.x = 0.2;
	_lightData->specular.y = 0.2;
	_lightData->specular.z = 0.2;
	_lightData->specular.w = 1.0;
}

void MooGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	for (SceneObject* n : objects)
		n->Update();

	glutPostRedisplay();
}

void MooGL::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w': {
			camera->eye.z--;
			break;
		}

		case 'a': {
			camera->eye.x++;
			break;
		}

		case 's': {
			camera->eye.z++;
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
	glClearColor(0.094f, 0.094f, 0.094f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //this clears the scene

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
