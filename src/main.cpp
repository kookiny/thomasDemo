#include "ofApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 360, 640, OF_WINDOW);
//    ofSetupOpenGL(&window, 600, 800, OF_WINDOW);
	ofRunApp(new ofApp());
}
