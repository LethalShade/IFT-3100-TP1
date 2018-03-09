#include "Scene.h"

Drawable::Drawable(const ofNode &model, const std::string &name, int x, int y, int z) : model(model), name(name), x(x), y(y), z(z), type(MODEL)
{
	std::ostringstream oss;

	if (name.empty())
	{
		oss << "MDL" << x << y << z;
		this->name = name;
	}
}

Drawable::Drawable(const ofImage &image, const std::string &name, int x, int y) : image(image), name(name), x(x), y(y), z(0), type(IMAGE)
{
	std::ostringstream oss;

	if (name.empty())
	{
		oss << "IMG" << x << y;
		this->name = name;
	}
}


Scene::Scene()
{
}


Scene::~Scene()
{
}

const std::list<Drawable> &Scene::getGraph()
{
	return (graph);
}

void Scene::drawScene()
{
	for (auto it = graph.begin(); it != graph.end(); it++)
		if (it->type == MODEL)
			it->model.draw();
}

void Scene::drawImages()
{
	for (auto it = graph.begin(); it != graph.end(); it++)
		if (it->type == IMAGE)
			it->image.draw(it->x, it->y);
}

void Scene::addDrawable(const Drawable &drawable)
{
	graph.push_back(drawable);
}

std::string Scene::typeToString(DrawableType type)
{
	switch (type)
	{
	case 0:
		return ("IMAGE");
	case 1:
		return ("MODEL");
	default:
		return ("UNKNOWN");
	}
}