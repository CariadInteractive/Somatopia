//
//  SharedData.cpp
//  Somatopia1
//
//  Created by James Bentley on 1/6/15.
//
//

#include "SharedData.h"

using namespace cv;
using namespace ofxCv;

void SharedData::drawDebug()
{
    if(bDebugOn)
    {
        ofSetHexColor(0xffffff);
        drawMat(smallFrame, 20,20);
        ofDrawBitmapString("Color Image", 20, 20);
        drawMat(greyFrame, 360,20);
        ofDrawBitmapString("GrayImage", 360, 20);
        drawMat(greyBackground, 20,280);
        ofDrawBitmapString("grayBg", 20, 280);
        drawMat(greyDiff, 360,280);
        ofDrawBitmapString("grayDiff", 360, 280);

        
//        ofFill();
//        ofSetHexColor(0x333333);
//        ofRect(360,540,camWidth,camHeight);
//        ofSetHexColor(0xffffff);
        
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
        ofSetColor(0);
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
    if(key = ' ')
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

void SharedData::handleUtils(int key) //handles fullscreen and mouse display
{
    switch(key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 'm':
            if(bIsCursorHidden) {
                ofShowCursor();
                bIsCursorHidden = false;
            }
            else {
                ofHideCursor();
                bIsCursorHidden = true;
            }
            break;
        default:
            break;
    }
}

int SharedData::mapColor(std::string colorName) {
    
    std::string upperName = ofToUpper(colorName);
    
    if(upperName == "ORANGE") {
        return 0;
    }
    else if(upperName == "RED") {
        return 1;
    }
    else if(upperName == "YELLOW") {
        return 2;
    }
    else if(upperName == "LIGHT BLUE") {
        return 3;
    }
    else if(upperName == "BACKGROUND") {
        return 3;
    }
    else if(upperName == "GREEN") {
        return 4;
    }
    else if(upperName == "DARK BLUE") {
        return 5;
    }
    else if(upperName == "BLUE") {
        return 5;
    }
    else if(upperName == "PURPLE") {
        return 6;
    }
    else if(upperName =="WHITE") {
        return 7;
    }
    else if(upperName =="GREY") {
        return 8;
    }
    else if(upperName =="PINK") {
        return 9;
    }
    else {
        cout<<"Color Name: "<<colorName<<" not recognized, acceptable inputs are:"<<endl;
        cout<<"orange"<<endl;
        cout<<"red"<<endl;
        cout<<"yellow"<<endl;
        cout<<"light blue"<<endl;
        cout<<"background"<<endl;
        cout<<"green"<<endl;
        cout<<"dark blue"<<endl;
        cout<<"blue"<<endl;
        cout<<"purple"<<endl;
        cout<<"white"<<endl;
        cout<<"grey"<<endl;
        cout<<"pink"<<endl;
    }
}

int SharedData::mapShape(std::string shapeName) {
    std::string upperName = ofToUpper(shapeName);
    if(upperName == "CIRCLE") {
        return 0;
    }
    else if(upperName == "CROSS") {
        return 1;
    }
    else if(upperName == "HEART") {
        return 2;
    }
    else if(upperName == "HEXAGON") {
        return 3;
    }
    else if(upperName == "SQUARE") {
        return 4;
    }
    else if(upperName == "TRIANGLE") {
        return 5;
    }
    else if(upperName == "ASTERIX") {
        return 6;
    }
    else {
        cout<<"Shape Name: "<<shapeName<<" not recognized, acceptable inputs are:"<<endl;
        cout<<"circle"<<endl;
        cout<<"cross"<<endl;
        cout<<"heart"<<endl;
        cout<<"hexagon"<<endl;
        cout<<"square"<<endl;
        cout<<"triangle"<<endl;
        cout<<"asterix"<<endl;
    }
}

void SharedData::handlePerformance(int key) {

}