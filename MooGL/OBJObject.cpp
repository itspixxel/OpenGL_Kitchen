#include "OBJObject.h"

OBJObject::OBJObject(OBJMesh* mesh, Material* material, Texture2D* _texture, float x, float y, float z) : SceneObject(mesh, _texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;

	_rotation = 0.0f;

	_material = new Material();
	_material->ambient.x = material->ambient.x; _material->ambient.y = material->ambient.y; _material->ambient.z = material->ambient.z; _material->ambient.w = material->ambient.w;
	_material->diffuse.x = material->diffuse.x; _material->diffuse.y = material->diffuse.y; _material->diffuse.z = material->diffuse.z; _material->diffuse.w = material->diffuse.w;
	_material->specular.x = material->specular.x; _material->specular.y = material->specular.y; _material->specular.z = material->specular.z; _material->specular.w = material->specular.w;
	_material->shininess = material->shininess;
}

OBJObject::~OBJObject()
{
	delete _material;
}

void OBJObject::Update()
{
	
}

void OBJObject::Draw()
{
	if (!_objMesh->vertices.empty() && !_objMesh->normals.empty() && !_objMesh->texCoords.empty() && !_objMesh->indices.empty())
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		//glRotatef(_rotation, 0, 1, 0);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < _objMesh->indices.size(); i++)
		{
			glTexCoord2fv(&_objMesh->texCoords[_objMesh->indices[i].texCoordIndex - 1].u);
			glNormal3fv(&_objMesh->normals[_objMesh->indices[i].normalIndex - 1].x);
			glVertex3fv(&_objMesh->vertices[_objMesh->indices[i].vertexIndex - 1].x);

			glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
			glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->diffuse.x));
			glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x));
			glMaterialf(GL_FRONT, GL_SHININESS, _material->shininess);
		}
		glEnd();

		glPopMatrix();
	}
}