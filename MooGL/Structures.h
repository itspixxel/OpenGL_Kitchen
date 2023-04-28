#pragma once

#include "GL\freeglut.h"
#include <vector>
#include <math.h>
#include <string>

#ifndef _hStructs
#define _hStructs

struct Node
{
	std::string data;
	Node* left, * right;
};

enum SCENES
{
	SCENE_KITCHEN
};

struct Vector3
{
	float x, y, z;

	Vector3 operator+(const Vector3& other) const
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	Vector3 operator-(const Vector3& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	Vector3 operator*(float scalar) const
	{
		return { x * scalar, y * scalar, z * scalar };
	}

	Vector3 operator/(float scalar) const
	{
		return { x / scalar, y / scalar, z / scalar };
	}

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void normalize()
	{
		float mag = sqrt(x * x + y * y + z * z);

		x = x / mag;
		y = y / mag;
		z = z / mag;
	}

	Vector3 normalize(bool returnValue)
	{
		float mag = sqrt(x * x + y * y + z * z);

		float x = x / mag;
		float y = y / mag;
		float z = z / mag;

		return Vector3(x, y, z);
	}

	Vector3 crossProduct(Vector3 cross)
	{
		float x = (this->y * cross.z) - (this->z * cross.y);
		float y = (this->z * cross.x) - (this->x * cross.z);
		float z = (this->x * cross.y) - (this->y * cross.x);

		return Vector3(x, y, z);
	}

};

struct Vector4
{
	float x, y, z, w;

};

struct Camera
{
	Vector3 eye, center, up;
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat	x, y, z;
};

struct TexCoord
{
	GLfloat u, v;
};
struct Face
{
	GLint vertexIndex;
	GLint texCoordIndex;
	GLint normalIndex;
};

struct Mesh
{
	Vertex* indexedVertices;
	Vector3* indexedNormals;
	GLushort* indices;
	TexCoord* texCoords;
	int numVertices, numNormals, numIndices, numTexCoords;
};

struct OBJMesh
{
	std::vector<Vertex>vertices;
	std::vector<Vector3>normals;
	std::vector<TexCoord>texCoords;

	std::vector<Face> indices;
};

struct Lighting
{
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
};

struct Material
{
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
	GLfloat shininess;
};

#endif // !_hStructs