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
    //initialize sounds.
    sensitivity = 0.7;
    soundStream.setup(0, 2, 44100, 512, 1);
    soundStream.setInput(this);
    
    //set image and color to 0
    imageIndex = 0;
    colorIndex = 0;
    
    //setup swapping constants for swapping between images
    audioFramesSinceLastSwapped = 0;
    MIN_FRAMES_BETWEEN_SWAPS = 0.3 * 44100; // 0.3 seconds at 44.1 kHz
    mustSwap = false;
    
    //load images we are going to use
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
    if(mustSwap) { //if a swap has been triggered
        swap(); //swap the image
        mustSwap = false; //set swap to false
    }
}

void CRState::draw()
{
//    ofDrawBitmapString("Call & Responce is currently under development: press 's' to return the splash page", 0, 10);
    
    ofPushStyle();
    ofSetColor(getSharedData().pallete[colorIndex]); //set color to our swapped color
    ofSetRectMode(OF_RECTMODE_CENTER);
    images[imageIndex].draw(ofGetWidth()/2, ofGetHeight()/2); //draw image
    ofPopStyle();
}

string CRState::getName()
{
    return "cr";
}

void CRState::mousePressed(int x, int y, int button)
{
//    print info about what we're drawing for debugging and video support purposes (not yet implemented)
    
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
}

void CRState::keyPressed(int key)
{
    if(key == 's')
    {
        changeState("splash"); //change state back to main page
    }
}

void CRState::tryToSwap() {
    mustSwap = true; //set mustSwap to true
}

void CRState::swap() {
    colorIndex = (int)ofRandom(7); //change color
    if(getSharedData().pallete[colorIndex] == getSharedData().background)
    {
        swap(); //make sure you never get the background color
    }
    imageIndex = (int)ofRandom(7); //change image
}

void CRState::audioIn(float *samples, int length, int numChannels) {
    for(int i =0 ; i < length; i++) {
        float f = ABS(samples[i]); //calculate the volume of incoming audio
        if(volume<f) volume = f; //cap the volume of incoming audio
        else volume *= 0.9995; //unsure why we do this...
        displayVolume = sqrt(volume); //take the square of the volume
        if(displayVolume>sensitivity) { //check if volume is above preset sensitivity
            if(audioFramesSinceLastSwapped>MIN_FRAMES_BETWEEN_SWAPS) { //check if we havn't swapped recently
                tryToSwap(); //swap if the volme is high enough
                audioFramesSinceLastSwapped = 0; //reset audio frames to 0
            }
        }
        audioFramesSinceLastSwapped++; //increment audio frames
    }
}