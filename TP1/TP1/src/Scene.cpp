#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}


void Scene::drawScene()
{
	for (auto it = graph.begin(); it != graph.end(); it++)
		it->draw();
}