//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "CRState.h"

void CRState::setup()
{
    sensitivity = 0.7;
    soundStream.setInput(this);
#ifdef __arm__
    soundStream.setDeviceID(2);
    soundStream.listDevices();
#endif
    soundStream.setup(0, 1, 44100, 512, 1);
    //soundStream.stop();
    imageIndex = 0;
    colorIndex = 0;
    vidOn = true;
    
    audioFramesSinceLastSwapped = 0;
    MIN_FRAMES_BETWEEN_SWAPS = 0.3 * 44100; // 0.3 seconds at 44.1 kHz
    mustSwap = false;
}

void CRState::update()
{
    if(mustSwap) {
        swap();
        mustSwap = false;
    }
}

void CRState::draw()
{
//    ofDrawBitmapString("Call & Responce is currently under development: press 's' to return the splash page", 0, 10);
    ofPushStyle();
    ofSetColor(getSharedData().pallete[colorIndex]);
    ofSetRectMode(OF_RECTMODE_CENTER);
    getSharedData().images[imageIndex].draw(ofGetWidth()/2, ofGetHeight()/2);
    ofPopStyle();
}

string CRState::getName()
{
    return "cr";
}

void CRState::mousePressed(int x, int y, int button)
{
    if(button == OF_MOUSE_BUTTON_RIGHT) {
        changeState("splash");
    }
//    unsigned char *pixels=images[imageIndex].getPixels();
//    int numPixels = images[imageIndex].getHeight() + images[imageIndex].getWidth();
//    for(int index = 0; index < numPixels*4; index += 4)
//    {
//        int red = pixels[index];
//        int green = pixels[index+1];
//        int blue = pixels[index+2];
//        int alpha = pixels[index+3];
//        printf(">>>>%i >>>%i >>>%i >>>%i >>>%i\n", index, red,green,blue,alpha);
//    }
//    cout<<numPixels<<endl;
//    changeState("splash");
}

void CRState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash");
    }
}

void CRState::tryToSwap() {
    mustSwap = true;
}

void CRState::swap() {
    colorIndex = (int)ofRandom(7);
    if(getSharedData().pallete[colorIndex] == getSharedData().background)
    {
        swap();
    }
    int newIndex = (int)ofRandom(7);
    if(newIndex == imageIndex) {
        imageIndex++;
        imageIndex %= 7;
    }
}

void CRState::audioIn(float *samples, int length, int numChannels) {
    for(int i =0 ; i < length; i++) {
        float f = ABS(samples[i]);
        if(volume<f) volume = f;
        else volume *= 0.9995;
        displayVolume = sqrt(volume);
        if(displayVolume>sensitivity) {
            if(audioFramesSinceLastSwapped>MIN_FRAMES_BETWEEN_SWAPS) {
                tryToSwap();
                getSharedData().wheelCount++;
                audioFramesSinceLastSwapped = 0;
            }
        }
        audioFramesSinceLastSwapped++;
    }
}
