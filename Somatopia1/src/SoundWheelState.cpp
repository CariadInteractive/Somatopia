//
//  SoundWheel.cpp
//  Somatopia1
//
//  Created by James Bentley on 1/20/15.
//
//

#include "SoundWheelState.h"

void SoundWheelState::setup() {
    
    userIndex = (int)ofRandom(users.size());
    
    fullImage.loadImage("Heart.png");
    emptyImage.loadImage("Heart_rev.png");
    getSharedData().wheelCount = 0;
    
    ofxJSONElement json;
    
    std::string file = "Users.json";
    bool parsingSuccessful = json.open(file);
    if(parsingSuccessful) {
        ofLogNotice("SoundWheelState::setup") << json.getRawString(true);
        for(int i = 0; i < json["Users"].size(); i++) {
            ofImage portrait;
            bool loaded = portrait.loadImage("portraits/"+json["Users"][i]["name"].asString()+".png");
            if(!loaded) loaded = portrait.loadImage("portraits/"+json["Users"][i]["name"].asString()+".jpg");
            if(!loaded) cout<<"unable to load portrait for "<< json["Users"][i]["name"].asString() << ", ensure your file has a .png or .jpg extension and the name of the file matches the name in Users.json" << endl;
            User tmpuser = {
                .col = getSharedData().pallete[getSharedData().mapColor(json["Users"][i]["color"].asString())],
                .portrait = portrait,
                .emptyImage = getSharedData().emptyImages[getSharedData().mapShape(json["Users"][i]["shape"].asString())],
                .fullImage = getSharedData().images[getSharedData().mapShape(json["Users"][i]["shape"].asString())],
                .name = json["Users"][i]["name"].asString()
            };
            users.push_back(tmpuser);
        }
    }
    
    col = getSharedData().pallete[2];
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
    users[userIndex].portrait.draw(ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(getSharedData().background);
    users[userIndex].emptyImage.draw(ofGetWidth()/2, ofGetHeight()/2);
    fillPage();
    ofSetColor(users[userIndex].col);
    for(int i = 0; i < getSharedData().wheelCount; i++) {
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(ofMap(i, 0, 9, 0, 360));
        users[userIndex].fullImage.draw(0, -emptyImage.getHeight()/2, 80, 80);
        ofPopMatrix();
    }
    getSharedData().futura.drawString(users[userIndex].name, ofGetWidth()/2 - getSharedData().futura.getStringBoundingBox(users[userIndex].name, 0, 0).getWidth()/2, ofGetHeight()/2 + emptyImage.getHeight()/2);
    ofPopStyle();
}

void SoundWheelState::swap() {
    int newIndex = (int)ofRandom(users.size());
    if(newIndex == userIndex) swap();
    else userIndex = newIndex;
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