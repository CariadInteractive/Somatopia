//
//  MirrorState.h
//  Somatopia2
//
//  Created by James Bentley on 1/27/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxState.h"
#include "SharedData.h"
#define MIRROR_AMBIENT_LAPSE	0
#define MIRROR_SLITSCAN			1
#define MIRROR_KALEIDOSCOPE		2


class MirrorState : public itg::ofxState<SharedData> {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    string getName();
private:
    float timeOfLastStar;
    int ratio(int l, int r, float ratio);
    int type;
    
    ofVideoGrabber mirrorCam;
    
    // stuff specifically for MIRROR_KALEIDOSCOPE
    float offset;
    int star;
    
    unsigned char *buffer;
    ofxCvColorImage image;
    
    // stuff specifically for MIRROR_SLITSCAN
    int slitScanPos;
};
