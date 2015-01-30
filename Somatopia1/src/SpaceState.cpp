//
//  Splash.cpp
//  example
//
//  Created by James Bentley on 1/5/15.
//
//

#include "SpaceState.h"
#define NUMROWS 10
#define NUMCOLS 10

using namespace ofxCv;
using namespace cv;

void SpaceState::setup()
{
    spaceCam.setDeviceID(getSharedData().cam.listDevices().size() - 1);
    spaceCam.initGrabber(320, 240);
    ofSetRectMode(OF_RECTMODE_CORNER);
    tiles = vector<Tile>(); //initialize a vector of tiles
    int w = ofGetWidth() / NUMCOLS; //measure width of each tile
    int h = ofGetHeight() / NUMROWS; //measure height of each tile
    int k = 0; //set counter = 0
    
    /*iterate over rows and columns initializing tiles*/
    for(int i = 0; i < NUMROWS; i++) {
        for(int j = 0; j < NUMCOLS; j++) {
            tiles.push_back(Tile(j*w+w/2, i*h+h/2, w, h));//set tile locations
            tiles[k].setCols(getSharedData().pallete[0], getSharedData().pallete[4]); //set tile colors (inside then outside)
            k++;
        }
    }
}

void SpaceState::update()
{
    if(getSharedData().bVidOn) { //check if global video is on
        if(!tiles[0].vidIsOn()) { //check if tiles know video is on
            for(int i = 0; i < tiles.size(); i++) {
                tiles[i].activateVid(); //tell each tile that the video is on
            }
        }
    }
    else { //if video is off
        if(tiles[0].vidIsOn()) { //check if tiles think that video is on
            for(int i = 0; i < tiles.size(); i++) {
                tiles[i].deactivateVid(); //tell each tile that the video is off
            }
        }
    }
    spaceCam.update(); //update camera
    
    if(spaceCam.isFrameNew()) { //check if the frame is new
        getSharedData().colImg.setFromPixels(spaceCam.getPixels(), 320, 240); //set colImg from pixels from video Grabber
        getSharedData().colImg.mirror(false, true); //mirror image

        getSharedData().grayImage = getSharedData().colImg; //set grey image equal to colImg (it will remain grey because we initialized it that way in testApp.cpp)
        if(getSharedData().bLearnBackground) { //chekc if we need to learnt he background
            getSharedData().grayBg = getSharedData().grayImage; //set the background image
            getSharedData().bLearnBackground = false; //stop learning the background
        }
        
        getSharedData().grayDiff.absDiff(getSharedData().grayBg, getSharedData().grayImage); // take the difference of the background and grey imahe
        getSharedData().grayDiff.threshold(getSharedData().threshold); //threshold the difference
        
        getSharedData().contourFinder.findContours(getSharedData().grayDiff); //find blobs in the subtracted thresholded image
        
        int n = getSharedData().contourFinder.size(); //get number of blobs
        for(int i = 0; i < n; i++) {
            ofPolyline convexHull; //use this class to calculate intersections
            convexHull = ofxCv::toOf(getSharedData().contourFinder.getConvexHull(i)); //convert the blobs into ofPlyLines using ofxCv
            for(int j = 0; j < tiles.size(); j++) {
                tiles[j].checkContour(convexHull); //check if each tile is inside a blob
            }
        }
        int closedCount = 0;
        for(int i = 0; i < tiles.size(); i++)
        {
            tiles[i].update(); //flip the tiles
            if(tiles[i].isClosed()) closedCount++;
        }
        if(closedCount == NUMROWS*NUMCOLS) {
            int newCol = (int)ofRandom(8);
            for(int i = 0; i < tiles.size(); i++) {
                tiles[i].reset(getSharedData().pallete[newCol]);
            }
        }
    }
}

void SpaceState::draw()
{
    ofSetColor(255);
    if(tiles[0].vidIsOn()) //check if the tiles this video is on
    {
        getSharedData().colImg.draw(0, 0, ofGetWidth(), ofGetHeight()); // if they do then draw the camera stream to the frame
    }
    for(int i = 0; i < tiles.size(); i++) {
        tiles[i].display(); //draw the tiles
    }
    getSharedData().drawDebug(); //draw debug images if debug is turned on
}

string SpaceState::getName()
{
    return "space";
}

void SpaceState::mousePressed(int x, int y, int button)
{
    changeState("splash"); //change to main page
}

void SpaceState::keyPressed(int key)
{
    if(key == 's') {
        changeState("splash"); //change to main page
    }
    if(key == 'v') {
        getSharedData().bVidOn = !getSharedData().bVidOn; //toggle video on and off
    }
    /*functions to handle global states (see SharedData.cpp for more info)*/
    getSharedData().handleDebug(key);
    getSharedData().handleBackground(key);
    getSharedData().handleThreshold(key);
    getSharedData().handleUtils(key);

}