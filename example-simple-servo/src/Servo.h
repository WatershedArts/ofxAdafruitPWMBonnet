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
        Servo(u_int16_t ctrlAddress, u_int16_t pinNo, glm::vec2 pos,float initAngle)
        {
            init(ctrlAddress, pinNo, pos, initAngle);
        }
    
        /**
         Initialize
         */
        //--------------------------------------------------------------
        void init(u_int16_t ctrlAddress, u_int16_t pinNo, glm::vec2 pos,float initAngle)
        {
            this->ctrlAddress = ctrlAddress;
            this->pinNo = pinNo;
            this->pos = pos;
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
            int width = 50;
            int height = 100;
            ofPushMatrix();
            {
                ofTranslate(pos.x,pos.y);
                ofPushStyle();
                ofNoFill();
                ofSetColor(255);
                ofDrawRectangle(-(width/2),-(height/2),width,height);
                ofPushMatrix();
                ofTranslate(0,-(height/3));
                {
                    ofPushMatrix();
                    {
                        ofTranslate(0,0);
                        ofRotateZDeg(currentAngle);
                        ofPushMatrix();
                        {
                            ofDrawCircle(0,0,35);
                            ofDrawCircle(0,0,5);
                            ofDrawLine(0,0,0,-35);
                        }
                        ofPopMatrix();
                    }
                    ofPopMatrix();
                }
                ofPopMatrix();
                ofPopStyle();
            }
            ofPopMatrix();
        }
    
    private:
    
        u_int16_t ctrlAddress;
        u_int16_t pinNo;
        glm::vec2 pos;
        float currentAngle;
};


#endif /* Servo_h */
