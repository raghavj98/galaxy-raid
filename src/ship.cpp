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
        Control{.bind = KEY_A, .state = InputState::DOWN, .label = "Torque CounterCW"}, 
        Control{.bind = KEY_D, .state = InputState::DOWN, .label = "Torque ClockWise"}, 
        Control{.bind = KEY_S, .state = InputState::PRPT, .label = "Thrust Decrease"},  
    };
    power = 2;
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
    rot_vel_damp *= 0.95;
    rot_vel += torque * time;
    rot_vel *= rot_vel_damp;
    angle += rot_vel * time;
    thrust = Vector2Rotate({0, -1}, angle) * power;
}

void Ship::incrThrust() {
    if (power >= 100) {
        power = 100;
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
    rot_vel_damp = 1;
    torque = power; 
}

bool Ship::HandleInput(int ctrl_idx) {
    switch (ctrl_idx) {
        case 0:
            incrThrust();
            break;
        case 1:
            applyTorque(-20);
            break;
        case 2:
            applyTorque(20);
            break;
        case 3:
            decrThrust();
            break;
        default:
            return false;
    }
    return true;
}
