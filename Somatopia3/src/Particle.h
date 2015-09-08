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
    void modAlpha();
    void setMaxVel(float newMaxVel);
    ofVec2f getLoc();
    ofVec2f getVel();
    Particle(float x, float y);
private:
    list<ofVec2f> loc;
    int alpha;
    ofVec2f vel;
    ofVec2f acc;
    float maxAcc;
    float maxVel;
    float rad;
    ofMesh mesh;
    ofColor col, dispCol, slowCol, fastCol;
};
