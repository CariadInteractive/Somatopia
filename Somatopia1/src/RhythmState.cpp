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
    getSharedData().noise.loadSound("pongSound.ogg"); //load pong sound
    ball.setCol(getSharedData().pallete[1]); //set ball color
}

void RhythmState::update() {
    ball.update(); //update ball locationa nd velocity
    ball.checkEdges(); //check ball isn't contacting any edges
    
    getSharedData().cam.update(); //update camera
    if(getSharedData().cam.isFrameNew()) { //check if the frame is new
        getSharedData().colImg.setFromPixels(getSharedData().cam.getPixels(), 320, 240); //set col Image from pixels
        getSharedData().colImg.mirror(false, true); //mirror image
        getSharedData().grayImage = getSharedData().colImg; //set grey image equal to colImg (is will stay grey because of how we initialized it in testApp.cpp)
        if(getSharedData().bLearnBackground) { //check if we need to learn the background
            getSharedData().grayBg = getSharedData().grayImage; //set the background tot he greyscale image
            getSharedData().bLearnBackground = false; //stop learning the background
        }
        
        getSharedData().grayDiff.absDiff(getSharedData().grayBg, getSharedData().grayImage); //take the difference between background and grey image
        getSharedData().grayDiff.threshold(getSharedData().threshold); //threshold the difference
        getSharedData().contourFinder.findContours(getSharedData().grayDiff); //find blocs int he thresholded subtraction image
    }

    int n = getSharedData().contourFinder.size(); //number of blobs found
    for(int i = 0; i < n; i++)
    {
        ofPolyline convexHull; //use this data structure to find the convex Hulls
        convexHull = ofxCv::toOf(getSharedData().contourFinder.getConvexHull(i)); //change the blobs into ofPolylines using ofxCv
        ball.checkContour(convexHull); //check to see of the ball is touching any contours and repel it if so
    }
}

void RhythmState::draw()
{
//    ofDrawBitmapString("Rhythm is currently under development: press 's' to return the splash page",  0, 10);
    ofSetColor(255);
    getSharedData().colImg.draw(0, 0, ofGetWidth(), ofGetHeight()); //display the video
    
    ball.display(); //display the ball
    
    getSharedData().drawDebug(); //draw the debug windows if turned on.
}

string RhythmState::getName()
{
    return "rhythm";
}

void RhythmState::mousePressed(int x, int y, int button)
{
    
}

void RhythmState::mouseMoved(int x, int y )
{
    mouseX = x; //set mouseX and Y
    mouseY = y;
}


void RhythmState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash"); //change state to main page
    }
    //handle global functions (see how the work in SharedData.cpp)
    getSharedData().handleDebug(key);
    getSharedData().handleBackground(key);
    getSharedData().handleThreshold(key);
    getSharedData().handleUtils(key);

}