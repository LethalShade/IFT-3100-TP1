#pragma once

#include <list>
#include "of3dPrimitives.h"
#include "of3dGraphics.h"
#include "ofImage.h"
#include "ofMain.h"

enum DrawableType 
{
	IMAGE = 0,
	MODEL = 1,
	TEXT = 2,
	SHAPE = 3
};


struct Image
{
	ofImage drawable;

	int w;
	int h;

	Image(const ofImage &image, int w, int l) : drawable(image), w(w), h(h) {	}
};

struct Model
{
	of3dPrimitive drawable;
	ofTexture texture;

	Model(const of3dPrimitive &model) : drawable(model) { }
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

struct Drawable
{
	ofColor color;
	DrawableType type;
	std::string name;
	bool selected;

	int x;
	int y;
	int z;

	union
	{
		Image image;
		Model model;
		Text text;
		Shape shape;
	};

	Drawable(const Drawable &c);
	Drawable(const of3dPrimitive &model, const std::string &name);
	Drawable(const ofImage &image, const std::string &name, int x, int y, int w, int h);
	Drawable(const ofTrueTypeFont &font, const std::string &text, const std::string &name, int x, int y, int s);
	Drawable(const ofPath &path, const std::string &name, int x, int y);

	~Drawable();
};

class Scene
{
	public:
		Scene();
		~Scene();

		const std::list<Drawable> &getGraph();
		const std::list<Drawable *> &getSelected();

		void drawScene();
		void drawImages();

		void addVertex(ofMesh mesh);
		Drawable *getDrawable(const std::string &name);
		Drawable *getDrawable(int x, int y);
		void addDrawable(const Drawable &drawable);

		void selectDrawable(Drawable *drawable);
		void selectDrawable(const std::string &name);

		void unselectDrawable(Drawable *drawable);
		void unselectDrawable(const std::string &name);
		
		bool eraseDrawable();
		bool eraseDrawable(const std::string &name);

		std::string typeToString(DrawableType type);

	private:
		std::list<Drawable> graph;
		std::list<Drawable *> selected;
};

