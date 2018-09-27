#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    // List of default addresses
    deque<u_int16_t> ctrlAddress;
    ctrlAddress.push_back(0x40);
    ctrlAddress.push_back(0x41);
    ctrlAddress.push_back(0x42);
    
    
    int centerX = ofGetWidth() / 2;
    int offsetX = 43;
    
    glm::vec2 servoSize(25,50);
    
    // Create a number of controllers
    for (unsigned int i = 0; i < ctrlAddress.size(); i++)
    {
        controllers.insert(pair<u_int16_t,ofxAdafruitPWMBonnet*>(ctrlAddress[i],new ofxAdafruitPWMBonnet("Controller "+ofToString(i),ctrlAddress[i])));
        bFloatControllers.push_back(false);
        
        for(unsigned int e = 0; e < 16; e++)
        {
            timeOffsets.push_back(ofRandom(1.0, 5.0));
            
            servos.push_back(new Servo(ctrlAddress[i],
                                           e,
                                           glm::vec2(((servoSize.x/2 + centerX + (offsetX/2)) - (8 * (servoSize.x + offsetX))) + (e*(servoSize.x+offsetX)),100+ofGetHeight()/3*i),
                                           servoSize,
                                           0));
        }
    }
    
    gui.setup();
    
#ifndef USE_IMGUI
    for(std::map<u_int16_t,ofxAdafruitPWMBonnet*>::iterator it=controllers.begin(); it!=controllers.end(); ++it)
    {
        gui.add(it->second->parameters);
    }
#endif
}

//--------------------------------------------------------------
void ofApp::exit()
{
//    controller->close();
//
//    if (controller)
//        delete controller;
}

//--------------------------------------------------------------
void ofApp::update()
{

    for(std::map<u_int16_t,ofxAdafruitPWMBonnet*>::iterator it=controllers.begin(); it!=controllers.end(); ++it)
    {
        if(!it->second->isMasterControlEnabled())
        {
            for (unsigned int i = 0; i < servos.size(); i++)
            {
                if (servos[i]->getCtrlAddress() == it->second->getI2CAddress())
                {
                    int angle = 0 + 90 * sin(ofGetElapsedTimef()*timeOffsets[i]);
                    servos[i]->setAngle(angle);
                    it->second->setAngle(servos[i]->getPin(),servos[i]->getCurrentAngle());
                }
            }
        }
        else
        {
            for (unsigned int i = 0; i < servos.size(); i++)
            {
                if (servos[i]->getCtrlAddress() == it->second->getI2CAddress())
                {
                    servos[i]->setAngle(it->second->getCurrentPWMValue(servos[i]->getPin()));
                }
            }
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
        int i = 0;
        for(std::map<u_int16_t,ofxAdafruitPWMBonnet*>::iterator it=controllers.begin(); it!=controllers.end(); ++it)
        {
            if (bFloatControllers[i])
            {
                ImGui::Begin("Floating Ctrl",&bFloatControllers[i],ImGuiWindowFlags_AlwaysAutoResize);
                ofxImGui::AddGroup(it->second->parameters, settings);
                ImGui::End();
            }
            else
            {
                if (ImGui::SmallButton("Detach Controller"))
                {
                    bFloatControllers[i] = true;
                }
                ofxImGui::AddGroup(it->second->parameters, settings);
            }
            i++;
        }
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
