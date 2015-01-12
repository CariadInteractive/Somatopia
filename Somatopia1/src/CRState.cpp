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
    soundStream.setup(0, 2, 44100, 512, 1);
    soundStream.setInput(this);
    //soundStream.stop();
    imageIndex = 0;
    colorIndex = 0;
    vidOn = true;
    
    audioFramesSinceLastSwapped = 0;
    MIN_FRAMES_BETWEEN_SWAPS = 0.3 * 44100; // 0.3 seconds at 44.1 kHz
    mustSwap = false;
    
    images[0].loadImage("Circle.png");
    images[1].loadImage("Cross.png");
    images[2].loadImage("Heart.png");
    images[3].loadImage("Hexagon.png");
    images[4].loadImage("Square.png");
    images[5].loadImage("Triangle.png");
    images[6].loadImage("Asterix.png");
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
    images[imageIndex].draw(ofGetWidth()/2, ofGetHeight()/2);
    ofPopStyle();
}

string CRState::getName()
{
    return "cr";
}

void CRState::mousePressed(int x, int y, int button)
{
    unsigned char *pixels=images[imageIndex].getPixels();
    int numPixels = images[imageIndex].getHeight() + images[imageIndex].getWidth();
    for(int index = 0; index < numPixels*4; index += 4)
    {
        int red = pixels[index];
        int green = pixels[index+1];
        int blue = pixels[index+2];
        int alpha = pixels[index+3];
        printf(">>>>%i >>>%i >>>%i >>>%i >>>%i\n", index, red,green,blue,alpha);
    }
    cout<<numPixels<<endl;
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
    imageIndex = (int)ofRandom(7);
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
                audioFramesSinceLastSwapped = 0;
            }
        }
        
        audioFramesSinceLastSwapped++;
    }
}