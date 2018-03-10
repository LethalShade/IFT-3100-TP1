#include "CmdController.h"

CmdController::CmdController()
{
	type = S2D;
}


CmdController::~CmdController()
{
}

const std::string &CmdController::getBuffer()
{
	return (buffer);
}

void CmdController::setBuffer(const std::string &newBuffer)
{
	buffer = newBuffer;
}

void CmdController::addChar(const char &c)
{
	buffer.push_back(c);
}

void CmdController::eraseLastChar()
{
	if (!buffer.empty())
		buffer.pop_back();
}

bool CmdController::execute()
{
	std::vector<std::string> parsedCommand = parseBuffer();
	
	std::cout << "[EXECUTION]: " << buffer << std::endl;
	buffer.clear();

	if (parsedCommand[0] == "2d" && parsedCommand.size() == 1)
		return (changeType(S2D));
	if (parsedCommand[0] == "3d" && parsedCommand.size() == 1)
		return (changeType(S3D));

	if (parsedCommand[0] == "tf")
		if (parsedCommand.size() == 5)
			return (transform(parsedCommand[1], stoi(parsedCommand[2]), stoi(parsedCommand[3]), stoi(parsedCommand[4])));
		else if (parsedCommand.size() == 4)
			return (transform(parsedCommand[1], stoi(parsedCommand[2]), stoi(parsedCommand[3])));

	if (parsedCommand[0] == "mv")
		if (parsedCommand.size() == 5)
			return (move(parsedCommand[1], stoi(parsedCommand[2]), stoi(parsedCommand[3]), stoi(parsedCommand[4])));
		else if (parsedCommand.size() == 4)
			return (move(parsedCommand[1], stoi(parsedCommand[2]), stoi(parsedCommand[3])));

	if (parsedCommand[0] == "color" && parsedCommand.size() == 3)
		return (changeColor(parsedCommand[1]));

	if (parsedCommand[0] == "cdir" && parsedCommand.size() == 1)
		return (currentDir());

	if (parsedCommand[0] == "rm" && parsedCommand.size() == 2)
		return (eraseElement(parsedCommand[1]));

	if (parsedCommand[0] == "load")
		if (parsedCommand.size() == 4)
			return (loadImage(parsedCommand[1], stoi(parsedCommand[2]), stoi(parsedCommand[3])));
		else if (parsedCommand.size() == 2)
			return (loadImage(parsedCommand[1]));

	if (parsedCommand[0] == "scene" && parsedCommand.size() == 1)
		return (printScene());

	if (parsedCommand[0] == "print")
		if (parsedCommand.size() == 5)
			return (printText(parsedCommand[1], stoi(parsedCommand[2]), stoi(parsedCommand[3]), stoi(parsedCommand[4])));
		else if (parsedCommand.size() == 4)
			return (printText(parsedCommand[1], stoi(parsedCommand[2]), stoi(parsedCommand[3])));
		else if (parsedCommand.size() == 2)
			return (printText(parsedCommand[1]));

	if (parsedCommand[0] == "size")
		if (parsedCommand.size() == 4)
			return (resizePic(parsedCommand[1], stoi(parsedCommand[2]), stoi(parsedCommand[3])));
		else if (parsedCommand.size() == 3)
			return (resizeText(parsedCommand[1], stoi(parsedCommand[2])));

	if (parsedCommand[0] == "exit")
		exit(1);

	if (parsedCommand[0] == "rectangle")
		return (makePremadeRectangle());

	if (parsedCommand[0] == "circle")
		return (makePremadeCircle());

	if (parsedCommand[0] == "triangle")
		return (makePremadeTriangle());


	if (parsedCommand[0] == "cube")
		return (makePremadeCube());

	if (parsedCommand[0] == "sphere")
		return (makePremadeSphere());

	if (parsedCommand[0] == "cone")
		return (makePremadeCone());

	if (parsedCommand[0] == "cylinder")
		return (makePremadeCylinder());

	if (parsedCommand[0] == "plane")
		return (makePremadePlane());

	if (parsedCommand[0] == "apply" && parsedCommand.size() == 3)
		return (applyTexture(parsedCommand[1], parsedCommand[2]));

	return (false);
}

bool CmdController::currentDir()
{
	WCHAR pBuf[512];

	int bytes = GetModuleFileNameW(NULL, (LPWSTR)&pBuf, 512);
	if (bytes == 0)
		return false;

	std::wstring sBuf(pBuf);

	std::wcout << sBuf << std::endl;
	return (true);
}

void CmdController::draw()
{
	if (type == S2D)
		scene.drawImages();
	else
		scene.drawScene();
}

bool CmdController::changeType(SceneType type)
{
	this->type = type;
	return (true);
}

bool CmdController::printScene()
{
	std::list<Drawable> graph = scene.getGraph();

	std::cout << "| ";
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		std::string type = scene.typeToString(it->type);
		std::cout << type << ": " << it->name << " | ";
	}
	std::cout << std::endl;

	return (true);
}

bool CmdController::changeColor(const std::string &name)
{
	Drawable *drawable = scene.getDrawable(name);

	if (drawable == NULL)
		return (false);

	drawable->color = ofColor::black;

	return (true);
}

bool CmdController::changeColorListener(const void *sender, ofColor &color)
{
	std::list<Drawable *> selected = scene.getSelected();

	for (auto it = selected.begin(); it != selected.end(); it++)
		(*it)->color = color;
	return (true);
}

bool CmdController::eraseElement(const std::string &name)
{
	return (scene.eraseDrawable(name));
}

bool CmdController::eraseSelected()
{
	return (scene.eraseDrawable());
}

bool CmdController::move(const std::string &name, int x, int y, int z)
{
	Drawable *drawable = scene.getDrawable(name);

	if (drawable == NULL)
		return (false);

	switch (drawable->type)
	{
	case IMAGE:
		drawable->x = x;
		drawable->y = y;
		break;
	case MODEL:
		drawable->x = x;
		drawable->y = y;
		drawable->z = z;
		drawable->model.drawable.setPosition(x, y, z);
		break;
	case TEXT:
		drawable->x = x;
		drawable->y = y;
		break;
	case SHAPE:
		drawable->x = x;
		drawable->y = y;
		drawable->shape.drawable.moveTo(x, y);
		break;
	}
	return (true);
}

bool CmdController::transform(const std::string &name, int x, int y, int z)
{
	Drawable *drawable = scene.getDrawable(name);
	int newX;
	int newY;
	int newZ;

	newX = drawable->x + x;
	newY = drawable->y + y;
	newZ = drawable->z + z;

	if (drawable == NULL)
		return (false);

	switch (drawable->type)
	{
	case IMAGE:
		drawable->x = newX;
		drawable->y = newY;
		break;
	case MODEL:
		drawable->x = newX;
		drawable->y = newY;
		drawable->z = newZ;
		drawable->model.drawable.setPosition(newX, newY, newZ);
		break;
	case TEXT:
		drawable->x = newX;
		drawable->y = newY;
		break;
	case SHAPE:
		drawable->x = newX;
		drawable->y = newY;
		drawable->shape.drawable.moveTo(newX, newY);
		break;
	}
	return (true);
}

bool CmdController::transform(int x, int y, int z)
{
	std::list<Drawable *> selected = scene.getSelected();

	for (auto it = selected.begin(); it != selected.end(); it++)
		transform((*it)->name, x, y, z);
	return (true);
}

bool CmdController::select(int x, int y)
{
	Drawable *drawable = scene.getDrawable(x, y);

	if (drawable == NULL)
		return (false);

	if (!drawable->selected)
		scene.selectDrawable(drawable);
	else
		scene.unselectDrawable(drawable);

	return (true);
}

bool CmdController::printText(const std::string &text, int x, int y, int s)
{
	ofTrueTypeFont font;

	font.loadFont("arial.ttf", s);

	Drawable newDrawable(font, text, "", x, y, s);

	scene.addDrawable(newDrawable);

	return (true);
}

bool CmdController::loadImage(const std::string &path, int x, int y, int w, int h)
{
	std::ostringstream oss;
	ofImage newImage;
	ofFile file;

	std::string absPath = ofFilePath::getAbsolutePath(path);

	file.open(absPath);

	if (!file.exists())
		return (false);

	newImage.load(path);
		
	oss << ofFilePath::getBaseName(path) << x << y;

	Drawable newDrawable(newImage, oss.str(), x, y, w, h);

	scene.addDrawable(newDrawable);

	return (true);
}

std::vector<std::string> CmdController::parseBuffer()
{
	std::vector<std::string> parsedCommand;

	for (int i = 0; i < buffer.length(); i++)
	{
		std::string word;
		bool inQuotes = false;
		for (int j = i; j < buffer.length(); j++)
		{
			if (buffer[j] == '"')
				inQuotes = !inQuotes;
			if (buffer[j] == ' ')
				if (!inQuotes)
				{
					i = j;
					break;
				}
			word.push_back(buffer[j]);
			if (j == buffer.length() - 1)
			{
				i = j;
				break;
			}
		}
		word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
		parsedCommand.push_back(word);
	}

	return (parsedCommand);
}

bool CmdController::resizeText(const std::string &name, int s)
{
	Drawable *drawable = scene.getDrawable(name);

	if (drawable == NULL || drawable->type != TEXT)
		return (false);

	drawable->text.s = s;

	drawable->text.drawable.loadFont("arial.ttf", s);

	return (true);
}

bool CmdController::resizePic(const std::string &name, int w, int h)
{
	Drawable *drawable = scene.getDrawable(name);

	if (drawable == NULL || drawable->type != IMAGE)
		return (false);

	drawable->image.w = w;
	drawable->image.h = h;

	return (true);
}

bool CmdController::makePremadeTriangle(int x, int y, int z)
{
	ofPath path;

	path.arc(x, y, x + 25, y - 50, x + 50, y);

	Drawable newDrawable(path, "", x, y);

	scene.addDrawable(newDrawable);

	return (true);
}

bool CmdController::makePremadeRectangle(int x, int y, int z)
{
	ofPath path;

	path.rectangle(x, y, 50, 50);

	Drawable newDrawable(path, "", x, y);

	scene.addDrawable(newDrawable);

	return (true);
}

bool CmdController::makePremadeCircle(int x, int y, int z)
{
	ofPath path;

	path.arc(x, y, 50, 50, 0, 360);

	Drawable newDrawable(path, "", x, y);

	scene.addDrawable(newDrawable);

	return (true);
}

bool CmdController::makePremadeCube(int x, int y, int z)
{
	ofBoxPrimitive box;

	box.set(100);

	x = ofGetWidth()*.2;

	y = ofGetHeight()*.75;

	box.setPosition(x, y, z);

	Drawable newDrawable(box, "SomeBox");

	scene.addDrawable(newDrawable);

	return (true);
}

bool CmdController::makePremadeSphere(int x, int y, int z)
{
	ofSpherePrimitive sphere;



	sphere.setRadius(100);

	x = ofGetWidth()*.2;

	y = ofGetHeight()*.75;

	sphere.setPosition(x, y, z);

	Drawable newDrawable(sphere, "SomeSphere");

	scene.addDrawable(newDrawable);

	return (true);
}

bool CmdController::makePremadeCone(int x, int y, int z)
{
	ofConePrimitive cone;

	cone.set(50, 100, 4, 4);

	x = ofGetWidth()*.2;

	y = ofGetHeight()*.75;

	cone.setPosition(x, y, z);

	Drawable newDrawable(cone, "SomeCone");

	scene.addDrawable(newDrawable);

	return (true);
}

bool CmdController::makePremadeCylinder(int x, int y, int z)
{
	ofCylinderPrimitive cylinder;

	cylinder.set(50, 100);

	x = ofGetWidth()*.2;

	y = ofGetHeight()*.75;

	cylinder.setPosition(x, y, z);

	Drawable newDrawable(cylinder, "SomeCylinder");

	scene.addDrawable(newDrawable);

	return (true);
}

bool CmdController::makePremadePlane(int x, int y, int z)
{
	ofPlanePrimitive plane;

	plane.set(640, 480);

	x = ofGetWidth()*.2;

	y = ofGetHeight()*.75;

	plane.setPosition(x, y, z);

	Drawable newDrawable(plane, "SomePlane");

	scene.addDrawable(newDrawable);

	return (true);
}

bool CmdController::applyTexture(const std::string &path, const std::string &name)
{
	ofImage newImage;
	ofFile file;
	Drawable *drawable = scene.getDrawable(name);

	if (drawable == NULL || drawable->type != MODEL)
		return (false);

	std::string absPath = ofFilePath::getAbsolutePath(path);

	file.open(absPath);

	if (!file.exists())
	{
		Drawable *image = scene.getDrawable(path);

		if (image == NULL || image->type != IMAGE)
			return (false);

		newImage = image->image.drawable;
	}
	else
	{
		newImage.load(path);
	}

	drawable->model.texture = newImage.getTexture();

	return (true);
}