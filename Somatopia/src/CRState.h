//
//  Splash.h
//  example
//
//  Created by James Bentley on 1/5/15.
//
//
#pragma once

#include "ofxState.h"
#include "SharedData.h"

class CRState : public itg::ofxState<SharedData>, public ofBaseSoundInput
{
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    void audioIn(float *samples, int length, int numChannels);
    void tryToSwap();
    void swap();
    string getName();
private:
    ofSoundStream soundStream;
    int DeviceId;
    float sensitivity;
    float volume;
    float displayVolume;
    int audioFramesSinceLastSwapped;
    int MIN_FRAMES_BETWEEN_SWAPS;
    int imageIndex;
    int colorIndex;
    bool mustSwap;
    bool vidOn;
    ofImage images[7];
};