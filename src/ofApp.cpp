#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
    ofSetLogLevel(OF_LOG_ERROR);
    ofSetFrameRate(30);
//	ofSetVerticalSync(true);
//	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    vidGrabber.setDeviceID(0);
	vidGrabber.initGrabber(640, 480);
    maxFaces = 2;
	multiTracker.setup(maxFaces,640,480);
    
    thomas.load("test2.png");
//    thomas.load("train2.png");
//    thomas.setAnchorPercent(0.5, 0.42);
//    thomas.setAnchorPercent(0.5, 0.5);
    

    
}

void ofApp::exit() {
    multiTracker.exit();
}

void ofApp::update() {
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
	vidGrabber.update();
	if(vidGrabber.isFrameNew()) {
        camImg.setFromPixels(vidGrabber.getPixels());
        camImg.mirror(0,1);
        multiTracker.update(toCv(camImg));


	}
    ofGetTimestampString();
}

void ofApp::draw() {
//	ofSetColor(255);
	camImg.draw(0, 0);
//    photoImg.draw(0, 0);
    
//    thomas.setCompression(ofTexCompression compression)
	ofDrawBitmapString("camera", 10, 20);
  
    drawMat(multiTracker.buffer, 640, 0);
    ofDrawBitmapString("buffer with blocked out faces", 640, 20);

//    drawMat(multiTracker.buffer2, 640, 480);

    
    for(int i=0; i< multiTracker.trackers_active.size(); i++){
        multiTracker.trackers_active[i]->draw();
       
        if(multiTracker.trackers_active[i]->getFound()) {
            
            ofMatrix4x4 rotMat = multiTracker.trackers_active[i]->getRotationMatrix();
            ofQuaternion quar = rotMat.getRotate();
       
            
            
            ofEnableAlphaBlending();
            
            float tomasSize = 85;
//            float tomasSize = 40;
            
            float wd = tomasSize * multiTracker.trackers_active[i]->getScale();
            float ht = tomasSize * multiTracker.trackers_active[i]->getScale()*1.4;
//            float ht = tomasSize * multiTracker.trackers_active[i]->getScale();
            
            
            ofPushMatrix();
            
            ofTranslate(multiTracker.trackers_active[i]->getPosition().x , multiTracker.trackers_active[i]->getPosition().y );
//            ofRotateX(ofRadToDeg(quar.x())*-2);
            ofRotateY(ofRadToDeg(quar.y())*-2);
            ofRotateZ(ofRadToDeg(quar.z())*2);
            
            ofSetColor(255,255,255,250);
            
            thomas.setAnchorPercent(0.5, 0.83);
//            thomas.setAnchorPercent(0.5, 0.45);

            thomas.draw(0, 0, wd, ht);
            ofPopMatrix();
            ofDisableAlphaBlending();
            

        }
       
    }
    

    
}

void ofApp::keyPressed(int key) {

     camImg.save("image.jpg");
}