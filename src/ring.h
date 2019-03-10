#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float r,float speed, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
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

#endif 
