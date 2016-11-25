#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
    ofSetLogLevel(OF_LOG_ERROR);
    ofSetFrameRate(30);
    vidGrabber.setDeviceID(0);
	vidGrabber.initGrabber(1280, 720);
    maxFaces = 2;
	multiTracker.setup(maxFaces,360,640);
    thomas.load("test2.png");
    camImg.allocate(360, 640, OF_IMAGE_COLOR);
}

void ofApp::exit() {
    multiTracker.exit();
}

void ofApp::update() {
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
	vidGrabber.update();
	if(vidGrabber.isFrameNew()) {
        for (int i = 0; i < camImg.getWidth(); i++) {
            for (int j = 0; j < camImg.getHeight(); j++) {
                camImg.setColor(i, j, vidGrabber.getPixels().getColor(i+459 , j+39) );
            }
        }
        camImg.mirror(0,1);
        multiTracker.update(toCv(camImg));
	}
    ofGetTimestampString();
}

void ofApp::draw() {
	camImg.draw(0, 0);
	for(int i=0; i< multiTracker.trackers_active.size(); i++){
        if(multiTracker.trackers_active[i]->getFound()) {
            ofMatrix4x4 rotMat = multiTracker.trackers_active[i]->getRotationMatrix();
            ofQuaternion quar = rotMat.getRotate();
            ofEnableAlphaBlending();
            float tomasSize = 85;
            float wd = tomasSize * multiTracker.trackers_active[i]->getScale();
            float ht = tomasSize * multiTracker.trackers_active[i]->getScale()*1.4;
            ofPushMatrix();
                ofTranslate(multiTracker.trackers_active[i]->getPosition().x , multiTracker.trackers_active[i]->getPosition().y );
                ofRotateY(ofRadToDeg(quar.y())*-2);
                ofRotateZ(ofRadToDeg(quar.z())*2);
                ofSetColor(255,255,255,250);
                thomas.setAnchorPercent(0.5, 0.83);
            thomas.draw(0, 0, wd, ht);
            ofPopMatrix();
            ofDisableAlphaBlending();
        }
    }
}

void ofApp::keyPressed(int key) {
     camImg.save("image.jpg");
}