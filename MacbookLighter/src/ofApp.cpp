#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    kbb.setup();
    //ofxUI
    gui0 = new ofxUISuperCanvas("MacBookLighter");
    //UI1
    gui0->addSpacer();
    gui0->addFPSSlider("FPS SLIDER");
    //UI2
    gui0->addSpacer();
    gui0->addSlider("display brightness", 0.0, 1.0, &bLevel);
    //UI3
    gui0->addSpacer();
    gui0->addSlider("keyboarf backlight brightness", 0.0, 1.0, &kbLevel);
    //UI4
    gui0->addSpacer();
    gui0->addSlider("audio Threshould", 0.0, 1.0, &audioThreshold);
    //UI5
    gui0->addSpacer();
    gui0->addSlider("audio Peak Decay", 0.0, 1.0, &audioPeakDecay);
    //UI6
    gui0->addSpacer();
    gui0->addSlider("audio Max Decay", 0.0, 1.0, &audioMaxDecay);
    //UI
    gui0->autoSizeToFitWidgets();
    
    //xmlsettings
    settings.loadFile("settings.xml");
    bLevel = settings.getValue("settings:ui1", 0.0);
    kbLevel = settings.getValue("settings:ui2", 0.0);
    audioThreshold = settings.getValue("settings:ui3", 0.0);
    audioPeakDecay = settings.getValue("settings:ui4", 0.0);
    audioMaxDecay = settings.getValue("settings:ui5", 0.0);
    
    //ofxFFT
    fftLive.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ikbLevel = (int)ofMap(kbLevel, 0, 1, 0, 4095);
    
    //ofxFFT
    fftLive.setThreshold(audioThreshold);
    fftLive.setPeakDecay(audioPeakDecay);
    fftLive.setMaxDecay(audioMaxDecay);
    fftLive.setMirrorData(audioMirror);
    fftLive.update();
    int num = 1000;
    float * audioData = new float[num];
    fftLive.getFftPeakData(audioData, num);
    for (int i = 0; i < num; i++) {
        float audioValue = audioData[i];
        
    }
    delete[] audioData;
}

//--------------------------------------------------------------
void ofApp::draw(){
    db.setBrightness(bLevel);
    kbb.setBrightness(ikbLevel);
    
    //ofxFFT
    ofSetColor(255);
    int w = OFX_FFT_WIDTH;
    int h = OFX_FFT_HEIGHT;
    int x = 20;
    int y = ofGetHeight() - h - 20;
    fftLive.draw(x, y, w, h);
}

void ofApp::exit(){
    //xmlsettings
    settings.setValue("settings:ui1", bLevel);
    settings.setValue("settings:ui2", kbLevel);
    settings.setValue("settings:ui3", audioThreshold);
    settings.setValue("settings:ui4", audioPeakDecay);
    settings.setValue("settings:ui5", audioMaxDecay);
    settings.saveFile("settings.xml");
    
    //UI
    delete gui0;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
