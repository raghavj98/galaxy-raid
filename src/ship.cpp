#include "raylib.h"
#include "raymath.h"
#include "ship.hpp"


Ship::Ship(Color color, float mass, float scale) : m_color(color), m_mass(mass), m_scale(scale) {
    vel = {0,0};
    points[0].x = 600;
    points[0].y = 400;
    _calculatePoints();
    angle = 0.f;
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
}

void Ship::applyThrust(float power) {
    thrust = Vector2Rotate({0, -1}, angle) * power;
}

void Ship::applyTorque(float power) {
    torque = power; 
}

bool Ship::HandleInput(int key) {
    if (key == KEY_W) {
        applyThrust(5);
        return true;
    } else if (key == KEY_A) {
        applyTorque(-2);
        return true;
    } else if (key == KEY_D) {
        applyTorque(2);
        return true;
    } else if (key == KEY_S) {
        applyThrust(0);
        return true;
    }
    return false;
}
