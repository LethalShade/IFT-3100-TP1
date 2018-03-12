#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	sliderBackgroundColor.set(ofColor::white);

	for (int i = 0; i < 42; i++)
	{
		int colorCode = 255 - (255 / 34) * (i + 1);


		background[i].circle(ofGetWidth() / 2, ofGetHeight() / 2, (i * 2 + 1) * (50 - 5 * (8 - i)));
		background[i].setColor(ofColor(colorCode, colorCode, colorCode, 255));
	}

	commandLine.setup(commandLineLabel, ofGetWidth());
	commandLine.setPosition(0, ofGetHeight() - commandLine.getHeight());

	currentlyPlacing = NONE;

	leftPanel.setup();
	rightPanel.setup("SampleText", "SampleText", ofGetWidth() - (leftPanel.getWidth() + 15), 0);
	
	sliderFillColor.setName("Fill Color");
	sliderFillColor.addListener(&cmd, &CmdController::changeFillColorListener);

	sliderOutlineWidthParameter.set("Outline Width", 0, 0, 10);
	sliderOutlineWidthParameter.addListener(&cmd, &CmdController::changeOutlineListener);

	sliderOutlineColor.setName("Outline Color");
	sliderOutlineColor.addListener(&cmd, &CmdController::changeOutlineColorListener);

	sliderBackgroundColor.setName("Background Color");
	sliderBackgroundColor.addListener(this, &ofApp::changeBackgroundListener);

	leftPanel.add(sliderBackgroundColor);

	rightPanel.add(sliderFillColor);
	rightPanel.add(sliderOutlineColor);
	rightPanel.add(sliderOutlineWidth.setup(sliderOutlineWidthParameter));

	drawTriangle.setName("Triangle");
	drawTriangle.set(false);
	drawTriangle.addListener(this, &ofApp::changeShapeListener);
	leftPanel.add(drawTriangle);

	drawRectangle.setName("Rectangle");
	drawRectangle.set(false);
	drawRectangle.addListener(this, &ofApp::changeShapeListener);
	leftPanel.add(drawRectangle);

	drawEllipse.setName("Ellipse");
	drawEllipse.set(false);
	drawEllipse.addListener(this, &ofApp::changeShapeListener);
	leftPanel.add(drawEllipse);

	drawCube.setName("Cube");
	drawCube.set(false);
	drawCube.addListener(this, &ofApp::changeShapeListener);
	leftPanel.add(drawCube);

	drawSphere.setName("Sphere");
	drawSphere.set(false);
	drawSphere.addListener(this, &ofApp::changeShapeListener);
	leftPanel.add(drawSphere);

	drawCylinder.setName("Cylinder");
	drawCylinder.set(false);
	drawCylinder.addListener(this, &ofApp::changeShapeListener);
	leftPanel.add(drawCylinder);

	drawCone.setName("Cone");
	drawCone.set(false);
	drawCone.addListener(this, &ofApp::changeShapeListener);
	leftPanel.add(drawCone);

	drawPlane.setName("Plane");
	drawPlane.set(false);
	drawPlane.addListener(this, &ofApp::changeShapeListener);
	leftPanel.add(drawPlane);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	for (int i = 41; i >= 0; i--)
	{
		ofSetColor(background[i].getFillColor());
		background[i].draw();
	}
	//ofSetColor(sliderColor);
	cmd.draw();
	leftPanel.draw();
	rightPanel.draw();
	commandLine.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	std::string label = commandLineLabel.get();
	if (isascii(key))
	{
		switch (key)
		{
		case (OF_KEY_BACKSPACE) :
			cmd.eraseLastChar();
			label.pop_back();
			std::cout << std::endl << cmd.getBuffer();
			break;
		case (OF_KEY_RETURN) :
			std::cout << std::endl;
			label.clear();
			if (!cmd.execute())
				std::cout << "[ERREUR]" << std::endl;
			break;
		case (OF_KEY_DEL) :
			cmd.eraseSelected();
			break;
		default :
			std::cout << (char)key;
			cmd.addChar((char)key);
			label.push_back((char)key);
		}
	}
	else
	{
		switch (key)
		{
		case (OF_KEY_UP):
			cmd.sizeUp();
			break;
		case (OF_KEY_DOWN):
			cmd.sizeDown();
			break;
		case (OF_KEY_RIGHT):
			cmd.rotateUp();
			break;
		case (OF_KEY_LEFT):
			cmd.rotateDown();
			break;
		}
	}
	commandLineLabel.set(label);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
	prevMouseX = x;
	prevMouseY = y;

	//std::cout << "Mouse(" << x << ", " << y << ")" << std::endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	switch (currentlyPlacing)
	{
	case NONE:
		if (!cmd.transform(x - prevMouseX, y - prevMouseY, 0))
			cmd.extendZone(x, y);
		break;
	default:
		cmd.transform(x - prevMouseX, y - prevMouseY, 0);
		break;
	/*case TRIANGLE:
		break;
	case RECTANGLE:
		break;
	case ELLIPSE:
		break;
	case CUBE:
		break;
	case SPHERE:
		break;
	case CYLINDER:
		break;
	case CONE:
		break;*/
	}
	prevMouseX = x;
	prevMouseY = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	if (button == OF_MOUSE_BUTTON_LEFT)
	{
		switch (currentlyPlacing)
		{
		case NONE:
			cmd.select(x, y);
			break;
		case TRIANGLE:
			cmd.makePremadeTriangle(x, y, 0);
			break;
		case RECTANGLE:
			cmd.makePremadeRectangle(x, y, 0);
			break;
		case ELLIPSE:
			cmd.makePremadeEllipse(x, y, 0);
			break;
		case CUBE:
			cmd.makePremadeCube(x, y, 0);
			break;
		case SPHERE:
			cmd.makePremadeSphere(x, y, 0);
			break;
		case CYLINDER:
			cmd.makePremadeCylinder(x, y, 0);
			break;
		case CONE:
			cmd.makePremadeCone(x, y, 0);
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	//currentlyPlacing = NONE;

	cmd.selectZone(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
	commandLine.setSize(w, commandLine.getHeight());

	for (int i = 0; i < 42; i++)
	{
		background[i].clear();
		background[i].circle(w / 2, h / 2, (i * 2 + 1) * (50 - 5 * (8 - i)));
	}
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

bool ofApp::changeBackgroundListener(const void *sender, ofColor &color)
{
	for (int i = 0; i < 42; i++)
	{
		int colorCodeR = sliderBackgroundColor.get().r - (sliderBackgroundColor.get().r / 34) * (i + 1);
		int colorCodeG = sliderBackgroundColor.get().g - (sliderBackgroundColor.get().g / 34) * (i + 1);;
		int colorCodeB = sliderBackgroundColor.get().b - (sliderBackgroundColor.get().b / 34) * (i + 1);;
		int colorCodeA = sliderBackgroundColor.get().a;

		background[i].setFillColor(ofColor(colorCodeR, colorCodeG, colorCodeB, colorCodeA));
	}
	return (true);
}

bool ofApp::changeShapeListener(const void *sender, bool &toggled)
{
	ofParameter<bool> *pSender = (ofParameter<bool>*)sender;

	if (pSender->getName() == "Triangle")
		changeShape(TRIANGLE);
	if (pSender->getName() == "Rectangle")
		changeShape(RECTANGLE);
	if (pSender->getName() == "Ellipse")
		changeShape(ELLIPSE);
	if (pSender->getName() == "Cube")
		changeShape(CUBE);
	if (pSender->getName() == "Sphere")
		changeShape(SPHERE);
	if (pSender->getName() == "Cylinder")
		changeShape(CYLINDER);
	if (pSender->getName() == "Cone")
		changeShape(CONE);
	if (pSender->getName() == "Plane")
		changeShape(PLANE);

	return (true);
}

void ofApp::changeShape(DrawableShape shape)
{
	switch (shape)
	{
	case TRIANGLE:
		if (currentlyPlacing == TRIANGLE)
		{
			currentlyPlacing = NONE;
			drawTriangle.setWithoutEventNotifications(false);
		}
		else
			currentlyPlacing = TRIANGLE;

		drawRectangle.setWithoutEventNotifications(false);
		drawEllipse.setWithoutEventNotifications(false);
		drawCube.setWithoutEventNotifications(false);
		drawSphere.setWithoutEventNotifications(false);
		drawCylinder.setWithoutEventNotifications(false);
		drawCone.setWithoutEventNotifications(false);
		drawPlane.setWithoutEventNotifications(false);

		break;
	case RECTANGLE:
		if (currentlyPlacing == RECTANGLE)
		{
			currentlyPlacing = NONE;
			drawRectangle.setWithoutEventNotifications(false);
		}
		else
			currentlyPlacing = RECTANGLE;

		drawTriangle.setWithoutEventNotifications(false);
		drawEllipse.setWithoutEventNotifications(false);
		drawCube.setWithoutEventNotifications(false);
		drawSphere.setWithoutEventNotifications(false);
		drawCylinder.setWithoutEventNotifications(false);
		drawCone.setWithoutEventNotifications(false);
		drawPlane.setWithoutEventNotifications(false);

		break;
	case ELLIPSE:
		if (currentlyPlacing == ELLIPSE)
		{
			currentlyPlacing = NONE;
			drawEllipse.setWithoutEventNotifications(false);
		}
		else
			currentlyPlacing = ELLIPSE;

		drawTriangle.setWithoutEventNotifications(false);
		drawRectangle.setWithoutEventNotifications(false);
		drawCube.setWithoutEventNotifications(false);
		drawSphere.setWithoutEventNotifications(false);
		drawCylinder.setWithoutEventNotifications(false);
		drawCone.setWithoutEventNotifications(false);
		drawPlane.setWithoutEventNotifications(false);

		break;
	case CUBE:
		if (currentlyPlacing == CUBE)
		{
			currentlyPlacing = NONE;
			drawCube.setWithoutEventNotifications(false);
		}
		else
			currentlyPlacing = CUBE;

		drawTriangle.setWithoutEventNotifications(false);
		drawRectangle.setWithoutEventNotifications(false);
		drawEllipse.setWithoutEventNotifications(false);
		drawSphere.setWithoutEventNotifications(false);
		drawCylinder.setWithoutEventNotifications(false);
		drawCone.setWithoutEventNotifications(false);
		drawPlane.setWithoutEventNotifications(false);

		break;
	case SPHERE:
		if (currentlyPlacing == SPHERE)
		{
			currentlyPlacing = NONE;
			drawSphere.setWithoutEventNotifications(false);
		}
		else
			currentlyPlacing = SPHERE;

		drawTriangle.setWithoutEventNotifications(false);
		drawRectangle.setWithoutEventNotifications(false);
		drawEllipse.setWithoutEventNotifications(false);
		drawCube.setWithoutEventNotifications(false);
		drawCylinder.setWithoutEventNotifications(false);
		drawCone.setWithoutEventNotifications(false);
		drawPlane.setWithoutEventNotifications(false);

		break;
	case CYLINDER:
		if (currentlyPlacing == CYLINDER)
		{
			currentlyPlacing = NONE;
			drawCylinder.setWithoutEventNotifications(false);
		}
		else
			currentlyPlacing = CYLINDER;

		drawTriangle.setWithoutEventNotifications(false);
		drawRectangle.setWithoutEventNotifications(false);
		drawEllipse.setWithoutEventNotifications(false);
		drawCube.setWithoutEventNotifications(false);
		drawSphere.setWithoutEventNotifications(false);
		drawCone.setWithoutEventNotifications(false);
		drawPlane.setWithoutEventNotifications(false);

		break;
	case CONE:
		if (currentlyPlacing == CONE)
		{
			currentlyPlacing = NONE;
			drawCone.setWithoutEventNotifications(false);
		}
		else
			currentlyPlacing = CONE;

		drawTriangle.setWithoutEventNotifications(false);
		drawRectangle.setWithoutEventNotifications(false);
		drawEllipse.setWithoutEventNotifications(false);
		drawCube.setWithoutEventNotifications(false);
		drawSphere.setWithoutEventNotifications(false);
		drawCylinder.setWithoutEventNotifications(false);
		drawPlane.setWithoutEventNotifications(false);

		break;
	case PLANE:
		if (currentlyPlacing == PLANE)
		{
			currentlyPlacing = NONE;
			drawPlane.setWithoutEventNotifications(false);
		}
		else
			currentlyPlacing = PLANE;

		drawTriangle.setWithoutEventNotifications(false);
		drawRectangle.setWithoutEventNotifications(false);
		drawEllipse.setWithoutEventNotifications(false);
		drawCube.setWithoutEventNotifications(false);
		drawSphere.setWithoutEventNotifications(false);
		drawCylinder.setWithoutEventNotifications(false);
		drawCone.setWithoutEventNotifications(false);

		break;
	default:
		currentlyPlacing = NONE;

		drawTriangle.setWithoutEventNotifications(false);
		drawRectangle.setWithoutEventNotifications(false);
		drawEllipse.setWithoutEventNotifications(false);
		drawCube.setWithoutEventNotifications(false);
		drawSphere.setWithoutEventNotifications(false);
		drawCylinder.setWithoutEventNotifications(false);
		drawCone.setWithoutEventNotifications(false);
		drawPlane.setWithoutEventNotifications(false);
		break;
	}
}