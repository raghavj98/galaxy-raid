#ifndef _ENTITY_H_
#define _ENTITY_H_

class Ticker {
    public:
        virtual void Tick(float frametime) {};
};

class Drawable {
    public:
        virtual void Draw() {};
};

#endif
