#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    if (controller)
        delete controller; // Delete if we have an instance already
    
    // Create a New Instance of the ofxAdafruitPWMBonnet using the Defaults
    controller = new ofxAdafruitPWMBonnet();
    controller->init("example-simple");
    
    servo_one.init(0x40,0,glm::vec2(ofGetWidth()/2,ofGetHeight()/2),0);
    
    gui.setup();
    
#ifndef USE_IMGUI
    gui.add(controller->parameters);
#endif
}

//--------------------------------------------------------------
void ofApp::exit()
{
    controller->close();
    
    if (controller)
        delete controller;
}

//--------------------------------------------------------------
void ofApp::update()
{
    int angle = 0 + 90 * sin(ofGetElapsedTimef());
    
    if (!controller->isMasterControlEnabled())
    {
        servo_one.setAngle(angle);
        controller->setAngle(servo_one.getPin(),servo_one.getCurrentAngle());
    }
    else
    {
        servo_one.setAngle(controller->getCurrentPWMValue(servo_one.getPin()));
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    drawGUI();
    servo_one.drawServo();
}

//--------------------------------------------------------------
void ofApp::drawGUI()
{
#ifdef USE_IMGUI
    auto settings = ofxImGui::Settings();
    settings.windowPos = glm::vec2(0,0);
    
    gui.begin();
    if (ofxImGui::BeginWindow("GUI", settings, false))
    {
        ImGui::Text("%.1f FPS (%.3f ms/frame)", ofGetFrameRate(), 1000.0f / ImGui::GetIO().Framerate);
        ImGui::TextWrapped("To effect PWM objects through the GUI. You must ENABLE the Master Control Checkbox :)");
        
        ofxImGui::AddGroup(controller->parameters, settings);
    }
    ofxImGui::EndWindow(settings);
    
    gui.end();
#else
    gui.draw();
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
}
