#include "OBJObject.h"

OBJObject::OBJObject(OBJMesh* mesh, Texture2D* _texture, float x, float y, float z) : SceneObject(mesh, _texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;

	_rotation = 0.0f;

	_material = new Material();
	_material->ambient.x = 0.05; _material->ambient.y = 0.3514; _material->ambient.z = 0.0654; _material->ambient.w = 1.0;
	_material->diffuse.x = 0.8; _material->diffuse.y = 0.05; _material->diffuse.z = 0.05; _material->diffuse.w = 1.0;
	_material->specular.x = 5.0; _material->specular.y = 5.0; _material->specular.z = 5.0; _material->specular.w = 5.0;
	_material->shininess = 100.0f;
}

OBJObject::~OBJObject()
{
}

void OBJObject::Update()
{
	//_rotation += 0.5f;
}

void OBJObject::Draw()
{
	if (!_objMesh->vertices.empty() && !_objMesh->normals.empty() && !_objMesh->texCoords.empty() && !_objMesh->indices.empty())
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 0, 1, 0);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < _objMesh->indices.size(); i++)
		{
			glTexCoord2fv(&_objMesh->texCoords[_objMesh->indices[i].texCoordIndex - 1].u);
			glNormal3fv(&_objMesh->normals[_objMesh->indices[i].normalIndex - 1].x);
			glVertex3fv(&_objMesh->vertices[_objMesh->indices[i].vertexIndex - 1].x);

			glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
			glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->ambient.x));
			glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x));
			glMaterialf(GL_FRONT, GL_SHININESS, _material->shininess);
		}
		glEnd();

		glPopMatrix();
	}
}