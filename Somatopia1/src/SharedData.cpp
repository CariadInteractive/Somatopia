//
//  SharedData.cpp
//  Somatopia1
//
//  Created by James Bentley on 1/6/15.
//
//

#include "SharedData.h"

void SharedData::drawDebug()
{
    if(bDebugOn)
    {
        ofSetHexColor(0xffffff);
        colorImg.draw(20,20);
        ofDrawBitmapString("Color Image", 20, 20);
        grayImage.draw(360,20);
        ofDrawBitmapString("GrayImage", 360, 20);
        grayBg.draw(20,280);
        ofDrawBitmapString("grayBg", 20, 280);
        grayDiff.draw(360,280);
        ofDrawBitmapString("grayDiff", 360, 280);

        
        ofFill();
        ofSetHexColor(0x333333);
        ofRect(360,540,320,240);
        ofSetHexColor(0xffffff);
        
        int n = contourFinder.size();
        for(int i = 0; i < n; i++) {
            ofSetColor(ofColor::yellow);
            ofPolyline convexHull = ofxCv::toOf(contourFinder.getConvexHull(i));
            ofPushMatrix();
            ofTranslate(360, 540);
            convexHull.draw();
            ofPopMatrix();
        }
        
        // finally, a report:
        ofSetHexColor(0xffffff);
        stringstream reportStr;
        reportStr << "bg subtraction and blob detection" << endl
        << "press ' ' to capture bg" << endl
        << "threshold " << threshold << " (press: +/-)" << endl
        << "num blobs found " << contourFinder.size() << ", fps: " << ofGetFrameRate();
        ofDrawBitmapString(reportStr.str(), 20, 600);
    }
}

void SharedData::handleDebug(int key)
{
    if(key == 'd')
    {
        bDebugOn = !bDebugOn;
    }
}

void SharedData::handleBackground(int key)
{
    if(key == ' ')
    {
        bLearnBackground = true;
    }
}

void SharedData::handleThreshold(int key)
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