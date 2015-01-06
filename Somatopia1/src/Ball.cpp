//
//  ball.cpp
//  bouncingBall
//
//  Created by James Bentley on 8/14/14.
//
//

#include "Ball.h"

Ball::Ball()
{
    inside = false;
    loc.set(ofGetWidth()/2, ofGetHeight()/2);
    vel.set(10, -5);
    acc.set(0, 0);
    rad = 10;
    color = ofColor::white;
    mass = 1;
    sound.loadSound("pongSound.ogg");
}


void Ball::display()
{
    ofSetColor(ofColor::red);
    ofFill();
    ofCircle(loc.x, loc.y, rad);
    ofDrawBitmapString("x: " + ofToString(loc.x) +  " y: " + ofToString(loc.y), loc.x+rad, loc.y+rad);
    inside = false;
}

void Ball::update()
{
    vel += acc;
    loc += vel;
}

void Ball::checkEdges()
{
    if (loc.y > ofGetWindowHeight() - 2*rad)
    {
        if(!sound.getIsPlaying()) {
            sound.play();
        }
        vel.y = vel.y * -1;
        loc.y = ofGetWindowHeight() - 2*rad;
    }
    else if(loc.y < -rad)
    {
        if(!sound.getIsPlaying()) {
            sound.play();
        }
        vel.y = vel.y * -1;
        loc.y = -rad;
    }
    if (loc.x > ofGetWindowWidth() - rad)
    {
        if(!sound.getIsPlaying()) {
            sound.play();
        }
        vel.x = vel.x * -1;
        loc.x = ofGetWindowWidth() - rad;
    }
    else if(loc.x < rad)
    {
        if(!sound.getIsPlaying()) {
            sound.play();
        }
        vel.x = vel.x * -1;
        loc.x = rad;
    }
}

void Ball::checkContour(ofPolyline contour)
{
    if (contour.inside(ofMap(loc.x, 0, ofGetWidth(), 0, 320), ofMap(loc.y, 0, ofGetHeight(), 0, 240))) {
        if(!sound.getIsPlaying()) {
            sound.play();
        }
        vel.x *= -1;
        vel.y *= -1;
    }
}