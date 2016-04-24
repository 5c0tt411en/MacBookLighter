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
    //UI
    gui0->autoSizeToFitWidgets();
    
    //xmlsettings
    settings.loadFile("settings.xml");
    bLevel = settings.getValue("settings:ui1", 0.0);
    kbLevel = settings.getValue("settings:ui2", 0.0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ikbLevel = (int)ofMap(kbLevel, 0, 1, 0, 4095);
    }

//--------------------------------------------------------------
void ofApp::draw(){
    db.setBrightness(bLevel);
    kbb.setBrightness(ikbLevel);

}

void ofApp::exit()
{
    //xmlsettings
    settings.setValue("settings:ui1", bLevel);
    settings.setValue("settings:ui2", kbLevel);
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
