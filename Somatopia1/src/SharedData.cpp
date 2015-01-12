//
//  SharedData.cpp
//  Somatopia1
//
//  Created by James Bentley on 1/6/15.
//
//

#include "SharedData.h"

using namespace ofxCv;
using namespace cv;

void SharedData::drawDebug()
{
    if(bDebugOn)
    {
//        ofSetHexColor(0xffffff);
//        cv::Point p1 = toCv(ofVec2f(20, 20));
//        cv::Point p2 = toCv(ofVec2f(340, 260));
//        cv::rectangle(frame, p1, p2, CV_RGB(255, 255, 255));
//        drawMat(frame, 20, 20);
        colImg.draw(20, 20);
        ofDrawBitmapString("Color Frame", 20, 20);
//        p1 = toCv(ofVec2f(360, 20));
//        p2 = toCv(ofVec2f(680, 260));
//        cv::rectangle(greyFrame, p1, p2, CV_RGB(255, 255, 255));
//        drawMat(greyFrame, 360, 20);
        grayImage.draw(360, 20);
        ofDrawBitmapString("GrayImage", 360, 20);
//        p1 = toCv(ofVec2f(20, 280));
//        p2 = toCv(ofVec2f(360, 520));
//        cv::rectangle(greyBg, p1, p2, CV_RGB(255, 255, 255));
//        drawMat(greyBg, 20, 280);
        grayBg.draw(20, 280);
        ofDrawBitmapString("grayBg", 20, 280);
//        p1 = toCv(ofVec2f(360, 280));
//        p2 = toCv(ofVec2f(680, 520));
//        cv::rectangle(greyDiff, p1, p2, CV_RGB(255, 255, 255));
//        drawMat(greyDiff, 360, 280);
        grayDiff.draw(20, 20);
        ofDrawBitmapString("greyDiff", 360, 280);
        
//        colImg.draw(680, 20);
//        ofDrawBitmapString("Color Image", 680, 20);
        
        
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

//void SharedData::findContoursMat()
//{
//    cam.update();
//    if(cam.isFrameNew())
//    {
//        colImg.setFromPixels(cam.getPixels(), 320, 240, OF_IMAGE_COLOR);
//        colImg.mirror(false, true);
//        frame = ofxCv::toCv(colImg);
//        cvtColor(frame, greyFrame, CV_BGR2GRAY);
//        if(bLearnBackground)
//        {
//            greyBg = frame.clone();
//        }
//        greyDiff = greyFrame.clone();
//        absdiff(greyFrame, greyBg, greyDiff);
//        cv::threshold(greyDiff, greyDiff, threshold, 255, CV_THRESH_BINARY);
//        contourFinder.findContours(greyDiff);
//    }
//}