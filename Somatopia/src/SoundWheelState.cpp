//
//  SoundWheel.cpp
//  Somatopia1
//
//  Created by James Bentley on 1/20/15.
//
//

#include "SoundWheelState.h"

void SoundWheelState::setup() {
    
    userIndex = (int)ofRandom(getSharedData().users.size());
    
    getSharedData().wheelCount = 0;
    
    col = getSharedData().pallete[2];
}

void SoundWheelState::stateEnter() {
    getSharedData().wheelCount = 0;
}

void SoundWheelState::update() {
    if(getSharedData().wheelCount >= 10) {
        swap();
        getSharedData().wheelCount = 0;
    }
}

void SoundWheelState::draw() {
    ofBackground(getSharedData().background);
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(255);
    getSharedData().users[userIndex].portrait.draw(ofGetWidth()/2, ofGetHeight()/2, 540, 360);
    ofSetColor(getSharedData().background);
    getSharedData().emptyImages[getSharedData().users[userIndex].imageIndex].draw(ofGetWidth()/2, ofGetHeight()/2, 320, 320);
    fillPage();
    ofSetColor(getSharedData().pallete[getSharedData().users[userIndex].colIndex]);
    for(int i = 0; i < getSharedData().wheelCount; i++) {
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(ofMap(i, 0, 9, 0, 360));
        getSharedData().images[getSharedData().users[userIndex].imageIndex].draw(0, -getSharedData().images[getSharedData().users[userIndex].imageIndex].getHeight()/4, 80, 80);
        ofPopMatrix();
    }
    getSharedData().futura.drawString(getSharedData().users[userIndex].name, ofGetWidth()/2 - getSharedData().futura.getStringBoundingBox(getSharedData().users[userIndex].name, 0, 0).getWidth()/2, ofGetHeight()/2 + emptyImage.getHeight()/2);
    ofPopStyle();
}

void SoundWheelState::swap() {
    userIndex++;
    userIndex %= getSharedData().users.size();
}

void SoundWheelState::fillPage() {
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(getSharedData().background);
    float yMargin = (ofGetHeight() - getSharedData().images[getSharedData().users[userIndex].imageIndex].getHeight()/2)/2;
    float xMargin = (ofGetWidth() - getSharedData().images[getSharedData().users[userIndex].imageIndex].getWidth()/2)/2;
    ofRect(0, 0, ofGetWidth(), yMargin);
    ofRect(0, 0, xMargin, ofGetHeight());
    ofRect(0, ofGetHeight() - yMargin - 1, ofGetWidth(), yMargin + 10);
    ofRect(ofGetWidth() - xMargin - 1, 0, xMargin + 10, ofGetHeight());
    ofPopStyle();
}

string SoundWheelState::getName() {
    return "soundWheel";
}

void SoundWheelState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash"); //change state back to main page
    }
    switch (key) {
        case '1':
            changeState("soundWheel");
            getSharedData().performanceOn = false;
            break;
        case '2':
            changeState("mirror");
            getSharedData().performanceOn = false;
            break;
        case '3':
            changeState("space");
            getSharedData().performanceOn = false;
            break;
        case '4':
            changeState("flow");
            getSharedData().performanceOn = false;
            break;
        case 'p':
            getSharedData().performanceOn = !getSharedData().performanceOn;
            break;
        default:
            break;
    }
}

void SoundWheelState::mousePressed(int x, int y, int button) {
    if(button == OF_MOUSE_BUTTON_RIGHT) {
        changeState("splash");
    }
}
