#pragma once

#include "ofMain.h"
#include "ofxAdafruitPWMBonnet.h"

//#define USE_IMGUI

#ifdef USE_IMGUI
#include "ofxImGui.h"
#else
#include "ofxGui.h"
#endif

#include "Servo.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void drawGUI();
    
#ifdef USE_IMGUI
    ofxImGui::Gui gui;
#else
    ofxPanel gui;
#endif
    
    ofxAdafruitPWMBonnet *controller = nullptr;
    Servo servo_one;
};
