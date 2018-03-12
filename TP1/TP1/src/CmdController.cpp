#include "CmdController.h"

CmdController::CmdController() : type(S2D), currentId(0)
{
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
	if (buffer.empty())
		return (false);

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

	if (parsedCommand[0] == "select" && parsedCommand.size() == 2)
		return (select(parsedCommand[1]));

	if (parsedCommand[0] == "load" && parsedCommand.size() > 2 && parsedCommand[1] == "image")
		if (parsedCommand.size() == 5)
			return (loadImage(parsedCommand[2], stoi(parsedCommand[3]), stoi(parsedCommand[4])));
		else if (parsedCommand.size() == 3)
			return (loadImage(parsedCommand[2]));

	if (parsedCommand[0] == "load" && parsedCommand.size() > 2 && parsedCommand[1] == "model")
		if (parsedCommand.size() == 5)
			return (loadModel(parsedCommand[2], stoi(parsedCommand[3]), stoi(parsedCommand[4])));
		else if (parsedCommand.size() == 3)
			return (loadModel(parsedCommand[2]));

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
		return (makePremadeEllipse());

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

	if (parsedCommand[0] == "capture" && parsedCommand.size() == 2)
		return (captureScreen(parsedCommand[1]));

	if (parsedCommand[0] == "faces" && parsedCommand.size() == 2)
		return (renderFaces(parsedCommand[1]));

	if (parsedCommand[0] == "wireframe" && parsedCommand.size() == 2)
		return (renderWireFrame(parsedCommand[1]));

	if (parsedCommand[0] == "vertices" && parsedCommand.size() == 2)
		return (renderVertices(parsedCommand[1]));

	return (false);
}

bool CmdController::currentDir()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	WCHAR pBuf[512];

	int bytes = GetModuleFileNameW(NULL, (LPWSTR)&pBuf, 512);
	if (bytes == 0)
		return false;

	std::wstring sBuf(pBuf);

	std::wcout << sBuf << std::endl;
	return (true);
#endif
	return (false);
}

void CmdController::draw()
{
	DrawableObject *selectionRectangle = scene.getSelectionRectangle();

	//if (type == S2D)
		scene.drawImages();
	//else
		scene.drawScene();

	if (selectionRectangle->x != -1 && selectionRectangle->y != -1)
	{
		ofSetColor(ofColor(255, 0, 0, 98));
		ofDrawRectangle(selectionRectangle->x, selectionRectangle->y, selectionRectangle->w, selectionRectangle->h);
	}
}

bool CmdController::changeType(SceneType type)
{
	this->type = type;
	return (true);
}

bool CmdController::printScene()
{
	std::list<DrawableObject> graph = scene.getGraph();

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
	DrawableObject *drawable = scene.getDrawable(name);

	if (drawable == NULL)
		return (false);

	drawable->color = ofColor::black;

	return (true);
}

bool CmdController::changeFillColorListener(const void *sender, ofColor &color)
{
	std::list<DrawableObject *> selected = scene.getSelected();

	for (auto it = selected.begin(); it != selected.end(); it++)
		(*it)->color = color;
	return (true);
}

bool CmdController::changeOutlineColorListener(const void *sender, ofColor &color)
{
	std::list<DrawableObject *> selected = scene.getSelected();

	for (auto it = selected.begin(); it != selected.end(); it++)
		if ((*it)->type == SHAPE)
			(*it)->shape.drawable.setStrokeColor(color);
	return (true);
}


bool CmdController::changeOutlineListener(const void *sender, int &width)
{
	std::list<DrawableObject *> selected = scene.getSelected();

	for (auto it = selected.begin(); it != selected.end(); it++)
		if ((*it)->type == SHAPE)
			(*it)->shape.drawable.setStrokeWidth(width);
	return (true);
}


bool CmdController::sizeUp()
{
	std::list<DrawableObject *> selected = scene.getSelected();

	for (auto it = selected.begin(); it != selected.end(); it++)
	{
		//resize(*it, (*it)->s < 100 ? (*it)->s + 0.01 : (*it)->s);
		resize(*it, 1.01);
	}
	return (true);
}


bool CmdController::sizeDown()
{
	std::list<DrawableObject *> selected = scene.getSelected();

	for (auto it = selected.begin(); it != selected.end(); it++)
	{
		//resize(*it, (*it)->s > 0 ? (*it)->s - 0.01 : (*it)->s);
		resize(*it, 0.99);
	}
	return (true);
}


bool CmdController::resize(DrawableObject *drawable, float scale)
{
	drawable->s *= scale;

	switch (drawable->type)
	{
	case IMAGE:
		drawable->image.drawable.resize(scale * drawable->w, scale * drawable->h);
		break;
	case PRIMITIVE:
		drawable->primitive.drawable.setScale(scale);
		break;
	case TEXT:
		drawable->text.drawable.loadFont("arial.ttf", drawable->text.s * scale);
		break;
	case SHAPE:
		drawable->shape.drawable.scale(scale, scale);
		break;
	case MODEL:
		drawable->model.drawable.setScale(scale, scale, scale);
	}
	return (true);
}

bool CmdController::rotateUp()
{
	std::list<DrawableObject *> selected = scene.getSelected();

	for (auto it = selected.begin(); it != selected.end(); it++)
		(*it)->r = (*it)->r + 0.5 >= 360 ? 0 : (*it)->r + 0.5;
	return (true);
}

bool CmdController::rotateDown()
{
	std::list<DrawableObject *> selected = scene.getSelected();

	for (auto it = selected.begin(); it != selected.end(); it++)
		(*it)->r = (*it)->r - 0.5 < 0 ? 359.5 : (*it)->r - 0.5;
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
	DrawableObject *drawable = scene.getDrawable(name);

	if (drawable == NULL)
		return (false);

	switch (drawable->type)
	{
	case IMAGE:
		drawable->x = x;
		drawable->y = y;
		break;
	case PRIMITIVE:
		drawable->x = x;
		drawable->y = y;
		drawable->z = z;
		drawable->primitive.drawable.setPosition(x, y, z);
		break;
	case TEXT:
		drawable->x = x;
		drawable->y = y;
		break;
	case SHAPE:
		drawable->x = x;
		drawable->y = y;
		break;
	case MODEL:
		drawable->x = x;
		drawable->y = y;
		drawable->z = z;
		drawable->primitive.drawable.setPosition(x, y, z);
		break;
	}
	return (true);
}

bool CmdController::transform(const std::string &name, int x, int y, int z)
{
	DrawableObject *drawable = scene.getDrawable(name);
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
		//drawable->image.drawable.rotate90(45);
		break;
	case PRIMITIVE:
		drawable->x = newX;
		drawable->y = newY;
		drawable->z = newZ;
		drawable->primitive.drawable.setPosition(newX, newY, newZ);
		break;
	case TEXT:
		drawable->x = newX;
		drawable->y = newY;
		break;
	case SHAPE:
		drawable->x = newX;
		drawable->y = newY;
		//drawable->shape.drawable.rotate(1, ofVec3f(0, 0, 1));
		break;
	case MODEL:
		drawable->x = newX;
		drawable->y = newY;
		drawable->z = newZ;
		drawable->model.drawable.setPosition(newX, newY, newZ);
	}
	return (true);
}

bool CmdController::transform(int x, int y, int z)
{
	std::list<DrawableObject *> selected = scene.getSelected();

	if (selected.size() == 0)
		return (false);

	for (auto it = selected.begin(); it != selected.end(); it++)
		transform((*it)->name, x, y, z);
	return (true);
}

bool CmdController::select(int x, int y)
{
	DrawableObject *drawable = scene.getDrawable(x, y);

	if (drawable == NULL)
		scene.unselectDrawable();
	else if (!drawable->selected)
		scene.selectDrawable(drawable);
	/*else
		scene.unselectDrawable(drawable);*/

	return (true);
}

bool CmdController::select(const std::string &name)
{
	DrawableObject *drawable = scene.getDrawable(name);

	if (drawable == NULL)
		return (false);

	if (!drawable->selected)
		scene.selectDrawable(drawable);
	else
		scene.unselectDrawable(drawable);

	return (true);
}

bool CmdController::extendZone(int x, int y)
{
	DrawableObject *selectionRectangle = scene.getSelectionRectangle();

	if (selectionRectangle->x == -1 || selectionRectangle->y == -1)
	{
		selectionRectangle->x = x;
		selectionRectangle->y = y;
	}
	else
	{
		selectionRectangle->w = x - selectionRectangle->x;
		selectionRectangle->h = y - selectionRectangle->y;
	}
	return (true);
}

bool CmdController::selectZone(int x, int y)
{
	DrawableObject *selectionRectangle = scene.getSelectionRectangle();

	scene.selectDrawable();

	selectionRectangle->x = -1;
	selectionRectangle->y = -1;
	selectionRectangle->w = -1;
	selectionRectangle->h = -1;
	return (true);
}

bool CmdController::printText(const std::string &text, int x, int y, int s)
{
	ofTrueTypeFont font;

	font.loadFont("arial.ttf", s);

	DrawableObject newDrawable(font, currentId++, text, "", x, y, s);

	newDrawable.getPosition = [](DrawableObject *drawable) { return (ofVec3f(drawable->x, drawable->y, drawable->z)); };

	scene.addDrawable(newDrawable, true);

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

	DrawableObject newDrawable(newImage, currentId++, oss.str(), x, y);

	newDrawable.getPosition = [](DrawableObject *drawable) { return (ofVec3f(drawable->x, drawable->y, drawable->z)); };

	scene.addDrawable(newDrawable, true);

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
	DrawableObject *drawable = scene.getDrawable(name);

	if (drawable == NULL || drawable->type != TEXT)
		return (false);

	drawable->text.s = s;

	drawable->text.drawable.loadFont("arial.ttf", s);

	return (true);
}

bool CmdController::resizePic(const std::string &name, int w, int h)
{
	DrawableObject *drawable = scene.getDrawable(name);

	if (drawable == NULL || drawable->type != IMAGE)
		return (false);

	drawable->w = w;
	drawable->h = h;

	return (true);
}

bool CmdController::makePremadeTriangle(int x, int y, int z, int w, int h)
{
	ofPath path;

	//path.triangle(x - x, y - y, (w / 2), -h, w, y - y);
	path.triangle(x - x, h, (w / 2), y - y, w, h);

	DrawableObject newDrawable(path, currentId++, "", x, y, w, h);

	newDrawable.getPosition = [](DrawableObject *drawable) { return (ofVec3f(drawable->x, drawable->y, drawable->z)); };

	scene.addDrawable(newDrawable, true);

	return (true);
}

bool CmdController::makePremadeRectangle(int x, int y, int z, int w, int h)
{
	ofPath path;

	path.rectangle(x - x, y - y, w, h);

	DrawableObject newDrawable(path, currentId++, "", x, y, w, h);

	newDrawable.getPosition = [](DrawableObject *drawable) { return (ofVec3f(drawable->x, drawable->y, drawable->z)); };

	scene.addDrawable(newDrawable, true);

	return (true);
}

bool CmdController::makePremadeEllipse(int x, int y, int z, int w, int h)
{
	ofPath path;

	//path.arc(x, y, 50, 50, 0, 360);

	path.ellipse(x - x, y - y, w, h);

	DrawableObject newDrawable(path, currentId++, "", x, y, w, h);

	newDrawable.getPosition = [](DrawableObject *drawable) { return (ofVec3f(drawable->x - (drawable->w / 2) * drawable->s, drawable->y - (drawable->h / 2) * drawable->s, drawable->z)); };
	//newDrawable.getPosition = [](Drawable *drawable) { return (ofVec3f(drawable->x, drawable->y, drawable->z)); };

	scene.addDrawable(newDrawable, true);

	return (true);
}

bool CmdController::makePremadeCube(int x, int y, int z)
{
	ofBoxPrimitive box;

	box.set(100);

	box.setPosition(x, y, z);

	DrawableObject newDrawable(box, currentId++, "");

	newDrawable.getPosition = [](DrawableObject *drawable) { return (ofVec3f(drawable->x, drawable->y, drawable->z)); };

	scene.addDrawable(newDrawable, true);

	return (true);
}

bool CmdController::makePremadeSphere(int x, int y, int z)
{
	ofSpherePrimitive sphere;

	sphere.setRadius(100);

	sphere.setPosition(x, y, z);

	DrawableObject newDrawable(sphere, currentId++, "");

	newDrawable.getPosition = [](DrawableObject *drawable) { return (ofVec3f(drawable->x, drawable->y, drawable->z)); };

	scene.addDrawable(newDrawable, true);

	return (true);
}

bool CmdController::makePremadeCone(int x, int y, int z)
{
	ofConePrimitive cone;

	cone.set(50, 100, 4, 4);

	cone.setPosition(x, y, z);

	DrawableObject newDrawable(cone, currentId++, "");

	newDrawable.getPosition = [](DrawableObject *drawable) { return (ofVec3f(drawable->x, drawable->y, drawable->z)); };

	scene.addDrawable(newDrawable, true);

	return (true);
}

bool CmdController::makePremadeCylinder(int x, int y, int z)
{
	ofCylinderPrimitive cylinder;

	cylinder.set(50, 100);

	cylinder.setPosition(x, y, z);

	DrawableObject newDrawable(cylinder, currentId++, "");

	newDrawable.getPosition = [](DrawableObject *drawable) { return (ofVec3f(drawable->x, drawable->y, drawable->z)); };

	scene.addDrawable(newDrawable, true);

	return (true);
}

bool CmdController::makePremadePlane(int x, int y, int z)
{
	ofPlanePrimitive plane;

	plane.set(640, 480);

	plane.setPosition(x, y, z);

	DrawableObject newDrawable(plane, currentId++, "");

	newDrawable.getPosition = [](DrawableObject *drawable) { return (ofVec3f(drawable->x, drawable->y, drawable->z)); };

	scene.addDrawable(newDrawable, true);

	return (true);
}

bool CmdController::captureScreen(const std::string &exportPath)
{
	ofImage screenshot;

	screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

	screenshot.save(exportPath);

	return (true);
}

bool CmdController::loadModel(const std::string &path, int x, int y, int z)
{
	ofxAssimpModelLoader newModel;
	ofFile file;

	std::string absPath = ofFilePath::getAbsolutePath(path);

	file.open(absPath);

	if (!file.exists())
		return (false);

	newModel.loadModel(path);

	newModel.setPosition(x, y, z);

	DrawableObject newDrawable(newModel, currentId++, "");

	newDrawable.getPosition = [](DrawableObject *drawable) { return (ofVec3f(drawable->x, drawable->y, drawable->z)); };

	scene.addDrawable(newDrawable, true);

	return (true);
}

bool CmdController::applyTexture(const std::string &path, const std::string &name)
{
	ofImage newImage;
	ofFile file;
	DrawableObject *drawable = scene.getDrawable(name);

	if (drawable == NULL || (drawable->type != PRIMITIVE && drawable->type != MODEL))
		return (false);

	std::string absPath = ofFilePath::getAbsolutePath(path);

	file.open(absPath);

	if (!file.exists())
	{
		DrawableObject *image = scene.getDrawable(path);

		if (image == NULL || image->type != IMAGE)
			return (false);

		newImage = image->image.drawable;
	}
	else
	{
		newImage.load(path);
	}

	drawable->primitive.texture = newImage.getTexture();

	return (true);
}

bool CmdController::renderFaces(const std::string &name)
{
	DrawableObject *drawable;

	drawable = scene.getDrawable(name);
	if (drawable == NULL || (drawable->type != MODEL && drawable->type != PRIMITIVE))
		return (false);

	if (drawable->type == MODEL)
		drawable->model.renderType = FACES;
	else
		drawable->primitive.renderType = FACES;

	return (true);
}

bool CmdController::renderWireFrame(const std::string &name)
{
	DrawableObject *drawable;

	drawable = scene.getDrawable(name);
	if (drawable == NULL || (drawable->type != MODEL && drawable->type != PRIMITIVE))
		return (false);

	if (drawable->type == MODEL)
		drawable->model.renderType = WIREFRAME;
	else
		drawable->primitive.renderType = WIREFRAME;

	return (true);
}

bool CmdController::renderVertices(const std::string &name)
{
	DrawableObject *drawable;

	drawable = scene.getDrawable(name);
	if (drawable == NULL || (drawable->type != MODEL && drawable->type != PRIMITIVE))
		return (false);

	if (drawable->type == MODEL)
		drawable->model.renderType = VERTICES;
	else
		drawable->primitive.renderType = VERTICES;

	return (true);
}
