#include "OBJObject.h"

OBJObject::OBJObject(OBJMesh* mesh, Texture2D* _texture, float x, float y, float z) : SceneObject(mesh, _texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;

	_rotation = 0.0f;
}

OBJObject::~OBJObject()
{
}

void OBJObject::Update()
{
	_rotation += 0.5f;
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
		}
		glEnd();

		glPopMatrix();
	}
}