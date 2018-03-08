#pragma once

#include <list>
#include "of3dPrimitives.h"
#include "of3dGraphics.h"
#include "ofImage.h"

class Scene
{
	public:
		Scene();
		~Scene();

		void drawScene();

	private:
		std::list<ofNode> graph;
};

