/*
 *  SharedData.h
 *
 *  Copyright (c) 2011, Neil Mendoza, http://www.neilmendoza.com
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of 16b.it nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */
#pragma once

#include "ofxCv.h"
#include "ofxOpenCv.h"

#ifdef __arm__
#include "ofxCvPiCam.h"// <--- for Linux
#endif

#include "ofxJSON.h"

//#include "ThreadedObject.h"//
//#include "ofxRPiCameraVideoGrabber.h"

class SharedData
{
public:
    ofTrueTypeFont futura;
    ofTrueTypeFont nameFutura;
//    ofVideoGrabber camVid; // <---- for mac
#ifdef __arm__
    ofxCvPiCam cam; // <---- for Linux
#elif __APPLE__
    ofVideoGrabber cam;
#endif
    
    cv::Mat frame, greyFrame, greyBackground, greyDiff, smallFrame;
//    ofxRPiCameraVideoGrabber video;
//    OMXCameraSettings omxCameraSettings;
    ofImage colImg;
    
    struct User {
        int imageIndex, colIndex;
        ofImage portrait;
        std::string name;
    };
    
    vector<User> users;
    User tmpUser;
    
    bool performanceOn;
    
    ofxCv::ContourFinder contourFinder;
//    ofxCvColorImage	colorImg;
//    ofxCvGrayscaleImage grayImage;
//    ofxCvGrayscaleImage grayBg;
//    ofxCvGrayscaleImage grayDiff;
    
    ofSoundPlayer noise;
    
    float threshold;
    
    int camWidth;
    int camHeight;
    
    bool bLearnBackground;
    bool bDebugOn;
    bool bVidOn;
    
    int numFlowParticles;
    int wheelCount;
    
    bool bIsCursorHidden;
    
//    ThreadedObject threadedObject;
    
    void drawDebug();
    void handleDebug(int key);
    void handleBackground(int key);
    void handleThreshold(int key );
    void handleUtils(int key);
    void handlePerformance(int key);
    
    void setupCamera(int width, int height);
        
    int mapColor(std::string colorName);
    int mapShape(std::string shapeName);

    
    ofColor pallete[10];
    ofImage images[7]; //array of images
    ofImage emptyImages[7]; //array of empty images
    ofColor background;

};
