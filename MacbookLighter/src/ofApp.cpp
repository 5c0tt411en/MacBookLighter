#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(165, 160, 175);
    ofSetVerticalSync(true);
    
    //ofxKeyboardBrightness
    kbb.setup();
    
    //xmlsettings
    settings.loadFile("settings.xml");
    dbLevel = settings.getValue("settings:ui1", 0.0);
    kbbLevel = settings.getValue("settings:ui2", 0.0);
    dbTargetFreq = settings.getValue("settings:ui3", 0.0);
    freqTextDB = ofToString(settings.getValue("settings:ui3-1", 0.0));
    dbMin = settings.getValue("settings:ui4", 0.0);
    dbMax = settings.getValue("settings:ui5", 0.0);
    kbbTargetFreq = settings.getValue("settings:ui6", 0.0) ;
    freqTextKBB = ofToString(settings.getValue("settings:ui6-1", 0.0));
    kbbMin = settings.getValue("settings:ui7", 0.0);
    kbbMax = settings.getValue("settings:ui8", 0.0);
    audioThreshold = settings.getValue("settings:ui9", 0.0);
    audioPeakDecay = settings.getValue("settings:ui10", 0.0);
    audioMaxDecay = settings.getValue("settings:ui11", 0.0);
    
    //ofxUI
    guiDB = new ofxUISuperCanvas("Display");
    guiDB->setTheme(7);
    guiDB->setPosition(0, 0);
    guiDB->setGlobalCanvasWidth(guiW);
    guiDB->setDrawBack(false);
    guiDB->setHeight(guiH);
    guiDB->addSpacer();
    guiDB->addSlider("display brightness", 0.0, 1.0, &dbLevel);
    guiDB->addSpacer();
    guiDB->addLabel("Audio reactive mode");
    guiDB->addToggle("audio reactive I/O", &audioReactiveDB, 20, 20);
    textInputDB = guiDB->addTextInput("display target freq.", freqTextDB);
    textInputDB->setAutoClear(false);
    guiDB->addRangeSlider("brightness range", 0.0, 1.0, &dbMin, &dbMax);
    guiDB->autoSizeToFitWidgets();
    
    guiKBB = new ofxUISuperCanvas("Keyboard");
    guiKBB->setTheme(5);
    guiKBB->setPosition(guiDB->getGlobalCanvasWidth(), 0);
    guiKBB->setGlobalCanvasWidth(guiW);
    guiKBB->setDrawBack(false);
    guiKBB->setHeight(guiH);
    guiKBB->addSpacer();
    guiKBB->addSlider("keyboard brightness", 0.0, 1.0, &kbbLevel);
    guiKBB->addSpacer();
    guiKBB->addLabel("Audio reactive mode");
    guiKBB->addToggle("audio reactive I/O", &audioReactiveKBB, 20, 20);
    textInputKBB = guiKBB->addTextInput("keyboard target freq.", freqTextKBB);
    textInputKBB->setAutoClear(false);
    guiKBB->addRangeSlider("brightness range", 0.0, 1.0, &kbbMin, &kbbMax);
    guiKBB->autoSizeToFitWidgets();
    
    guiAUDIO = new ofxUISuperCanvas("Audio setting");
    guiAUDIO->setTheme(19);
    guiAUDIO->setPosition(guiDB->getGlobalCanvasWidth() + guiKBB->getGlobalCanvasWidth(), 0);
    guiAUDIO->setGlobalCanvasWidth(guiW);
    guiAUDIO->setDrawBack(false);
    guiAUDIO->setHeight(guiH);
    guiAUDIO->addSpacer();
    guiAUDIO->addSlider("audio threshould", 0.0, 1.0, &audioThreshold);
    guiAUDIO->addSlider("audio peak decay", 0.0, 1.0, &audioPeakDecay);
    guiAUDIO->addSlider("audio max decay", 0.0, 1.0, &audioMaxDecay);
    guiAUDIO->autoSizeToFitWidgets();
    
    //ofxFFT
    fft.setup();
    
    dbColor.r = 251;
    dbColor.g = 89;
    dbColor.b = 101;
    kbbColor.r = 39;
    kbbColor.g = 108;
    kbbColor.b = 185;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ikbLevel = (int)ofMap(kbbLevel, 0, 1, 0, 4095);
    
    freqTextDB = textInputDB->getTextString();
    dbTargetFreq = ofToInt(freqTextDB);
    freqTextKBB = textInputKBB->getTextString();
    kbbTargetFreq = ofToInt(freqTextKBB);
    
    //ofxFFT
    fft.setThreshold(audioThreshold);
    fft.setPeakDecay(audioPeakDecay);
    fft.setMaxDecay(audioMaxDecay);
    fft.update();
    int num = 22000;
    float * audioData = new float[num];
    fft.getFftPeakData(audioData, num);
    for (int i = 0; i < num; i++) float audioValue = audioData[i];
    if (audioReactiveDB) {
        dbLevel = audioData[dbTargetFreq];
        dbLevel = ofMap(dbLevel, 0.0, 1.0, dbMin, dbMax);
        while (dbLevel > dbMax) dbLevel = dbMax;
    }
    if (audioReactiveKBB) {
        kbbLevel = audioData[kbbTargetFreq];
        kbbLevel = ofMap(kbbLevel, 0.0, 1.0, kbbMin, kbbMax);
        while (kbbLevel > kbbMax) kbbLevel = kbbMax;
    }
    delete[] audioData;
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofxDisplayBrightness, ofxKeyboardBrightness
    db.setBrightness(dbLevel);
    kbb.setBrightness(ikbLevel);
    
    //ofxFFT
    ofSetColor(255);
    fft.draw(fftX, fftY, fftW, fftH);
    
    // draw line to target freq.
    drawTargetFreq("Display", dbTargetFreq, dbColor);
    drawTargetFreq("Keyboard", kbbTargetFreq, kbbColor);
}

void ofApp::exit(){
    //xmlsettings
    settings.setValue("settings:ui1", dbLevel);
    settings.setValue("settings:ui2", kbbLevel);
    settings.setValue("settings:ui3", dbTargetFreq);
    settings.setValue("settings:ui3-1", freqTextDB);
    settings.setValue("settings:ui4", dbMin);
    settings.setValue("settings:ui5", dbMax);
    settings.setValue("settings:ui6", kbbTargetFreq);
    settings.setValue("settings:ui6-1", freqTextKBB);
    settings.setValue("settings:ui7", kbbMin);
    settings.setValue("settings:ui8", kbbMax);
    settings.setValue("settings:ui9", audioThreshold);
    settings.setValue("settings:ui10", audioPeakDecay);
    settings.setValue("settings:ui11", audioMaxDecay);
    settings.saveFile("settings.xml");
    
    //UI
    delete guiDB;
    delete guiKBB;
    delete guiAUDIO;
}

void ofApp::drawTargetFreq(string targetName, int freq, ofColor &rgb){
    ofSetColor(rgb);
    ofDrawLine(fftX + (float)freq / 42.96825, fftY, fftX + (float)freq / 42.96825, fftY + fftH);
    targetName += '\n' + ofToString(freq) + "Hz";
    ofDrawBitmapString(targetName, fftX + (float)freq / (22000 / 512) + 5, fftY + fftH / 2);
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
