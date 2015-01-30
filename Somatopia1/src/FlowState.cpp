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
    getSharedData().numFlowParticles = 1500; //set number of particles to render
    ofSetVerticalSync(true); //set Vertical sync for some reason? (not sure if this matters)
    
    //initialize particles
    for(int i = 0; i < getSharedData().numFlowParticles; i++) {
        particles.push_back(Particle(ofRandom(ofGetWidth()), ofMap(i, 0, getSharedData().numFlowParticles, 10, ofGetHeight()-10)));
        particles[i].setCols(getSharedData().pallete[6], getSharedData().pallete[0]);
    }
    
    flowCam.setDeviceID(getSharedData().cam.listDevices().size() - 1);
    flowCam.initGrabber(320, 240);
}

void FlowState::update() {
    flowCam.update(); //update camera
    if(flowCam.isFrameNew()) { //if there is a new frame
        getSharedData().colImg.setFromPixels(flowCam.getPixels(), 320, 240); //set col Image from videoGrabber pixels
        getSharedData().colImg.mirror(false, true); //mirror the image
//        cv::Mat frame = toCv(getSharedData().colImg);
        farneback.calcOpticalFlow(getSharedData().colImg); //calculate the farneback flow
    }
    
    float maxVel = farneback.getTotalFlow().length(); //modify maximum velocity based on movement
    
    for(int i = 0; i < particles.size(); i++) {
        particles[i].setMaxVel(maxVel);
        particles[i].update(); //update particles velocity and position
        particles[i].checkEdges(); //check to see if they bump into the sides
        particles[i].modAlpha();
        
        //map the particles from screen space into camera space

        float x = ofMap(particles[i].getLoc().x, 0, ofGetWidth(), 0, getSharedData().cam.getWidth());
        float y = ofMap(particles[i].getLoc().y, 0, ofGetHeight(), 0, getSharedData().cam.getHeight());
        
        ofRectangle region = ofRectangle(x, y, 1, 1); //set region to calculate flow
        ofVec2f accMod = farneback.getAverageFlowInRegion(region); //measure flow in that region
//        float flowThresh = 1; //set flow Threshold below which we give it an artificial flow
//        if(accMod.length() < flowThresh) accMod = ofVec2f(0.1, 0); //set acceleration to a slight positive X-value if flow is below a certain threshold
        particles[i].modAcc(accMod); //modify the acceleration of each particle based on the flow in it's region
    }
}

void FlowState::draw()
{
//    ofDrawBitmapString("Flow is currently under development: press 's' to return the splash page",  0, 10);
    ofSetColor(255);
    if(getSharedData().bVidOn) getSharedData().colImg.draw(0, 0, ofGetWidth(), ofGetHeight());//draw color image if the video is turned on
    ofSetLineWidth(10);
    for(int i = 0; i < particles.size(); i++) {
        particles[i].display(); //draw all the particles
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
        changeState("splash"); //change to main page
    }
    if(key == 'v')
    {
        getSharedData().bVidOn = !getSharedData().bVidOn; //toggle video on and off
    }
    getSharedData().handleUtils(key);

}