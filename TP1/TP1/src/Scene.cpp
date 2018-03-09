#include "Scene.h"

Drawable::Drawable(const Drawable &c) : type(c.type), name(c.name)
{
	switch (type)
	{
	case IMAGE:
		new (&this->image) Image(c.image.drawable, c.image.x, c.image.y, c.image.w, c.image.h);
		break;
	case MODEL:
		new (&this->model) Model(c.model.drawable, c.model.x, c.model.y, c.model.z);
		break;
	case TEXT:
		new (&this->text) Text(c.text.drawable, c.text.text, c.text.x, c.text.y, c.text.s);
		break;
	}
}

Drawable::Drawable(const ofNode &model, const std::string &name, int x, int y, int z) : name(name), type(MODEL)
{
	//Model newModel(model, x, y, z);
	std::ostringstream oss;

	if (name.empty())
	{
		oss << "MDL" << x << y << z;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->model) Model(model, x, y, z);
	//this->model = newModel;
}

Drawable::Drawable(const ofImage &image, const std::string &name, int x, int y, int w, int h) : name(name), type(IMAGE)
{
	//Image newImage(image, x, y, w, h);
	std::ostringstream oss;

	if (name.empty())
	{
		oss << "IMG" << x << y << w << h;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->image) Image(image, x, y, w, h);
	//this->image = newImage;
}

Drawable::Drawable(const ofTrueTypeFont &font, const std::string &text, const std::string &name, int x, int y, int s) : name(name), type(TEXT)
{
	//Text newText(font, text, x, y, s);
	std::ostringstream oss;

	if (name.empty())
	{
		oss << text << x << y << s;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->text) Text(font, text, x, y, s);
	//this->text = newText;
}

Drawable::~Drawable()
{
	switch (type)
	{
	case IMAGE:
		image.~Image();
		break;
	case MODEL:
		model.~Model();
		break;
	case TEXT:
		text.~Text();
		break;
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
	{
		ofSetColor(it->color);
		if (it->type == MODEL)
			it->model.drawable.draw();
	}
}

void Scene::drawImages()
{
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		ofSetColor(it->color);
		if (it->type == IMAGE)
			if (it->image.w == -1 || it->image.h == -1)
				it->image.drawable.draw(it->image.x, it->image.y);
			else
				it->image.drawable.draw(it->image.x, it->image.y, it->image.w, it->image.h);
		if (it->type == TEXT)
			it->text.drawable.drawString(it->text.text, it->text.x, it->text.y);
	}
}

Drawable *Scene::getDrawable(const std::string &name)
{
	for (auto it = graph.begin(); it != graph.end(); it++)
		if (it->name == name)
			return (&(*it));
	return (NULL);
}

void Scene::addDrawable(const Drawable &drawable)
{
	graph.push_back(drawable);
}

bool Scene::eraseDrawable(const std::string &name)
{
	for (auto it = graph.begin(); it != graph.end(); it++)
		if (it->name == name)
		{
			graph.erase(it);
			return (true);
		}
	return (false);
}

std::string Scene::typeToString(DrawableType type)
{
	switch (type)
	{
	case 0:
		return ("IMAGE");
	case 1:
		return ("MODEL");
	case 2:
		return ("TEXT");
	default:
		return ("UNKNOWN");
	}
}