//
//  Particle.h
//  Somatopia1
//
//  Created by James Bentley on 1/7/15.
//
//

#pragma once
#include "ofMain.h"

class Particle
{
public:
    void setCols(ofColor newSlowCol, ofColor newFastCol);
    void update();
    void display();
    void checkEdges();
    void modAcc(ofVec2f flow);
    void setMaxVel(float newMaxVel);
    ofVec2f getLoc();
    Particle(float x, float y);
private:
    list<ofVec2f> loc;
    ofVec2f vel;
    ofVec2f acc;
    float maxAcc;
    float maxVel;
    float rad;
    ofMesh mesh;
    ofColor dispCol, slowCol, fastCol;
};
