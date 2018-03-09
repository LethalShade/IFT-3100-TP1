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
	bool eraseElement(const std::string &name);
	bool transform(const std::string &name, int x = -1, int y = -1, int z = -1);

	// Commandes 2D
	bool printText(const std::string &text, int x = 0, int y = 32, int s = 32);
	bool loadImage(const std::string &path, int x = 0, int y = 0, int w = -1, int h = -1);
	bool resizeText(const std::string &name, int s = -1);
	bool resizePic(const std::string &name, int w = -1, int h = -1);

	// Commandes 3D
	bool makePremadeCube(int x = 0, int y = 0, int z = 0);
	bool makePremadeCone(int x = 0, int y = 0, int z = 0);

private:
	std::vector<std::string> parseBuffer();
	std::string buffer;

	Scene scene;
	SceneType type;
};

