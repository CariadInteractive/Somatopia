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
    Ball();
    
private:
    ofVec2f loc; //location of Ball
    ofVec2f vel; //velocity of Ball
    ofVec2f acc; //Acceleration of Ball
    
    ofSoundPlayer sound; //sound that the ball plays
    int rad; //radius of the ball
    int mass; //mass of the ball (not actually used, could be used for some physics)
    
    ofColor col; //color of the ball
    
    bool inside; //check if the ball is inside any polyLines
    int soundTimer; //timer to keep sound from pinging too much
    int MIN_TIME_BETWEEN_BEEPS; //min time between each sound being played
};



#endif
