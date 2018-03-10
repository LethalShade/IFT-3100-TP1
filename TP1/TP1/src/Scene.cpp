#include "Scene.h"

Drawable::Drawable(const Drawable &c) : color(c.color), name(c.name), type(c.type), selected(c.selected), x(c.x), y(c.y), z(c.z)
{
	switch (type)
	{
	case IMAGE:
		new (&this->image) Image(c.image.drawable, c.image.w, c.image.h);
		break;
	case MODEL:
		new (&this->model) Model(c.model.drawable);
		break;
	case TEXT:
		new (&this->text) Text(c.text.drawable, c.text.text, c.text.s);
		break;
	case SHAPE:
		new (&this->model) Shape(c.shape.drawable);
		break;
	}
}

Drawable::Drawable(const of3dPrimitive &model, const std::string &name) : name(name), type(MODEL), selected(false), x(model.getX()), y(model.getY()), z(model.getZ())
{
	//Model newModel(model, x, y, z);
	std::ostringstream oss;

	if (name.empty())
	{
		oss << "MDL" << this->x << this->y << this->z;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->model) Model(model);
	//this->model = newModel;
}

Drawable::Drawable(const ofImage &image, const std::string &name, int x, int y, int w, int h) : name(name), type(IMAGE), selected(false), x(x), y(y), z(-1)
{
	//Image newImage(image, x, y, w, h);
	std::ostringstream oss;

	if (name.empty())
	{
		oss << "IMG" << x << y << w << h;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->image) Image(image, w, h);
	//this->image = newImage;
}

Drawable::Drawable(const ofTrueTypeFont &font, const std::string &text, const std::string &name, int x, int y, int s) : name(name), type(TEXT), selected(false), x(x), y(y), z(-1)
{
	//Text newText(font, text, x, y, s);
	std::ostringstream oss;

	if (name.empty())
	{
		oss << text << x << y << s;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->text) Text(font, text, s);
	//this->text = newText;
}

Drawable::Drawable(const ofPath &path, const std::string &name, int x, int y) : name(name), type(SHAPE), selected(false), x(x), y(y), z(-1)
{
	//Model newModel(model, x, y, z);
	std::ostringstream oss;

	if (name.empty())
	{
		oss << "SHP" << x << y;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->shape) Shape(path);
	//this->model = newModel;
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
	case SHAPE:
		shape.~Shape();
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

const std::list<Drawable *> &Scene::getSelected()
{
	return (selected);
}

void Scene::drawScene()
{
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		ofSetColor(it->color);
		if (it->type == MODEL)
		{
			//it->model.texture.bind();
			it->model.drawable.draw();
			//it->model.texture.unbind();
		}
	}
}

void Scene::drawImages()
{
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		if (it->selected)
			ofSetColor(ofColor::red);
		else
			ofSetColor(it->color);
		if (it->type == IMAGE)
			if (it->image.w == -1 || it->image.h == -1)
				it->image.drawable.draw(it->x, it->y);
			else
				it->image.drawable.draw(it->x, it->y, it->image.w, it->image.h);
		if (it->type == TEXT)
			it->text.drawable.drawString(it->text.text, it->x, it->y);
		if (it->type == SHAPE)
			it->shape.drawable.draw(it->x, it->y);
	}
}

Drawable *Scene::getDrawable(const std::string &name)
{
	for (auto it = graph.begin(); it != graph.end(); it++)
		if (it->name == name)
			return (&(*it));
	return (NULL);
}

Drawable *Scene::getDrawable(int x, int y)
{
	for (auto it = graph.begin(); it != graph.end(); it++)
		switch (it->type)
		{
		case IMAGE:
			if ((x >= it->x && x <= it->x + it->image.drawable.getWidth()) && (y >= it->y && y <= it->y + it->image.drawable.getHeight()))
				return (&(*it));
			break;
		case MODEL:
			if (false)
				return (&(*it));
			break;
		case TEXT:
			if ((x >= it->x && x <= it->x + it->text.drawable.stringWidth(it->text.text)) && (y >= it->y - it->text.drawable.stringHeight(it->text.text) && y <= it->y))
				return (&(*it));
			break;
		case SHAPE:
			if (false)
				return (&(*it));
			break;
		}
	return (NULL);
}

void Scene::addDrawable(const Drawable &drawable)
{
	graph.push_back(drawable);
}

void Scene::selectDrawable(Drawable *drawable)
{
	drawable->selected = true;
	selected.push_back(drawable);
}

void Scene::selectDrawable(const std::string &name)
{
	for (auto it = graph.begin(); it != graph.end(); it++)
		if (it->name == name)
		{
			selectDrawable(&(*it));
		}
}

void Scene::unselectDrawable(Drawable *drawable)
{
	auto it = selected.begin();
	while (it != selected.end())
	{
		if ((*it) == drawable)
		{
			(*it)->selected = false;
			selected.erase(it++);
		}
		else
			++it;
	}
}

void Scene::unselectDrawable(const std::string &name)
{
	auto it = selected.begin();
	while (it != selected.end())
	{
		if ((*it)->name == name)
		{
			(*it)->selected = false;
			selected.erase(it++);
		}
		else
			++it;
	}
}

bool Scene::eraseDrawable()
{
	selected.clear();

	auto it = graph.begin();
	while (it != graph.end())
	{
		if (it->selected)
			graph.erase(it++);
		else
			++it;
	}

	return (true);
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
	case 3:
		return ("SHAPE");
	default:
		return ("UNKNOWN");
	}
}