//
//  SoundWheel.cpp
//  Somatopia1
//
//  Created by James Bentley on 1/20/15.
//
//

#include "SoundWheelState.h"

void SoundWheelState::setup() {
    
    fullImage.loadImage("Heart.png");
    emptyImage.loadImage("Heart_rev.png");
    getSharedData().wheelCount = 0;
    photoIndex = 0;
    photos[0].loadImage("photo1.png");
    photos[1].loadImage("photo1.png");
    photos[2].loadImage("photo1.png");
    photos[3].loadImage("photo1.png");
    photos[4].loadImage("photo1.png");
    photos[5].loadImage("photo1.png");
    photos[6].loadImage("photo1.png");
    photos[7].loadImage("photo1.png");
    photos[8].loadImage("photo1.png");
    photos[9].loadImage("photo1.png");
}

void SoundWheelState::update() {
    if(getSharedData().wheelCount >= 10) {
        swap();
        getSharedData().wheelCount = 0;
    }
    cout<<getSharedData().wheelCount<<endl;
}

void SoundWheelState::draw() {
    ofBackground(getSharedData().background);
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(col);
    ofSetColor(255);
    photos[photoIndex].draw(ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(getSharedData().background);
    emptyImage.draw(ofGetWidth()/2, ofGetHeight()/2);
    fillPage();
    ofSetColor(col);
    for(int i = 0; i < getSharedData().wheelCount; i++) {
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(ofMap(i, 0, 9, 0, 360));
        fullImage.draw(0, -emptyImage.getHeight()/2, 50, 50);
        ofPopMatrix();
    }
    ofPopStyle();
}

void SoundWheelState::swap() {
    int index = (int)ofRandom(10);
    if(index != photoIndex) {
        col = getSharedData().pallete[(int)ofRandom(8)];
        if (col == getSharedData().background) swap();
        photoIndex = index;
    }
    else swap();
}

void SoundWheelState::fillPage() {
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(getSharedData().background);
    float yMargin = (ofGetHeight() - emptyImage.getHeight())/2;
    float xMargin = (ofGetWidth() - emptyImage.getWidth())/2;
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
}