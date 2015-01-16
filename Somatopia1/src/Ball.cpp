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
    inside = false; //keep track of whether the ball is inside a blob
    loc.set(ofGetWidth()/2, ofGetHeight()/2); //initialize location to center of the screen
    vel.set(10, -5); //set the initial velocity
    acc.set(0, 0); //set the initial acceleration
    rad = 100; //set the radiu of the ball
    col = ofColor(0); //set the color of the ball
    sound.loadSound("pongSound.ogg"); //set hte sound that the ball will make whne it hits a wall
    soundTimer = 0; //counter for how long it's been before hte ball makes a sound again
    MIN_TIME_BETWEEN_BEEPS = 10; //minimum time between sounds
}

void Ball::setCol(ofColor newCol) //set color function
{
    col = newCol;
}

void Ball::display() //draw the ball
{
    ofPushStyle();
    ofSetColor(col);
    ofFill();
    ofCircle(loc.x, loc.y, rad);
    ofPopStyle();
}

void Ball::update() //update the balls location and increment the sound timer
{
    vel += acc;
    loc += vel;
    soundTimer++;
    inside = false;
}

void Ball::checkEdges() //bounce off of edges and play sound whenever it hits an edge
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

void Ball::checkContour(ofPolyline contour) //bounce off of ofPolyLine objects
{
    if (contour.inside(ofMap(loc.x, 0, ofGetWidth(), 0, 320), ofMap(loc.y, 0, ofGetHeight(), 0, 240))) //check if the ball is inside an ofPolyLine
    {
        if(!sound.getIsPlaying() && soundTimer > MIN_TIME_BETWEEN_BEEPS) { //if the sound isn;t currently playing and the sound timer is ok
            sound.play(); //play sound
            soundTimer = 0; //reset sound timer
        }
        ofVec2f centroid = contour.getCentroid2D(); //find the centroid of the polyLine blob
        ofVec2f dir = centroid - loc; //find direction from center of the polyLine blob
        dir.normalize(); //normalize that direction
        loc += dir*vel.length(); //set the ball outside of the blob so it doesn't get stuck in it
        //reverse the velocity (very rudimentary bouncing
        vel.x *= -1;
        vel.y *= -1;
    }
}