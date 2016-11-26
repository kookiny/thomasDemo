#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
    ofSetLogLevel(OF_LOG_ERROR);
    ofSetFrameRate(30);
    
//    ofEnableSmoothing();
//    ofEnableAntiAliasing();
//    
//    vidGrabber.setDeviceID(0);
//	vidGrabber.initGrabber(1280, 720);
//    maxFaces = 2;
//	multiTracker.setup(maxFaces,360,640);
    
    camImg.allocate(360, 640, OF_IMAGE_COLOR);
    tmpImage.allocate(1280, 720, OF_IMAGE_COLOR);
    
    thomas.load("test2.png");
    thomasVideo.load("TomasAtardecer02.mov");
    
    
    font.load("brothers.ttf", 25);
    countingEnable = false;
    
    for(int i = 0;i < 5; i++) {
        string file = "count" + ofToString(i+1) + ".png";
        countingImg[i].load(file);
    }
    
    keyboard.setup( this, OFXSK_LAYOUT_KEYBOARD_EMAIL,0.57);
//    keyboard.setScale(0.6);
    thomasVideo.play();
    
}

void ofApp::exit() {
    multiTracker.exit();
}

void ofApp::update() {
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    if(multiTracker.amtFound == 0){
        thomasVideo.update();
    }
    /*
	vidGrabber.update();
	if(vidGrabber.isFrameNew()) {
        
        ofPixels tmpPix = vidGrabber.getPixels();
        tmpImage.setFromPixels(tmpPix);
        camImg.cropFrom(tmpImage, 459, 39, camImg.getWidth(), camImg.getHeight());
        
        camImg.mirror(0,1);
        multiTracker.update(toCv(camImg));
	}
    */
    ofGetTimestampString();
    
//    printf("Found = %d",multiTracker.amtFound);
    
}
void ofApp::drawCam() {
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

void ofApp::drawEmail() {
    ofBackground(0);
    keyboard.draw(5, 400);
    font.drawString(message, 30, 200);
//    ofDrawBitmapString(message, 10, 200);
}

void ofApp::drawCounting() {
    ofBackground(0);
    if(countingEnable) {
        float elapsed = ofGetElapsedTimef() - startTime;
        if(elapsed > 5.999999) {
            countingEnable = false;
        } else if (elapsed > 4.999999){
            float alpha = (1 - elapsed + int(elapsed)) * 255;
            ofBackground(alpha);
        } else {
            ofImage num = countingImg[4-int(elapsed)];
            num.setAnchorPercent(0.5, 0.5);
            ofEnableAlphaBlending();
            float alpha = (1 - elapsed + int(elapsed)) * 255;
            ofSetColor(255,255,255,alpha);
            num.draw(ofGetWidth()/2,ofGetHeight()/2);
            ofDisableAlphaBlending();
        }
    }

    
}

void ofApp::drawVideo() {
    thomasVideo.draw(0,0,ofGetWidth(),ofGetHeight());
}

void ofApp::draw() {
    
//    drawEmail();

//    drawCounting();
    if(multiTracker.amtFound>0) {
        drawCam();
    } else {
        drawVideo();
    }
    
}

void ofApp::keyPressed(int key) {
    
    sprintf(eventString, "keyPressed = %c (ASCII %i)", key, key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
    sprintf(eventString, "keyReleased = %c (ASCII %i)", key, key);
    
    if(key == OF_KEY_BACKSPACE) {
        message = message.substr(0, message.size()-1);
    } else {
        message += (char)key;
    }
    if (key == '=') {
        countingEnable = true;
        startTime = ofGetElapsedTimef();
        countingTime = 5.0;
        
    }
    if (key == '\\') {
        thomasVideo.play();
    }
    cout<< "message = " << message <<endl;
}