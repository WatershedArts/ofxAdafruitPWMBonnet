//
//  Servo.h
//  example-simple-servo
//
//  Created by David Haylock on 26/09/2018.
//

#include "ofMain.h"

#ifndef Servo_h
#define Servo_h

class Servo
{
public:
    
    /**
     Default Constructor
     */
    //--------------------------------------------------------------
    Servo()
    {
        
    }
    
    /**
     Deconstructor
     */
    //--------------------------------------------------------------
    ~Servo() {}
    
    /**
     Init Constructor
     */
    //--------------------------------------------------------------
    Servo(u_int16_t ctrlAddress, u_int16_t pinNo, glm::vec2 pos, glm::vec2 size, float initAngle)
    {
        init(ctrlAddress, pinNo, pos, size, initAngle);
    }
    
    /**
     Initialize
     */
    //--------------------------------------------------------------
    void init(u_int16_t ctrlAddress, u_int16_t pinNo, glm::vec2 pos, glm::vec2 size, float initAngle)
    {
        this->ctrlAddress = ctrlAddress;
        this->pinNo = pinNo;
        this->pos = pos;
        this->size = size;
        this->currentAngle = initAngle;
    }
    
    /**
     Returns the Current Angle of the Servo
     
     @return Servo Angle
     */
    //--------------------------------------------------------------
    int getCurrentAngle()
    {
        return currentAngle;
    }
    
    /**
     Get the Connected Pin Number
     
     @return pin no
     */
    //--------------------------------------------------------------
    u_int16_t getPin()
    {
        return pinNo;
    }
    
    /**
     Returns the Size of the Servo
     
     @return size
     */
    //--------------------------------------------------------------
    glm::vec2 getSize()
    {
        return size;
    }
    
    /**
     Returns the Position of the Servo
     
     @return pos
     */
    //--------------------------------------------------------------
    glm::vec2 getPosition()
    {
        return pos;
    }
    
    /**
     Set the New Angle
     
     @param angle angle
     */
    //--------------------------------------------------------------
    void setAngle(float angle)
    {
        this->currentAngle = angle;
    }
    
    /**
     Draw Servo
     */
    //--------------------------------------------------------------
    void drawServo()
    {
        ofPushMatrix();
        {
            ofTranslate(pos.x,pos.y);
            ofPushStyle();
            ofNoFill();
            ofSetColor(255);
            ofDrawRectangle(-(size.x/2),-(size.y/2),size.x,size.y);
            ofPushMatrix();
            ofTranslate(0,-(size.y/3));
            {
                ofPushMatrix();
                {
                    ofTranslate(0,0);
                    ofRotateZDeg(currentAngle);
                    ofPushMatrix();
                    {
                        ofDrawCircle(0,0,(size.y/3));
                        ofDrawCircle(0,0,5);
                        ofDrawLine(0,0,0,-(size.y/3));
                    }
                    ofPopMatrix();
                }
                ofPopMatrix();
            }
            ofPopMatrix();
            ofPopStyle();
        }
        ofPopMatrix();
        ofSetColor(255,255,0);
        ofDrawBitmapString("Servo " + ofToString(int(pinNo)),pos.x-(size.x/2),pos.y+size.y/2+15);
    }
    
private:
    
    u_int16_t ctrlAddress;
    u_int16_t pinNo;
    glm::vec2 pos;
    glm::vec2 size;
    float currentAngle;
};


#endif /* Servo_h */
