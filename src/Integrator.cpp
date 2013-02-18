//
//  Integrator.cpp
//  BookReview_Final
//
//  Created by Luis Daniel Palacios on 3/4/12.
//  Copyright (c) 2012 luisdaniel. All rights reserved.
//

#include <iostream>
#include "Integrator.h"


Integrator::Integrator() {
    DAMPING = .05;
    ATTRACTION = 0.2;
    mass = 1;
    damping = DAMPING;
    attraction = ATTRACTION;
    
}

Integrator::Integrator(float _value) {
    DAMPING = .05;
    ATTRACTION = 0.2;
    mass = 1;
    damping = DAMPING;
    attraction = ATTRACTION;
    value = _value;
}

Integrator::Integrator(float _value, float _damping, float _attraction) {
    DAMPING = .05;
    ATTRACTION = 0.2;
    mass = 1;
    damping = DAMPING;
    attraction = ATTRACTION;
    value = _value;
    damping = _damping;
    attraction = _attraction;
}


void Integrator::set(float v) {
    value = v;
}

void Integrator::update() {
    if (targeting) {
        force += attraction * (target - value);      
    }
    accel = force / mass;
    vel = (vel + accel) * damping;
    value += vel;
    force = 0;
}

void Integrator::tarGet(float t) {
    targeting = true;
    target = t;
}

void Integrator::noTarget() {
    targeting = false;
}

