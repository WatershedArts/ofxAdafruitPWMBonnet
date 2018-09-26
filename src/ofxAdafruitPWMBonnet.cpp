// * --------------------------------------------------------------
// * Name: ofxAdafruitPWMBonnet.cpp
// * Project: ofxAdafruitPWMBonnet
// * Author: David Haylock
// * Creation Date: 22/08/2018
// * Copyright: (c) 2018 by Watershed Arts Trust Ltd.
// * --------------------------------------------------------------
#include "ofxAdafruitPWMBonnet.h"

//--------------------------------------------------------
ofxAdafruitPWMBonnet::ofxAdafruitPWMBonnet()
{
    // Construct
}

//--------------------------------------------------------
ofxAdafruitPWMBonnet::~ofxAdafruitPWMBonnet()
{
    // Deconstruct
}

//--------------------------------------------------------
ofxAdafruitPWMBonnet::ofxAdafruitPWMBonnet(string name, u_int16_t i2cAddress, float pwmFrequency, int pwmMinPulse, int pwmMaxPulse, int pwmLimit)
{
    init(name,i2cAddress, pwmFrequency, pwmMinPulse, pwmMaxPulse, pwmLimit);
}

//--------------------------------------------------------
void ofxAdafruitPWMBonnet::init(string name, u_int16_t i2cAddress, float pwmFrequency, int pwmMinPulse, int pwmMaxPulse, int pwmLimit)
{
    // Copy Values
    this->i2cAddress = i2cAddress;
    this->pwmFrequency = pwmFrequency;
    this->pwmMinPulse = pwmMinPulse;
    this->pwmMaxPulse = pwmMaxPulse;
    this->pwmLimit = pwmLimit;
    this->name = name;
    
    ofLogNotice() << "Initializing ofxAdafruitPWMBonnet";
    
#ifdef TARGET_RASPBERRY_PI
    ofLogNotice() << "Setting Up I2C Connection";
    
    // Close the Bus
    if(bus != nullptr)
        delete bus;
    
    // Open the Bus
    bus = new I2c("/dev/i2c-1");
    bus->addressSet(i2cAddress);
    bus->writeByte(MODE2, OUTDRV);
    bus->writeByte(MODE1, ALLCALL);
    usleep(50);
    
    u_int16_t mode1 = bus->readByte(MODE1);
    mode1 = mode1 & ~SLEEP;
    bus->writeByte(MODE1, mode1);
    usleep(50);
    
    // Set the frequency (This is important!!!)
    setPWMFrequency(pwmFrequency);
    
    // Zero Everything
    setAllPWM(0, 0);
    
#else
    ofLogError() << "Not On a Raspberry Pi: But thats ok you can still use the addon for testing purposes";
#endif
    
    // Do stuff for the GUI
    if(getName() == "Default")
        parameters.setName("ofxAdafruitPWMBonnet");
    else
        parameters.setName(getName());
    
    parameters.add(bMasterControl.set("Master Control",false));
    
    static const int center = (pwmMaxPulse + pwmMinPulse) / 2;
    
    ofParameterGroup msGroup;
    ofParameterGroup angleGroup;
    
    msGroup.setName("Microseconds");
    angleGroup.setName("Angles");
    
    // Resize the parameters
    ms.resize(16);
    angles.resize(16);
    
    for (int i = 0; i < 16; i++)
    {
        msGroup.add(ms[i].set("Pin " + ofToString(i) + " (ms)", center, pwmMinPulse, pwmMaxPulse));
        angleGroup.add(angles[i].set("Pin " + ofToString(i) + " (angle)", 0, -pwmLimit, pwmLimit));
    }
    
    parameters.add(msGroup);
    parameters.add(angleGroup);
    
    ofAddListener(parameters.parameterChangedE(), this, &ofxAdafruitPWMBonnet::parameterChanged);
}

//--------------------------------------------------------
void ofxAdafruitPWMBonnet::close()
{
    ofLogNotice() << "Closing I2C Connection";
#ifdef TARGET_RASPBERRY_PI    
    // Close the Bus
    if(bus != nullptr)
        delete bus;
#endif
}

//--------------------------------------------------------
void ofxAdafruitPWMBonnet::setPWMFrequency(float pwmFrequency)
{
    float prescaleval = 25000000.0; //25MHz
    prescaleval /= 4096.0; // 12 bit
    prescaleval /= pwmFrequency;
    prescaleval -= 1.0;
    
    float prescale = int(floor(prescaleval + 0.5));
    
#ifdef TARGET_RASPBERRY_PI
    u_int16_t oldmode = bus->readByte(MODE1);
    u_int16_t newmode = (oldmode & 0x7F) | 0x10;
    
    bus->writeByte(MODE1, newmode);
    bus->writeByte(PRESCALE, prescale);
    bus->writeByte(MODE1, oldmode);
    usleep(50);
    bus->writeByte(MODE1, oldmode | 0x80);
#endif
    
    ofLogNotice() << "Setting ofxAdafruitPWMBonnet PWM Frequency to " << pwmFrequency;
}

//--------------------------------------------------------
void ofxAdafruitPWMBonnet::setAllPWM(u_int16_t on, u_int16_t off)
{
#ifdef TARGET_RASPBERRY_PI
    bus->writeByte(ALL_PWM_ON_L, on & 0xFF);
    bus->writeByte(ALL_PWM_ON_H, on >> 8);
    bus->writeByte(ALL_PWM_OFF_L, off & 0xFF);
    bus->writeByte(ALL_PWM_OFF_H, off >> 8);
#endif
}

//--------------------------------------------------------
void ofxAdafruitPWMBonnet::setPWM(u_int16_t num, u_int16_t on, u_int16_t off)
{
    if (num > 16 || num < 0)
    {
        ofLogError() << "Invalid Servo Number: " << num;
        return;
    }
    
    static const int offset = 4;
    
#ifdef TARGET_RASPBERRY_PI
    bus->writeByte(PWM_ON_L + offset * num, on & 0xFF);
    bus->writeByte(PWM_ON_H + offset * num, on >> 8);
    bus->writeByte(PWM_OFF_L + offset * num, off & 0xFF);
    bus->writeByte(PWM_OFF_H + offset * num, off >> 8);
#endif
}

//-------------------------------------------------------------
void ofxAdafruitPWMBonnet::setAngle(u_int16_t num, int angle)
{
        float pulse = 0;
        float zeroPulse = (pwmMinPulse + pwmMaxPulse) / 2;
        float pulseWidth = zeroPulse - pwmMinPulse;
        pulse = zeroPulse + (pulseWidth * angle / pwmLimit);
        angles.at(num) = angle;
        
        setPWM(num,0,int(pulse));
}

//--------------------------------------------------------
u_int16_t ofxAdafruitPWMBonnet::getI2CAddress()
{
    return i2cAddress;
}

//--------------------------------------------------------
string ofxAdafruitPWMBonnet::getName()
{
    return name;
}

//--------------------------------------------------------
bool ofxAdafruitPWMBonnet::isMasterControlEnabled()
{
    return bMasterControl.get();
}

//--------------------------------------------------------
int ofxAdafruitPWMBonnet::getCurrentPWMValue(int i) const
{
    if(i > angles.size() || i < 0) {
        ofLogError() << "Servo Does not exist, Index is incorrect";
        return 0;
    }
    
    return angles.at(i);
}

//--------------------------------------------------------
void ofxAdafruitPWMBonnet::parameterChanged(ofAbstractParameter &e)
{
    if(bMasterControl)
    {
        if (ofIsStringInString(e.getName(),"(ms)"))
        {
            setPWM(ofToInt(ofSplitString(e.getName(), " ")[1]), 0, e.cast<int>());
        }
        else if (ofIsStringInString(e.getName(),"(angle)"))
        {
            setAngle(ofToInt(ofSplitString(e.getName(), " ")[1]), e.cast<int>());
        }
    }
}


