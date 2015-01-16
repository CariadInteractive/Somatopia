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
    //set up vidToggle button
    vidToggle = StateButton(50, 50, 50, 50, "null");
    vidToggle.setCol(ofColor(getSharedData().pallete[0]));
}

void OptionsState::update() {
    getSharedData().cam.update(); //update camera
    if(getSharedData().cam.isFrameNew()); { //check if camera frame is new
        getSharedData().colImg.setFromPixels(getSharedData().cam.getPixels(), 320, 240); //set colImg from pixelss from video grabber
        getSharedData().colImg.mirror(false, true); //mirror image
        getSharedData().grayImage = getSharedData().colImg; //set grey image to be the same as colImg (it stays grey because we initialized it like that in testApp.cpp)
        if(getSharedData().bLearnBackground) { //check if we need to learn the background
            getSharedData().grayBg = getSharedData().grayImage; //set background equal to the grey image
            getSharedData().bLearnBackground = false; //don't update background again until told to do so
        }
    }
}

void OptionsState::draw() {
    ofSetColor(255);
    /*vid Toggle button*/
    vidToggle.display(); //draw the vidToggle button
    if(getSharedData().bVidOn) getSharedData().futura.drawString("Video On", 100 + getSharedData().futura.getStringBoundingBox(" ", 0, 0).getWidth(), 100); //draw name of vidToggle button when vid On
    else getSharedData().futura.drawString("Video Off", 100 + getSharedData().futura.getStringBoundingBox(" ", 0, 0).getWidth(), 100); //draw name of vidToggle button when vid OFf
    
    /*draw current color frame on left*/
    getSharedData().colImg.draw(0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
    /*"draw background frame on right*/
    getSharedData().grayBg.draw(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
    /*draw the debug if it is toggled on*/
    getSharedData().drawDebug();
    /*draw the title of the page*/
    getSharedData().futura.drawString("Options", ofGetWidth()/2 - getSharedData().futura.getStringBoundingBox("Options", 0, 0).getWidth()/2, getSharedData().futura.getStringBoundingBox("Options", 0, 0).getHeight());
    /*lables for camera and background*/
    getSharedData().futura.drawString("Camera Input", ofGetWidth()/4 - getSharedData().futura.getStringBoundingBox("Camera Input", 0, 0).getWidth()/2, ofGetHeight()/2/* - getSharedData().futura.getStringBoundingBox("Camera Input", 0, 0).getHeight()/2*/);
    getSharedData().futura.drawString("Background Image", ofGetWidth()*3/4 - getSharedData().futura.getStringBoundingBox("Background Image", 0, 0).getWidth()/2, ofGetHeight()/2/* - getSharedData().futura.getStringBoundingBox("Camera Input", 0, 0).getHeight()/2*/);
}

void OptionsState::keyPressed(int key) {
    if(key == 's') {
        changeState("splash"); //return to main page
    }
    //handle global functions, see Shared Data.cpp for how each works
    getSharedData().handleDebug(key);
    getSharedData().handleBackground(key);
    getSharedData().handleThreshold(key);
}

void OptionsState::mousePressed(int x, int y, int button) {
    if(x < ofGetWidth() && x > ofGetWidth()/2 && y > ofGetHeight()/2 && y < ofGetHeight()) {
        getSharedData().bLearnBackground = true; //change background
    }
    if(vidToggle.isInside(x, y)) {
        getSharedData().bVidOn = !getSharedData().bVidOn; //toggle video
    }
}

string OptionsState::getName() {
    return "options";
}