#include "ofApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 640, 480, OF_WINDOW);
//    ofSetupOpenGL(&window, 600, 800, OF_WINDOW);
	ofRunApp(new ofApp());
}
