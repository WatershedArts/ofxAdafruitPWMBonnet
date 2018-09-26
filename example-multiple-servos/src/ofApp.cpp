#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    if (controller)
        delete controller; // Delete if we have an instance already
    
    // Create a New Instance of the ofxAdafruitPWMBonnet using the Defaults
    controller = new ofxAdafruitPWMBonnet();
    controller->init("example-multiple-servos");
    
    int centerX = ofGetWidth() / 2;
    int offsetX = 50;
    
    glm::vec2 servoSize(50,100);
    
    for(unsigned int i = 0; i < 16; i++)
    {
        timeOffsets.push_back(ofRandom(1.0, 5.0));
        if(i < 8)
        {
            servos.push_back(new Servo(0x40,
                                       i,
                                       glm::vec2(((servoSize.x/2 + centerX + (offsetX/2)) - (4 * (servoSize.x + offsetX))) + (i*(servoSize.x+offsetX)),ofGetHeight()/4),
                                       servoSize,
                                       0));
        }
        else
        {
            servos.push_back(new Servo(0x40,
                                       i,
                                       glm::vec2(((servoSize.x/2 + centerX + (offsetX/2)) - (4 * (servoSize.x + offsetX))) + ((i-8)*(servoSize.x+offsetX)),
                                                 ofGetHeight()/4*3),
                                       servoSize,
                                       0));
        }
    }
    
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
    if (!controller->isMasterControlEnabled())
    {
        for (unsigned int i = 0; i < servos.size(); i++)
        {
            int angle = 0 + 90 * sin(ofGetElapsedTimef()*timeOffsets[i]);
            servos[i]->setAngle(angle);
            controller->setAngle(servos[i]->getPin(),servos[i]->getCurrentAngle());
        }
    }
    else
    {
        for (unsigned int i = 0; i < servos.size(); i++)
        {
            servos[i]->setAngle(controller->getCurrentPWMValue(servos[i]->getPin()));
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    
    for(unsigned int i = 0; i < servos.size(); i++ )
    {
        servos[i]->drawServo();
    }
    
    drawGUI();
}

//--------------------------------------------------------------
void ofApp::drawGUI()
{
#ifdef USE_IMGUI
    auto settings = ofxImGui::Settings();
    settings.windowPos = glm::vec2(0,0);
    settings.lockPosition = true;
    
    gui.begin();
    if (ofxImGui::BeginWindow("GUI", settings, true))
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
