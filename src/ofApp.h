#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxSoftKeyboard.h"

using namespace ofxCv;
using namespace cv;

//#include "ofxFaceTrackerThreaded.h"

#include "ofxFaceTrackerMulti.h"

class ofApp : public ofBaseApp {
public:
	void setup();
    void exit();
	void update();
	void keyPressed(int key);
    void keyReleased(int key);
    
    void draw();
    void drawCam();
    void drawEmail();
    void drawCounting();
    void drawVideo();
    
	ofVideoGrabber vidGrabber;
    ofImage camImg;
    ofImage photoImg;
	//ofxFaceTrackerThreaded tracker;
   // ofxFaceTracker tracker;
    ofxFaceTrackerMulti multiTracker;
	
    ofImage tmpImage;
    ofImage thomas;
    ofImage countingImg[5];
    ofxSoftKeyboard keyboard;
    ofVideoPlayer thomasVideo;
    
    
    ofTrueTypeFont 	font;
    
    bool countingEnable;
    float countingTime;
    float startTime;
    
    char eventString[255];
    string message;
    
    int maxFaces;
};
