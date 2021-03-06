#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
#ifdef __APPLE__
    ofAppGlutWindow window;
    ofSetupOpenGL(&window, 1024,768, OF_FULLSCREEN);			// <-------- setup the GL context
#elif __arm__
    ofSetupOpenGL(1280, 720, OF_FULLSCREEN);
#endif
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp( new testApp());
    
}