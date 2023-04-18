#pragma once

#include "GL\freeglut.h"
#include <vector>

#ifndef _hStructs
#define _hStructs

	struct Vector3
	{
		float x, y, z;
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