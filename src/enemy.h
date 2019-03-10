#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float speed, float rotation, color_t color);
    glm::vec3 position;
    
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void tick1();
        void tick2();
    bounding_box_t getstruct();
    double speed;
    float rotation;
private:
    VAO *object;
};

#endif // BALL_H
