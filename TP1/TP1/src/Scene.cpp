#include "Scene.h"

DrawableObject::DrawableObject(const DrawableObject &c) : color(c.color), name(c.name), type(c.type), selected(c.selected), x(c.x), y(c.y), z(c.z), w(c.w), h(c.h), d(c.d), s(c.s), r(c.r), getPosition(c.getPosition)
{
	switch (type)
	{
	case IMAGE:
		new (&this->image) Image(c.image.drawable);
		break;
	case PRIMITIVE:
		new (&this->primitive) Primitive(c.primitive.drawable);
		break;
	case TEXT:
		new (&this->text) Text(c.text.drawable, c.text.text, c.text.s);
		break;
	case SHAPE:
		new (&this->shape) Shape(c.shape.drawable);
		break;
	case MODEL:
		new (&this->model) Model(c.model.drawable);
		break;
	}
}

DrawableObject::DrawableObject(const of3dPrimitive &primitive, int currentId, const std::string &name) : name(name), type(PRIMITIVE), selected(false), x(primitive.getX()), y(primitive.getY()), z(primitive.getZ()), h(-1), w(-1), d(-1), s(1), r(0)
{
	//Primitive newModel(primitive, x, y, z);
	std::ostringstream oss;

	if (name.empty())
	{
		oss << "PRM" << currentId;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->primitive) Primitive(primitive);
	//this->primitive = newModel;
}

DrawableObject::DrawableObject(const ofImage &image, int currentId, const std::string &name, int x, int y) : name(name), type(IMAGE), selected(false), x(x), y(y), z(-1), w(image.getWidth()), h(image.getHeight()), d(-1), s(1), r(0)
{
	//Image newImage(image, x, y, w, h);
	std::ostringstream oss;

	if (name.empty())
	{
		oss << "IMG" << currentId;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->image) Image(image);
	//this->image = newImage;
}

DrawableObject::DrawableObject(const ofTrueTypeFont &font, int currentId, const std::string &text, const std::string &name, int x, int y, int s) : name(name), type(TEXT), selected(false), x(x), y(y), z(-1), w(font.stringWidth(text)), h(font.stringHeight(text)), d(-1), s(1), r(0)
{
	//Text newText(font, text, x, y, s);
	std::ostringstream oss;

	if (name.empty())
	{
		oss << text << currentId;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->text) Text(font, text, s);
	//this->text = newText;
}

DrawableObject::DrawableObject(const ofPath &path, int currentId, const std::string &name, int x, int y, int w, int h) : name(name), type(SHAPE), selected(false), x(x), y(y), z(-1), w(w), h(h), d(-1), s(1), r(0)
{
	//Primitive newModel(primitive, x, y, z);
	std::ostringstream oss;

	if (name.empty())
	{
		oss << "SHP" << currentId;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->shape) Shape(path);
	//this->primitive = newModel;
}

DrawableObject::DrawableObject(const ofxAssimpModelLoader &model, int currentId, const std::string &name) : name(name), type(MODEL), selected(false), h(-1), w(-1), d(-1), s(1), r(0)
{
	//Primitive newModel(primitive, x, y, z);


	std::ostringstream oss;

	if (name.empty())
	{
		oss << "MDL" << currentId;
		this->name = oss.str();
	}

	color = ofColor::black;

	new (&this->model) Model(model);

	x = this->model.drawable.getPosition().x;
	y = this->model.drawable.getPosition().y;
	z = this->model.drawable.getPosition().z;
	//this->primitive = newModel;
}

DrawableObject::~DrawableObject()
{
	switch (type)
	{
	case IMAGE:
		image.~Image();
		break;
	case PRIMITIVE:
		primitive.~Primitive();
		break;
	case TEXT:
		text.~Text();
		break;
	case SHAPE:
		shape.~Shape();
		break;
	case MODEL:
		model.~Model();
	}
}

Scene::Scene() : selectionRectangle(ofPath(), -1, "", -1, -1, -1, -1)
{
}


Scene::~Scene()
{
}

const std::list<DrawableObject> &Scene::getGraph()
{
	return (graph);
}

const std::list<DrawableObject *> &Scene::getSelected()
{
	return (selected);
}

DrawableObject *Scene::getSelectionRectangle()
{
	return (&selectionRectangle);
}

void Scene::drawScene()
{
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		ofSetColor(it->color);
		if (it->type == PRIMITIVE)
		{
			//it->primitive.texture.bind();
			ofEnableDepthTest();
			if (it->primitive.renderType == FACES)
				it->primitive.drawable.drawFaces();
			if (it->primitive.renderType == WIREFRAME)
				it->primitive.drawable.drawWireframe();
			if (it->primitive.renderType == VERTICES)
				it->primitive.drawable.drawVertices();
			ofDisableDepthTest();
			//it->primitive.texture.unbind();
		}
		if (it->type == MODEL)
		{
			ofSetColor(ofColor::white);
			ofEnableDepthTest();
			if (it->model.renderType == FACES)
				it->model.drawable.drawFaces();
			if (it->model.renderType == WIREFRAME)
				it->model.drawable.drawWireframe();
			if (it->model.renderType == VERTICES)
				it->model.drawable.drawVertices();
			ofDisableDepthTest();
		}
	}
}

void Scene::drawImages()
{
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		ofVec3f vector = it->getPosition(&(*it));

		if (it->r != 0)
		{
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofPushMatrix();
			ofTranslate(vector.x + it->w / 2, vector.y + it->h / 2);
			//ofTranslate(it->x + it->w / 2, it->y + it->h / 2);
			ofRotateZ(it->r);
		}

		ofSetColor(it->color);
		if (it->type == IMAGE)
		{
			ofSetColor(ofColor(255, 255, 255, 255));
			//it->image.drawable.draw(it->x, it->y, it->w, it->h);
			if (it->r != 0)
				it->image.drawable.draw((it->x - vector.x) * it->s, (it->y - vector.y) * it->s, it->w * it->s, it->h * it->s);
			else
				it->image.drawable.draw(it->x, it->y, it->w * it->s, it->h * it->s);
		}
		if (it->type == TEXT)
			it->text.drawable.drawString(it->text.text, it->x, it->y);
		if (it->type == SHAPE)
		{
			it->shape.drawable.setFillColor(it->color);
			if (it->r != 0)
				it->shape.drawable.draw((it->x - vector.x) - (it->w / 2), (it->y - vector.y) - (it->h / 2));
			else
				it->shape.drawable.draw(it->x, it->y);
		}

		if (it->selected)
		{
			ofSetColor(ofColor(255, 0, 0, 128));
			if (it->r != 0)
				ofDrawRectangle(0, 0, it->w * it->s, it->h * it->s);
			else
				ofDrawRectangle(vector.x, vector.y, it->w * it->s, it->h * it->s);
		}
		if (it->r != 0)
		{
			ofSetRectMode(OF_RECTMODE_CORNER);
			ofPopMatrix();
		}
		//ofGetCurrentMatrix().
	}
}

DrawableObject *Scene::getDrawable(const std::string &name)
{
	for (auto it = graph.begin(); it != graph.end(); it++)
		if (it->name == name)
			return (&(*it));
	return (NULL);
}

DrawableObject *Scene::getDrawable(int x, int y)
{
	bool found = false;

	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		ofVec3f vector = it->getPosition(&(*it));

		/*if (it->r != 0)
		{
			ofPushMatrix();
			ofTranslate(vector.x, vector.y);
			ofRotateZ(it->r);
			vector = ofMatrix4x4::transform3x3(ofGetCurrentMatrix(OF_MATRIX_PROJECTION), vector);
		}*/

		switch (it->type)
		{
		case IMAGE:
			if ((x >= it->x && x <= it->x + it->image.drawable.getWidth() * it->s) && (y >= it->y && y <= it->y + it->image.drawable.getHeight() * it->s))
				found = true;
			break;
		case PRIMITIVE:
			if (false)
				found = true;
			break;
		case TEXT:
			if ((x >= it->x && x <= it->x + it->text.drawable.stringWidth(it->text.text)) && (y >= it->y - it->text.drawable.stringHeight(it->text.text) && y <= it->y))
				found = true;
			break;
		case SHAPE:
			if ((x >= vector.x && x <= vector.x + it->w * it->s) && (y >= vector.y && y <= vector.y + it->h * it->s))
				found = true;
			break;
		case MODEL:
			if (false)
				found = true;
		}

		/*if (it->r != 0)
		{
			ofPopMatrix();
		}*/

		if (found == true)
			return (&(*it));

	}
	return (NULL);
}

bool Scene::select3dDrawable(int mouseX, int mouseY, DrawableObject *drawable)
{
	float x = (2.0f * mouseX) / ofGetWidth() - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / ofGetHeight();
	float z = 1.0f;

	ofVec3f ray_nds = ofVec3f(x, y, z);

	ofVec4f ray_clip = ofVec4f(ray_nds.x, ray_nds.y, -1.0, 1.0);

	ofVec4f ray_eye = ofMatrix4x4::getInverseOf(ofCamera().getProjectionMatrix(ofGetCurrentViewport())) * ray_clip;

	ray_eye = ofVec4f(ray_eye.x, ray_eye.y, -1.0, 0.0);

	ofVec3f ray_wor = (ofMatrix4x4::getInverseOf(ofCamera().getModelViewMatrix()) * ray_eye);

	ray_wor = ray_wor.getNormalized();

	// Incomplet

	return (true);
}

void Scene::addDrawable(const DrawableObject &drawable, bool select)
{
	graph.push_back(drawable);
	if (select)
	{
		selected.push_back(&graph.back());
		selected.back()->selected = true;
	}
}

void Scene::rotate(const DrawableObject &drawable)
{
	//ofSetRectMode(OF_RECTMODE_CENTER);
	ofPushMatrix();
	ofTranslate(drawable.x, drawable.y);
	ofRotateZ(drawable.r);
	ofRect(0, 0, 20, 20);
	ofPopMatrix();
}

void Scene::selectDrawable()
{
	for (auto it = graph.begin(); it != graph.end(); it++)
	{

		int sourceX = selectionRectangle.w > 0 ? selectionRectangle.x : selectionRectangle.x + selectionRectangle.w;
		int sourceY = selectionRectangle.h > 0 ? selectionRectangle.y : selectionRectangle.y + selectionRectangle.h;

		int targetX = selectionRectangle.w < 0 ? selectionRectangle.x : selectionRectangle.x + selectionRectangle.w;
		int targetY = selectionRectangle.h < 0 ? selectionRectangle.y : selectionRectangle.y + selectionRectangle.h;

		if (it->x >= sourceX && it->x + it->w <= targetX && it->y >= sourceY && it->y + it->h <= targetY)
			selectDrawable(&(*it));
	}
}

void Scene::selectDrawable(DrawableObject *drawable)
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

void Scene::unselectDrawable()
{
	auto it = selected.begin();
	while (it != selected.end())
	{
		if ((*it)->type != PRIMITIVE && (*it)->type != MODEL)
		{
			(*it)->selected = false;
			selected.erase(it++);
		}
		else
			++it;
	}
}


void Scene::unselectDrawable(DrawableObject *drawable)
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
		return ("PRIMITIVE");
	case 2:
		return ("TEXT");
	case 3:
		return ("SHAPE");
	case 4:
		return ("MODEL");
	default:
		return ("UNKNOWN");
	}
}
