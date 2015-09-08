//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "FlowState.h"
#define NUMPARTICLES 150

using namespace cv;
using namespace ofxCv;

void FlowState::setup() {
    ofSetVerticalSync(true);
    for(int i = 0; i < NUMPARTICLES; i++) {
        particles.push_back(Particle(ofRandom(ofGetWidth()), ofMap(i, 0, NUMPARTICLES, 10, ofGetHeight()-10)));
        particles[i].setCols(getSharedData().pallete[6], getSharedData().pallete[0]);
    }
    vidOn = true;
    dimFac = 0.15;
    alpha = 255;
    tick = 0;
    userIndex = (int)ofRandom(getSharedData().users.size());
    timer = ofGetElapsedTimeMillis();
}

void FlowState::update() {
#ifdef __arm__
    getSharedData().frame = getSharedData().cam.grab();
#elif __APPLE__
    getSharedData().cam.update();
    getSharedData().frame = toCv(getSharedData().cam.getPixelsRef());
#endif
    if(!getSharedData().frame.empty()) {
        cv::flip(getSharedData().frame, dst, 1);
        ofxCv::toOf(dst, getSharedData().colImg);
        getSharedData().colImg.update();
        cv::resize(dst, getSharedData().smallFrame, cv::Size(round(dimFac*getSharedData().frame.cols), round(dimFac*getSharedData().frame.rows)));
        farneback.calcOpticalFlow(getSharedData().smallFrame);
        float maxVel = farneback.getTotalFlow().length()*2;
        
        for(int i = 0; i < particles.size(); i++) {
            particles[i].setMaxVel(maxVel);
            particles[i].modAlpha();
            particles[i].update();
            particles[i].checkEdges();
            float x = ofMap(particles[i].getLoc().x, 0, ofGetWidth(), 0, getSharedData().camWidth*dimFac);
            float y = ofMap(particles[i].getLoc().y, 0, ofGetHeight(), 0, getSharedData().camHeight*dimFac);
            ofRectangle region = ofRectangle(x, y, 1, 1);
            ofVec2f accMod = farneback.getAverageFlowInRegion(region);
            particles[i].modAcc(accMod*20);
        }
    }
}

void FlowState::draw() {
    ofPushStyle();
    ofSetColor(255);
    getSharedData().colImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofSetLineWidth(10);
    for(int i = 0; i < particles.size(); i++) {
        particles[i].display();
    }
    ofPopStyle();
    getSharedData().drawDebug();
    if(getSharedData().performanceOn) {
        int timeLength = 20000;
        ofSetColor(ofColor(255), alpha);
        getSharedData().nameFutura.drawString(getSharedData().users[userIndex].name, ofGetWidth()/2 - getSharedData().nameFutura.getStringBoundingBox(getSharedData().users[userIndex].name, 0, 0).getWidth()/2, ofGetHeight()/2);
        if(ofGetElapsedTimeMillis() - timer > timeLength/255) {
            tick++;
            alpha -= 255/(timeLength/255)*2;
            timer = ofGetElapsedTimeMillis();
            if(tick > timeLength/255) {
                timer = ofGetElapsedTimeMillis();
                tick = 0;
                alpha = 255;
                userIndex++;
                userIndex%=getSharedData().users.size();
            }
        }
    }
}

string FlowState::getName() {
    return "flow";
}

void FlowState::mousePressed(int x, int y, int button) {
    changeState("splash");
}

void FlowState::keyPressed(int key) {
    if(key == 's')
    {
        changeState("splash");
    }
    if(key == 'v')
    {
        vidOn = !vidOn;
    }
    getSharedData().handleDebug(key);
    switch (key) {
        case '1':
            changeState("soundWheel");
            getSharedData().performanceOn = false;
            break;
        case '2':
            changeState("mirror");
            getSharedData().performanceOn = false;
            break;
        case '3':
            changeState("space");
            getSharedData().performanceOn = false;
            break;
        case '4':
            changeState("flow");
            getSharedData().performanceOn = false;
            break;
        case 'p':
            getSharedData().performanceOn = !getSharedData().performanceOn;
            alpha = 255;
            tick = 0;
            userIndex = (int)ofRandom(getSharedData().users.size());
            timer = ofGetElapsedTimeMillis();
            break;
        default:
            break;
    }
}

/*
void FlowState::setup() {
    ofSetVerticalSync(true);
    for(int i = 0; i < NUMPARTICLES; i++) {
        particles.push_back(Particle(ofRandom(ofGetWidth()), ofMap(i, 0, NUMPARTICLES, 10, ofGetHeight()-10)));
        particles[i].setCol(getSharedData().pallete[6]);
    }
    vidOn = true;
    timer = ofGetElapsedTimeMillis();
//    getSharedData().frame = getSharedData().cam.grab();
//    threadedObject.setFrame(getSharedData().frame);
}





void FlowState::update() {
    getSharedData().frame = getSharedData().cam.grab();
//    if(ofGetElapsedTimeMillis() - timer > 1000)
//    {
//        if(!getSharedData().frame.empty()) {
//            farneback.calcOpticalFlow(getSharedData().frame);
//        }
//        timer = ofGetElapsedTimeMillis();
//    }
//    threadedObject.setFrame(getSharedData().frame);
//    farneback = threadedObject.getFlow();

//    for(int i = 0; i < particles.size(); i++) {
//        particles[i].update();
//        particles[i].checkEdges();
//        float x = ofMap(particles[i].getLoc().x, 0, ofGetWidth(), 0, getSharedData().camWidth);
//        float y = ofMap(particles[i].getLoc().y, 0, ofGetHeight(), 0, getSharedData().camHeight);
//        ofRectangle region = ofRectangle(x, y, 1, 1);
//        ofVec2f accMod = farneback.getAverageFlowInRegion(region);
//        if(accMod.length() < 1) accMod = ofVec2f(0.1, 0);
//        particles[i].modAcc(accMod);
//    }
}

void FlowState::draw()
{
    ofDrawBitmapString("Flow is currently under development: press 's' to return the splash page",  0, 10);
    ofSetColor(255);
//    threadedObject.getFlow().draw(0, 0, ofGetWidth(), ofGetHeight());
    drawMat(getSharedData().frame, 0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(getSharedData().background, 20);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(getSharedData().pallete[0]);
    ofSetLineWidth(10);
    for(int i = 0; i < particles.size(); i++) {
        particles[i].display();
    }
    getSharedData().drawDebug();
}
*/

