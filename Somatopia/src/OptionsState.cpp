//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "OptionsState.h"

using namespace ofxCv;
using namespace cv;

void OptionsState::setup() {
    vidToggle = StateButton(50, 50, 50, 50, "CheckMark.png");
    vidToggle.setImage("CheckMark.png");
    //vidToggle.setCol(ofColor(getSharedData().pallete[0]));
    
    snapShot = StateButton(50, 110, 50, 50, "CheckMark.png");
    snapShot.setImage("CheckMark.png");
    //snapShot.setCol(ofColor(getSharedData().pallete[1]));
}

void OptionsState::update() {
#ifdef __arm__
    getSharedData().frame = getSharedData().cam.grab();
#elif __APPLE__
    getSharedData().cam.update();
    getSharedData().frame = toCv(getSharedData().cam.getPixelsRef());
#endif
    if(!getSharedData().frame.empty()) {
        cvtColor(getSharedData().frame, getSharedData().greyFrame, CV_BGR2GRAY);
        if(getSharedData().bLearnBackground)
        {
            getSharedData().greyBackground = getSharedData().greyFrame.clone();
            getSharedData().bLearnBackground = false;
        }
        absdiff(getSharedData().greyFrame, getSharedData().greyBackground, getSharedData().greyDiff);
        getSharedData().contourFinder.setThreshold(getSharedData().threshold);
        getSharedData().contourFinder.findContours(getSharedData().greyDiff);
        cv::threshold(getSharedData().greyDiff, getSharedData().greyDiff, getSharedData().threshold, 255, CV_THRESH_BINARY);
    }
}

void OptionsState::draw() {
    ofSetColor(255);
    vidToggle.display();
    
    if(getSharedData().bVidOn) getSharedData().futura.drawString("Video On", 100 + getSharedData().futura.getStringBoundingBox(" ", 0, 0).getWidth(), 100);
    else getSharedData().futura.drawString("Video Off", 100 + getSharedData().futura.getStringBoundingBox(" ", 0, 0).getWidth(), 100);
    
    snapShot.display();
    getSharedData().futura.drawString("Save Your Portrait!", 100 + getSharedData().futura.getStringBoundingBox(" ", 0, 0).getWidth(), 160);
    ofPopStyle();
    if(ofGetMousePressed() && snapShot.isInside(ofGetMouseX(), ofGetMouseY())) {
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofRect(snapShot.getX(), snapShot.getY(), snapShot.getW(), snapShot.getH() );
        ofPopStyle();
    }
    
    drawMat(getSharedData().frame, 0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
    drawMat(getSharedData().greyBackground, ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
    getSharedData().drawDebug();
    getSharedData().futura.drawString("Options", ofGetWidth()/2 - getSharedData().futura.getStringBoundingBox("Options", 0, 0).getWidth()/2, getSharedData().futura.getStringBoundingBox("Options", 0, 0).getHeight());
    getSharedData().futura.drawString("Camera Input", ofGetWidth()/4 - getSharedData().futura.getStringBoundingBox("Camera Input", 0, 0).getWidth()/2, ofGetHeight()/2/* - getSharedData().futura.getStringBoundingBox("Camera Input", 0, 0).getHeight()/2*/);
    getSharedData().futura.drawString("Background Image", ofGetWidth()*3/4 - getSharedData().futura.getStringBoundingBox("Background Image", 0, 0).getWidth()/2, ofGetHeight()/2/* - getSharedData().futura.getStringBoundingBox("Camera Input", 0, 0).getHeight()/2*/);
    getSharedData().futura.drawString("Mic Sensitivity: " + ofToString(getSharedData().micSensitivity), ofGetWidth()/2 + 50, 100);
    getSharedData().futura.drawString("Change with left and right arrow keys", ofGetWidth()/2 + 50, 150);
    getSharedData().futura.drawString("Sound Input Device: " + ofToString(getSharedData().soundDeviceId), ofGetWidth()*3/4 - getSharedData().futura.getStringBoundingBox("Sound Input Device", 0, 0).getWidth()/2, 200);
}

void OptionsState::keyPressed(int key) {
    if(key == OF_KEY_LEFT) {
        getSharedData().micSensitivity -= 0.05;
        if(getSharedData().micSensitivity < 0) getSharedData().micSensitivity = 0;
    } else if(key == OF_KEY_RIGHT) {
        getSharedData().micSensitivity += 0.05;
        if(getSharedData().micSensitivity > 1) getSharedData().micSensitivity = 1;
    } else if(key == '0') {
        getSharedData().soundDeviceId = 0;
        ofxJSONElement json;
        json.open("Settings.json");
        json["soundDeviceId"] = getSharedData().soundDeviceId;
        json.save("Settings.json");
    } else if(key == '1') {
        getSharedData().soundDeviceId = 1;
        ofxJSONElement json;
        json.open("Settings.json");
        json["soundDeviceId"] = getSharedData().soundDeviceId;
        json.save("Settings.json");
    } else if(key == '2') {
        getSharedData().soundDeviceId = 2;
        ofxJSONElement json;
        json.open("Settings.json");
        json["soundDeviceId"] = getSharedData().soundDeviceId;
        json.save("Settings.json");
    } else if(key == '3') {
        getSharedData().soundDeviceId = 3;
        ofxJSONElement json;
        json.open("Settings.json");
        json["soundDeviceId"] = getSharedData().soundDeviceId;
        json.save("Settings.json");
    } else if(key == '4') {
        getSharedData().soundDeviceId = 4;
        ofxJSONElement json;
        json.open("Settings.json");
        json["soundDeviceId"] = getSharedData().soundDeviceId;
        json.save("Settings.json");
    }
    else {
        getSharedData().handleDebug(key);
        getSharedData().handleBackground(key);
        getSharedData().handleThreshold(key);
    }
}

void OptionsState::mousePressed(int x, int y, int button) {
    if(x < ofGetWidth() && x > ofGetWidth()/2 && y > ofGetHeight()/2 && y < ofGetHeight()) {
        getSharedData().bLearnBackground = true;
    }
    if(vidToggle.isInside(x, y)) {
        getSharedData().bVidOn = !getSharedData().bVidOn;
    }
    if(snapShot.isInside(x, y)) {
        ofImage imageToSave;
        #ifdef __arm__
        getSharedData().frame = getSharedData().cam.grab();
        ofxCv::toOf(getSharedData().frame, imageToSave);
        #elif __APPLE__
        getSharedData().cam.update();
        imageToSave.setFromPixels(getSharedData().cam.getPixels(), getSharedData().cam.width, getSharedData().cam.height, OF_IMAGE_COLOR);
        #endif
        imageToSave.saveImage("portraits/image" + ofGetTimestampString() + ".jpg");
    }
    if(button == OF_MOUSE_BUTTON_RIGHT) {
        changeState("splash");
    }
}

string OptionsState::getName() {
    return "options";
}