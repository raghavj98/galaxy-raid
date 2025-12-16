#include "raylib.h"
#include "raymath.h"
#include "ship.hpp"


Ship::Ship(Color color, float mass, float scale) : m_color(color), m_mass(mass), m_scale(scale) {
    vel = {0,0};
    points[0].x = 600;
    points[0].y = 400;
    _calculatePoints();
    angle = 0.f;
    controls = {
        Control{.bind = KEY_W, .state = InputState::PRPT, .label = "Thrust Increase"},  
        Control{.bind = KEY_A, .state = InputState::PRSD, .label = "Torque CounterCW"}, 
        Control{.bind = KEY_D, .state = InputState::PRSD, .label = "Torque ClockWise"}, 
        Control{.bind = KEY_S, .state = InputState::PRPT, .label = "Thrust Decrease"},  
    };
    power = 0;
}

bool Ship::HandleInput(int input_mask) {
    bool retval = false;
    auto pos = points[0] + Vector2(10,10);
    if (input_mask & 1) { // Control idx 0 is true
        incrThrust();
        retval = true;
    }
    if (input_mask & 2) { // Control idx 1 is true
        applyTorque(-100);
        retval = true;
    }
    if (input_mask & 4) { // Control idx 2 is true
        applyTorque(100);
        retval = true;
    }
    if (input_mask & 8) { // Control idx 3 is true
        decrThrust();
        retval = true;
    }
    if (!(input_mask & 6)) {
        applyTorque(0);
        retval = true;
    }
    return retval;
}

void Ship::_calculatePoints() {
    Vector2 right = Vector2Rotate({m_scale, m_scale/2}, angle);
    Vector2 top = Vector2Rotate({0, -1.5f*m_scale}, angle);
    Vector2 left = Vector2Rotate({-m_scale, m_scale/2}, angle);     
    points[1] = points[0] + right;
    points[2] = points[0] + top;
    points[3] = points[0] + left;
}

void Ship::Draw() {
    _calculatePoints();
    DrawTriangleFan(points, 4, m_color);
}

void Ship::updatePos(float time) {
    vel += thrust * time;
    points[0] = points[0] + (vel * time);
}

void Ship::updateRot(float time) {
    rot_vel += torque * time;
    angle += rot_vel * time;
    if (rot_vel <= 0.01f && rot_vel >= -0.01f) rot_vel = 0;
    thrust = Vector2Rotate({0, -1}, angle) * power;
}

void Ship::incrThrust() {
    if (power >= max_power) {
        power = max_power;
        return;
    }
    power += 2;
}

void Ship::decrThrust() {
    if (power <= 0) {
        power = 0;
        return;
    }
    power -= 2;
}

void Ship::applyTorque(float power) {
    torque = power; 
}
