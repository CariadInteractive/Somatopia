//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "SpaceState.h"
#define NUMROWS 20
#define NUMCOLS 20

using namespace ofxCv;
using namespace cv;

void SpaceState::setup()
{
    dimFac = 0.15;
    ofSetRectMode(OF_RECTMODE_CORNER);
    tiles = vector<Tile>();
    int w = ofGetWidth() / NUMCOLS;
    int h = ofGetHeight() / NUMROWS;
    int k = 0;
    for(int i = 0; i < NUMROWS; i++) {
        for(int j = 0; j < NUMCOLS; j++) {
            tiles.push_back(Tile(j*w+w/2, i*h+h/2, w, h));
            k++;
        }
    }
    
    alpha = 255;
    tick = 0;
    userIndex = (int)ofRandom(getSharedData().users.size());
    timer = ofGetElapsedTimeMillis();
}

void SpaceState::update()
{
#ifdef __arm__
    getSharedData().frame = getSharedData().cam.grab();
#elif __APPLE__
    getSharedData().cam.update();
    getSharedData().frame = toCv(getSharedData().cam.getPixelsRef());
#endif
    if(!getSharedData().frame.empty()) {
        cv::flip(getSharedData().frame, dst, 1);
        ofxCv::toOf(dst, getSharedData().colImg);
        getSharedData().colImg.update();
        cv::resize(dst, getSharedData().smallFrame, cv::Size(round(dimFac*getSharedData().frame.cols), round(dimFac*getSharedData().frame.rows)));
        farneback.calcOpticalFlow(getSharedData().smallFrame);
    }
    ofColor col = getSharedData().pallete[(int)ofRandom(7)];
    
    float w = ofMap(tiles[0].fullWidth, 0, ofGetWidth(), 0, getSharedData().camWidth*dimFac);
    float h = ofMap(tiles[0].h, 0, ofGetHeight(), 0, getSharedData().camHeight*dimFac);
    float avg = farneback.getAverageFlow().length();
    cout<<avg<<endl;
    for(int i = 0; i < tiles.size(); i++) {
        float x = ofMap(tiles[i].x, 0, ofGetWidth(), 0, getSharedData().camWidth*dimFac);
        float y = ofMap(tiles[i].y, 0, ofGetHeight(), 0, getSharedData().camHeight*dimFac);
        ofRectangle region = ofRectangle(x, y, w, h);
        float flow = farneback.getAverageFlowInRegion(region).length();
//        cout<<flow<<endl;
        if(flow > avg) {
            if(avg > 0.02) {
                tiles[i].activate();
            }
        }
        else {
            tiles[i].deactivate();
        }
        tiles[i].update(col);
    }
}

void SpaceState::draw()
{
    ofSetColor(255);
    getSharedData().colImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    for(int i = 0; i < tiles.size(); i++) {
        tiles[i].display();
    }
//    farneback.draw(0, 0, ofGetWidth(), ofGetHeight());
    if(getSharedData().performanceOn) {
        int timeLength = 20000;
        int nextIndex = (userIndex + 1)%getSharedData().users.size();
        ofSetColor(ofColor(255), alpha);
        getSharedData().nameFutura.drawString(getSharedData().users[userIndex].name, ofGetWidth()/2 - getSharedData().nameFutura.getStringBoundingBox(getSharedData().users[userIndex].name, 0, 0).getWidth()/2, ofGetHeight()/4);
        getSharedData().nameFutura.drawString(getSharedData().users[nextIndex].name, ofGetWidth()/2 - getSharedData().nameFutura.getStringBoundingBox(getSharedData().users[nextIndex].name, 0, 0).getWidth()/2, ofGetHeight()*3/4);
        if(ofGetElapsedTimeMillis() - timer > timeLength/255) {
            tick++;
            alpha -= 255/(timeLength/255)*2;
            timer = ofGetElapsedTimeMillis();
            if(tick > timeLength/255) {
                timer = ofGetElapsedTimeMillis();
                tick = 0;
                alpha = 255;
                userIndex += 2;
                userIndex%=getSharedData().users.size();
            }
        }
    }
}

string SpaceState::getName()
{
    return "space";
}

void SpaceState::mousePressed(int x, int y, int button) {
    if(button == OF_MOUSE_BUTTON_RIGHT) {
        changeState("splash");
    }
}

void SpaceState::keyPressed(int key)
{
    if(key == 's') {
        changeState("splash");
    }
    if(key == 'v') {
        getSharedData().bVidOn = !getSharedData().bVidOn;
    }
    getSharedData().handleDebug(key);
    getSharedData().handleBackground(key);
    getSharedData().handleThreshold(key);
    switch (key) {
        case '1':
            changeState("soundWheel");
            getSharedData().performanceOn = false;
            break;
        case '2':
            changeState("mirror");
            getSharedData().performanceOn = false;
            break;
        case '3':
            changeState("space");
            getSharedData().performanceOn = false;
            break;
        case '4':
            changeState("flow");
            getSharedData().performanceOn = false;
            break;
        case 'p':
            getSharedData().performanceOn = !getSharedData().performanceOn;
            alpha = 255;
            tick = 0;
            userIndex = (int)ofRandom(getSharedData().users.size());
            timer = ofGetElapsedTimeMillis();
            break;
        default:
            break;
    }
}