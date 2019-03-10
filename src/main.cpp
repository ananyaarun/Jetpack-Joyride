#include "main.h"
#include "timer.h"
#include "ball.h"
#include "man.h"
#include "coin.h"
#include "enemy.h"
#include "circle.h"
#include "enemyy.h"
#include "prop.h"
#include "water.h"
#include "obs.h"
#include "boom.h"
#include "magnet.h"
#include "ring.h"
#include "circl.h"
#include "spike.h"
#include "end.h"
#include <iostream>
#include <cmath>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int score = 0;

int level = 1;

int health = 4;

float playerpos=0;

Ball ball2;
Ball ball1;
Man man1;
Coin coin[40];
Enemy enemy[5];
Circle circle1[10];
Circle circle2[20];
Circle dragon;
Enemyy enemyy[10];
Prop prop;
End end;
Obs obs[50];
Water water;
Boom boom[4];
Magnet magnet[2];
Ring ring[2];
Circl circl[7];
Spike spike[20];
Ring ice;
Ring ring1[2];

Timer magnet_life(1);

float screen = 0;
float screeny = 0;

int boomstate[4]={0};

float screen_zoom = 100, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

int check=0;
int chk=0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {

    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f));
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    //Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(screen, screeny, 3), glm::vec3(screen, screeny, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ring[0].draw(VP);
    ring[1].draw(VP);

    ring1[0].draw(VP);
    ring1[1].draw(VP);

    man1.draw(VP);

    for(int i =0;i<40;i++)
        coin[i].draw(VP);

    for(int i =0;i<5;i++)
        enemy[i].draw(VP);

    for(int i =0;i<10;i++)
        circle1[i].draw(VP);

    for(int i =0;i<10;i++)
       enemyy[i].draw(VP);

    for(int i =0;i<20;i++)
       circle2[i].draw(VP);
 
    if(magnet[0].draw_mag)
    {
        for(int i =0;i<2;i++)
             magnet[0].draw(VP);
    }
    if(magnet[1].draw_mag)
    {
        for(int i =0;i<2;i++)
             magnet[1].draw(VP);
    }
    
    if(check==1)
    {
        prop.position.x=man1.position.x;
        prop.position.y=man1.position.y-0.7;
        prop.draw(VP);
    }

    for(int i =0;i<50;i++)
        obs[i].draw(VP);

    if(chk==1)
        water.draw(VP);
    
    for(int i =0;i<4;i++)
        boom[i].draw(VP);
   
    for(int i =0;i<7;i++)
        circl[i].draw(VP);

    ball1.draw(VP);
    
    ball2.draw(VP);

    for(int i=0;i<20;i++)
        spike[i].draw(VP);

    dragon.draw(VP);

    if(man1.position.x >= 52)
    ice.draw(VP);

    end.draw(VP);
    
}

void tick_input(GLFWwindow *window) {
    
    //bounding_box_t m = man1.getstruct();
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int enter = glfwGetKey(window, GLFW_KEY_ENTER);
    int attack = glfwGetKey(window, GLFW_KEY_UP);
    int panl = glfwGetKey(window, GLFW_KEY_A);
    int panr = glfwGetKey(window, GLFW_KEY_D);
    int panu = glfwGetKey(window, GLFW_KEY_W);  
    int pand = glfwGetKey(window, GLFW_KEY_S);
    if(panl)
        {
            screen-=0.02;
            //reset_screen();
        }
    if (panr)
    {
        screen+=0.02;
        //reset_screen();
    }
    if (panu)
    {
        screeny+=0.02;
        //reset_screen();
    }
    if (pand)
    {
        screeny-=0.02;
        //reset_screen();
}

    float pi=3.14159265359;
    
    check=0;
    
    if (left) 
    {

        if(man1.state==0)
        {
        screen-=0.01;
        man1.position.x-=0.01;
        }
        else
        {
             screen-=0.01;
             man1.position.x-=0.01;

             if(man1.position.x<=18)
                 man1.position.y-=0.015;
 
             else
                man1.position.y+=0.005;

        }

        }

    if (right) 
    {
        if(man1.state==0)
        {
            screen+=0.01;
            man1.position.x+=0.01;
        }
        else
        {
            screen+=0.01;
            man1.position.x+=0.01;

            if(man1.position.x<=18)
                man1.position.y+=0.015;
            else
                man1.position.y-=0.005;

        }
    }

    if (space) 
    {
        check=1;
        man1.speed += 0.02;

    }

    if(attack)
    {

        chk=1;
        water.position.x=man1.position.x+0.5;
        water.position.y=man1.position.y;
        if(water.position.y <= -2.4)
            chk=0;
    }
}

void tick_elements() {
    if(man1.position.x >= 69.9)
    {
        cout<<"CONGRATS U WON !!!"<< " "<< " your score is : "<<score<<endl;
        quit(window);
    }

    if(health <= 0)
    {
         cout<<"OOPS U LOST :/"<< " "<< " your score is : "<<score<<endl;
        quit(window);
    }

    if(man1.position.x >= 15)
        level = 2;

    if(man1.position.x >= 30)
        level = 3;

    playerpos = man1.position.x;

    for(int i=0;i<4;i++)
    {
        if(boom[i].position.x <= man1.position.x -1.5 )
            {
                boomstate[i]=1;
            }
        
    }

    ball1.tick();

    if(man1.state==0)
        man1.tick();
    
    prop.tick();
    
    water.tick();

    dragon.tick();
    
    for(int i =0;i<10;i++)
       enemyy[i].tick();
    
    for(int i =0;i<20;i++)
       circle2[i].tick();
    
    int chkk[4]={0};
    
    for(int i =0;i<4;i++)
    {
        if(boomstate[i]==0)
        boom[i].tick();
        else
           {
            boom[i].tick1();
           }
    }

    for(int i =0;i<7;i++)
        if(man1.position.x+4 >= circl[i].position.x )
           circl[i].tick();

    camera_rotation_angle += 1;
    
    for(int i=0;i<40;i++)
    {
         if(detect_collision(coin[i].getstruct(),man1.getstruct())!=0)
            {
                coin[i].position.y = 100;
                if(i%2==0)
                    score+=10;
                else
                    score +=20;
            }

    }

    if((man1.position.x >= 16) && (man1.position.x <=20) && (man1.position.y >= -0.5) && (man1.position.y <=1.5))
        man1.state=1;
    else
        man1.state=0;

    for(int i=0;i<5;i++)
    {
        if(detect_collision(enemy[i].getstruct(),man1.getstruct())!=0)
       {
            enemy[i].position.y = 100;
            circle1[2*i].position.y = 100;
            circle1[2*i+1].position.y = 100;
            score -= 5;
        }

    }

    for(int i=0;i<5;i++)
    {
     if(detect_collision(enemy[i].getstruct(),water.getstruct())!=0)
       {
            enemy[i].position.y = 100;
            circle1[2*i].position.y = 100;
            circle1[2*i+1].position.y = 100;
            score+= 10;
       }


    }


    for(int i=0;i<20;i++)
     {
       if(detect_collision(spike[i].getstruct(),man1.getstruct())!=0)
        {
            man1.position.y -= 1;
            health -= 1;
        }


    }


    for(int i=0;i<2;i++)
    {
     if(detect_collision(magnet[i].getstruct(),man1.getstruct())!=0)
       { 
            if(man1.position.x == magnet[i].position.x-0.5)
                magnet[i].position.y=1000;
            man1.tick1();

       }
    }


    for(int i=0;i<10;i++)
    {
     if(detect_collision(enemyy[i].getstruct(),man1.getstruct())!=0)
       { 
           enemyy[i].position.y = 100;
           circle2[2*i].position.y = 100;
           circle2[2*i+1].position.y = 100;
           score -= 5;
        }
    }

    for(int i=0;i<10;i++)
    {
     if(detect_collision(enemyy[i].getstruct(),water.getstruct())!=0)
       { 
           enemyy[i].position.y = 100;
           circle2[2*i].position.y = 100;
           circle2[2*i+1].position.y = 100;
           score += 15;
        }
    }

    for(int i=0;i<50;i++)
    {

     if(detect_collision(obs[i].getstruct(),water.getstruct())!=0)
        {
           obs[i].position.y=100;
           score += 15;
        }
    }

    for(int i=0;i<50;i++)
    {

     if(detect_collision(obs[i].getstruct(),man1.getstruct())!=0)
        {
           obs[i].position.y=100;
           health -= 1;
        }
    }

    for(int i=0;i<4;i++)
    {

     if(detect_collision(boom[i].getstruct(),man1.getstruct())!=0 && man1.state == 0)
        {
           boom[i].position.y = 100;
           health -= 1;
        }
    }

    for(int i=0;i<7;i++)
    {

     if(detect_collision(circl[i].getstruct(),man1.getstruct())!=0)
        {
           circl[i].position.y = 10000;
           health += 1;
        }
    }


    if(detect_collision(dragon.getstruct(),man1.getstruct())!=0)
        {
           dragon.position.y = 10000;
           health -= 1;
        }

    if(detect_collision(ice.getstruct(),man1.getstruct())!=0)
        {
           ice.position.y = 10000;
           health -= 1;
        }

    if(man1.position.x >= 52)
        ice.tick();



    for(int i =0;i<50;i++)
       obs[i].tick();

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(-3.5, -3.5, 0, COLOR_PLATFORM);
    
    ball2       = Ball(-3.5, 3.5, 0, COLOR_PLATFORM);
    
    man1        = Man(-2, -2.5, 0,0, COLOR_BLACK);
    
    prop        = Prop(man1.position.x,man1.position.y-0.7,0,COLOR_CRIMSON);
    
    water = Water(man1.position.x-0.5,man1.position.y-0.7,0.01,COLOR_LBLUE);
    
    boom[0]=Boom(10,1.5,0.02,0,COLOR_maroon);
    boom[1]=Boom(25,1.5,0.02,0,COLOR_maroon);
    boom[2]=Boom(45,1.5,0.02,0,COLOR_maroon);
    boom[3]=Boom(60,1.5,0.02,0,COLOR_maroon);
    
    int neg = -1;
    
    for(int i=0;i<40;i++)
    {
     neg=neg*-1;
     int a = i*2;
     int b = neg*(i%3);
     if (i%2==0)
     coin[i]     = Coin(a-1.5, b, 0, COLOR_BLUE);
     else
     coin[i]     = Coin(a, b, 0, COLOR_purple);  
    }

    int j=0;
    
    float pi=3.14159265359;
    
    for(int i=0;i<5;i++)
    {
     neg=neg*-1;
     int a = i*7;
     int b = neg*(i%3);
     int c = rand()%180;
     enemy[i]     = Enemy(a, b, 0 ,c , COLOR_RED);
     circle1[j] = Circle(a+cos(c*pi/180),b+sin(c*pi/180),0.2,0,COLOR_CRIMSON);
     j++;
     circle1[j] = Circle(a-cos(c*pi/180),b-sin(c*pi/180),0.2,0,COLOR_CRIMSON);
     j++;


    }
     
    j=0;

    for(int i=0;i<10;i+=2)
    {
     neg=neg*-1;
     int a = (i*7)-3;
     int b = neg*(i%3);
     int c = 0;
     enemyy[i]     = Enemyy(a, b, 0.01 ,c , COLOR_RED);
     circle2[j] = Circle(a+1,b,0.1,0.01,COLOR_CRIMSON);
     j++;
     circle2[j] = Circle(a-1,b,0.1,0.01,COLOR_CRIMSON);
     j++;
     enemyy[i+1]     = Enemyy(a, b+0.2, 0.01 ,c , COLOR_RED);
     circle2[j] = Circle(a+1,b+0.2,0.1,0.01,COLOR_CRIMSON);
     j++;
     circle2[j] = Circle(a-1,b+0.2,0.1,0.01,COLOR_CRIMSON);
     j++;


    }

    int pos=500;
    
    for(int i =0;i<50;i++)
    {
       obs[i]=Obs(pos,-2.8,0.03,COLOR_GREEN);
       pos-=10;
    }

        magnet[0]=Magnet(3,0,0,COLOR_PLATFORM);
        magnet[1]=Magnet(26,0,0,COLOR_PLATFORM);

    ring[0]=Ring(18,-0.5,2,0,COLOR_GREEN);
    ring[1]=Ring(18,-0.5,1.9,0,COLOR_BACKGROUND);

    ring1[0]=Ring(71,-0.5,2,0,COLOR_GREEN);
    ring1[1]=Ring(71,-0.5,1.9,0,COLOR_BACKGROUND);
     
     for(int i =0;i<7;i++)
    {
       circl[i]=Circl(((4*i) + 35),-2,0.25,0.01,COLOR_LBLUE);
       
    }

    float spi = 35;

    for(int i =0;i<20;i++)
    {
       spike[i]=Spike(spi,2.75,0.01,COLOR_PLATFORM);
       spi+=0.6;
       
    }

    dragon = Circle(55,0,0.7,0.01,COLOR_PLATFORM);

    ice = Ring (55,0,0.2,0.01,COLOR_RED);

    end = End (65,0,0,COLOR_PLATFORM);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    char stringPrint[1000];

    window = initGLFW(width, height);

    initGL (window, width, height);

 Matrices.projection = glm::perspective(glm::radians(screen_zoom),(float)600/(float)600,0.1f,100.0f);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            sprintf(stringPrint, "Level: %d  Score: %d Health: %d", level, score, health);
            glfwSetWindowTitle(window, stringPrint);
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        if(magnet_life.processTick())
        {
            if(magnet[0].draw_mag == 0)
                magnet[0].draw_mag = 1;
            else
                     magnet[0].draw_mag = 0;
            if(magnet[1].draw_mag == 0)
                magnet[1].draw_mag = 1;
            else
                     magnet[1].draw_mag = 0; 
        }    
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
