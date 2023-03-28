#include "Cube.h"

using namespace std;

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh)
{

	_position.x = x;
	_position.y = y;
	_position.z = z;
	
	_texture = texture;

	_material = new Material();
	_material->ambient.x = 0.8; _material->ambient.y = 0.05; _material->ambient.z = 0.05; _material->ambient.w = 1.0;
	_material->diffuse.x = 0.8; _material->diffuse.y = 0.05; _material->diffuse.z = 0.05; _material->diffuse.w = 1.0;
	_material->specular.x = 1.0; _material->specular.y = 1.0; _material->specular.z = 1.0; _material->specular.w = 1.0;
	_material->shininess = 100.0f;

}

void Cube::Update()
{
	//_rotation += 0.1f;
	_position.z += 0.05f;
}

void Cube::Draw()
{

	if (_mesh->indexedVertices != nullptr && _mesh->indexedNormals != nullptr && _mesh->indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);


		glNormalPointer(GL_FLOAT, 0, _mesh->indexedNormals);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->indexedVertices);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->texCoords);

		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
		glMaterialf(GL_FRONT, GL_SHININESS, _material->shininess);

		glPushMatrix();
			glScalef(1, 1, 1);
			glTranslatef(_position.x, _position.y, _position.z);
			glRotatef(_rotation, 0.0f, 1.0f, 0.0f);
			glDrawElements(GL_TRIANGLES, _mesh->numIndices, GL_UNSIGNED_SHORT, _mesh->indices);
		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}


Cube::~Cube()
{

}