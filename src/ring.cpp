#include "ball.h"
#include "main.h"
#include "man.h"
#include "coin.h"
#include "circle.h"
#include "ring.h"
#include <iostream>

Ring::Ring(float x, float y, float r,float speed,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->radius=r;
    this->speed=speed;
    //this->rotation = rotation;
    const double PI=3.14159265358979324;
    
    GLfloat g_vertex_buffer_data[100000];
    int j=0;
    double xcor[360];
    double ycor[360];
    for (int i = 0; i < 360; i++)
    {
    
        xcor[i] = r * cos(2.0*PI*i/360);
        ycor[i] = r * sin(2.0*PI*i/360);
        
    }
    for(int i=0;i<180;i++)
    {
        //if(i%10<5) continue;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=xcor[i%360];
        g_vertex_buffer_data[j++]=ycor[i%360];
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=xcor[(i+1)%360];
        g_vertex_buffer_data[j++]=ycor[(i+1)%360];
        g_vertex_buffer_data[j++]=0.0f;

    }
    this->object = create3DObject(GL_TRIANGLES, j, g_vertex_buffer_data, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
   //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick() {
    
    this->position.x -= 0.035;
    
    
}

bounding_box_t Ring::getstruct(){
    bounding_box_t t1;
    t1.x= this->position.x;
    t1.y= this->position.y;
    t1.width = 0.5;
    t1.height = 0.5;
    return t1;
}






