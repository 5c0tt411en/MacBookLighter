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
    void drawTargetFreq(string targetName, int freq, ofColor &rgb);
    
    //UI
    ofxUISuperCanvas *guiDB, *guiKBB, *guiAUDIO;
    ofxUITextInput *textInputDB, *textInputKBB;
    void exit();
    
    //xmlsettings
    ofxXmlSettings settings;
    
    //keyboard backlight brightness
    ofxKeyboardBacklightBrightness kbb;
    float kbbLevel;
    int ikbLevel;
    
    //display brightness
    ofxDisplayBrightness db;
    float dbLevel;
    
    //fft
    ofxFFTLive fft;
    float   audioThreshold,
            audioPeakDecay,
            audioMaxDecay,
            dbMin, kbbMin,
            dbMax, kbbMax;
    bool    audioReactiveDB, audioReactiveKBB;
    int     dbTargetFreq, kbbTargetFreq,
            guiWidth = 150;
    const int fftW = OFX_FFT_WIDTH,
              fftH = OFX_FFT_HEIGHT,
              fftX = (ofGetWidth() - fftW) / 2,
              fftY = ofGetHeight() - fftH - 10,
              guiW = 174,
              guiH = 150;
    ofColor dbColor, kbbColor;
    string freqTextDB, freqTextKBB;
};
