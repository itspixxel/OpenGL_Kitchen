#pragma once

#include "GL\freeglut.h"

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

	struct Mesh
	{
		Vertex* indexedVertices;
		//Color* indexedColors;
		Vector3* indexedNormals;
		GLushort* indices;
		TexCoord* texCoords;
		int numVertices, numNormals, numIndices, numTexCoords;
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