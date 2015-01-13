//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "FlowState.h"

using namespace ofxCv;
using namespace cv;

void FlowState::setup() {
    getSharedData().numFlowParticles = 1000;
    ofSetVerticalSync(true);
    for(int i = 0; i < getSharedData().numFlowParticles; i++) {
        particles.push_back(Particle(ofRandom(ofGetWidth()), ofMap(i, 0, getSharedData().numFlowParticles, 10, ofGetHeight()-10)));
        particles[i].setCol(getSharedData().pallete[6]);
    }
}

void FlowState::update() {
    getSharedData().cam.update();
    if(getSharedData().cam.isFrameNew()) {
        getSharedData().colImg.setFromPixels(getSharedData().cam.getPixels(), 320, 240);
        getSharedData().colImg.mirror(false, true);
//        cv::Mat frame = toCv(getSharedData().colImg);
        farneback.calcOpticalFlow(getSharedData().colImg);
    }
    
    for(int i = 0; i < particles.size(); i++) {
        particles[i].update();
        particles[i].checkEdges();
        float x = ofMap(particles[i].getLoc().x, 0, ofGetWidth(), 0, getSharedData().cam.getWidth());
        float y = ofMap(particles[i].getLoc().y, 0, ofGetHeight(), 0, getSharedData().cam.getHeight());
        ofRectangle region = ofRectangle(x, y, 1, 1);
        ofVec2f accMod = farneback.getAverageFlowInRegion(region);
        if(accMod.length() < 1) accMod = ofVec2f(0.1, 0);
        particles[i].modAcc(accMod);
    }
}

void FlowState::draw()
{
//    ofDrawBitmapString("Flow is currently under development: press 's' to return the splash page",  0, 10);
    ofSetColor(255);
    if(!getSharedData().bVidOn) getSharedData().colImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(getSharedData().background, 20);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(getSharedData().pallete[0]);
    ofSetLineWidth(10);
    for(int i = 0; i < particles.size(); i++) {
        particles[i].display();
    }
}

string FlowState::getName()
{
    return "flow";
}

void FlowState::mousePressed(int x, int y, int button) {
}

void FlowState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash");
    }
    if(key == 'v')
    {
        getSharedData().bVidOn = !getSharedData().bVidOn;
    }
}