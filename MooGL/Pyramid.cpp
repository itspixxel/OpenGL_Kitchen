#include "Pyramid.h"

Pyramid::Pyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

Pyramid::~Pyramid()
{

}

void Pyramid::Draw()
{
	if (m_mesh->Vertices != nullptr && m_mesh->Colors != nullptr && m_mesh->Indices != nullptr)
	{
		glPushMatrix();

		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation, 1.0f, 1.0f, 1.0f);

		glBegin(GL_TRIANGLES);

		for (int i = 0; i < 36; i++)
		{
			Vertex v = m_mesh->Vertices[m_mesh->Indices[i]];
			Color c = m_mesh->Colors[m_mesh->Indices[i]];
			glColor3f(c.r, c.g, c.b);
			glVertex3f(v.x, v.y, v.z);
		}
		glEnd();

		glPopMatrix();
	}
}

void Pyramid::Update()
{

}
