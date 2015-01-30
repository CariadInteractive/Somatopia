//
//  MirrorState.cpp
//  Somatopia2
//
//  Created by James Bentley on 1/27/15.
//
//

#include "MirrorState.h"

#define WIDTH 320
#define HEIGHT 240

void MirrorState::setup() {
    type = MIRROR_KALEIDOSCOPE;
    mirrorCam.setDeviceID(getSharedData().cam.listDevices().size() - 1);
    mirrorCam.initGrabber(320, 240);
    buffer = NULL;
    timeOfLastStar = -100;
    
    star = 2;
    offset = 0.5;
    slitScanPos = 0;
    
    if(buffer==NULL) {
        buffer = new unsigned char[WIDTH*HEIGHT*3];
        memset(buffer, 0, WIDTH*HEIGHT*3);
    }
    image.allocate(WIDTH, HEIGHT);
    
    image.set(0);
}

void MirrorState::update() {
    star = getSharedData().wheelCount;
    if(getSharedData().wheelCount >= 10) getSharedData().wheelCount = 0;
    mirrorCam.update();
    if(mirrorCam.isFrameNew()) {
        
        image.setFromPixels(mirrorCam.getPixelsRef());
        
        int numPixels = image.getWidth()*image.getHeight()*3;
        unsigned char *pixels = image.getPixels();
        if(type==MIRROR_AMBIENT_LAPSE) {
            
            // blend previous frames
            float feedback = 0.05;
            float ff = 0.03*255;
            int f = ff;
            int mf = 255 - f;
            for (int i = 0; i < numPixels; i++) { // For each pixel in the video frame...
                buffer[i] = (pixels[i]*f + buffer[i]*mf)/256;
                //				pixels[i] = ratio(pixels[i], buffer[i], feedback);
                //buffer[i] = pixels[i];
            }
            //memcpy(buffer, pixels, numPixels);
        } else if(type==MIRROR_SLITSCAN) {
            
            for(int i = 0; i < 2; i++) {
                // only copy one row of pixels
                int pixelsStart = slitScanPos*image.getWidth()*3;
                int numPixToCopy = image.getWidth()*3;
                
                memcpy(buffer + pixelsStart, pixels+pixelsStart, numPixToCopy);
                
                
                // increment and wrap the position
                slitScanPos++;
                if(slitScanPos>=image.getHeight()) slitScanPos = 0;
            }
            // then copy the whole buffer over
            memcpy(pixels, buffer, numPixels);
            
        }
        
        if(type==MIRROR_AMBIENT_LAPSE) {
            image.setFromPixels(buffer, image.getWidth(), image.getHeight());
        } else {
            
            image.setFromPixels(pixels, image.getWidth(), image.getHeight());
        }
        
        // because we're not calling draw() on the camera's image
        // when doing mirror, we need to explicitly update the
        // texture on the video card.
        if(type==MIRROR_KALEIDOSCOPE) {
            image.updateTexture();
        }
    }
}

void MirrorState::draw() {
    ofSetHexColor(0xFFFFFF);
    bool usingNormTexCoords = ofGetUsingNormalizedTexCoords();
    
    //image.draw(0, 0, WIDTH, HEIGHT);
    if(type==MIRROR_KALEIDOSCOPE) {
        // push normalized tex coords
        if(!usingNormTexCoords) {
            ofEnableNormalizedTexCoords();
        }
        
        image.getTextureReference().bind();
        
        if(star<=2) {
            ofMesh mesh;
            mesh.clear();
            mesh.addVertex(ofVec3f(0, 0));
            mesh.addVertex(ofVec3f(0, ofGetHeight()));
            mesh.addVertex(ofVec3f(ofGetWidth()/2, 0));
            mesh.addVertex(ofVec3f(ofGetWidth()/2, ofGetHeight()));
            mesh.addVertex(ofVec3f(ofGetWidth(), 0));
            mesh.addVertex(ofVec3f(ofGetWidth(), ofGetHeight()));
            
            
            mesh.addTexCoord(ofVec2f(0.25, 0.0));
            mesh.addTexCoord(ofVec2f(0.25, 1.0));
            mesh.addTexCoord(ofVec2f(0.75, 0.0));
            mesh.addTexCoord(ofVec2f(0.75, 1.0));
            mesh.addTexCoord(ofVec2f(0.25, 0.0));
            mesh.addTexCoord(ofVec2f(0.25, 1.0));
            
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            mesh.draw();
        } else {
            
            float angle = 360.f/(float)star;
            
            
            
            ofMesh mesh;
            
            ofVec3f vec(0,0,0);
            mesh.addVertex(vec);
            vec.x += ofGetHeight()/2;
            
            for(int i = 0; i < star; i++) {
                mesh.addVertex(vec);
                vec.rotate(angle, ofVec3f(0,0,1));
            }
            
            // close the loop
            mesh.addVertex(vec);
            
            
            
            // now work out the texcoords
            /*
             __________________
             |   \        /   |
             |    \      /    |
             |     \    /     |
             |      \  /      |
             |       \/       |
             +----------------+
             
             A v shape out of the centre of the camera texture
             */
            
            
            
            float realOffset = 0.5;
            // normalized distance from the centre (half the width of the above 'V')
            float dist = ABS((float)image.getHeight()*tan(ofDegToRad(angle)*0.5))/(float)image.getHeight();
            
            
            // the realOffset is where the (normalized) middle of the 'V' is on the x-axis
            realOffset = ofMap(offset, 0, 1, dist, 1-dist);
            
            
            // this is the point at the bottom of the triangle - our centre for the triangle fan
            mesh.addTexCoord(ofVec2f(realOffset, 1));
            
            
            ofVec2f ta(realOffset-dist, 0);
            ofVec2f tb(realOffset+dist, 0);
            for(int i = 0; i <= star; i++) {
                if(i%2==0) {
                    mesh.addTexCoord(ta);
                } else {
                    mesh.addTexCoord(tb);
                }
            }
            
            
            glPushMatrix();
            glTranslatef(ofGetWidth()/2, ofGetHeight()/2, 0);
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
            mesh.draw();
            glPopMatrix();
        }
        
        image.getTextureReference().unbind();
        
        float timeSinceLastStar = ofGetElapsedTimef() - timeOfLastStar;
        
        if(timeSinceLastStar<1) {
            glLineWidth(3);
            glColor4f(1, 1, 1, ofMap(timeSinceLastStar, 0, 1, 1, 0));
            if(star>2) {
                glPushMatrix();
                glTranslatef(ofGetWidth()/2, ofGetHeight()/2, 0);
                
                for(int i = 0; i < star; i++) {
                    float angle = ofMap(i, 0, star, 0, PI*2);
                    ofLine(0, 0, (ofGetWidth()/2)*cos(angle), (ofGetHeight()/2)*sin(angle));
                }
                glPopMatrix();
            } else {
                ofLine(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
            }
            glLineWidth(1);
        }
        // pop normalized tex coords
        if(!usingNormTexCoords) {
            ofDisableNormalizedTexCoords();
        }
    } else {
        image.draw(0, 0, ofGetWidth(), ofGetHeight());
    }

}

void MirrorState::mousePressed(int x, int y, int button) {
//    int newStar = 2*(int)ofMap(x, 0, ofGetWidth(), 1, 10);
//    if(newStar!=star) {
//        timeOfLastStar = ofGetElapsedTimef();
//    }
//    star = newStar;
//    offset = ofMap(y, 0, ofGetHeight(), 0, 1);
//    return true;
}

void MirrorState::keyPressed(int key) {
    if(key == 's')
    {
        changeState("splash"); //change state to main page
    }
    getSharedData().handleDebug(key);
    getSharedData().handleBackground(key);
    getSharedData().handleThreshold(key);
    getSharedData().handleUtils(key);
}

int MirrorState::ratio(int l, int r, float ratio) {
    float f = ((float)l)*ratio + ((float)r)*(1.f - ratio);
    return (int) f;
}

string MirrorState::getName() {
    return "mirror";
}