//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "RhythmState.h"

using namespace ofxCv;
using namespace cv;

void RhythmState::setup() {
    dimFac = 0.5;
    getSharedData().noise.loadSound("pongSound.ogg");
    ball.setCol(getSharedData().pallete[1]);
    ball.setFrame(getSharedData().camWidth*dimFac, getSharedData().camHeight*dimFac);
}

void RhythmState::update() {
    ball.update();
    ball.checkEdges();
#ifdef __arm__
    getSharedData().frame = getSharedData().cam.grab();
#elif __APPLE__
    getSharedData().cam.update();
    getSharedData().frame = toCv(getSharedData().cam.getPixelsRef());
#endif
    if(!getSharedData().frame.empty()) {
        cv::resize(getSharedData().frame, getSharedData().smallFrame, cv::Size(round(dimFac*getSharedData().frame.cols), round(dimFac*getSharedData().frame.rows)));
        cvtColor(getSharedData().smallFrame, getSharedData().greyFrame, CV_BGR2GRAY);
        if(getSharedData().bLearnBackground)
        {
            getSharedData().greyBackground = getSharedData().greyFrame.clone();
            getSharedData().bLearnBackground = false;
        }
        absdiff(getSharedData().greyFrame, getSharedData().greyBackground, getSharedData().greyDiff);
        getSharedData().contourFinder.setThreshold(getSharedData().threshold);
        getSharedData().contourFinder.findContours(getSharedData().greyDiff);
        cv::threshold(getSharedData().greyDiff, getSharedData().greyDiff, getSharedData().threshold, 255, CV_THRESH_BINARY);
    }
    
    int n = getSharedData().contourFinder.size();
    for(int i = 0; i < n; i++)
    {
        ofPolyline convexHull;
        convexHull = ofxCv::toOf(getSharedData().contourFinder.getConvexHull(i));
        ball.checkContour(convexHull);
    }
}

void RhythmState::draw()
{
//    ofDrawBitmapString("Rhythm is currently under development: press 's' to return the splash page",  0, 10);
    ofSetColor(255);
//    getSharedData().frame.draw(0, 0, ofGetWidth(), ofGetHeight());
    drawMat(getSharedData().frame, 0, 0, ofGetWidth(), ofGetHeight());
//    getSharedData().colImg.draw(0, 0, ofGetWidth(), ofGetHeight());
//    getSharedData().video.draw();
    
    ball.display();
    
    getSharedData().drawDebug();
}

string RhythmState::getName()
{
    return "rhythm";
}

void RhythmState::mousePressed(int x, int y, int button) {
    if(button == OF_MOUSE_BUTTON_RIGHT) {
        changeState("splash");
    }
    
}

void RhythmState::mouseMoved(int x, int y )
{
    mouseX = x;
    mouseY = y;
}


void RhythmState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash");
    }
    
    getSharedData().handleDebug(key);
    getSharedData().handleThreshold(key);
    getSharedData().handleBackground(key);

}