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
//    void stateEnter();
//    void stateExit();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    string getName();
private:
    ofxCv::FlowFarneback farneback;
    float dimFac;
    vector<Particle> particles;
    bool vidOn;
    int alpha;
    int timer;
    int tick;
    int userIndex;
    cv::Mat dst;
};