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
	Node* glutCallbacks = tree->addChild(root, "GLUTCallbacks");
	Node* sceneManager = tree->addChild(glutCallbacks, "Scene Manager");
	Node* scene = tree->addSibling(sceneManager, "Scene");
	Node* MooGL = tree->addChild(scene, "MooGL");
	Node* structs = tree->addChild(scene, "Structures");
	Node* texture2D = tree->addChild(structs, "Texture2D");
	Node* meshLoader = tree->addChild(texture2D, "Mesh Loader");
	Node* cube = tree->addChild(meshLoader, "Cube");

	tree->traverseTree(root);
}