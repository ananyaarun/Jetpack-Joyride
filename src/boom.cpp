#include "ball.h"
#include "main.h"
#include "man.h"
#include "coin.h"
#include "enemy.h"
#include "boom.h"
#include <iostream>
#include <stdlib.h>

Boom::Boom(float x, float y, float speed, float rotation, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->chk1 = rotation;
    this->speed=speed;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {

        -0.30f,0.050f,0.0f, // triangle 1 : begin
        -0.30f,-0.050f, 0.0f,
        0.30f, 0.050f, 0.0f, // triangle 1 : end
        -0.30f, -0.050f,0.0f, // triangle 2 : begin
        0.30f,0.050f,0.0f,
        0.30f, -0.050f,0.0f

      /*  -0.60f,-0.60f,0.0f, // triangle 1 : begin
        -0.60f,0.60f, 0.0f,
        0.30f, -0.60f, 0.0f, // triangle 1 : end
        -0.60f, 0.60f,0.0f, // triangle 2 : begin
        0.30f,-0.60f,0.0f,
        0.30f, 0.60f,0.0f*/

        };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Boom::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boom::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boom::tick() {
        //if(this->position.x <= 5)
          //  {this->speed *=-1;
            //    this->position.y -=0.35;}
        this->position.x -= this->speed;
    }

    void Boom::tick1() {
        //if(this->position.x <= 5)
           // this->speed *=-1;
        if(this->chk1==0 ){
                this->position.y -=1.25;
             this->position.x -=this->speed;
                this->chk1=1;
            }
        //else if(chk2==0 && chk1==1)
          //   {
            //    this->position.y -=0.25;
                this->position.x +=this->speed;
              //  chk2=1;
             //}
             //else
        //this->position.x += this->speed;
    }

bounding_box_t Boom::getstruct(){
    bounding_box_t t1;
    t1.x= this->position.x;
    t1.y= this->position.y;
    t1.width = 0.6;
    t1.height = 0.1;
    return t1;
}


