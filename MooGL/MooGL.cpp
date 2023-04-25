#include "MooGL.h"
#define MAX_OBJECTS 4

MooGL::MooGL(int argc, char* argv[])
{
	// Randomize srand with a seed
	srand(time(NULL));
	InitGL(argc, argv);
	InitObjects();
	InitLighting();

	glutMainLoop();
}

MooGL::~MooGL(void)
{

}

void MooGL::InitGL(int argc, char* argv[])
{
	// Initialize GLUTCallbacks
	GLUTCallbacks::Init(this);

	// Initialize GLUT
	glutInit(&argc, argv);

	// Initialize window settings
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MooGL");

	// Bind OpenGL to program funcs
	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutSpecialFunc(GLUTCallbacks::SpecialInput);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(30, 1, 0.01, 1000);

	// Enable GL modes
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GLUT_MULTISAMPLE);

	// Backface culling
	glCullFace(GL_BACK);

	// Switch to model view
	glMatrixMode(GL_MODELVIEW);
}

void MooGL::InitObjects()
{
	camera = new Camera();
	camera->eye.z = -5.0f; camera->up.y = 1.0f;
	camera->eye.x = 2.5f; camera->eye.y = 0.0f; camera->eye.z = 9.0f;

	// Load meshes
	Mesh* cubeMesh = MeshLoader::Load((char*)"objects/cube.txt");
	OBJMesh* toasterMesh = OBJLoader::LoadOBJ((char*)"objects/OBJ_Toaster.obj");
	OBJMesh* knotMesh = OBJLoader::LoadOBJ((char*)"objects/OBJ_Knot.obj");
	OBJMesh* teapotMesh = OBJLoader::LoadOBJ((char*)"objects/OBJ_Teapot.obj");
	OBJMesh* kitchenScene = OBJLoader::LoadOBJ((char*)"objects/OBJ_KitchenScene.obj");

	// Initialize materials
	Material* crateMaterial = new Material();
	Material* toasterMaterial = new Material();
	Material* teapotMaterial = new Material();
	Material* knotMaterial = new Material();
	Material* kitchenMaterial = new Material();

	// Crate material
	crateMaterial->ambient.x = 0.545f; crateMaterial->diffuse.x = 0.545f; crateMaterial->specular.x = 0.984f;
	crateMaterial->ambient.y = 0.684f; crateMaterial->diffuse.y = 0.894f; crateMaterial->specular.y = 0.471f;
	crateMaterial->ambient.z = 0.894f; crateMaterial->diffuse.z = 0.951f; crateMaterial->specular.z = 0.684f;
	crateMaterial->shininess = 25.0f;

	// Monke material
	toasterMaterial->ambient.x = 0.648f; toasterMaterial->diffuse.x = 0.514f; toasterMaterial->specular.x = 2.51f;
	toasterMaterial->ambient.y = 0.654f; toasterMaterial->diffuse.y = 0.694f; toasterMaterial->specular.y = 4.06f;
	toasterMaterial->ambient.z = 0.587f; toasterMaterial->diffuse.z = 0.648f; toasterMaterial->specular.z = 9.59f;
	toasterMaterial->shininess = 50.0f;

	// Teapot material
	teapotMaterial->ambient.x = 0.854f; teapotMaterial->diffuse.x = 0.481f; teapotMaterial->specular.x = 9.59f;
	teapotMaterial->ambient.y = 0.871f; teapotMaterial->diffuse.y = 0.642f; teapotMaterial->specular.y = 2.51f;
	teapotMaterial->ambient.z = 0.587f; teapotMaterial->diffuse.z = 0.847f; teapotMaterial->specular.z = 4.06f;
	teapotMaterial->shininess = 75.0f;

	// Knot material
	knotMaterial->ambient.x = 0.514f; knotMaterial->diffuse.x = 0.648f; knotMaterial->specular.x = 0.694f;
	knotMaterial->ambient.y = 0.845f; knotMaterial->diffuse.y = 0.684f; knotMaterial->specular.y = 0.689f;
	knotMaterial->ambient.z = 0.645f; knotMaterial->diffuse.z = 0.816f; knotMaterial->specular.z = 0.614f;
	knotMaterial->shininess = 100.0f;

	// Kitchen material
	kitchenMaterial->ambient.x = 0.5f; kitchenMaterial->diffuse.x = 0.5f; kitchenMaterial->specular.x = 0.5f;
	kitchenMaterial->ambient.y = 0.5f; kitchenMaterial->diffuse.y = 0.5f; kitchenMaterial->specular.y = 0.5f;
	kitchenMaterial->ambient.z = 0.5f; kitchenMaterial->diffuse.z = 0.5f; kitchenMaterial->specular.z = 0.5f;
	kitchenMaterial->shininess = 100.0f;

	// Load textures
	Texture2D* starsTexture = new Texture2D();
	starsTexture->Load((char*)"textures/TX_Stars.raw", 512, 512);
	
	Texture2D* crateTexture = new Texture2D();
	crateTexture->Load((char*)"textures/TX_Crate.bmp", 512, 512);

	Texture2D* plasticTexture = new Texture2D();
	plasticTexture->Load((char*)"textures/TX_Scratched_Plastic.bmp", 512, 512);

	Texture2D* marbleTexture = new Texture2D();
	marbleTexture->Load((char*)"textures/TX_Marble.bmp", 512, 512);

	Texture2D* woodTexture = new Texture2D();
	woodTexture->Load((char*)"textures/TX_Wood.bmp", 512, 512);

	Texture2D* kitchenTexture = new Texture2D();
	kitchenTexture->Load((char*)"textures/TX_Kitchen.bmp", 512, 512);

	Texture2D* toasterTexture = new Texture2D();
	toasterTexture->Load((char*)"textures/TX_Toaster.bmp", 512, 512);

	// Cube field
	for (int i = 0; i < 200; i++)
	{
		primitives.push_back(new Cube(cubeMesh, crateMaterial, crateTexture, ((rand() % 600) / 10.0f) - 20.0f, ((rand() % 400) / 10.0f) - 10.0f, -(rand() % 2000) / 10.0f));
	}

	// Create objects and add to map
	objects["toaster"] = new OBJObject(toasterMesh, toasterMaterial, plasticTexture, 10.0f, -4.3f, -10.0f);
	objects["knot"] = new OBJObject(knotMesh, knotMaterial, woodTexture, 20.0f, 0.0f, 0.0f);
	objects["teapot"] = new OBJObject(teapotMesh, teapotMaterial, marbleTexture, 40.0f, 0.0f, 0.0f);
	objects["kitchen"] = new OBJObject(kitchenScene, kitchenMaterial, kitchenTexture, 0.0, 0.0f, 0.0f);
}

void MooGL::InitLighting()
{
	// Positional data
	_lightPosition = new Vector4();
	_lightPosition->x = 0.5;
	_lightPosition->y = 1.0;
	_lightPosition->z = 0.5;
	_lightPosition->w = 0.0;

	// Lighting data
	_lightData = new Lighting();
	_lightData->ambient.x = 0.5;
	_lightData->ambient.y = 0.5;
	_lightData->ambient.z = 0.5;
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
	// Replaces the current matrix with the identity matrix
	glLoadIdentity();
	
	// Switch between different focus objects
	switch (objectFocusID)
	{
		
		// Focus on toaster object
		case 0:
		{
			if (objects.find("toaster") != objects.end())
			{
				camera->center = objects["toaster"]->GetPosition();
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

		// Focus on torus knot object
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

		// Focus on teapot object
		case 2:
		{
			if (objects.find("teapot") != objects.end())
			{
				camera->center = objects["teapot"]->GetPosition();
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

		// Focus on kitchen object
		case 3:
		{
			if (objects.find("kitchen") != objects.end())
			{
				camera->center = objects["kitchen"]->GetPosition();
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
		
	}
	
	// Update lighting every frame
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	// Update primitive objects every frame
	/*for (SceneObject* n : primitives)
	{
		n->Update();
	}*/

	// Update OBJ objects every frame
	for (std::map<std::string, OBJObject*>::const_iterator it = objects.begin(); it != objects.end(); ++it)
	{
		it->second->Update();
	}

	// Marks the current window as needing to be redisplayed
	glutPostRedisplay();
}

void MooGL::Keyboard(unsigned char key, int x, int y)
{
	// Calculate the direction vector
	Vector3 dir = camera->center - camera->eye;
	dir.normalize();

	switch (key)
	{
		// Rotate around current object in the left direction
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

		// Rotate around current object in the right direction
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

		case 'e':
		{
			camera->eye.y += 0.1f;
			break;
		}

		case 'q':
		{
			camera->eye.y -= 0.1f;
			break;
		}
	}
}

void MooGL::SpecialInput(int key, int x, int y)
{
	switch (key)
	{
		// Move current object up with up arrow key
	case GLUT_KEY_UP:
		{
			if (objectFocusID == 0)
			{
				Vector3 currentPos = objects["toaster"]->GetPosition();
				Vector3 newPos = currentPos + Vector3(0.0f, 0.5f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["toaster"]->SetPosition(newPos);
			}
			if (objectFocusID == 1)
			{
				Vector3 currentPos = objects["knot"]->GetPosition();
				Vector3 newPos = currentPos + Vector3(0.0f, 0.5f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["knot"]->SetPosition(newPos);
			}
			if (objectFocusID == 2)
			{
				Vector3 currentPos = objects["teapot"]->GetPosition();
				Vector3 newPos = currentPos + Vector3(0.0f, 0.5f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["teapot"]->SetPosition(newPos);
			}
			if (objectFocusID == 3)
			{
				Vector3 currentPos = objects["kitchen"]->GetPosition();
				Vector3 newPos = currentPos + Vector3(0.0f, 0.5f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["kitchen"]->SetPosition(newPos);
			}
			break;
		}

		case GLUT_KEY_DOWN:
		{
			if (objectFocusID == 0)
			{
				Vector3 currentPos = objects["toaster"]->GetPosition();
				Vector3 newPos = currentPos - Vector3(0.0f, 0.5f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["toaster"]->SetPosition(newPos);
			}
			if (objectFocusID == 1)
			{
				Vector3 currentPos = objects["knot"]->GetPosition();
				Vector3 newPos = currentPos - Vector3(0.0f, 0.5f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["knot"]->SetPosition(newPos);
			}
			if (objectFocusID == 2)
			{
				Vector3 currentPos = objects["teapot"]->GetPosition();
				Vector3 newPos = currentPos - Vector3(0.0f, 0.5f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["teapot"]->SetPosition(newPos);
			}
			if (objectFocusID == 3)
			{
				Vector3 currentPos = objects["kitchen"]->GetPosition();
				Vector3 newPos = currentPos - Vector3(0.0f, 0.5f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["kitchen"]->SetPosition(newPos);
			}
			break;
		}

		// Move current object left with left arrow key
		case GLUT_KEY_LEFT:
		{
			if (objectFocusID == 0)
			{
				Vector3 currentPos = objects["toaster"]->GetPosition();
				Vector3 newPos = currentPos - Vector3(0.5f, 0.0f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["toaster"]->SetPosition(newPos);
			}
			if (objectFocusID == 1)
			{
				Vector3 currentPos = objects["knot"]->GetPosition();
				Vector3 newPos = currentPos - Vector3(0.5f, 0.0f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["knot"]->SetPosition(newPos);
			}
			if (objectFocusID == 2)
			{
				Vector3 currentPos = objects["teapot"]->GetPosition();
				Vector3 newPos = currentPos - Vector3(0.5f, 0.0f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["teapot"]->SetPosition(newPos);
			}
			if (objectFocusID == 3)
			{
				Vector3 currentPos = objects["kitchen"]->GetPosition();
				Vector3 newPos = currentPos - Vector3(0.5f, 0.0f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["kitchen"]->SetPosition(newPos);
			}
			break;
		}

		// Move current object right with right arrow key
		case GLUT_KEY_RIGHT:
		{
			if (objectFocusID == 0)
			{
				Vector3 currentPos = objects["toaster"]->GetPosition();
				Vector3 newPos = currentPos + Vector3(0.5f, 0.0f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["toaster"]->SetPosition(newPos);
			}
			if (objectFocusID == 1)
			{
				Vector3 currentPos = objects["knot"]->GetPosition();
				Vector3 newPos = currentPos + Vector3(0.5f, 0.0f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["knot"]->SetPosition(newPos);
			}
			if (objectFocusID == 2)
			{
				Vector3 currentPos = objects["teapot"]->GetPosition();
				Vector3 newPos = currentPos + Vector3(0.5f, 0.0f, 0.0f);
				camera->eye = currentPos + Vector3(0.0f, 0.0f, 9.0f);
				objects["teapot"]->SetPosition(newPos);
			}
			break;
		}

		// Switch to next object with PAGE UP key
		case GLUT_KEY_PAGE_UP:
		{
			objects["toaster"]->SetPosition(0, 0, 0);
			objects["knot"]->SetPosition(20, 0, 0);
			objects["teapot"]->SetPosition(40, 0, 0);
			objects["kitchen"]->SetPosition(0, 0, 0);

			if (objectFocusID < MAX_OBJECTS - 1)
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
					camera->eye = Vector3(2.5f, 0, 9);
					break;
				}
				case 1:
				{
					camera->eye = Vector3(22.5f, 0, 9);
					break;
				}
				case 2:
				{
					camera->eye = Vector3(42.5f, 0, 9);
					break;
				}
				case 3:
				{
					camera->eye = Vector3(0, 0, 0);
					break;
				}
			}
			break;
		}

		// Switch to last object with PAGE DOWN key
		case GLUT_KEY_PAGE_DOWN:
		{
			objects["toaster"]->SetPosition(0, 0, 0);
			objects["knot"]->SetPosition(20, 0, 0);
			objects["teapot"]->SetPosition(40, 0, 0);
			objects["kitchen"]->SetPosition(0, 0, 0);

			if (objectFocusID > 0)
			{
				--objectFocusID;
			}
			else {
				objectFocusID = MAX_OBJECTS - 1;
			}

			switch (objectFocusID)
			{
				case 0:
				{
					camera->eye = Vector3(2.5f, 0, 9);
					break;
				}
				case 1:
				{
					camera->eye = Vector3(22.5f, 0, 9);
					break;
				}
				case 2:
				{
					camera->eye = Vector3(42.5f, 0, 9);
					break;
				}
				case 3:
				{
					camera->eye = Vector3(0, 0, 0);
					break;
				}
			}
			break;
		}
	}
}

void MooGL::Display()
{
	// Background color
	glClearColor(0.094f, 0.094f, 0.094f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears the scene

	DrawString();

	// Draw all primitives
	/*for (SceneObject* n : primitives)
	{
		glPushMatrix();
			n->Draw();
		glPopMatrix();
	}*/

	// Draw all OBJs
	for (std::map<std::string, OBJObject*>::const_iterator it = objects.begin(); it != objects.end(); ++it)
	{
		glPushMatrix();
			it->second->Draw();
		glPopMatrix();
	}

	glFlush(); // Forces execution of OpenGL functions in finite time
	glutSwapBuffers(); // Swaps the buffers of the current window
}

void MooGL::DrawString()
{
	/*glPushMatrix();
		glTranslatef(position->x)
	glPopMatrix();*/
	glDisable(GL_LIGHTING);
	// toaster text
	glPushMatrix();
		Vector3 toasterPos = objects["toaster"]->GetPosition();
		glColor3f(1, 1, 1);
		glTranslatef(toasterPos.x, toasterPos.y + 1.25f, toasterPos.z);
		glRasterPos2f(0.0f, 0.0f);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*) "Toaster");
	glPopMatrix();

	// Knot text
	glPushMatrix();
		Vector3 knotPosition = objects["knot"]->GetPosition();
		glColor3f(1, 1, 1);
		glTranslatef(knotPosition.x - 0.25f, knotPosition.y + 1.3f, knotPosition.z);
		glRasterPos2f(0.0f, 0.0f);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*) "Torus Knot");
	glPopMatrix();

	// Teapot text
	glPushMatrix();
		Vector3 teapotPosition = objects["teapot"]->GetPosition();
		glColor3f(1, 1, 1);
		glTranslatef(teapotPosition.x, teapotPosition.y + 1.4f, teapotPosition.z);
		glRasterPos2f(0.0f, 0.0f);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*) "Teapot");
	glPopMatrix();
	glEnable(GL_LIGHTING);
}