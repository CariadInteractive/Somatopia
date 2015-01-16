//
//  Particle.cpp
//  Somatopia1
//
//  Created by James Bentley on 1/7/15.
//
//

#include "Particle.h"

Particle::Particle(float x, float y) {
    loc.assign(20, ofVec2f(x, y)); //loc is a list of points that I will be popping and pushing from, I want there to be 20 points and I want them to be ofVec2fs
    acc = ofVec2f(0, 0); //set acc to 0
    vel = ofVec2f(5, 0); //set vel to 5 in the positive x
    maxAcc = 1; //set max acceleration rate
    maxVel = 10; //set max possible velocity
    col = ofColor(0); //set color (defualt reset it later)
}

void Particle::setCol(ofColor newCol)
{
    col = newCol; //set color to comthing pretty!
}

void Particle::update() {
    acc.limit(maxAcc); //limit the acceleration
    vel += acc; //add acceleration to velocity
    vel.limit(maxVel); //limit velocity
    //add a new location where it should be (ie where the last loc was plus the new velocity)
    ofVec2f newLoc;
    newLoc.x = loc.begin()->x += vel.x;
    newLoc.y = loc.begin()->y += vel.y;
    //push the new location to the front of the list of locations
    loc.push_front(newLoc);
    //remove the last location
    loc.pop_back();
    //clear the mesh (the mesh is what we want to draw in the end)
    mesh.clear();
    //add all the points in the list to the mesh one at a time and set their colors with decreasing alpha values
    float i = 1;
    for(list<ofVec2f>::iterator locIt = loc.begin(); locIt != loc.end(); locIt++) {
        ofColor newCol = ofColor(col, 255/i);
        mesh.addColor(newCol);
        mesh.addVertex(ofVec3f(locIt->x, locIt->y, 0));
        i += 0.3;
    }
}

void Particle::display() {
    //draw the mesh
    ofPushStyle();
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    mesh.draw();
    //draw a circle at the front of the object
    ofSetColor(mesh.getColor(0));
    ofCircle(loc.begin()->x, loc.begin()->y, 5);
    ofPopStyle();
}

void Particle::checkEdges() {
    //check edges of screen, if they are at the endge wrap them around to the opposite side
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
    acc = flow; //change the acceleration (use it the input flow values
}

ofVec2f Particle::getLoc()
{
    return ofVec2f(loc.begin()->x, loc.begin()->y); //return the location for convenience
}