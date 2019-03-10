#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water {
public:
    Water() {}
    Water(float x, float y, float speed, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void tick1();
        void tick2();
    bounding_box_t getstruct();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
