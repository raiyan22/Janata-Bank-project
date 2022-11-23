#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"

#define PI 3.14167

//eye pos 46 30 50
//lookat -4 10 0


using namespace std;

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1200, windowWidth=1400;
double gammaa = 0;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
//GLfloat eye_x = 50.0, eye_y = 20.0, eye_z = 50.0;
//GLfloat lookat_x = 0.0, lookat_y = 0.0, lookat_z = 0.0;

// iso
GLfloat eye_x = 46.0, eye_y = 30.0, eye_z = 50.0;
GLfloat lookat_x = -4.0, lookat_y = 10.0, lookat_z = 0.0;

//GLfloat eye_x = 0.0, eye_y = 0.0, eye_z = 60.0;
//GLfloat lookat_x = 0.0, lookat_y = 0.0, lookat_z = 0.0;

GLdouble up_x = 0.0;
GLdouble up_y = 1.0;
GLdouble up_z = 0.0;

//GLdouble sx=1.0,sy=1.0,sz=1.0;
GLdouble sx=0.4,sy=0.4,sz=0.4;


double anglePitch=0,angleYaw=90,angleRoll = 0;
GLboolean bRotate = false, uRotate = false, light0 = true,light1=false,light2=false,zRotate = false;
int pilotPitch=0, pilotYaw=0, pilotRoll=0;
unsigned int ID,ID1;



static GLubyte quadIndices[6][4] =
{
    //{4,5,6,7},
    {0,1,2,3},
    {7,6,5,4},
    {2,6,7,3},

    {0,4,5,1},
    {2,1,5,6},
    {7,4,0,3},
};




static GLfloat v_box[8][3] =
{
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},


    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0},
    {-1.0, 1.0, -1.0},
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


void cube(GLfloat r = 1,
          GLfloat g = 1,
          GLfloat b = 1
          )
{
  //  glColor3f(1,1,1);
    //GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_box[quadIndices[i][0]][0], v_box[quadIndices[i][0]][1], v_box[quadIndices[i][0]][2],
                    v_box[quadIndices[i][1]][0], v_box[quadIndices[i][1]][1], v_box[quadIndices[i][1]][2],
                    v_box[quadIndices[i][2]][0], v_box[quadIndices[i][2]][1], v_box[quadIndices[i][2]][2]);

        glVertex3fv(&v_box[quadIndices[i][0]][0]); glTexCoord2f(1,1);
        glVertex3fv(&v_box[quadIndices[i][1]][0]); glTexCoord2f(1,0);
        glVertex3fv(&v_box[quadIndices[i][2]][0]); glTexCoord2f(0,0);
        glVertex3fv(&v_box[quadIndices[i][3]][0]); glTexCoord2f(0,1);
    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);
}


void teapot(GLfloat r=0.3,
          GLfloat g=0.4,
          GLfloat b=0.5
          ) {

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

//    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
//    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glutSolidTeapot(1);
}


void cone(GLfloat r=0.3,
          GLfloat g=0.4,
          GLfloat b=0.5,
          GLboolean emission = false ) {

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glutSolidCone(.2,.4,20,10);
}


void sphere(GLfloat r=0.3,
          GLfloat g=0.4,
          GLfloat b=0.5,
          GLboolean emission = false ) {

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(.1,10,10);
}



void fan(GLfloat r=0.3,
          GLfloat g=0.4,
          GLfloat b=0.5,
          GLboolean emission = false ) {

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glPushMatrix();
    glTranslatef(-1,-1,-1);
    glScalef(0.3, 0.8, 3.8 );
    glutSolidCube(1);
    glPopMatrix();
}


//void roll(){
//        up_x = 1.0 * ( sin(rolltheta * PI / (float)180));
//        up_y = 1.0 * ( cos(rolltheta * PI / (float)180));
//}

void cyl(GLfloat r=0.3,
          GLfloat g=0.4,
          GLfloat b=0.5,
          GLboolean emission = false ) {

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
    gluCylinder(qobj,2,2,5,20,10);
}


void light(double x,
           double y,
           double z,
           GLenum Lights,
           bool lighton)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(Lights);

    if(lighton) {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, light_diffuse);
            glLightfv( Lights, GL_SPECULAR, light_specular);
            glLightfv( Lights, GL_POSITION, light_position);
        //}


    }
    else {
        glLightfv( Lights, GL_AMBIENT, no_light);
        glLightfv( Lights, GL_DIFFUSE, no_light);
        glLightfv( Lights, GL_SPECULAR, no_light);
        glLightfv( Lights, GL_POSITION, no_light);
    }
    //to know the position of * light
    /*glPushMatrix();
    glTranslatef(-15,4,28);
    glutSolidCube(2);
    glPopMatrix();*/


}

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

int i = 1;
GLuint ID_[100];

void LoadTexture1(const char*filename)
{
    glGenTextures(1, &ID_[i]);
    glBindTexture(GL_TEXTURE_2D, ID_[i]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID_[i++]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


void cameraPitch()
{
    lookat_x = 30*(cos(anglePitch*3.1416/180.0))*(cos(angleYaw*3.1416/180.0));
    lookat_y = 30*(sin(anglePitch*3.1416/180.0));
    lookat_z = 30*(cos(anglePitch*3.1416/180.0))*(sin(angleYaw*3.1416/180.0));
}

void cameraYaw()
{
    lookat_x = 30*(cos(anglePitch*3.1416/180.0))*(cos(angleYaw*3.1416/180.0));
    lookat_z = 30*(cos(anglePitch*3.1416/180.0))*(sin(angleYaw*3.1416/180.0));
}

void cameraRoll()
{
    up_x = 1.0*(sin(angleRoll*3.1416/180.0));
    up_y = 1.0*(cos(angleRoll*3.1416/180.0));
}

void fire_extinguisher() {
    glPushMatrix();
        glTranslatef(0, 0, 0);
        glRotatef(90, 1, 0, 0 );
        glScalef(1, 1, 1.6);
        cyl( .6,0,0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0, 0);
        glScalef(20, 20, 20);
        sphere( .6,0,0);
    glPopMatrix();

    // pin
    glPushMatrix();
        glTranslatef(0, 2.5, 0);
        glScalef(1, 1, 1);
        cube( .1,.1,0);
    glPopMatrix();

    // pipe
    glPushMatrix();
        glTranslatef(-1, 2.5,0);
        glScalef(2, 0.5, 0.5);
        cube( .1,.1,0);
    glPopMatrix();

    // pipe down
    glPushMatrix();
        glTranslatef(-3, 2.5-3, 0);
        glScalef(0.5, 4, 0.5);
        cube( .1,.1,0);
    glPopMatrix();

    // cone
    glPushMatrix();
        glTranslatef(-3, 2.5-9, 0);
        glRotatef(-90,1,0,0);
        glScalef(7, 7, 14);
        cone( .1,.1,0);
    glPopMatrix();


    // nicher sphere
    glPushMatrix();
        glTranslatef(0, -8, 0);
        glScalef(20, 20, 20);
        sphere( .6,0,0);
    glPopMatrix();
}


void chair() {
    // employee chair

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-15,5,30);
    glScalef(3.5,0.4,3.5);
    glBindTexture(GL_TEXTURE_2D, 5); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // employee chair rest

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-15,8,33);
    glScalef(3.5,3,0.4);
    glBindTexture(GL_TEXTURE_2D, 5); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // employee chair legs 1

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-18,2.5,33);
    glScalef(0.5,2.5,0.5);
    glBindTexture(GL_TEXTURE_2D, 5); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // employee chair legs 2

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,2.5,33);
    glScalef(0.5,2.5,0.5);
    glBindTexture(GL_TEXTURE_2D, 5); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // employee chair legs 3

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-18,2.5,27);
    glScalef(0.5,2.5,0.5);
    glBindTexture(GL_TEXTURE_2D, 5); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // employee chair legs 4

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,2.5,27);
    glScalef(0.5,2.5,0.5);
    glBindTexture(GL_TEXTURE_2D, 5); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



void atm() {
    // atm base
    glPushMatrix();
    glTranslatef(0,3,0);
    glScalef(4,2,4);
    cube(1,0.3,1);
    glPopMatrix();

    // atm top of base
    glPushMatrix();
    glTranslatef(0,7,0);
    glScalef(4,1,4);
    cube(1,0.3,1);
    glPopMatrix();

    // atm left between
    glPushMatrix();
    glTranslatef(-3,6,0);
    glScalef(4/3,1,4);
    cube(1,0.3,1);
    glPopMatrix();

    // atm right between
    glPushMatrix();
    glTranslatef(3,6,0);
    glScalef(4/3,1,4);
    cube(1,0.3,1);
    glPopMatrix();

    // atm taka
    glPushMatrix();
    glTranslatef(0,5.5,4); // z param will go from 0 to 4 if clicked a button
    glScalef(4/2.9,0.3,0.7);
    cube(0,0.8,0.1);
    glPopMatrix();

    // atm screen
    glPushMatrix();
    glTranslatef(0,8,-2.5);
    glRotatef(60,1,0,0);
    glScalef(4,3,3);
    cube(1,0.3,1);
    glPopMatrix();

    // atm screen tex
    glPushMatrix();
    glTranslatef(0,8.4,-2);
    glRotatef(60,1,0,0);
    glScalef(3.8,2.8,2.8);
    cube(0.3,1,1);
    glPopMatrix();

    // atm numpad tex
    glPushMatrix();
    glTranslatef(0,7.4,0);
    glScalef(3.8,0.8,3.8);
    cube(0.3,1,1);
    glPopMatrix();

    // atm backside
    glPushMatrix();
    glTranslatef(0,5,-3.5);
    glScalef(4,4,3);
    cube(1,0.3,1);
    glPopMatrix();
}

void atm2() {
    // atm base
    glPushMatrix();
    glTranslatef(0,3,0);
    glScalef(4,2,4);
    cube(1,0.3,1);
    glPopMatrix();

    // atm top of base
    glPushMatrix();
    glTranslatef(0,7,0);
    glScalef(4,1,4);
    cube(1,0.3,1);
    glPopMatrix();

    // atm left between
    glPushMatrix();
    glTranslatef(-3,6,0);
    glScalef(4/3,1,4);
    cube(1,0.3,1);
    glPopMatrix();

    // atm right between
    glPushMatrix();
    glTranslatef(3,6,0);
    glScalef(4/3,1,4);
    cube(1,0.3,1);
    glPopMatrix();

    // atm taka
    glPushMatrix();
    glTranslatef(0,5.5,0); // z param will go from 0 to 4 if clicked a button
    glScalef(4/2.9,0.3,0.7);
    cube(0,0.8,0.1);
    glPopMatrix();

    // atm screen
    glPushMatrix();
    glTranslatef(0,8,-2.5);
    glRotatef(60,1,0,0);
    glScalef(4,3,3);
    cube(1,0.3,1);
    glPopMatrix();

    // atm screen tex
    glPushMatrix();
    glTranslatef(0,8.4,-2);
    glRotatef(60,1,0,0);
    glScalef(3.8,2.8,2.8);
    cube(0.3,1,1);
    glPopMatrix();

    // atm numpad tex
    glPushMatrix();
    glTranslatef(0,7.4,0);
    glScalef(3.8,0.8,3.8);
    cube(0.3,1,1);
    glPopMatrix();

    // atm backside
    glPushMatrix();
    glTranslatef(0,5,-3.5);
    glScalef(4,4,3);
    cube(1,0.3,1);
    glPopMatrix();
}

void fan(){

}

void monitor(){
    // monitor

    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(90,0,1,0);
    glRotatef(90-15, 0,0,1);
    glScalef(3,0.2,4);
    cube(1,1,1);
    glPopMatrix();

    // monitor screen tex

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,0.1);
    glRotatef(90,0,1,0);
    glRotatef(90-15, 0,0,1);
    glScalef(2.8,0.2,3.8);
    glBindTexture(GL_TEXTURE_2D, 3); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // monitor stand
    glPushMatrix();
    glTranslatef(0,-3,0);
    glScalef(0.6,1,0.6);
    cube(1,1,1);
    glPopMatrix();

    // monitor base
    glPushMatrix();
    glTranslatef(0,-4,0);
    glScalef(2,0.2,1);
    cube(1,1,1);
    glPopMatrix();
}

void keyboard_mouse() {
    // keyboard
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(3,0.2,1.5);
    glBindTexture(GL_TEXTURE_2D, 10); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // mouse
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(5,0,0);
    glRotatef(15,0,1,0);
    glScalef(0.5,0.3,0.8);
    glBindTexture(GL_TEXTURE_2D, 11); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-5, 5, -5, 5, 4, 100);
    gluPerspective(50,1,4,200);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


    gluLookAt(eye_x,eye_y,eye_z, lookat_x,lookat_y,lookat_z, up_x,up_y,up_z);
    glViewport(0, 0, windowHeight, windowWidth);

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );

    glScaled(sx,sy,sz);


    /////////////////////////////////////////////////////////////////////////////
    ///////////  START
    ////////////////////////////////////////////////////////////////////////
    glPushMatrix();
    glTranslatef(0,0,0);
    cube(0.1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25,0,0);
    cube(1,0.1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,25);
    cube(1,1,0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,20,0);
    cube(1,0,0);
    glPopMatrix();

    ///////////////////////////////////

    // FLOOR of 2nd floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(40,0.4,65);
    glBindTexture(GL_TEXTURE_2D, 1); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // WALL of vault cashier er back side

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(20,12,-40);
    glScalef(20,12,0.4);
    glBindTexture(GL_TEXTURE_2D, 12); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     // WALL of vault cashier er back side solid color
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(20,12,-40.2);
    glScalef(20,12,0.4);
    glBindTexture(GL_TEXTURE_2D, 8); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //WALL 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,12,-30);
    glRotatef(90,0,1,0);
    glScalef(10,12,0.4);
    glBindTexture(GL_TEXTURE_2D, 6); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // WALL vault
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,12,-47-5.5);
    glRotatef(90,0,1,0);
    glScalef(12.5,12,0.4);
    glBindTexture(GL_TEXTURE_2D, 6); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // WALL vault tex
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-0.2,12,-47-5.5);
    glRotatef(90,0,1,0);
    glScalef(12.4-4,11.9-4,0.3+0.6);
    glBindTexture(GL_TEXTURE_2D, 13); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //WALL 3
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-27,12,-21);
    glScalef(13,12,0.9);
    glBindTexture(GL_TEXTURE_2D, 8); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//    cashier table top
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(20,11.02,-10);
    glScalef(20.03,1,2.8);
    glBindTexture(GL_TEXTURE_2D, 8); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // cashier
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(20,6,-10);
    glScalef(20,6,2);
    glBindTexture(GL_TEXTURE_2D, 7); // 1
    cube(1,1,0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // cashier 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(20,23,-10);
    glScalef(20,2,2);
    glBindTexture(GL_TEXTURE_2D, 8); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Cubicle

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-25,8,20);
    glScalef(15,8,0.4);
    glBindTexture(GL_TEXTURE_2D,6);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-25,8,20);
    glRotatef(90,0,1,0);
    glScalef(15,8,0.4);
    glBindTexture(GL_TEXTURE_2D,6);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // SOFA
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-25,1.8,55);
    glScalef(10,1.8,5);
    glBindTexture(GL_TEXTURE_2D,4);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-15,3,55);
    glScalef(2,3,5);
    glBindTexture(GL_TEXTURE_2D,4);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-35,3,55);
    glScalef(2,3,5);
    glBindTexture(GL_TEXTURE_2D,4);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-25,4,58.7);
//    glRotatef(15,1,0,0);
    glRotatef(90,0,1,0);
    glScalef(1.5,4,8);
    glBindTexture(GL_TEXTURE_2D,4);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Cublicle table

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-25,8,20);
    glScalef(15,0.4,10);
    glBindTexture(GL_TEXTURE_2D,7);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Cabinet
    glPushMatrix();
    glTranslatef(-34,10,-14);
    glScalef(5,10,5);
    cube(0.2,0.5,0.5);
    glPopMatrix();

    // Cabinet style
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-33.5,10,-14);
    glRotatef(90,0,1,0);
    glScalef(4.8,9.8,4.8);
    glBindTexture(GL_TEXTURE_2D,9);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    // GM table

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-22,8,-35);
    glScalef(8,0.3,12);
    glBindTexture(GL_TEXTURE_2D,7);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // GM table style front

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-16,4,-35);
    glScalef(0.3,4,10);
    glBindTexture(GL_TEXTURE_2D, 6);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // GM table style side

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-22.5,4,-25);
    glScalef(6.5,4,0.3);
    glBindTexture(GL_TEXTURE_2D, 6);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-22.5,4,-45);
    glScalef(6.5,4,0.3);
    glBindTexture(GL_TEXTURE_2D, 6);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    int disY = 3;

    // GM chair seat

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-22-10,10-disY,-35);
    glScalef(4.5,0.7,4);
    glBindTexture(GL_TEXTURE_2D, 17);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // GM chair rest

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-27-10,14-disY,-35);
    glRotatef(90+15,0,0,1);
    glScalef(5,0.7,4);
    glBindTexture(GL_TEXTURE_2D, 17);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // GM chair stand

    glPushMatrix();
    glTranslatef(-22-10,7-disY,-35);
    glScalef(0.7,3.5,0.7);
    cube(1,1,1);
    glPopMatrix();

    // GM chair legs

    glPushMatrix();
    glTranslatef(-22-10,4-disY,-35);
    glScalef(3,0.6,0.6);
    cube(0.1,0.1,0.1);
    glPopMatrix();

    // GM chair legs rotated

    glPushMatrix();
    glTranslatef(-22-10,4-disY,-35);
    glScalef(0.6,0.6,3);
    cube(0.1,0.1,0.1);
    glPopMatrix();

    // GM Cabinet
    glPushMatrix();
    glTranslatef(-34,10,-60);
    glScalef(4,10,4);
    cube(1,1,0.4);
    glPopMatrix();

    // GM Cabinet style
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-34,10,-59.5);
    glScalef(3.8,9.8,3.8);
    glBindTexture(GL_TEXTURE_2D,9);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-17,0,3);
    chair();
    glPopMatrix();


    // cashier chair 1
    glPushMatrix();
    glTranslatef(-5,0,2);
    glRotatef(180, 0,1,0);
    chair();
    glPopMatrix();

    // cashier chair 2
    glPushMatrix();
    glTranslatef(16,0,2);
    glRotatef(180, 0,1,0);
    chair();
    glPopMatrix();

    // employee chair 3
    glPushMatrix();
    glTranslatef(-40,0,39);
    glRotatef(15,0,1,0);
    glRotatef(180, 0,1,0);
    chair();
    glPopMatrix();

    // employee chair 3
    glPushMatrix();
    glTranslatef(-34,0,36);
    glRotatef(180, 0,1,0);
    chair();
    glPopMatrix();

    // Cashier table ////////////////

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(22,8,-16.2);
    glScalef(16,0.4,8);
    glBindTexture(GL_TEXTURE_2D,7);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // GM laptop base

    glPushMatrix();
    glTranslatef(-23.5,8.5,-35);
    glScalef(3,0.2,4);
    cube(1,1,1);
    glPopMatrix();

    // base style for keyboard
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-23.5,8.5,-35);
    glScalef(2.8,0.3,3.8);
    glBindTexture(GL_TEXTURE_2D,15);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // GM laptop lid

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-20,10,-35);
    glRotatef(90-15, 0,0,1);
    glScalef(3,0.2,4);
    glBindTexture(GL_TEXTURE_2D,14);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // screen

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-20.2,10.2,-35);
    glRotatef(90-15, 0,0,1);
    glScalef(2.8,0.2,3.8);
    glBindTexture(GL_TEXTURE_2D,16);
    cube(0.7,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    /////////////////

    // extended FLOOR of 2nd floor
    glPushMatrix();
    glTranslatef(30,-0.6,80);
    glScalef(10,1,15);
    cube(1,1,1);
    glPopMatrix();

    // stair 1
    glPushMatrix();

    glTranslatef(19,-2,72);
    glScalef(3,1,15/2);
    cube(1,1,1);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(15,-4,72);
    glScalef(3,1,15/2);
    cube(1,1,1);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(11,-6,72);
    glScalef(3,1,15/2);
    cube(1,1,1);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(11-4,-6-2,72);
    glScalef(3,1,15/2);
    cube(1,1,1);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(11-4-4,-6-2-2,72);
    glScalef(3,1,15/2);
    cube(1,1,1);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(11-4-4-4,-6-2-2-2,72);
    glScalef(3,1,15/2);
    cube(1,1,1);

    glPopMatrix();

//    glPushMatrix();
//
//    glTranslatef(11-4-4-4,-6-2-2-2-2,85);
//    glScalef(3,1,15/2);
//    cube(1,1,1);
//
//    glPopMatrix();

    // going up from the 1st to 2nd floor
    glPushMatrix();
    glTranslatef(23-4,-25+1,88);
    glScalef(3,1,15/2);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23-4-4,-25+1+2,88);
    glScalef(3,1,15/2);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23-4-4-4,-25+1+2+2,88);
    glScalef(3,1,15/2);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23-4-4-4-4,-25+1+2+2+2,88);
    glScalef(3,1,15/2);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23-4-4-4-4-4,-25+1+2+2+2+2,88);
    glScalef(3,1,15/2);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23-4-4-4-4-4-4,-25+1+2+2+2+2+2,88);
    glScalef(3,1,15/2);
    cube(1,1,1);
    glPopMatrix();

    // HALF FLOOR
    glPushMatrix();
    glTranslatef(11-4-4-4-10,-6-2-2-2-1,80);
    glScalef(10,0.4,15);
    cube(1,1,1);
    glPopMatrix();

//    // half floor
//    glPushMatrix();
//    glTranslatef(11-4-4,-6-2-2,80);
//    glScalef(10,1,15);
//    cube(1,1,1);
//    glPopMatrix();


// extended FLOOR of 1st floor
    glPushMatrix();
    glTranslatef(30,-25.6,80);
    glScalef(10,1,15);
    cube(1,1,1);
    glPopMatrix();

    // extended FLOOR of 1st floor extended far back under the stairs
    glPushMatrix();
    glTranslatef(9,-25.6,80);
    glScalef(30,1,15);
    cube(1,1,1);
    glPopMatrix();


    //////////////////////////////////
    ////// 1st floor
    //////////////////////////

    // FLOOR of 1st floor
    glPushMatrix();
    glTranslatef(0,-25,0);
    glScalef(40,0.4,65);
    cube(1,1,1);
    glPopMatrix();


    //////////////////////////////////
    ////// roof
    //////////////////////////

    // FLOOR of 1st floor
//    glPushMatrix();
//    glTranslatef(0,24,0);
//    glScalef(40,0.4,65);
//    cube(1,1,1);
//    glPopMatrix();

    // ATM
    glPushMatrix();
    glTranslatef(-10,-25,50);
    glRotatef(180,0,1,0);
    atm();
    glPopMatrix();

    // ATM 2
    glPushMatrix();
    glTranslatef(0,-25,50);
    glRotatef(180,0,1,0);
    atm2();
    glPopMatrix();


    // monitor 4
    glPushMatrix();
    glTranslatef(-20,12.5,23);
    glRotatef(20,0,1,0);
    monitor();
    glPopMatrix();

    // monitor 2
    glPushMatrix();
    glTranslatef(-20,12.5,17);
    glRotatef(180-30,0,1,0);
    monitor();
    glPopMatrix();

    // monitor 1
    glPushMatrix();
    glTranslatef(-32,12.5,17);
    glRotatef(180,0,1,0);
    monitor();
    glPopMatrix();

    // monitor 3
    glPushMatrix();
    glTranslatef(-32,12.5,23);
    glRotatef(-10,0,1,0);
    monitor();
    glPopMatrix();

    // keyboard_mouse 4
    glPushMatrix();
    glTranslatef(-17,8.5,26);
    keyboard_mouse();
    glPopMatrix();

    // keyboard_mouse 2
    glPushMatrix();
//    glTranslatef(-17,8.5,26);
    glTranslatef(-17,8.5,14);
    glRotatef(180,0,1,0);
    keyboard_mouse();
    glPopMatrix();


    // keyboard_mouse 1
    glPushMatrix();
//    glTranslatef(-17,8.5,26);
    glTranslatef(-31,8.5,14);
    glRotatef(180,0,1,0);
    keyboard_mouse();
    glPopMatrix();

    // keyboard_mouse 3
    glPushMatrix();
//    glTranslatef(-17,8.5,26);
    glTranslatef(-34,8.5,26);
//    glRotatef(180,0,1,0);
    keyboard_mouse();
    glPopMatrix();


////    // tob
//    glPushMatrix();
//    glTranslatef(0,10,0);
//    glScalef(4,4,4);
////    glutSolidDodecahedron(); // gaas er pata
//    glutSolidTetrahedron();
//    glPopMatrix();

    glPushMatrix();
    glTranslatef(3+35,-25.6+10,85);
    glScalef(.8,0.8,0.8);
    fire_extinguisher();
    glPopMatrix();









/////////////////////////////////////////////////////////////////////////////////

//// BASIN
//    glPushMatrix();
//        glTranslatef(3, 8, 20);
//        glScalef(6, 1, 6);
//        cube( 1,1,0.8);
//    glPopMatrix();
//
//    //bottom
//    glPushMatrix();
//        glTranslatef(2, 4, 20);
//        glScalef(2.5, 8, 2.5);
//        cube( 1,1,0.8);
//    glPopMatrix();
//
//    // left
//    glPushMatrix();
//        glTranslatef(3, 9, 23);
//        glScalef(6, 1, 1);
//        cube( 1,1,0.8);
//    glPopMatrix();
//
//    // right
//    glPushMatrix();
//        glTranslatef(3, 9, 17);
//        glScalef(6, 1, 1);
//        cube( 1,1,0.8);
//    glPopMatrix();
//
//    // front
//    glPushMatrix();
//        glTranslatef(6.5, 9, 20);
//        glScalef(1, 1, 7);
//        cube( 1,1,0.8);
//    glPopMatrix();
//
//
//    // knob
//    glPushMatrix();
//        glTranslatef(1.7, 11, 20);
//        glScalef(3, 0.5, 1);
//        cube( .4,.4,.4);
//    glPopMatrix();
//
//    // knob 1
//    glPushMatrix();
//        glTranslatef(.6, 11, 21);
//        glScalef(.8, .8, .8);
//        cube( .4,.4,.4);
//    glPopMatrix();
//
//    // knob 2
//    glPushMatrix();
//        glTranslatef(.6, 11, 19);
//        glScalef(.8, .8, .8);
//        cube( .4,.4,.4);
//    glPopMatrix();
//
//
//    // light
//    glPushMatrix();
//        glTranslatef(.6, 18, 24);
//        glScalef(.5, .5, 8);
//        cube( .9,.9,.9);
//    glPopMatrix();
//
//    // light holder
//    glPushMatrix();
//        glTranslatef(.2, 18, 24);
//        glScalef(0.2, 1, 8.1);
//        cube( .3,.3,.3);
//    glPopMatrix();
//
//
//    // spotlight
//    glPushMatrix();
//        glTranslatef(23, 10, 5);
//        glRotatef(220, 1, 0, 0 );
//        glScalef(8, 8, 8);
//        cone( .9,.1,.9);
//    glPopMatrix();
//
//    // sport stand base
//    glPushMatrix();
//        glTranslatef(23, 0.4, 2.2);
//        glScalef(4, 0.4, 4);
//        cube( 0.9,.1,0.9);
//    glPopMatrix();
//
//    // sport stand stand
//    glPushMatrix();
//        glTranslatef(23, 6, 2.2);
//        glScalef(0.5, 12, 0.5);
//        cube( 0.6,.1,0.6);
//    glPopMatrix();
//
//
//    // spotlight bulb
//    glPushMatrix();
//        glTranslatef(23, 10, 5);
////        glRotatef(220, 1, 0, 0 );
//        glScalef(8, 8, 8);
//        sphere( .9,.9,.9);
//    glPopMatrix();

//    // cyl
//    glPushMatrix();
//        glTranslatef(10, 10, 10);
////        glRotatef(220, 1, 0, 0 );
//        glScalef(2, 2, 2);
//        cyl( .5,.3,.4);
//    glPopMatrix();


//    // disk
//    glPushMatrix();
//        glTranslatef(23, 1, 1);
//        glRotatef(90, 1, 0, 0 );
//        glScalef(0.5, 0.5, 0.5);
//        disk( .5,.3,.4);
//    glPopMatrix();

//    // partdisk
//    glPushMatrix();
//        glTranslatef(23, 1, 1);
//        glRotatef(90, 1, 0, 0 );
//        glScalef(0.5, 0.5, 0.5);
//        partialDisc( .5,.3,.4);
//    glPopMatrix();

//////////////////////////////////////////
    // fan
//    glPushMatrix();
//
//    glTranslatef(0,17,15);
//    glRotatef( rotAngle, 1,0,0 );
//
//        glPushMatrix();
//            glTranslatef(0,0,0);
//            glScalef(0.3, 0.8, 3 );
//            glutSolidCube(1);
//        glPopMatrix();
//
//            glTranslatef(0,0,0);
//            glRotatef(90, 1,0,0);
//        glPushMatrix();
//            glTranslatef(0,0,0);
//            glScalef(0.3, 0.8, 3 );
//            glutSolidCube(1);
//        glPopMatrix();
//    glPopMatrix();
//


//    // dir light
//    glPushMatrix();
//        glTranslatef(8, 20, .6);
//        glScalef(8, .5, 0.5);
//        cube( .9,.9,.9);
//    glPopMatrix();



    light(1,18,24, GL_LIGHT0,light0);
    light(23,10,5.2,GL_LIGHT1,light1);
//    light(-15,4,28,GL_LIGHT2,light2,false,true);

    glFlush();
    glutSwapBuffers();
}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 't':
    case 'T':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case 'w':
        eye_y++;
        lookat_y++;
        glutPostRedisplay();
        break;
    case 's':
        eye_y--;
        lookat_y--;
        glutPostRedisplay();
        break;
    case 'd':
        eye_x++;
        lookat_x++;
        glutPostRedisplay();
        break;
    case 'a':
        eye_x--;
        lookat_x--;
        glutPostRedisplay();
        break;

    case '+':
        eye_z--;
        if(pilotRoll)
        {
            angleRoll++;
        }
        else
        {
            lookat_z--;
        }
        glutPostRedisplay();
        break;
    case '-':
        eye_z++;
        if(pilotRoll)
        {
            angleRoll--;
        }
        else
        {
            lookat_z;
        }
        glutPostRedisplay();
        break;
    case '*':
        sx+=0.1;
        sy+=0.1;
        sz+=0.1;
        glutPostRedisplay();
        break;
    case '/':
        sx-=0.1;
        sy-=0.1;
        sz-=0.1;
        glutPostRedisplay();
        break;
    //for pitch-yaw-roll
    case 'i':
        if(angleRoll<=180)
        {
            angleRoll++;
            cameraRoll();
        }
        glutPostRedisplay();
        break;
    case 'j':
        if(angleRoll>=-180)
        {
            angleRoll--;
            cameraRoll();
        }
        glutPostRedisplay();
        break;
    case 'o':
        if(angleYaw<180)
        {
            angleYaw++;
            cameraYaw();

        }
        glutPostRedisplay();
        break;
    case 'p':
        if(angleYaw>0)
        {
            angleYaw--;
            cameraYaw();
        }
        glutPostRedisplay();
        break;
    case 'k':
        if(anglePitch<90)
        {
            anglePitch++;
            cameraPitch();

        }
        glutPostRedisplay();
        break;
    case 'l':
        if(anglePitch>-90)
        {
            anglePitch--;
            cameraPitch();
        }
        glutPostRedisplay();
        break;

    //switch for light0
    case '1':
        light0 = !light0;
        glutPostRedisplay();
        break;
    case '2':
        light1 = !light1;
        glutPostRedisplay();
        break;
    case '3':
        light2 = !light2;
        glutPostRedisplay();
        break;

    //for fan
    case '4':
        zRotate = !zRotate;
        glutPostRedisplay();
        break;

    //for pilotview
    case '7':
        pilotPitch = !pilotPitch;
        glutPostRedisplay();
        break;
    case '8':
        pilotYaw = !pilotYaw;
        glutPostRedisplay();
        break;
    case '9':
        pilotRoll = !pilotRoll;
        glutPostRedisplay();
        break;



    case 27:  // Escape key
        exit(1);
    }


}


void animate()
{
    if (bRotate == true)
    {
        theta += 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if (zRotate == true)
    {
        gammaa += 0.1;
        if(gammaa > 360.0)
            gammaa -= 360.0*floor(gammaa/360.0);
    }
//    cout << "eye pos "<< eye_x << " " << eye_y << " " << eye_z << endl;
//    cout << "lookat "<< lookat_x << " " << lookat_y << " " << lookat_z << endl;
//    cout << "sxsysz "<< sx << " " << sy << " " << sz << endl;
    glutPostRedisplay();

}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Janata Bank, Kuet");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    // C:\Users\Raiyan\Desktop\ogl


    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\floor1.bmp"); // 1
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\mo.bmp"); // 2
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\win_desktop.bmp"); // 3
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\sofa.bmp"); // 4
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\chair_tex.bmp"); // 5
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\cubicle_table.bmp"); // 6
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\cubicle_table_1.bmp"); // 7

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\queue_1.bmp"); // 8
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\cabinet.bmp"); // 9

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\keyboard.bmp"); // 10
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\mouse.bmp"); // 11
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\cashier_bg.bmp"); // 12

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\vault.bmp"); // 13

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\laptop_back.bmp"); // 14
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\keyboard_laptop.bmp"); // 15

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\laptop_screen.bmp"); // 16

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\chair_tex2.bmp"); // 17



    glutKeyboardFunc(myKeyboardFunc);
    //sndPlaySound("woo.wav",SND_ASYNC);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    //PlaySound(TEXT("woo.wav"),NULL, SND_SYNC);
    glutMainLoop();

    return 0;
}


