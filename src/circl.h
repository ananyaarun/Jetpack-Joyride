#include "main.h"

#ifndef CIRCL_H
#define CIRCL_H


class Circl {
public:
    Circl() {}
    Circl(float x, float y, float r,float speed, color_t color);
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
