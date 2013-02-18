//
//  Integrator.h
//  BookReview_Final
//
//  Created by Luis Daniel Palacios on 3/4/12.
//  Copyright (c) 2012 luisdaniel. All rights reserved.
//




#ifndef BookReview_Final_Integrator_h
#define BookReview_Final_Integrator_h


#include "ofMain.h"

class Integrator {
    
public:
    
    //constructors
    Integrator();
    Integrator(float _value);
    Integrator(float _value, float _damping, float _attraction);
    
    //functions
    void set(float v);
    void update();
    void tarGet(float t);
    void noTarget();
    
    //variables
    float DAMPING;
    float ATTRACTION;
    
    float value;
    float vel;
    float accel;
    float force;
    float mass;
    
    float damping;
    float attraction;
    bool targeting;
    float target;
};



#endif
