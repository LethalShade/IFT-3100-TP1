#pragma once

#include <list>
#include "of3dPrimitives.h"
#include "of3dGraphics.h"
#include "ofImage.h"

enum DrawableType 
{
	IMAGE = 0,
	MODEL = 1
};

struct Drawable
{
	DrawableType type;
	std::string name;
	int x = 0;
	int y = 0;
	int z = 0;

	ofNode model;
	ofImage image;

	Drawable(const ofNode &model, const std::string &name, int x, int y, int z);
	Drawable(const ofImage &image, const std::string &name, int x, int y);
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
		void addDrawable(const Drawable &drawable);

		std::string typeToString(DrawableType type);

	private:
		std::list<Drawable> graph;
};

