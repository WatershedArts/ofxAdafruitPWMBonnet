//--------------------------------------------------------------
//  Tween.h
//  Created by David Haylock on 22/08/2018.
/** Tween Class */
//-------------------------------------------------------------
#ifndef Tween_h
#define Tween_h

#include "ofxEasing.h"

class Tween {
    public:
    
        /**
         Init Tween
         */
        //-----------------------------------------------------
        Tween()
        {
            
        }
    
        /**
         Init Tween
         */
        //-----------------------------------------------------
        Tween(int id, string tweenName)
        {
            fromValue = 0;
            toValue = 0;
            currentValue = 0;
            
            this->tweenName = tweenName;
            this->id = id;
            ofAddListener(ofEvents().update,this,&Tween::update);
        }
    
        /**
         Init Tween
         */
        //-----------------------------------------------------
        void setup(int id, string tweenName)
        {
            fromValue = 0;
            toValue = 0;
            currentValue = 0;
            
            this->tweenName = tweenName;
            this->id = id;
            ofAddListener(ofEvents().update,this,&Tween::update);
        }
    
        /**
         Start a New Tween
         
         @param duration length of the tween
         @param value to which value
         */
        //-----------------------------------------------------
        void triggerNewTween(float duration, float fromValue, float toValue,string tweenName = "",float delay = 0.0f) {
            this->duration = duration;
            this->fromValue = fromValue;
            this->toValue = toValue;
            this->delay = delay;
            
            initTime = ofGetElapsedTimef() + delay;
            endTime = initTime + duration;
            notified = false;
            
            if(tweenName != "") {
                this->tweenName = tweenName;
            }
            ofNotifyEvent(tweenStarted,tweenName,this);
        }
    
        /**
         Auto Update Loop
         
         @param evt listener
         */
        //-----------------------------------------------------
        void update(ofEventArgs &evt)
        {
            auto now = ofGetElapsedTimef();
            
            if(!notified) {
                currentValue = ofxeasing::map_clamp(now,
                                                    initTime,
                                                    endTime,
                                                    fromValue,
                                                    toValue,
                                                    &ofxeasing::linear::easeInOut);
            }
            
            if(currentValue == toValue && !notified)
            {
                notified = true;
                ofNotifyEvent(tweenEnd,tweenName,this);
            }
        }
    
        /**
         Get the Current Value
         
         @return Current Value
         */
        //-----------------------------------------------------
        float getCurrentValue()
        {
            return currentValue;
        }
    
    
        /**
         Has the Tween Finished

         @return completed
         */
        //-----------------------------------------------------
        bool hasCompleted()
        {
            return (currentValue == toValue ? true : false);
        }
    
        ofEvent <string> tweenStarted;
        ofEvent <string> tweenEnd;
    
    private:
        
        bool notified = true;
        float duration = 0.0f;
        float toValue = 0.0f;
        float currentValue = 0.0f;
        float fromValue = 0.0f;
        float initTime = 0.0f;
        float endTime = 0.0f;
        float delay = 0.0f;
        int id;
        string tweenName;
};
#endif /* Tween_h */
