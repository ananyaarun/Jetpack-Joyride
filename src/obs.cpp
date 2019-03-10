#include "ball.h"
#include "main.h"
#include "man.h"
#include "coin.h"
#include "obs.h"
#include <iostream>

Obs::Obs(float x, float y, float speed, color_t color) {
    this->position = glm::vec3(x, y, 0);
   // this->rotation = 0;
    this->speed=speed;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {

        -0.10f,0.10f,0.0f, // triangle 1 : begin
        -0.10f,-0.10f, 0.0f,
        0.10f, 0.10f, 0.0f, // triangle 1 : end
        -0.10f, -0.10f,0.0f, // triangle 2 : begin
        0.10f,0.10f,0.0f,
        0.10f, -0.10f,0.0f

      /*  -0.60f,-0.60f,0.0f, // triangle 1 : begin
        -0.60f,0.60f, 0.0f,
        0.30f, -0.60f, 0.0f, // triangle 1 : end
        -0.60f, 0.60f,0.0f, // triangle 2 : begin
        0.30f,-0.60f,0.0f,
        0.30f, 0.60f,0.0f*/

        };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Obs::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Obs::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Obs::tick() {
        
        this->position.x -= this->speed;
    
}

bounding_box_t Obs::getstruct(){
    bounding_box_t t1;
    t1.x= this->position.x;
    t1.y= this->position.y;
    t1.width = 0.4;
    t1.height = 0.4;
    return t1;
}


