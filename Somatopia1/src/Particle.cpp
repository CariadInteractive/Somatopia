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
}

void Particle::setCol(ofColor newCol)
{
    col = newCol;
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
    float i = 1;
    for(list<ofVec2f>::iterator locIt = loc.begin(); locIt != loc.end(); locIt++) {
        ofColor newCol = ofColor(col, 255/i);
        mesh.addColor(newCol);
        mesh.addVertex(ofVec3f(locIt->x, locIt->y, 0));
        i += 0.3;
    }
}

void Particle::display() {
    ofPushStyle();
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    mesh.draw();
    ofSetColor(mesh.getColor(0));
    ofCircle(loc.begin()->x, loc.begin()->y, 5);
    ofPopStyle();
}

void Particle::checkEdges() {
    if(loc.begin()->x > ofGetWidth()-10) {
        for(list<ofVec2f>::iterator locIt = loc.begin(); locIt != loc.end(); locIt++) {
            locIt->x = 10;
        }
    }
    else if(loc.begin()->x < 10) {
        for(list<ofVec2f>::iterator locIt = loc.begin(); locIt != loc.end(); locIt++) {
            locIt->x = ofGetWidth() - 10;
        }
    }
    if(loc.begin()->y > ofGetHeight()-10) {
        for(list<ofVec2f>::iterator locIt = loc.begin(); locIt != loc.end(); locIt++) {
            locIt->y = 10;
        }
    }
    if(loc.begin()->y < 10) {
        for(list<ofVec2f>::iterator locIt = loc.begin(); locIt != loc.end(); locIt++) {
            locIt->y = ofGetHeight() - 10;
        }
    }
}

void Particle::modAcc(ofVec2f flow)
{
    acc = flow;
}

ofVec2f Particle::getLoc()
{
    return ofVec2f(loc.begin()->x, loc.begin()->y);
}