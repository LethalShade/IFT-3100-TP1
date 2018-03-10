#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	gui.setup();
	sliderColor.addListener(&cmd, &CmdController::changeColorListener);
	gui.add(cSlider.setup(sliderColor));


	test.setRadius(100);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	//font.drawString("hi!!", 100, 100);
	ofSetColor(sliderColor);
	test.draw();
	cmd.draw();
	gui.draw();
	//someImage.draw(100, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (isascii(key))
	{
		switch (key)
		{
		case (OF_KEY_BACKSPACE) :
			cmd.eraseLastChar();
			std::cout << std::endl << cmd.getBuffer();
			break;
		case (OF_KEY_RETURN) :
			std::cout << std::endl;
			if (!cmd.execute())
				std::cout << "[ERREUR]" << std::endl;
			break;
		case (OF_KEY_DEL) :
			cmd.eraseSelected();
			break;
		default :
			std::cout << (char)key;
			cmd.addChar((char)key);
		}
	}
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
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	cmd.transform(x - prevMouseX, y - prevMouseY, 0);

	prevMouseX = x;
	prevMouseY = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	if (button == OF_MOUSE_BUTTON_LEFT)
		cmd.select(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
