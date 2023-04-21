#include "Cube.h"

using namespace std;

Cube::Cube(Mesh* mesh, Material* material, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	
	_texture = texture;

	_material = new Material();
	_material->ambient.x = material->ambient.x; _material->ambient.y = material->ambient.y; _material->ambient.z = material->ambient.z; _material->ambient.w = material->ambient.w;
	_material->diffuse.x = material->diffuse.x; _material->diffuse.y = material->diffuse.y; _material->diffuse.z = material->diffuse.z; _material->diffuse.w = material->diffuse.w;
	_material->specular.x = material->specular.x; _material->specular.y = material->specular.y; _material->specular.z = material->specular.z; _material->specular.w = material->specular.w;
	_material->shininess = material->shininess;
}

void Cube::Update()
{
	_rotation += 0.5f;
	_position.z += 0.05f;
}

void Cube::Draw()
{

	if (_mesh->indexedVertices != nullptr && _mesh->indexedNormals != nullptr && _mesh->indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glScalef(1, 1, 1);
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 1.0f, 1.0f);

		glEnable(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, _mesh->indexedNormals);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->indexedVertices);

		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x));
		glMaterialf(GL_FRONT, GL_SHININESS, _material->shininess);

		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->texCoords);
		glPushMatrix();
		glDrawElements(GL_TRIANGLES, _mesh->numIndices, GL_UNSIGNED_SHORT, _mesh->indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glTranslatef(0, 0, 0);
	}
}


Cube::~Cube()
{

}