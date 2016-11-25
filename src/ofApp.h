#pragma once

#include "ofMain.h"
#include "ofxCv.h"
using namespace ofxCv;
using namespace cv;

//#include "ofxFaceTrackerThreaded.h"

#include "ofxFaceTrackerMulti.h"

class ofApp : public ofBaseApp {
public:
	void setup();
    void exit();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber vidGrabber;
    ofImage camImg;
    ofImage photoImg;
	//ofxFaceTrackerThreaded tracker;
   // ofxFaceTracker tracker;
    ofxFaceTrackerMulti multiTracker;
	
    ofImage thomas;
    
    int maxFaces;
};
