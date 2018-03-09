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
	TEXT = 2
};


struct Image
{
	ofImage drawable;

	int x;
	int y;

	int w;
	int h;

	Image(const ofImage &image, int x, int y, int w, int l) : drawable(image), x(x), y(y), w(w), h(h) {	}
};

struct Model
{
	ofNode drawable;

	int x;
	int y;
	int z;

	Model(const ofNode &model, int x, int y, int z) : drawable(model), x(x), y(y), z(z) { }
};

struct Text
{
	ofTrueTypeFont drawable;
	std::string text;

	int x;
	int y;

	int s;

	Text(const ofTrueTypeFont &font, const std::string &text, int x, int y, int s) : drawable(font), text(text), x(x), y(y), s(s) { }
};

struct Drawable
{
	ofColor color;
	DrawableType type;
	std::string name;

	union
	{
		Image image;
		Model model;
		Text text;
	};

	Drawable(const Drawable &c);
	Drawable(const ofNode &model, const std::string &name, int x, int y, int z);
	Drawable(const ofImage &image, const std::string &name, int x, int y, int w, int h);
	Drawable(const ofTrueTypeFont &font, const std::string &text, const std::string &name, int x, int y, int s);

	~Drawable();
};

class Scene
{
	public:
		Scene();
		~Scene();

		const std::list<Drawable> &getGraph();

		void drawScene();
		void drawImages();

		void addVertex(ofMesh mesh);
		Drawable *getDrawable(const std::string &name);
		void addDrawable(const Drawable &drawable);
		bool eraseDrawable(const std::string &name);

		std::string typeToString(DrawableType type);

	private:
		std::list<Drawable> graph;
};

