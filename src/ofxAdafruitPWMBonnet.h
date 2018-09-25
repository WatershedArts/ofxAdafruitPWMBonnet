// * --------------------------------------------------------------
// * Name: ofxAdafruitPWMBonnet.h
// * Project: ofxAdafruitPWMBonnet
// * Author: David Haylock
// * Creation Date: 22/08/2018
// * Copyright: (c) 2018 by Watershed Arts Trust Ltd.
// * --------------------------------------------------------------

#ifndef ofxAdafruitPWMBonnet_h
#define ofxAdafruitPWMBonnet_h

#include "ofMain.h"

#ifdef TARGET_RASPBERRY_PI
    #include "ofxGPIO.h"
#endif

#define DEFAULT_ADDRESS 0x40
#define MODE1           0x00
#define MODE2           0x01
#define SUBADR1         0x02
#define SUBADR2         0x03
#define SUBADR3         0x04
#define PRESCALE        0xFE
#define PWM_ON_L       0x06
#define PWM_ON_H       0x07
#define PWM_OFF_L      0x08
#define PWM_OFF_H      0x09
#define ALL_PWM_ON_L    0xFA
#define ALL_PWM_ON_H    0xFB
#define ALL_PWM_OFF_L   0xFC
#define ALL_PWM_OFF_H   0xFD
#define RESTART         0x80
#define SLEEP           0x10
#define ALLCALL         0x01
#define INVRT           0x10
#define OUTDRV          0x04

class ofxAdafruitPWMBonnet {
    public:

        /**
         * Default Constructor
         */
        //--------------------------------------------------------
        ofxAdafruitPWMBonnet();

        /**
         * Deconstructor
         */
        //--------------------------------------------------------
        ~ofxAdafruitPWMBonnet();

        /**
         * Initialize Constructor 
         *
         * @param name string identifier
         * @param i2cAddress the i2c address of Bonnet. (Default 0x40 or int(64)) 
         * @param pwmFrequency the refresh rate of the PWM. (Default 50.0)
         * @param pwmMinPulse the min pulse for the PWM. (Default 100)
         * @param pwmMaxPulse the max pulse for the PWM. (Default 100)
         * @param pwmLimit the extreme limit of the PWM. (Default 180 for servos)
         */
        //--------------------------------------------------------
        ofxAdafruitPWMBonnet(string name, u_int16_t i2cAddress = 0x40, float pwmFrequency = 50.0f, int pwmMinPulse = 100, int pwmMaxPulse = 600, int pwmLimit = 90);

        /**
         * Initialize 
         *
         * @param name string identifier
         * @param i2cAddress the i2c address of Bonnet. (Default 0x40 or int(64)) 
         * @param pwmFrequency the refresh rate of the PWM. (Default 50.0)
         * @param pwmMinPulse the min pulse for the PWM. (Default 100)
         * @param pwmMaxPulse the max pulse for the PWM. (Default 100)
         * @param pwmLimit the extreme limit of the PWM. (Default 180 for servos)
         */
        //--------------------------------------------------------
        void init(string name = "Default", u_int16_t i2cAddress = 0x40, float pwmFrequency = 50.0f, int pwmMinPulse = 100, int pwmMaxPulse = 600, int pwmLimit = 90);

        /**
         * Close the Connection 
         */
        //--------------------------------------------------------
        void close();

        /**
         * Sets the Value of the PWM Pin
         * 
         * @param num Pin Number
         * @param on microseconds on
         * @param off microseconds off
         */
        //-------------------------------------------------------------
        void setPWM(u_int16_t num, u_int16_t on, u_int16_t off);

        /**
         * Set the All the PWMs
         * 
         * @param on microseconds on
         * @param off microseconds off
         */
        //-------------------------------------------------------------
        void setAllPWM(u_int16_t on, u_int16_t off);

        /**
         * Set the Servo to the angle
         * This is specific for servo control
         * 
         * @param num Servo Number
         * @param angle what angle to set to
         */
        //-------------------------------------------------------------
        void setAngle(u_int16_t num, int angle);
        
        /**
         * Get the PWM Frequnency
         * 
         * @param pwmFrequency
         * @return pwm value
         */
        //--------------------------------------------------------
        int getCurrentPWMValue(int i) const;

        /**
         * Get the i2c address
         * 
         * @return i2c address
         */
        //--------------------------------------------------------
        u_int16_t getI2CAddress();

        /**
         * Set the PWM Frequnency
         * 
         * @return name of the object
         */
        //--------------------------------------------------------
        string getName();

        // Gui Parameters
        ofParameterGroup parameters;

    private:

        /**
         * Set the PWM Frequnency
         * 
         * @param pwmFrequency
         */
        //--------------------------------------------------------
        void setPWMFrequency(float pwmFrequency);
    
        /**
         * Listener for the Parameters Changed value
         *
         * @param listener value
         */
        //--------------------------------------------------------
        void parameterChanged(ofAbstractParameter &e);

        #ifdef TARGET_RASPBERRY_PI
            I2c *bus = nullptr;
        #endif

        u_int16_t i2cAddress;
        float pwmFrequency;
        int pwmMinPulse;
        int pwmMaxPulse;
        int pwmLimit;
        string name;

        ofParameter <bool> bMasterControl;
        vector<ofParameter<int> > ms;
        vector<ofParameter<int> > angles;
};

#endif /* ofxAdafruitPWMBonnet_h */
