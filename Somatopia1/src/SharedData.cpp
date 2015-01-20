//
//  SharedData.cpp
//  Somatopia1
//
//  Created by James Bentley on 1/6/15.
//
//

#include "SharedData.h"

//setup cv and ofxCv namespaces
using namespace ofxCv;
using namespace cv;

void SharedData::drawDebug()
{
    if(bDebugOn)
    {
        //draw debug images with labels
        colImg.draw(20, 20);
        ofDrawBitmapString("Color Frame", 20, 20);
        
        grayImage.draw(360, 20);
        ofDrawBitmapString("GrayImage", 360, 20);

        grayBg.draw(20, 280);
        ofDrawBitmapString("grayBg", 20, 280);

        grayDiff.draw(20, 20);
        ofDrawBitmapString("greyDiff", 360, 280);
        
        ofFill();
        ofSetHexColor(0x333333);
        ofRect(360,540,320,240);
        ofSetHexColor(0xffffff);
        
//        int n = contourFinder.size();
//        for(int i = 0; i < n; i++) {
//            ofSetColor(ofColor::yellow);
//            ofPolyline convexHull = ofxCv::toOf(contourFinder.getConvexHull(i));
//            ofPushMatrix();
//            ofTranslate(360, 540);
//            convexHull.draw();
//            ofPopMatrix();
//        }
        
        // draw some information in debug mode:
        ofSetHexColor(0xffffff);
        stringstream reportStr;
        reportStr << "bg subtraction and blob detection" << endl
        << "press ' ' to capture bg" << endl
        << "threshold " << threshold << " (press: +/-)" << endl
        << "num blobs found " << contourFinder.size() << ", fps: " << ofGetFrameRate();
        ofDrawBitmapString(reportStr.str(), 20, 600);
    }
}

void SharedData::handleDebug(int key) //turns on and off debug in each state
{
    if(key == 'd')
    {
        bDebugOn = !bDebugOn;
    }
}

void SharedData::handleBackground(int key) //handleds background resetting in each state
{
    if(key == ' ')
    {
        bLearnBackground = true;
    }
}

void SharedData::handleThreshold(int key) //handles threshold setting in each state
{
    switch (key){
        case '+':
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
    }
}