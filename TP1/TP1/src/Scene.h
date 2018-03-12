#pragma once

#include <list>
#include <functional>
#include "of3dPrimitives.h"
#include "of3dGraphics.h"
#include "ofImage.h"
#include "ofMain.h"
#include "ofMath.h"
#include "ofxAssimpModelLoader.h"

enum DrawableType
{
	IMAGE = 0,
	PRIMITIVE = 1,
	TEXT = 2,
	SHAPE = 3,
	MODEL = 4
};

enum RenderType
{
	FACES = 0,
	WIREFRAME = 1,
	VERTICES = 2
};


struct Image
{
	ofImage drawable;

	Image(const ofImage &image) : drawable(image) { }
};

struct Primitive
{
	of3dPrimitive drawable;
	ofTexture texture;

	RenderType renderType;

	Primitive(const of3dPrimitive &primitive) : drawable(primitive), renderType(FACES) { }
};

struct Text
{
	ofTrueTypeFont drawable;
	std::string text;

	int s;

	Text(const ofTrueTypeFont &font, const std::string &text, int s) : drawable(font), text(text), s(s) { }
};

struct Shape
{
	ofPath drawable;

	Shape(const ofPath &path) : drawable(path) { }
};

struct Model
{
	ofxAssimpModelLoader drawable;

	RenderType renderType;

	Model(const ofxAssimpModelLoader &model) : drawable(model), renderType(FACES) { }
};


struct DrawableObject
{
	ofColor color;
	DrawableType type;
	std::string name;
	bool selected;

	int x;
	int y;
	int z;

	int w;
	int h;
	int d;

	float s;
	float r;

	union
	{
		Image image;
		Primitive primitive;
		Text text;
		Shape shape;
		Model model;
	};

	DrawableObject(const DrawableObject &c);
	DrawableObject(const of3dPrimitive &primitive, int currentId, const std::string &name);
	DrawableObject(const ofImage &image, int currentId, const std::string &name, int x, int y);
	DrawableObject(const ofTrueTypeFont &font, int currentId, const std::string &text, const std::string &name, int x, int y, int s);
	DrawableObject(const ofPath &path, int currentId, const std::string &name, int x, int y, int w, int h);
	DrawableObject(const ofxAssimpModelLoader &model, int currentId, const std::string &name);

	~DrawableObject();

	std::function<ofVec3f(DrawableObject *)> getPosition;
};

class Scene
{
public:
	Scene();
	~Scene();

	const std::list<DrawableObject> &getGraph();
	const std::list<DrawableObject *> &getSelected();
	DrawableObject *getSelectionRectangle();

	void drawScene();
	void drawImages();

	DrawableObject *getDrawable(const std::string &name);
	DrawableObject *getDrawable(int x, int y);
	void addDrawable(const DrawableObject &drawable, bool select = false);

	void rotate(const DrawableObject &drawable);

	void selectDrawable();
	void selectDrawable(DrawableObject *drawable);
	void selectDrawable(const std::string &name);
	bool select3dDrawable(int x, int y, DrawableObject *drawable);

	void unselectDrawable();
	void unselectDrawable(DrawableObject *drawable);
	void unselectDrawable(const std::string &name);

	bool eraseDrawable();
	bool eraseDrawable(const std::string &name);

	std::string typeToString(DrawableType type);

private:
	std::list<DrawableObject> graph;
	std::list<DrawableObject *> selected;

	DrawableObject selectionRectangle;
};

