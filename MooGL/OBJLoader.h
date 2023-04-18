#pragma once

#ifndef _OBJLoader
#define _OBJLoader

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include "GL\freeglut.h"

#ifndef _hStructs
#include "Structures.h"
#endif

namespace OBJLoader
{
	OBJMesh* LoadOBJ(char* path);
};

#endif //!_OBJLoader