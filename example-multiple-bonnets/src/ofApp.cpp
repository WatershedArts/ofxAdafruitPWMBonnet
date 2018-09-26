#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup()
{
    if (controller_one)
        delete controller_one; // Delete if we have an instance already
    
    if (controller_two)
        delete controller_two; // Delete if we have an instance already
    
    // Create a New Instance of the ofxAdafruitPWMBonnet
    controller_one = new ofxAdafruitPWMBonnet();
    controller_one->init("Controller One", 0x40);
    
    // Create a New Instance of the ofxAdafruitPWMBonnet 
    controller_two = new ofxAdafruitPWMBonnet();
    controller_two->init("Controller Two", 0x41);
    gui.setup();
    
#ifndef USE_IMGUI
    gui.add(controller_one->parameters);
    gui.add(controller_two->parameters);
#endif
}

//--------------------------------------------------------------
void ofApp::exit()
{
    controller_one->close();
    controller_two->close();
    
    if (controller_one)
        delete controller_one;
    
    if (controller_two)
        delete controller_two;
}

//--------------------------------------------------------------
void ofApp::update()
{
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    drawGUI();
}

//--------------------------------------------------------------
void ofApp::drawGUI()
{
#ifdef USE_IMGUI
    auto settings = ofxImGui::Settings();
    gui.begin();
    {
        if (ofxImGui::BeginWindow("example-multiple-bonnets", settings,ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
        {
            ImGui::Text("%.1f FPS (%.3f ms/frame)", ofGetFrameRate(), 1000.0f / ImGui::GetIO().Framerate);
            ImGui::TextWrapped("To effect PWM objects through the GUI. You must ENABLE the Master Control Checkbox :)");

            
            if (bFloatControllerOne)
            {
                ImGui::Begin("Floating Ctrl One",&bFloatControllerOne,ImGuiWindowFlags_AlwaysAutoResize);
                ofxImGui::AddGroup(controller_one->parameters, settings);
                ImGui::End();
            }
            else
            {
                if (ImGui::SmallButton("Detach Controller One"))
                {
                    bFloatControllerOne = true;
                }
                ofxImGui::AddGroup(controller_one->parameters, settings);
            }
            
            if (bFloatControllerTwo)
            {
                ImGui::Begin("Floating Ctrl Two",&bFloatControllerTwo,ImGuiWindowFlags_AlwaysAutoResize);
                ofxImGui::AddGroup(controller_two->parameters, settings);
                ImGui::End();
            }
            else
            {
                if (ImGui::SmallButton("Detach Controller Two"))
                {
                    bFloatControllerTwo = true;
                }
                ofxImGui::AddGroup(controller_two->parameters, settings);
            }
        }
        ofxImGui::EndWindow(settings);
    }
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
