//
//  main.cpp
//  CGlab7
//
//  Created by rital shafiei on 09/01/2023.
//
#include <iostream>
#include <GL/glew.h>
#include <stdlib.h>
#include <GLUT/glut.h>
//#include <GL\freeglut.h>   // handle the window-managing operations
#include <iostream>
#include <stdio.h>
#include<math.h>
#include<GL/gl.h>
#include<GL/glut.h>
// audio for windows:
#include<windows.h>
#include <MMSystem.h>

# define PI           3.14159265358979323846
using namespace std;

float transValue;
float transValuer;
float transValueair;
float transValuemicro;
float Riyadh;
float Solarpanelsvalue;
float down;
float uprig;
float upair;
float raun;
float toiqup;
float toidown;
float logo;
float saudit;
float chip;
float transValueX;
float transValueY;
float transValueZ;

GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 0.0, 0.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 3.0, 5.0, 10.0, 1.0 };
float  shininess[] = { 128 };

// note that imges must be converted to bmp first
GLuint myTexture1;
GLuint myTexture2;
char image1Path[] = "/Users/ritalshafiei/Desktop/semster2/رسومات/عملي/zchip/CGlab6/chip.bmp";
char image2Path[] = "/Users/ritalshafiei/Desktop/semster2/رسومات/عملي/zchip/CGlab6/saudi.bmp";
GLint win_width = 500,
win_hight = 500;


GLuint LoadTexture(const char * filename, int width, int height)
{
    GLuint texture;
    unsigned char * data;
    FILE * file;
    //The following code will read in our RAW file
    file = fopen(filename, "rb");

    if (file == NULL)
    {
        cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;
        exit(0);
        return 0;
    }

    data = (unsigned char *)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);

    fclose(file);


    // reorder the image colors to RGB not BGR
    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;

    }


    glGenTextures(1, &texture);            //generate the texture with the loaded data
    glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //set texture environment parameters

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    /////////////////////////////////////////

    free(data); //free the texture array

    if (glGetError() != GL_NO_ERROR)
        printf("GLError in genTexture()\n");

    return texture; //return whether it was successfull
}





static void play(void)
{
    glutPostRedisplay();
}

static
void key(unsigned char keyPressed, int x, int y) // key handling
{
    switch (keyPressed) {

    case 'x':
        light_position[0]++;
        cout << "Light pos x: " << light_position[0] << endl;
        break;
        // Countinue in the same manner
    case 'X':
        light_position[0]--;
        cout << "Light pos x: " << light_position[0] << endl;
        break;
    case 'y':
        light_position[1]++;
        cout << "Light pos y: " << light_position[1] << endl;
        break;
    case 'Y':
        light_position[1]--;
        cout << "Light pos y: " << light_position[1] << endl;
        break;
    case 'z':
        light_position[2] += 1;
        cout << "Light pos z: " << light_position[2] << endl;
        break;
    case 'Z':
        light_position[2] -= 1;
        cout << "Light pos z: " << light_position[2] << endl;
        break;
    case 's':
        shininess[0] += 2;
        cout << "shininess: " << shininess[0] << endl;
        break;
    case 'S':
        shininess[0] -= 2;
        cout << "shininess: " << shininess[0] << endl;
        break;
        
// change shadng model
    case 'f':
        glShadeModel(GL_SMOOTH);
        cout << "your shading model is SMOOTH" << endl;
        break;
    case 'F':
        glShadeModel(GL_FLAT);
        cout << "your shading model is FLAT" << endl;
        break;
        
    case 'q':
    case 27:
        exit(0);
        break;

    default:
        fprintf(stderr, "\nKeyboard commands:\n\n"
            "q, <esc> - Quit\n");
        break;

        
    }
}

void init() {
    //------- Texture ---------
    myTexture1 = LoadTexture(image1Path, 297,306);

    if (myTexture1 == -1)
    {
        cout << "Error in loading the texture" << endl;
    }
    else
        cout << "The texture value is: " << myTexture1 << endl;
    
    myTexture2 = LoadTexture(image2Path, 1024,683);

    if (myTexture2 == -1)
    {
        cout << "Error in loading the texture" << endl;
    }
    else
        cout << "The texture value is: " << myTexture2 << endl;
    //----------------------

    transValueX = 0.0;
    transValueY = 0.0;
    transValueZ = 1.5;

    // create light 0
    
    glEnable(GL_DEPTH_TEST);
    // Specify shading model
    glShadeModel(GL_SMOOTH);
    // Define light
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    

    glClearColor(0.70f, 0.70f, 0.70f, 1.0f); // Set background color to black and opaque

    glMatrixMode(GL_PROJECTION);
    gluPerspective(65, (win_width / win_hight), 0.01, 50);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);

}

void reshapeFunc(GLint new_width, GLint new_hight)
{
    glViewport(0, 0, new_width, new_hight);
    win_width = new_width;
    win_hight = new_hight;
}


void TreeLeaves(float cx, float cy, float rx, float ry, int num_segments) {
    glBegin(GL_POLYGON);
    glColor3f(0.137255, 0.556863, 0.137255);//forest green
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);
    float s = sinf(theta);
    float t;

    float x = 0.2;
    float y = 0.0;
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < num_segments; i++)
    {
        glVertex2f(x * rx + cx, y * ry + cy);
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}


void UpperTower(float cx, float cy, float rx, float ry, int num_segments) {
    glBegin(GL_POLYGON);
    glColor3f(0.74902, 0.847059, 0.897059);//blue sky
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);
    float s = sinf(theta);
    float t;

    float x = 0.2;
    float y = 0.0;
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < num_segments; i++)
    {
        glVertex2f(x * rx + cx, y * ry + cy);
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}


// tower
void almamlakaTower() {

    //Tower
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);//gray
    glVertex2f(-0.9, -0.9);
    glVertex2f(-0.9, 0.4);
    glVertex2f(-0.65, 0.4);
    glVertex2f(-0.65, -0.9);
    glEnd();

    //Grass
    glBegin(GL_POLYGON);
    glColor3f(0.137255, 0.556863, 0.137255);//forest green
    glVertex2f(-1, -1);
    glVertex2f(-1, -0.9);
    glVertex2f(1, -0.9);
    glVertex2f(1, -1);
    glEnd();

    //Upper tower part1 //layer1
    glBegin(GL_POLYGON);
    glColor3f(0.184314, 0.184314, 0.309804);//Midnight blue
    glVertex2f(-0.88, 0.35);
    glVertex2f(-0.67, 0.35);
    glVertex2f(-0.706, 0.09);
    glVertex2f(-0.833, 0.09);
    glEnd();

    //layer2
    glBegin(GL_POLYGON);
    glColor3f(0.74902, 0.847059, 0.897059);//blue sky
    glVertex2f(-0.87, 0.34);
    glVertex2f(-0.68, 0.34);
    glVertex2f(-0.707, 0.09);
    glVertex2f(-0.832, 0.09);

    glEnd();

    //Upper tower part2
    UpperTower(-0.77, 0.15, 0.352, 0.6, 40);
    glBegin(GL_POLYGON);
    glColor3f(0.184314, 0.184314, 0.309804);//Midnight blue
    glVertex2f(-0.88, 0.35);
    glVertex2f(-0.67, 0.35);
    glVertex2f(-0.67, 0.32);
    glVertex2f(-0.88, 0.32);

    glEnd();
    glFlush();

    //Tree trunk
    glBegin(GL_POLYGON);
    glColor3f(0.52, 0.37, 0.26); //Brown
    glVertex2f(-0.53, -0.9);
    glVertex2f(-0.53, -0.7);
    glVertex2f(-0.48, -0.7);
    glVertex2f(-0.48, -0.9);

    //Tree leaves
    TreeLeaves(-0.5, -0.7, 0.6, 0.3, 40);
    TreeLeaves(-0.48, -0.7, 0.3, 0.4, 40);
    TreeLeaves(-0.52, -0.7, 0.3, 0.4, 40);

    

}


void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments) {
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);
    float s = sinf(theta);
    float t;

    float x = 0.4;
    float y = 0;

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < num_segments; i++)
    {
        glVertex2f(x * rx + cx, y * ry + cy);
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}
//cloud
void cloud1() {

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    DrawEllipse(-0.4, 1.6, 0.5, 0.3, 40);
    glColor3f(1.0, 1.0, 1.0);
    DrawEllipse(-0.4, 1.6, 0.3, 0.4, 40);
    glPopMatrix();


}
//cloud

void cloud2() {

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    DrawEllipse(-0.8, 2.3, 0.5, 0.3, 40);
    glColor3f(1.0, 1.0, 1.0);
    DrawEllipse(-0.8, 2.3, 0.3, 0.4, 40);
    glPopMatrix();
}
//cloud

void cloud3() {

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    DrawEllipse(-1.6, 1.7, 0.5, 0.3, 40);
    glColor3f(1.0, 1.0, 1.0);
    DrawEllipse(-1.6, 1.7, 0.3, 0.4, 40);
    glPopMatrix();
}

//animation

void spin() {
    //rain
    transValuer += 0.003;
    if (transValuer >= 1)
        transValuer = 0;
    //airpaln
    if (transValueair <= -1)
        transValueair = 1;
    else
        transValueair += -0.0009;
    //cloud
    if (transValue >= 1)
        transValue = 0;
    else
        transValue += 0.0005;
    if (Solarpanelsvalue >= 1)
        Solarpanelsvalue = 0;
    else
        Solarpanelsvalue = +0.0005;



    glutPostRedisplay();
}

//rain
void rain2(double y, double z) {
    glClearColor(0.74902, 0.847059, 0.897059, 0);
    glLineWidth(1);
    glLineStipple(5, 0x0C0F);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.5f);
    glVertex2f(y, 2);
    glVertex2f(z, -1);
    glDisable(GL_LINE_STIPPLE);
    glEnd();

}

void multipuleRain() {
    double x = -1.2;
    double y = -1.12;
    for (int i = 1; i <= 30; i++) {
        x = x + 0.1;
        y = y + 0.12;
        rain2(x, y);
    }

}
// airplane
void ariplan() {

    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(0.74902, 0.847059, 0.897059, 0);

    glBegin(GL_POLYGON); // airplane
    glColor3ub(234, 229, 229);
    glVertex2f(-0.3f, 0.2f);
    glVertex2f(0.3, 0.2f);

    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.45f, 0.4f);

    glVertex2f(0.45f, 0.5f);

    glVertex2f(0.3f, 0.4f);
    glVertex2f(0.0f, 0.4f);

    glVertex2f(-0.2f, 0.4f);
    glVertex2f(-0.3f, 0.4f);

    glVertex2f(-0.35f, 0.38f);
    glVertex2f(-0.4f, 0.3f);

    glVertex2f(-0.35f, 0.26f);
    glVertex2f(-0.3f, 0.2f);
    glEnd();

    glBegin(GL_LINES); // airplane front window
    glColor3f(0.0f, 0.5f, 0.5f);//Blue-Green

    glVertex2f(-0.37f, 0.35f);
    glVertex2f(-0.32f, 0.35f);
    glVertex2f(-0.3f, 0.36f);
    glVertex2f(-0.3f, 0.38f);
    glVertex2f(-0.35f, 0.38f);

    glEnd();





    glBegin(GL_POLYGON); // Airplane front wind
    glColor3f(0.0f, 0.5f, 0.5f);//Blue-Green

    glVertex2f(0.03f, 0.17f);
    glVertex2f(0.06f, 0.17f);
    glVertex2f(-0.04f, 0.30f);
    glVertex2f(-0.1f, 0.30f);

    glEnd();
    glBegin(GL_POLYGON); // Airplane back wind
    glColor3f(0.0f, 0.5f, 0.5f);//Blue-Green

    glVertex2f(-0.08f, 0.4f);
    glVertex2f(0.0f, 0.4f);
    glVertex2f(0.07f, 0.49f);
    glVertex2f(0.04f, 0.49f);
    glEnd();

    // Airplane  window
    glColor3f(0.0f, 0.5f, 0.5f);//Blue-Green
    GLfloat x2 = -0.09f;
    GLfloat y2 = 0.35f;
    GLfloat  radius1 = .02f;
    int triangleAmount1 = 100;
    GLfloat twicePi1 = 2.0f * PI;
    glBegin(GL_POLYGON);
    glVertex2f(x2, y2); // center of circle
    for (int i = 0; i <= triangleAmount1; i++)
    {
        glVertex2f(
            x2 + (radius1 * cos(i * twicePi1 / triangleAmount1)),
            y2 + (radius1 * sin(i * twicePi1 / triangleAmount1))
        );


    }
    glEnd();
    // Airplane  window
    glColor3f(0.0f, 0.5f, 0.5f);//Blue-Green
    GLfloat x3 = -0.02f;
    GLfloat y3 = 0.35f;
    radius1 = .02f;
    twicePi1 = 2.0f * PI;
    glBegin(GL_POLYGON);
    glVertex2f(x3, y3); // center of circle
    for (int i = 0; i <= triangleAmount1; i++)
    {
        glVertex2f(
            x3 + (radius1 * cos(i * twicePi1 / triangleAmount1)),
            y3 + (radius1 * sin(i * twicePi1 / triangleAmount1))
        );
    }

    glEnd();
    // Airplane  window
    glColor3f(0.0f, 0.5f, 0.5f);//Blue-Green
    GLfloat x4 = 0.06f;
    GLfloat y4 = 0.35f;
    radius1 = .02f;
    twicePi1 = 2.0f * PI;
    glBegin(GL_POLYGON);
    glVertex2f(x4, y4); // center of circle
    for (int i = 0; i <= triangleAmount1; i++)
    {
        glVertex2f(
            x4 + (radius1 * cos(i * twicePi1 / triangleAmount1)),
            y4 + (radius1 * sin(i * twicePi1 / triangleAmount1))
        );
    }
    glEnd();

    glPopMatrix();

    //PLANE CODE END
    glEnd();

    glFlush();

}

//Function to draw a square using OpenGL primitives
void drawSquare() {

    glBegin(GL_QUADS); //Begin quadrilateral coordinates

    glVertex2f(0.3, -0.3); //Specify the first vertex

    glVertex2f(0.5, -0.3); //Specify the second vertex

    glVertex2f(0.5, -0.5); //Specify the third vertex

    glVertex2f(0.3, -0.5); //Specify the fourth vertex

    glEnd(); //End quadrilateral coordinates

    glFlush(); //Render Object
}

void drawSquare2() {

    glBegin(GL_QUADS); //Begin quadrilateral coordinates

    glVertex2f(0.5, -0.5); //Specify the first vertex

    glVertex2f(0.7, -0.5); //Specify the second vertex

    glVertex2f(0.7, -0.7); //Specify the third vertex

    glVertex2f(0.5, -0.7); //Specify the fourth vertex

    glEnd(); //End quadrilateral coordinates

    glFlush(); //Render Object
}

void drawSquare3() {

    glBegin(GL_QUADS); //Begin quadrilateral coordinates

    glVertex2f(0.3, -0.3); //Specify the first vertex

    glVertex2f(0.7, -0.7); //Specify the second vertex

    glVertex2f(0.7, -0.7); //Specify the third vertex

    glVertex2f(0.3, -0.7); //Specify the fourth vertex

    glEnd(); //End quadrilateral coordinates

    glFlush(); //Render Object
}

void drawSquare4() {

    glBegin(GL_QUADS); //Begin quadrilateral coordinates

    glVertex2f(0.3, -0.3); //Specify the first vertex

    glVertex2f(0.7, -0.3); //Specify the second vertex

    glVertex2f(0.7, -0.5); //Specify the third vertex

    glVertex2f(0.7, -0.7); //Specify the fourth vertex

    glEnd(); //End quadrilateral coordinates

    glFlush(); //Render Object
}

// microsoft logo
void microsoft() {

    glPushMatrix();
    glColor3f(0.196078, 0.6, 0.8);
    drawSquare3();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.498039, 1.0, 0.0);
    drawSquare4();
    glPopMatrix();


    glPushMatrix();
    glColor3f(1.0, 0.25, 0.0);
    drawSquare();
    glPopMatrix();


    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    drawSquare2();
    glPopMatrix();


}
static
void key2(unsigned char keyPressed, int x, int y) // key handling
{
    switch (keyPressed) {

    case '1':  // airplan up
        upair = upair + 0.01;
        break;

    case '2'://  airplan down

        upair = upair - 0.1;

        break;
        // microsoft up
    case '3':
        transValuemicro = transValuemicro + 0.1;
        break;
    case '4':// microsoft down
        transValuemicro = transValuemicro - 0.1;
        break;
        // rain down
    case '5':
        raun = raun - 0.1;
        break;
        // rain up
    case '6':
        raun = raun + 0.8;
        break;
    case '7':// toiqup up
        toiqup = toiqup + 0.1;
        break;
    case'8'://toiqup down
        toiqup = toiqup - 0.1;
        break;

    case'9':// mamlakah up
        uprig = uprig + 0.01;
        break;
    case'0': //mamlakah down
        uprig = uprig - 0.1;
        break;
    case'A':
        logo = logo + 0.1;
        break;
    case'L':
        logo = logo - 0.1;
        break;
    case't':
        saudit = saudit + 0.1;
        break;

    case's':
        saudit = saudit - 0.1;
        break;

    case'B':
        chip = chip + 0.1;
        break;
    case'C':
        chip = chip - 0.1;
        break;

    case 27:
        exit(0);
        break;

    default:
        fprintf(stderr, "\nKeyboard commands:\n\n"
            "q, <esc> - Quit\n");
        break;
    }
}


// light
void light() {
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0); //Black
    glVertex2f(0.0, -0.9);
    glVertex2f(0.0, 0.0);
    glVertex2f(-0.05, 0.0);
    glVertex2f(-0.05, -0.9);
    glEnd();

}
// road
void display1(void) {

  
    //front floor
    glBegin(GL_QUADS);
    glColor3ub(1, 1, 1);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, -0.8);
    glVertex2f(-1, -0.8);
    glEnd();

   
    //devider
    glBegin(GL_QUADS);
    glColor3ub(254, 254, 254);
    glVertex2f(-0.78, -0.82);
    glVertex2f(-0.50, -0.82);
    glVertex2f(-0.50, -0.85);
    glVertex2f(-0.78, -0.85);
    glEnd();

    glTranslatef(0.9, 0, 0);

    glBegin(GL_QUADS);
    glColor3ub(254, 254, 254);
    glVertex2f(-0.78, -0.82);
    glVertex2f(-0.50, -0.82);
    glVertex2f(-0.50, -0.85);
    glVertex2f(-0.78, -0.85);
    glEnd();


    glTranslatef(0.8, 0, 0);
    

    glBegin(GL_QUADS);
    glColor3ub(254, 254, 254);
    glVertex2f(-0.78, -0.82);
    glVertex2f(-0.50, -0.82);
    glVertex2f(-0.50, -0.85);
    glVertex2f(-0.78, -0.85);
    glEnd();

}
//mountain
void toiq() {
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.4f, 0.2f); // set a light brown
    glVertex2f(-0.2f, -0.5f);
    glVertex2f(0.9f, -0.5f);
    glVertex2f(0.9f, -0.5f);
    glVertex2f(0.7f, -0.3f);
    glVertex2f(0.7f, -0.3f);
    glVertex2f(0.4f, 0.2f);
    glVertex2f(0.4f, 0.2f);
    glVertex2f(0.35f, 0.1f);
    glVertex2f(0.35f, 0.1f);
    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.15f, -0.1f);
    glVertex2f(0.15f, -0.1f);
    glVertex2f(0.0f, -0.2f);
    glVertex2f(0.0f, -0.2f);
    glVertex2f(-0.1f, -0.3f);
    glVertex2f(-0.1f, -0.3f);
    glVertex2f(-0.2f, -0.5f);
    glEnd();



}
void applebody(float cx, float cy, float rx, float ry, int num_segments) {
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);//gray
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);
    float s = sinf(theta);
    float t;

    float x = 0.2;
    float y = 0.0;
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < num_segments; i++)
    {
        glVertex2f(x * rx + cx, y * ry + cy);
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

// apple
void apple() {

    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(0.05, 0.5);
    glVertex2f(0.1, 0.55);
    glVertex2f(0.15, 0.55);
    glEnd();
    applebody(0.0, 0.3, 0.7, 0.8, 40);
    applebody(0.1, 0.3, 0.7, 0.8, 40);
    UpperTower(0.2, 0.3, 0.4, 0.4, 40);

}
//squere
void square(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTexture1);
    
    glEnable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);
    
    glNormal3f(0,0,1);
    
    
    glTexCoord2f(0,0);
    glVertex3f(0,0,0);
    
    glTexCoord2f(0,1);
    glVertex3f(0,1,0);
    
    glTexCoord2f(1,1);
    glVertex3f(1,1,0);
    
    glTexCoord2f(1,0);
    glVertex3f(1,0,0);
 
    
    glEnd();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

}


//saudi FLAG
void  saudi(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTexture2);
    
    glEnable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);
    
    glNormal3f(0,0,1);
    
    
    glTexCoord2f(0,0);
    glVertex3f(0,0,0);
    
    glTexCoord2f(0,1);
    glVertex3f(0,1,0);
    
    glTexCoord2f(1,1);
    glVertex3f(1,1,0);
    
    glTexCoord2f(1,0);
    glVertex3f(1,0,0);
 
    
    glEnd();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

}


void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //airplane
    glPushMatrix();
    glTranslatef(0, 0.5, 0.0);
    glTranslatef(0, upair, 0);
    glTranslatef(transValueair, 0, 0);
    ariplan();
    glPopMatrix();


// clouds
    glPushMatrix();
    glTranslatef(1, -1.0, 0.0);
    cloud1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(transValue, -1.5, 0.0);
    cloud2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1, -1.0, 0.0);
    cloud3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, raun, 0);
    glTranslatef(0, -transValuer, 0);
    multipuleRain();
    glPopMatrix();


    // logo
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glTranslatef(0, transValuemicro, 0);
    microsoft();
    glPopMatrix();


// tower

    glPushMatrix();
    glTranslatef(0, uprig, 0);
    almamlakaTower();
    glPopMatrix();
    
 // light and road
    glPushMatrix();
    light();
    display1();
    glLoadIdentity();
    glPopMatrix();

    // toiq
    glPushMatrix();
    gluOrtho2D(-2, 1, -2, 1);
    glTranslatef(0, -2.5, 0);
    glTranslatef(-0.3, toiqup, 0);
    toiq();
    glPopMatrix();

    // apple
    glPushMatrix();
    glTranslatef(1.5, 0, 0);
    glTranslatef(logo, 0, 0);
    apple();
    glPopMatrix();
    
    
    ////chip
    glPushMatrix();
    gluOrtho2D(-5, 1, -5, 1);
    glTranslatef(0, -1.6, 0);
    glTranslatef(chip, 0, 0);
    square();
    glPopMatrix();
   

    ////saudi
    glPushMatrix();
    gluOrtho2D(-5, 1, -5, 1);
    glTranslatef(0, -0.8, 0);
    glTranslatef(saudit, 0, 0);
    saudi();
    glPopMatrix();

  
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(transValueX, transValueY, transValueZ, 0, 0, 0, 0, 1, 0);


    //  create light 0

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // change the value of the light position and the value of shininess

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);


    glEnable(GL_DEPTH_TEST);
    glutSolidSphere(0.05, 20, 20);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glFlush();
    glutSwapBuffers();


}


////////////////
//    Main    //
////////////////
int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(250, 50);
    glutCreateWindow("project");
    PlaySound(TEXT("jj"), NULL, SND_ASYNC);//audio in windows
    init();
    transValue = 0;
    transValuemicro = 0;
    glutDisplayFunc(display);
    glutIdleFunc(spin);
    glutReshapeFunc(reshapeFunc);
    glutKeyboardFunc(key);
    glutKeyboardFunc(key2);
    glutMainLoop();
    return 0;
}


