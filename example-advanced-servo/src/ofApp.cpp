#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    if (controller)
        delete controller; // Delete if we have an instance already
    
    // Create a New Instance of the ofxAdafruitPWMBonnet using the Defaults
    controller = new ofxAdafruitPWMBonnet();
    controller->init("example-advanced-servo");
    
    glm::vec2 servoSize(50,100);
    int centerX = ofGetWidth() / 2;
    int offsetX = 50;
    
    for(unsigned int i = 0; i < 8; i++)
    {
        servos.push_back(new Servo(0x40,
                                   i,
                                   glm::vec2(((servoSize.x/2 + centerX + (offsetX/2)) - (4 * (servoSize.x + offsetX))) + (i*(servoSize.x+offsetX)),ofGetHeight()/4*3),
                                       servoSize,
                                       0));
    }

    tween.setup(0, "Line");
    gui.setup();
    
#ifndef USE_IMGUI
    gui.add(mode.set("Mode",0,0,3));
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
float ofApp::getRelativeAngle(glm::vec2 from,glm::vec2 to)
{
    float angle;
    float cx = from.x - to.x;
    float cy = from.y - to.y;
    
    if(cy == 0)
    {
        angle = 0;
    }
    else if(cy < 0)
    {
        angle = -90 * (cx < 0 ? -1 : 1); // Clamping as not to divide by zero
    }
    else
    {
        angle = atan(-cx / cy) * 180 / M_PI;
    }
    
    return angle;
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
    
    int angle = 0 + 90 * sin(ofGetElapsedTimef());
    
    ofSetColor(85, 239, 196);
    
    if (!controller->isMasterControlEnabled())
    {
        switch (mode)
        {
            case 0:
            {
                for(unsigned int i = 0; i < servos.size(); i++)
                {
                    servos[i]->setAngle(angle);
                }
            }
                break;
            case 1:
            {
                for(unsigned int i = 0; i < servos.size(); i++)
                {
                    servos[i]->setAngle(getRelativeAngle(servos[i]->getPosition(),glm::vec2(mouseX,mouseY)));
                    
                    controller->setAngle(servos[i]->getPin(), servos[i]->getCurrentAngle());
                    ofDrawCircle(mouseX,mouseY,10);
                }
            }
                break;
            case 2:
            {
                int x = ofGetWidth()/2;
                int y = ofGetHeight()/4;
                
                x = x + 100 * cos(ofGetElapsedTimef());
                y = y + 100 * sin(ofGetElapsedTimef());
                
                ofDrawCircle(x, y, 10   );
                for(unsigned int i = 0; i < servos.size(); i++)
                {
                    servos[i]->setAngle(getRelativeAngle(servos[i]->getPosition(),glm::vec2(x,y)));
                    
                    controller->setAngle(servos[i]->getPin(), servos[i]->getCurrentAngle());
                }
            }
                break;
            case 3:
            {
                if(!tween.hasCompleted())
                {
                    if(line.size() > 0)
                    {
                        
                        glm::vec2 t = line.getPointAtPercent(tween.getCurrentValue());
                        for(unsigned int i = 0; i < servos.size(); i++)
                        {
                            servos[i]->setAngle(getRelativeAngle(servos[i]->getPosition(),t));
                            
                            controller->setAngle(servos[i]->getPin(), servos[i]->getCurrentAngle());
                        }
                        ofDrawCircle(t,10);
                    }
                }
                
                line.draw();
            }
                break;
            default:
                break;
        }
    }
    else
    {
        for(unsigned int i = 0; i < servos.size(); i++)
        {
            servos[i]->setAngle(controller->getCurrentPWMValue(i));
        }
    }
    
    for (unsigned int i = 0; i < servos.size(); i++)
    {
        servos[i]->drawServo();
    }
    
    
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
        
        mode.setName("Mode");
        ofxImGui::AddRadio(mode, {"Sweep", "Follow", "Rotate","Draw Line"});
        
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

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if(mode == 3)
    {
        line.clear();
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    if(mode == 3)
    {
        line.addVertex(x,y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    if(mode == 3)
    {
        tween.triggerNewTween(5, 0.0, 1.0);
    }
}

//--------------------------------------------------------------
void ofApp::tweenFinished(string &val)
{
    
}
