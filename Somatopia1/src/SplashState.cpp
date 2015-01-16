//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "SplashState.h"

void SplashState::setup()
{
    offSet = ofGetWidth()/100; //set offset for buttons so they don't bump into eachother
    buttonWidth = ofGetWidth()/2 - offSet*2; //set button width for our four buttons
    buttonHeight = ofGetHeight()/4 - offSet*2; //set button height for our four buttons
    
    /*initialize buttons*/
    flow = StateButton(offSet, (int)ofGetHeight()/2 - offSet, buttonWidth, buttonHeight, "flow");
    cr = StateButton((int)ofGetWidth()/2, (int)ofGetHeight()/2 - offSet, buttonWidth, buttonHeight, "cr");
    rhythm = StateButton(offSet, (int)ofGetHeight()*3/4 - offSet, buttonWidth, buttonHeight, "rhythm");
    space = StateButton((int)ofGetWidth()/2, (int)ofGetHeight()*3/4 - offSet, buttonWidth, buttonHeight, "space");
    options = StateButton(offSet, offSet, buttonWidth/2, buttonHeight/2, "options");
    
    /*set the images for our 4 buttons*/
    flow.setImage("flowSplash.png");
    cr.setImage("crSplash.png");
    rhythm.setImage("rhythmSplash.png");
    space.setImage("spaceSplash.png");
    options.setImage("optionsSplash.png");
}

void SplashState::update() {
    /*no udate stuff yet*/
}

void SplashState::draw()
{
    /*draw page title*/
    getSharedData().futura.drawString("Somatopia", ofGetWidth()/2 - getSharedData().futura.getStringBoundingBox("Somatopia", 0, 0).getWidth()/2, ofGetHeight() * 0.1);
    
    /*draw all of our interaction buttons*/
    flow.display();
    ofSetColor(255);
    getSharedData().futura.drawString("Flow", flow.getX() + flow.getW()/2 -getSharedData().futura.getStringBoundingBox("Flow", 0, 0).getWidth()/2, flow.getY() + flow.getH()/2);
    cr.display();
    ofSetColor(255);
    getSharedData().futura.drawString("Call & Response", cr.getX() + cr.getW()/2 -getSharedData().futura.getStringBoundingBox("Call & Response", 0, 0).getWidth()/2, cr.getY() + cr.getH()/2);
    rhythm.display();
    ofSetColor(255);
    getSharedData().futura.drawString("Rhythm", rhythm.getX() + rhythm.getW()/2 -getSharedData().futura.getStringBoundingBox("Rhythm", 0, 0).getWidth()/2, rhythm.getY() + rhythm.getH()/2);
    space.display();
    ofSetColor(255);
    getSharedData().futura.drawString("Space", space.getX() + space.getW()/2 -getSharedData().futura.getStringBoundingBox("Space", 0, 0).getWidth()/2, space.getY() + space.getH()/2);
    
    /*draw our optios button*/
    options.display();
    ofSetColor(255);
    getSharedData().futura.drawString("Options", options.getX() + options.getW()/2 -getSharedData().futura.getStringBoundingBox("Options", 0, 0).getWidth()/2, options.getY() + options.getH()/2);
}

string SplashState::getName()
{
    return "splash";
}

void SplashState::mousePressed(int x, int y, int button)
{
    /*handle state changes*/
    if(flow.isInside(x, y))
    {
        changeState(flow.getLink());
    }
    else if(cr.isInside(x, y))
    {
        changeState(cr.getLink());
    }
    else if(rhythm.isInside(x, y))
    {
        changeState(rhythm.getLink());
    }
    else if(space.isInside(x, y))
    {
        changeState(space.getLink());
    }
    else if(options.isInside(x, y))
    {
        changeState(options.getLink());
    }
}
