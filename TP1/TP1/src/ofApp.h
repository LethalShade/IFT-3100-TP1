#pragma once

#include "CmdController.h"
#include "ofxGui.h"
#include "ofxGuiGroup.h"

enum DrawableShape
{
	NONE = -1,
	TRIANGLE = 0,
	RECTANGLE = 1,
	ELLIPSE = 2,
	CUBE = 3,
	SPHERE = 4,
	CYLINDER = 5,
	CONE = 6,
	PLANE = 7
};

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	bool changeBackgroundListener(const void *sender, ofColor &color);

	bool changeShapeListener(const void *sender, bool &color);
	void changeShape(DrawableShape shape);

private:

	ofxLabel commandLine;
	ofParameter<std::string> commandLineLabel;

	DrawableShape currentlyPlacing;

	ofPath background[42];

	CmdController cmd;

	ofxPanel leftPanel;
	ofxPanel rightPanel;

	ofxColorSlider cSlider;

	ofParameter<ofColor> sliderFillColor;

	ofxIntSlider sliderOutlineWidth;
	ofParameter<int> sliderOutlineWidthParameter;

	ofParameter<ofColor> sliderOutlineColor;

	ofParameter<ofColor> sliderBackgroundColor;

	ofxGuiGroup image;

	ofParameter<bool> drawTriangle;

	ofParameter<bool> drawRectangle;

	ofParameter<bool> drawEllipse;

	ofParameter<bool> drawCube;

	ofParameter<bool> drawSphere;

	ofParameter<bool> drawCylinder;

	ofParameter<bool> drawCone;

	ofParameter<bool> drawPlane;

	int prevMouseX;
	int prevMouseY;
};
