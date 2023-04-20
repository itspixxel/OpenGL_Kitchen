#include "MooGL.h"
#define MAXOBJECTS 2

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
	gluPerspective(30, 1, 0.01, 1000);

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
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 9.0f;

	// Load meshes
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	OBJMesh* monkeMesh = OBJLoader::LoadOBJ((char*)"objects/monke.obj");
	OBJMesh* knotMesh = OBJLoader::LoadOBJ((char*)"objects/knot.obj");

	// Load textures
	Texture2D* woodTexture = new Texture2D();
	woodTexture->Load((char*)"crate.bmp", 512, 512);
	Texture2D* monkeTexture = new Texture2D();
	monkeTexture->Load((char*)"Monke.bmp", 512, 512);
	Texture2D* grassTexture = new Texture2D();
	grassTexture->Load((char*)"grass.bmp", 512, 512);

	for (int i = 0; i < 200; i++)
	{
		primitives.push_back(new Cube(cubeMesh, woodTexture, ((rand() % 600) / 10.0f) - 20.0f, ((rand() % 400) / 10.0f) - 10.0f, -(rand() % 2000) / 10.0f));
	}

	objects["monkey"] = new OBJObject(monkeMesh, woodTexture, 0.0f, 0.0f, 0.0f);;
	objects["knot"] = new OBJObject(knotMesh, grassTexture, 20.0f, 0.0f, 0.0f);;


	/*for (int i = 0; i < 200; i++)
	{
		objects.push_back(new OBJObject(roomMesh, texture, ((rand() % 600) / 10.0f) - 20.0f, ((rand() % 400) / 10.0f) - 10.0f, -(rand() % 2000) / 10.0f));
	}*/
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
	
	switch (objectFocusID)
	{
		case 0:
		{
			if (objects.find("monkey") != objects.end())
			{
				camera->center = objects["monkey"]->GetPosition();
				gluLookAt(
					camera->eye.x, camera->eye.y, camera->eye.z,
					camera->center.x, camera->center.y, camera->center.z,
					camera->up.x, camera->up.y, camera->up.z);
			}
			else {
				gluLookAt(
					camera->eye.x, camera->eye.y, camera->eye.z,
					camera->center.x, camera->center.y, camera->center.z,
					camera->up.x, camera->up.y, camera->up.z);
			}
			break;
		}
		case 1:
		{
			if (objects.find("knot") != objects.end())
			{
				camera->center = objects["knot"]->GetPosition();
				gluLookAt(
					camera->eye.x, camera->eye.y, camera->eye.z,
					camera->center.x, camera->center.y, camera->center.z,
					camera->up.x, camera->up.y, camera->up.z);
			}
			else {
				gluLookAt(
					camera->eye.x, camera->eye.y, camera->eye.z,
					camera->center.x, camera->center.y, camera->center.z,
					camera->up.x, camera->up.y, camera->up.z);
			}
			break;
		}
		case 2:
		{
			gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
			break;
		}
		
	}
		
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	for (SceneObject* n : primitives)
	{
		n->Update();
	}

	for (std::map<std::string, OBJObject*>::const_iterator it = objects.begin(); it != objects.end(); ++it)
	{
		it->second->Update();
	}

	glutPostRedisplay();
}

void MooGL::Keyboard(unsigned char key, int x, int y)
{
	// Calculate the direction vector
	Vector3 dir = camera->center - camera->eye;
	dir.normalize();

	switch (key)
	{
		case 'w': 
		{
			//// Calculate the direction vector
			//Vector3 dir = camera->center - camera->eye;
			//dir.normalize();
			//camera->eye = camera->eye + dir;

			//// Move the camera forward
			////if (camera->eye.x - dir.x > camera->center.x - 25 && camera->eye.x - dir.x < 25 && camera->eye.z - dir.z > camera->center.z + 7 && //camera->eye.z - dir.z < 20)
			////	camera->eye = camera->eye + dir;

			break;
		}

		case 'a': 
		{
			Vector3 cross = dir.crossProduct(camera->up);
			cross.normalize();
			if (camera->eye.x - cross.x > camera->center.x - 20 && camera->eye.x - cross.x < camera->center.x + 20)
			{
				camera->eye.x = camera->eye.x - cross.x;
			}
			if (camera->eye.z - cross.z > camera->center.z - 10 && camera->eye.z - cross.z < camera->center.z + 10)
			{
				camera->eye.z = camera->eye.z - cross.z;
			}

			break;
		}

		case 's':
		{
			//// Calculate the direction vector
			//Vector3 dir = camera->center - camera->eye;
			//dir.normalize();

			//// Move the camera forward
			//if (camera->eye.x - dir.x > camera->center.x - 25 && camera->eye.x - dir.x < 25 && camera->eye.z - dir.z > camera->center.z - 15 && camera->eye.z - dir.z < 15)
			//camera->eye = camera->eye - dir;

			break;
		}

		case 'd': 
		{
			Vector3 cross = dir.crossProduct(camera->up);
			cross.normalize();
			if (camera->eye.x + cross.x > camera->center.x - 20 && camera->eye.x + cross.x < camera->center.x + 20)
			{
				camera->eye.x = camera->eye.x + cross.x;
			}
			if (camera->eye.z + cross.z > camera->center.z - 10 && camera->eye.z + cross.z < camera->center.z + 10)
			{
				camera->eye.z = camera->eye.z + cross.z;
			}
			break;
		}
				
		case 'i':
		{
			if (objectFocusID < MAXOBJECTS - 1)
			{
				++objectFocusID;
			}
			else
			{
				objectFocusID = 0;
			}

			switch (objectFocusID)
			{
				case 0:
				{
					camera->eye = Vector3(2.25f, 0, 9);
					break;
				}
				case 1:
				{
					camera->eye = Vector3(22.5f, 0, 9);
					break;
				}
			}

			break;
		}

		case 'e':
		{
			camera->eye.y -= 0.1f;
			break;
		}
		
		case 'q':
		{
			camera->eye.y += 0.1f;
			break;
		}

		case 'o':
		{
			if (objectFocusID > 0)
			{
				--objectFocusID;
			}
			else {
				objectFocusID = MAXOBJECTS - 1;
			}

			switch (objectFocusID)
			{
				case 0:
				{
					camera->eye = Vector3(0, 0, 9);
					break;
				}
				case 1:
				{
					camera->eye = Vector3(20, 0, 9);
					break;
				}
			}


			break;
		}
	}
}

void MooGL::Display()
{
	glClearColor(0.094f, 0.094f, 0.094f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //this clears the scene

	for (SceneObject* n : primitives)
	{
		glPushMatrix();
		n->Draw();
		glPopMatrix();
	}

	for (std::map<std::string, OBJObject*>::const_iterator it = objects.begin(); it != objects.end(); ++it)
	{
		glPushMatrix();
		it->second->Draw();
		glPopMatrix();
	}

	glFlush();
	glutSwapBuffers();
}

MooGL::~MooGL(void)
{

}
