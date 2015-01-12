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
    rad = 100;
    col = ofColor(0);
    sound.loadSound("pongSound.ogg");
    soundTimer = 0;
    MIN_TIME_BETWEEN_BEEPS = 10;
}

void Ball::setCol(ofColor newCol)
{
    col = newCol;
}

void Ball::display()
{
    ofPushStyle();
    ofSetColor(col);
    ofFill();
    ofCircle(loc.x, loc.y, rad);
    ofPopStyle();
}

void Ball::update()
{
    vel += acc;
    loc += vel;
    soundTimer++;
    inside = false;
}

void Ball::checkEdges()
{
    if (loc.y > ofGetWindowHeight() - rad)
    {
        if(!sound.getIsPlaying() && soundTimer > MIN_TIME_BETWEEN_BEEPS) {
            sound.play();
            soundTimer = 0;
        }
        vel.y = vel.y * -1;
        loc.y = ofGetWindowHeight() - rad;
    }
    else if(loc.y < rad)
    {
        if(!sound.getIsPlaying() && soundTimer > MIN_TIME_BETWEEN_BEEPS) {
            sound.play();
            soundTimer = 0;
        }
        vel.y = vel.y * -1;
        loc.y = rad;
    }
    if (loc.x > ofGetWindowWidth() - rad)
    {
        if(!sound.getIsPlaying() && soundTimer > MIN_TIME_BETWEEN_BEEPS) {
            sound.play();
            soundTimer = 0;
        }
        vel.x = vel.x * -1;
        loc.x = ofGetWindowWidth() - rad;
    }
    else if(loc.x < rad)
    {
        if(!sound.getIsPlaying() && soundTimer > MIN_TIME_BETWEEN_BEEPS) {
            sound.play();
            soundTimer = 0;
        }
        vel.x = vel.x * -1;
        loc.x = rad;
    }
}

void Ball::checkContour(ofPolyline contour)
{
    if (contour.inside(ofMap(loc.x, 0, ofGetWidth(), 0, 320), ofMap(loc.y, 0, ofGetHeight(), 0, 240))) {
        if(!sound.getIsPlaying() && soundTimer > MIN_TIME_BETWEEN_BEEPS) {
            sound.play();
            soundTimer = 0;
        }
        ofVec2f centroid = contour.getCentroid2D();
        ofVec2f dir = centroid - loc;
        dir.normalize();
        loc += dir*vel.length();
        vel.x *= -1;
        vel.y *= -1;
    }
}