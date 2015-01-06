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
    
    void display();
    void update();
    void checkEdges();
    void checkContour(ofPolyline contour);
    Ball();
    
private:
    ofVec2f loc;
    ofVec2f vel;
    ofVec2f acc;
    
    ofSoundPlayer sound;
    int rad;
    int mass;
    
    ofColor color;
    
    bool inside;
};



#endif
