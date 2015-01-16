//
//  Splash.h
//  example
//
//  Created by James Bentley on 1/5/15.
//
//
#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "Particle.h"

class FlowState : public itg::ofxState<SharedData>
{
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    string getName();
private:
    ofxCv::FlowFarneback farneback; //ofxCv flow finder (farneback style!)
    vector<Particle> particles; //vector of particles to be drawn on screen
};