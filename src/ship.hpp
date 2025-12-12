#ifndef _SHIP_H_
#define _SHIP_H_

#include "raylib.h"
#include "entity.hpp"

class Ship : public Ticker , public Drawable, public InputSubscriber {
    private:
    Color m_color;
    float m_scale;
    float m_mass;

    Vector2 points[4];
    float angle;

    Vector2 vel;
    Vector2 thrust;

    float rot_vel;
    float torque;

    public:
    // Entity methods
    void Draw() override;
    void Tick(float time) override {
        updateRot(time);
        updatePos(time);
    }
    bool HandleInput(int key) override;

    Ship(Color color = PURPLE, float mass = 10, float scale = 20);
    void _calculatePoints();
    void updatePos(float time);
    void updateRot(float time);
    void applyThrust(float power);
    void applyTorque(float power);
    Vector2 getPos() const {
        return points[0];
    }
    const float getAngle() const {return angle;}
};

#endif
