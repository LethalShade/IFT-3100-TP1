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

	bool currentDir();

	void draw();

	bool printScene();
	bool changeColor(int id);
	bool printText();
	bool loadImage(const std::string &path, int x = 0, int y = 0);
	bool unloadImage();

private:
	std::vector<std::string> parseBuffer();

	std::string buffer;

	Scene scene;
	SceneType type;
};

