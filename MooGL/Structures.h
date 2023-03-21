#pragma once

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat	x, y, z;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct Mesh
{
	Vertex* Vertices;
	Color* Colors;
	GLushort* Indices;
	int VertexCount, ColorCount, IndexCount;
};
