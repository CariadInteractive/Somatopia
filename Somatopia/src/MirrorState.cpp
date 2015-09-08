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
    buffer = NULL;
    timeOfLastStar = -100;
    
    star = 2;
    offset = 0.5;
    slitScanPos = 0;
    
//    if(buffer==NULL) {
//        buffer = new unsigned char[WIDTH*HEIGHT*3];
//        memset(buffer, 0, WIDTH*HEIGHT*3);
//    }
    image.allocate(WIDTH, HEIGHT, OF_IMAGE_COLOR);
    
    alpha = 255;
    tick = 0;
    userIndex = (int)ofRandom(getSharedData().users.size());
    timer = ofGetElapsedTimeMillis();
    
//    image.set(0);
}

void MirrorState::stateEnter() {
    getSharedData().wheelCount = 2;
}

void MirrorState::update() {
#ifdef __arm__
    getSharedData().frame = getSharedData().cam.grab();
#elif __APPLE__
    getSharedData().cam.update();
    getSharedData().frame = ofxCv::toCv(getSharedData().cam.getPixelsRef());
#endif
    if(!getSharedData().frame.empty()) {
        ofxCv::toOf(getSharedData().frame, image);
    }
    image.update();
    star = 6;//getSharedData().wheelCount;
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
            vec.x += ofGetHeight();
            
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
        // pop normalized tex 84coords
        if(!usingNormTexCoords) {
            ofDisableNormalizedTexCoords();
        }
    } else {
        image.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    if(getSharedData().performanceOn) {
        int timeLength = 90000;
        ofSetColor(ofColor(255), alpha);
        getSharedData().nameFutura.drawString(getSharedData().users[userIndex].name, ofGetWidth()/2 - getSharedData().nameFutura.getStringBoundingBox(getSharedData().users[userIndex].name, 0, 0).getWidth()/2, ofGetHeight()/2);
        if(ofGetElapsedTimeMillis() - timer > timeLength/255) {
            tick++;
            alpha -= 1;
            timer = ofGetElapsedTimeMillis();
            if(tick > 255) {
                timer = ofGetElapsedTimeMillis();
                tick = 0;
                alpha = 255;
                userIndex++;
                userIndex%=getSharedData().users.size();
            }
        }
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
    getSharedData().handlePerformance(key);
//    else {
//        star++;
//    }
    getSharedData().handleDebug(key);
    getSharedData().handleBackground(key);
    getSharedData().handleThreshold(key);
    getSharedData().handleUtils(key);
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

int MirrorState::ratio(int l, int r, float ratio) {
    float f = ((float)l)*ratio + ((float)r)*(1.f - ratio);
    return (int) f;
}

string MirrorState::getName() {
    return "mirror";
}
