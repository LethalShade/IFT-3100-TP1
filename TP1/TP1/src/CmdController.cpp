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

	if (parsedCommand[0] == "cdir")
		return (currentDir());

	if (parsedCommand[0] == "load")
		if (parsedCommand.size() == 4)
			return (loadImage(parsedCommand[1], stoi(parsedCommand[2]), stoi(parsedCommand[3])));
		else
			return (loadImage(parsedCommand[1]));

	if (parsedCommand[0] == "scene")
		return (printScene());

	return (false);
}

bool CmdController::currentDir()
{
	WCHAR pBuf[512];

	int bytes = GetModuleFileName(NULL, (LPWSTR)&pBuf, 512);
	if (bytes == 0)
		return -1;

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

bool CmdController::printScene()
{
	std::list<Drawable> graph = scene.getGraph();

	std::cout << "| ";
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		std::string type = scene.typeToString(it->type);
		std::cout << type << ": " << it->name << " | ";
	}

	return (true);
}

bool CmdController::changeColor(int id)
{
	return (true);
}

bool CmdController::printText()
{
	return (true);
}

bool CmdController::loadImage(const std::string &path, int x, int y)
{
	std::ostringstream oss;
	ofImage newImage;
	ofFile file;

	std::string absPath = ofFilePath::getAbsolutePath(path);

	file.open(absPath);
	//file.open(path);

	if (!file.exists())
		return (false);

	newImage.load(path);
		
	oss << ofFilePath::getBaseName(path) << x << y;

	Drawable newDrawable(newImage, oss.str(), x, y);

	scene.addDrawable(newDrawable);

	return (true);
}

std::vector<std::string> CmdController::parseBuffer()
{
	std::vector<std::string> parsedCommand;

	/*for (int i = 0; i < buffer.length(); i++)
	{
		int separator = buffer.find(' ', i);

		if (separator == string::npos)
			separator = buffer.length();

		parsedCommand.push_back(buffer.substr(i, separator - i));

		i = separator;
	}*/

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