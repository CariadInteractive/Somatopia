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
    ofSoundStream soundStream; //sound input stream
    float sensitivity; //sound sensitivity
    float volume; //input volume
    float displayVolume; //square of input volume
    int audioFramesSinceLastSwapped; //audio counter
    int MIN_FRAMES_BETWEEN_SWAPS; //audio timer threshold
    int imageIndex; //index holding the image
    int colorIndex; //index holding the color
    bool mustSwap; //bool to tell update to change images and colors
    bool vidOn; //bool to check if vid is on (deprecated I believe)
    ofImage images[7]; //array of images
};