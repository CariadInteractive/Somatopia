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
    vidToggle = StateButton(50, 50, 50, 50, "null");
    vidToggle.setCol(ofColor(getSharedData().pallete[1]));
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
    
    drawMat(getSharedData().frame, 0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
    drawMat(getSharedData().greyBackground, ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
    getSharedData().drawDebug();
    getSharedData().futura.drawString("Options", ofGetWidth()/2 - getSharedData().futura.getStringBoundingBox("Options", 0, 0).getWidth()/2, getSharedData().futura.getStringBoundingBox("Options", 0, 0).getHeight());
    getSharedData().futura.drawString("Camera Input", ofGetWidth()/4 - getSharedData().futura.getStringBoundingBox("Camera Input", 0, 0).getWidth()/2, ofGetHeight()/2/* - getSharedData().futura.getStringBoundingBox("Camera Input", 0, 0).getHeight()/2*/);
    getSharedData().futura.drawString("Background Image", ofGetWidth()*3/4 - getSharedData().futura.getStringBoundingBox("Background Image", 0, 0).getWidth()/2, ofGetHeight()/2/* - getSharedData().futura.getStringBoundingBox("Camera Input", 0, 0).getHeight()/2*/);
}

void OptionsState::keyPressed(int key) {
    if(key == 's') {
        changeState("splash");
    }
    getSharedData().handleDebug(key);
    getSharedData().handleBackground(key);
    getSharedData().handleThreshold(key);
}

void OptionsState::mousePressed(int x, int y, int button) {
    if(x < ofGetWidth() && x > ofGetWidth()/2 && y > ofGetHeight()/2 && y < ofGetHeight()) {
        getSharedData().bLearnBackground = true;
    }
    if(vidToggle.isInside(x, y)) {
        getSharedData().bVidOn = !getSharedData().bVidOn;
    }
}

string OptionsState::getName() {
    return "options";
}