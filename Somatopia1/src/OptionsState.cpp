//
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
    vidToggle.setCol(ofColor(getSharedData().pallete[0]));
}

void OptionsState::update() {
    getSharedData().cam.update();
    if(getSharedData().cam.isFrameNew()); {
        getSharedData().colImg.setFromPixels(getSharedData().cam.getPixels(), 320, 240);
        getSharedData().colImg.mirror(false, true);
        getSharedData().grayImage = getSharedData().colImg;
        if(getSharedData().bLearnBackground) {
            getSharedData().grayBg = getSharedData().grayImage;
            getSharedData().bLearnBackground = false;
        }
    }
}

void OptionsState::draw() {
    ofSetColor(255);
    vidToggle.display();
    
    if(getSharedData().bVidOn) getSharedData().futura.drawString("Video On", 100 + getSharedData().futura.getStringBoundingBox(" ", 0, 0).getWidth(), 100);
    else getSharedData().futura.drawString("Video Off", 100 + getSharedData().futura.getStringBoundingBox(" ", 0, 0).getWidth(), 100);
    
    getSharedData().colImg.draw(0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
    getSharedData().grayBg.draw(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
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