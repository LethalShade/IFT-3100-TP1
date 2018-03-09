#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	font.loadFont("arial.ttf", 32);
}

//--------------------------------------------------------------
void ofApp::update()
{
	//scene.drawScene();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//font.drawString("hi!!", 100, 100);
	cmd.draw();
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

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

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
