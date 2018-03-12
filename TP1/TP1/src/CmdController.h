#pragma once

#include <string>
#include <iostream>
#include "Scene.h"

class CmdController
{
	enum SceneType
	{
		S2D = 0,
		S3D = 1
	};

public:
	CmdController();
	~CmdController();

	const std::string &getBuffer();
	void setBuffer(const std::string &newBuffer);

	void addChar(const char &c);
	void eraseLastChar();
	
	bool execute();

	// Commandes de debug
	bool currentDir();

	// Commandes générales
	void draw();
	bool changeType(SceneType type);
	bool printScene();
	bool changeColor(const std::string &name);
	bool changeFillColorListener(const void *sender, ofColor &color);
	bool changeOutlineColorListener(const void *sender, ofColor &color);
	bool changeOutlineListener(const void *sender, int &width);
	bool sizeUp();
	bool sizeDown();
	bool resize(DrawableObject *drawable, float scale);
	bool rotateUp();
	bool rotateDown();
	bool eraseElement(const std::string &name);
	bool eraseSelected();
	bool move(const std::string &name, int x = -1, int y = -1, int z = -1);
	bool transform(const std::string &name, int x = -1, int y = -1, int z = -1);
	bool transform(int x, int y, int z);
	bool select(int x, int y);
	bool select(const std::string &name);
	bool extendZone(int x, int y);
	bool selectZone(int x, int y);
	bool captureScreen(const std::string &exportPath);

	// Commandes 2D
	bool printText(const std::string &text, int x = ofGetWidth() / 2, int y = ofGetHeight() / 2, int s = 32);
	bool loadImage(const std::string &path, int x = ofGetWidth() / 2, int y = ofGetHeight() / 2, int w = -1, int h = -1);
	bool resizeText(const std::string &name, int s = -1);
	bool resizePic(const std::string &name, int w = -1, int h = -1);
	bool makePremadeTriangle(int x = ofGetWidth() / 2 - 50, int y = ofGetHeight() / 2 - 50, int z = 0, int w = 100, int h = 100);
	bool makePremadeRectangle(int x = ofGetWidth() / 2 -50, int y = ofGetHeight() / 2 - 50, int z = 0, int w = 100, int h = 100);
	bool makePremadeEllipse(int x = ofGetWidth() / 2 -50, int y = ofGetHeight() / 2 - 50, int z = 0, int w = 100, int h = 100);

	// Commandes 3D
	bool makePremadeCube(int x = ofGetWidth() / 2, int y = ofGetHeight() / 2, int z = 0);
	bool makePremadeSphere(int x = ofGetWidth() / 2, int y = ofGetHeight() / 2, int z = 0);
	bool makePremadeCone(int x = ofGetWidth() / 2, int y = ofGetHeight() / 2, int z = 0);
	bool makePremadeCylinder(int x = ofGetWidth() / 2, int y = ofGetHeight() / 2, int z = 0);
	bool makePremadePlane(int x = ofGetWidth() / 2, int y = ofGetHeight() / 2, int z = 0);
	bool loadModel(const std::string &path, int x = ofGetWidth() / 2, int y = ofGetHeight() / 2, int z = 0);
	bool applyTexture(const std::string &path, const std::string &name);

	bool renderFaces(const std::string &name);
	bool renderWireFrame(const std::string &name);
	bool renderVertices(const std::string &name);

private:
	long int currentId;

	std::vector<std::string> parseBuffer();
	std::string buffer;

	Scene scene;
	SceneType type;
};

