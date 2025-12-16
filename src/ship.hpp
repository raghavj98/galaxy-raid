#ifndef _SHIP_H_
#define _SHIP_H_

#include "raylib.h"
#include "entity.hpp"

class Ship : public Ticker , public Drawable, public InputSubscriber {
    private:
    Color m_color;
    float m_scale;
    float m_mass;
    float max_power = 100;
    float power_incr = max_power / 10;

    Vector2 points[4];
    Vector2 vel;
    Vector2 thrust;
    float power; 

    float angle;
    float rot_vel; 
    float rot_vel_damp = 0.99f;
    float torque;
    float max_torque = 20;


    public:
    void Draw() override;
    void Tick(float time) override {
        rot_vel_damp *= 0.9;
        updateRot(time);
        updatePos(time);
    }
    bool HandleInput(int input_mask) override;

    Ship(Color color = PURPLE, float mass = 10, float scale = 20);
    void _calculatePoints();
    void updatePos(float time);
    void updateRot(float time);
    void incrThrust();
    void decrThrust();
    void applyTorque(float power);
    Vector2 getPos() const {
        return points[0];
    }
    const float getAngle() const {return angle;}
};

#endif
