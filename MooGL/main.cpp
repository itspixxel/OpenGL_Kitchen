#include "MooGL.h"
#include "SceneGraph.h"
#include "SceneManager.h"

SceneManager* sceneManager;
SceneGraph* tree;

void CreateSceneGraph();

int main(int argc, char* argv[])
{
	CreateSceneGraph();
	MooGL* game = new MooGL(argc, argv);
	return 0;
}

void CreateSceneGraph()
{
	std::cout << "SCENE GRAPH" << std::endl << std::endl;

	tree = new SceneGraph();

	Node* root = tree->newNode("main");
	Node* sceneManager = tree->addChild(root, "SceneManager");
	Node* glutCallbacks = tree->addChild(sceneManager, "GLUTCallbacks");
	Node* scene = tree->addSibling(glutCallbacks, "Scene");
	Node* structs = tree->addChild(sceneManager, "Structures");
	Node* sceneKitchen = tree->addChild(structs, "Cube");

	tree->traverseTree(root);
}