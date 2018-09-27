#pragma once

#include "ofMain.h"
#include "ofxAdafruitPWMBonnet.h"

#define USE_IMGUI

#ifdef USE_IMGUI
#include "ofxImGui.h"
#else
#include "ofxGui.h"
#endif

#include "Servo.h"
#include "Tween.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mousePressed(int x, int y,int button);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    void drawGUI();
    float getRelativeAngle(glm::vec2 from,glm::vec2 to);
    
#ifdef USE_IMGUI
    ofxImGui::Gui gui;
#else
    ofxPanel gui;
#endif
    
    ofxAdafruitPWMBonnet *controller = nullptr;
    vector <Servo*> servos;
    ofParameter <int> mode;

    ofPolyline line;
    Tween tween;
    void tweenFinished(string &val);
};
