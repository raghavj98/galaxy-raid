#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <vector>

enum InputState {
    DOWN,
    PRSD,
    PRPT,
};

struct Control {
    int bind;
    InputState state;
    const char* label;
};

class Ticker {
    public:
        virtual void Tick(float frametime) {};
};

class Drawable {
    public:
        virtual void Draw() {};
};

class InputSubscriber {
    public:
        virtual bool HandleInput(int input_mask) {return false;};
        std::vector<Control> controls;
};

#endif
