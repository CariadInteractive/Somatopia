//
//  ball.h
//  bouncingBall
//
//  Created by James Bentley on 8/14/14.
//
//

#ifndef bouncingBall_ball_h
#define bouncingBall_ball_h

#include "ofMain.h"

class Ball
{
public:
    void setCol(ofColor newCol);
    void display();
    void update();
    void checkEdges();
    void checkContour(ofPolyline contour);
    void setFrame(int camWidth, int camHeight);
    Ball();
    
private:
    ofVec2f loc;
    ofVec2f vel;
    ofVec2f acc;
    
    int frameWidth;
    int frameHeight;
    
    ofSoundPlayer sound;
    int rad;
    int mass;
    
    ofColor col;
    
    bool inside;
    int soundTimer;
    int MIN_TIME_BETWEEN_BEEPS;
};



#endif
