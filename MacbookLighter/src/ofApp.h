#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"
#include "ofxDisplayBrightness.h"
#include "ofxKeyboardBacklightBrightness.h"
#include "ofxFFTLive.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //UI
    ofxUISuperCanvas *gui0;
    void guiEvent(ofxUIEventArgs &e);
    void exit();
    
    //xmlsettings
    ofxXmlSettings settings;
    
    //keyboard backlight brightness
    ofxKeyboardBacklightBrightness kbb;
    float kbLevel;
    int ikbLevel;
    
    //display brightness
    ofxDisplayBrightness db;
    float bLevel;
    
    //fft
    ofxFFTLive fftLive;
    float   audioThreshold,
            audioPeakDecay,
            audioMaxDecay,
            audioMirror;
};
