#pragma once
#include "Structures.h"
#include <iostream>
#include <iomanip>

#define WIDTH 2

class SceneGraph
{
	public:
		SceneGraph();
		~SceneGraph();

		Node* newNode(std::string data);
		Node* addSibling(Node* n, std::string data);
		Node* addChild(Node* n, std::string data);
		void traverseTree(Node* root);

	private:
		bool treeStarted, treeFinished;
};