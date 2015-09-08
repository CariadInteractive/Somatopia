//
//  Particle.cpp
//  Somatopia1
//
//  Created by James Bentley on 1/7/15.
//
//

#include "Particle.h"

Particle::Particle(float x, float y) {
    loc.assign(20, ofVec2f(x, y));
    acc = ofVec2f(0, 0);
    vel = ofVec2f(5, 0);
    maxAcc = 1;
    maxVel = 10;
    col = ofColor(0);
    alpha = 0;
}

void Particle::setCols(ofColor newSlowCol, ofColor newFastCol) {
    dispCol = newSlowCol;
    slowCol = newSlowCol;
    fastCol = newFastCol;
    col = newSlowCol;
}

void Particle::setMaxVel(float newMaxVel) {
    maxVel = newMaxVel = ofMap(newMaxVel, 0, 2500, 1, 20);
    if(maxVel > 20) maxVel = 20;
}

void Particle::update() {
    acc.limit(maxAcc);
    vel += acc;
    vel.limit(maxVel);
    ofVec2f newLoc;
    newLoc.x = loc.begin()->x += vel.x;
    newLoc.y = loc.begin()->y += vel.y;
    loc.push_front(newLoc);
    loc.pop_back();
    mesh.clear();
    
    dispCol = slowCol;
    float val = ofMap(vel.length(), 0, 20, 0, 1);
    if(val > 1) val = 1;
    dispCol.lerp(fastCol, val);
    
    float i = 1;
    for(list<ofVec2f>::iterator locIt = loc.begin(); locIt != loc.end(); locIt++) {
        ofColor newCol = ofColor(dispCol, alpha/i);
        mesh.addColor(newCol);
        mesh.addVertex(ofVec3f(locIt->x, locIt->y, 0));
        i += 0.3;
    }
}

void Particle::display() {
    ofPushStyle();
    ofSetLineWidth(20);
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    mesh.draw();
    ofSetColor(mesh.getColor(0));
    ofCircle(loc.begin()->x, loc.begin()->y, 10);
    ofPopStyle();
}

void Particle::checkEdges() {
    //check edges of screen, if they are at the endge wrap them around to the opposite side
    float randX = ofRandom(10, ofGetWidth() - 10);
    float randY = ofRandom(10, ofGetHeight() - 10);
    
    if(loc.begin()->x > ofGetWidth()-10) {
        for(list<ofVec2f>::iterator locIt = loc.begin(); locIt != loc.end(); locIt++) {
            //locIt->x = 10;
            locIt->x = randX;
            locIt->y = randY;
        }
    }
    else if(loc.begin()->x < 10) {
        for(list<ofVec2f>::iterator locIt = loc.begin(); locIt != loc.end(); locIt++) {
            //            locIt->x = ofGetWidth() - 10;
            locIt->x = randX;
            locIt->y = randY;
        }
    }
    if(loc.begin()->y > ofGetHeight()-10) {
        for(list<ofVec2f>::iterator locIt = loc.begin(); locIt != loc.end(); locIt++) {
            //            locIt->y = 10;
            locIt->x = randX;
            locIt->y = randY;
        }
    }
    if(loc.begin()->y < 10) {
        for(list<ofVec2f>::iterator locIt = loc.begin(); locIt != loc.end(); locIt++) {
            //            locIt->y = ofGetHeight() - 10;
            locIt->x = randX;
            locIt->y = randY;
        }
    }

}

void Particle::modAcc(ofVec2f flow)
{
    acc = flow;
}

ofVec2f Particle::getLoc()
{
    ofVec2f outLoc = ofVec2f(loc.begin()->x, loc.begin()->y);
    return outLoc;
}

void Particle::modAlpha() {
    if(vel.length() < 2) alpha-=5;
    else alpha+=5;
    if(alpha > 255) alpha = 255;
    if(alpha < 0) alpha = 0;
}