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

GLfloat eye_x = 46.0, eye_y = 30.0, eye_z = 50.0;
GLfloat lookat_x = -4.0, lookat_y = 10.0, lookat_z = 0.0;

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


int i = 1;
GLuint ID_[100];


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
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(40,0.4,65);
    cube(1,1,1);
    glPopMatrix();

    // WALL

    glPushMatrix();
    glTranslatef(20,12,-40);
    glScalef(20,12,0.4);
    cube(1,1,1);
    glPopMatrix();

    //WALL 2
    glPushMatrix();
    glTranslatef(0,12,-40);
    glRotatef(90,0,1,0);
    glScalef(20,12,0.4);
    cube(1,1,1);
    glPopMatrix();

    //WALL 3
    glPushMatrix();
    glTranslatef(-27,12,-20);
    glScalef(13,12,0.4);
    cube(1,1,1);
    glPopMatrix();

    // cashier
    glPushMatrix();
    glTranslatef(20,6,-10);
    glScalef(20,6,2);
    cube(1,1,1);
    glPopMatrix();

    // cashier 2
    glPushMatrix();
    glTranslatef(20,23,-10);
    glScalef(20,2,2);
    cube(1,1,1);
    glPopMatrix();


    // Cubicle

    glPushMatrix();
    glTranslatef(-25,8,20);
    glScalef(15,8,0.4);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25,8,20);
    glRotatef(90,0,1,0);
    glScalef(15,8,0.4);
    cube(1,1,1);
    glPopMatrix();


    // SOFA
    glPushMatrix();
    glTranslatef(-25,1.8,55);
    glScalef(10,1.8,5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,3,55);
    glScalef(2,3,5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-35,3,55);
    glScalef(2,3,5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25,4,58.7);
//    glRotatef(15,1,0,0);
    glRotatef(90,0,1,0);
    glScalef(1.5,4,8);
    cube(1,1,1);
    glPopMatrix();

    // Cublicle table

    glPushMatrix();
    glTranslatef(-25,8,20);
    glScalef(15,0.4,10);
    cube(1,1,1);
    glPopMatrix();

    // Cabinet
    glPushMatrix();
    glTranslatef(-34,10,-14);
    glScalef(05,10,5);
    cube(1,1,1);
    glPopMatrix();

    // Cabinet style
    glPushMatrix();
    glTranslatef(-34,10,-13.5);
    glScalef(4.8,9.8,4.8);
    cube(1,1,1);
    glPopMatrix();



    // GM table

    glPushMatrix();
    glTranslatef(-22,8,-35);
    glScalef(8,0.3,12);
    cube(1,1,1);
    glPopMatrix();

    // GM table style front

    glPushMatrix();
    glTranslatef(-16,4,-35);
    glScalef(0.3,4,10);
    cube(1,1,1);
    glPopMatrix();

    // GM table style side

    glPushMatrix();
    glTranslatef(-22.5,4,-25);
    glScalef(6.5,4,0.3);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-22.5,4,-45);
    glScalef(6.5,4,0.3);
    cube(1,1,1);
    glPopMatrix();

    // GM chair seat

    glPushMatrix();
    glTranslatef(-22,10,-35);
    glScalef(4.5,0.7,4);
    cube(1,1,1);
    glPopMatrix();

    // GM chair rest

    glPushMatrix();
    glTranslatef(-26,14,-35);
    glRotatef(90+15,0,0,1);
    glScalef(5,0.7,4);
    cube(1,1,1);
    glPopMatrix();

    // GM Cabinet
    glPushMatrix();
    glTranslatef(-34,10,-60);
    glScalef(4,10,4);
    cube(1,1,1);
    glPopMatrix();

    // GM Cabinet style
    glPushMatrix();
    glTranslatef(-34,10,-59.5);
    glScalef(3.8,9.8,3.8);
    cube(1,1,1);
    glPopMatrix();

/////////////////////////////////////////////////////////////////////////////////

    // POINTS
/*
    // right side wall
    glPushMatrix();
        glTranslatef(0,0,0);
//        glTranslatef(0,0,0);
//        glScalef(30,30,0.5);
        cube( 0.1,0.2,0.3);
    glPopMatrix();

    // left side wall

    glPushMatrix();
        glTranslatef(30,0,0);
//        glTranslatef(0,10,0);
//        glScalef(30, 0.5,30);
        cube( 0.6,0.7,0.8);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(0,30,0);
//        glTranslatef(0,10,0);
//        glScalef(30, 0.5,30);
        cube( 0.9,0.1,0.1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,30);
//        glTranslatef(0,10,0);
//        glScalef(30, 0.5,30);
        cube( 0.3,0.0,0.9);
    glPopMatrix();
*/

    // WALLS
    // LEFT WALL

//    glPushMatrix();
//        glTranslatef(0,10,5);
//        glScalef(0.5,20,10);
//        cube( 0.3,0.0,0.9);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslatef(0,10,10);
//        glScalef(0.5,20,5);
//        cube( 0.3,0.0,0.9);
//    glPopMatrix();
//
//    // fan bottom wall
//    glPushMatrix();
//        glTranslatef(0,7.5,15);
//        glScalef(0.5,14.5,5);
//        cube( 0.3,0.0,0.9);
//    glPopMatrix();
//
//    // fan top wall
//    glPushMatrix();
//        glTranslatef(0,19.4,15);
//        glScalef(0.5,1.2,5);
//        cube( 0.3,0.0,0.9);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslatef(0,10,23.5);
//        glScalef(0.5,20,12);
//        cube( 0.3,0.0,0.9);
//    glPopMatrix();

//    glPushMatrix();
//        glTranslatef(0,20,15);
//        glScalef(0.5,1,5);
//        cube( 0.3,0.0,0.9);
//    glPopMatrix();

    // EXHAUST FAN
//    glPushMatrix();
//        glTranslatef(0,17.5,15);
//        glScalef(0.5,5,5);
//        cube( 0.3,0.5,0.9);
//    glPopMatrix();
//
//   glPushMatrix();
//        glTranslatef(0,16,15);
//        glScalef(0.5,5,5);
//        cube( 0.3,0.5,0.9);
//    glPopMatrix();





    // RIGHT WALL
//    glPushMatrix();
//        glTranslatef(15,10,0);
//        glScalef(30,20,0.5);
//        cube( 0.3,0.0,0.9);
//    glPopMatrix();

    ////////////////////////////////////////////////////////////////////////
    // FLOOR
//    glEnable(GL_TEXTURE_2D);
//    glPushMatrix();
//        glTranslatef(15,0,0);
//        glScalef(7.5, 0.5,14.75);
//        LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\floor.bmp");
//        cube( 1,1,1);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);

//    // CABINET
//    glPushMatrix();
//        glTranslatef(6,15,3);
//        glScalef(12, 6, 5);
//        cube( 0.8,0.5,0.2);
//    glPopMatrix();
//
//
//    //
//    glPushMatrix();
//        glTranslatef(15,16,3);
//        glScalef(6, 4, 5);
//        cube( 0.8,0.5,0.2);
//    glPopMatrix();
//
//    // CABINET
//    glPushMatrix();
//        glTranslatef(6,3,3);
//        glScalef(12, 6, 5);
//        cube( 0.8,0.5,0.2);
//    glPopMatrix();
//
//    // CABINET
//    glPushMatrix();
//        glTranslatef(15,2,3);
//        glScalef(12, 4, 5);
//        cube( 0.8,0.5,0.2);
//    glPopMatrix();
//
//    ////////////////////////////
//    // CABINET style 1 from right to left
//    glPushMatrix();
//        glTranslatef(10,15,5.2);
//        glScalef(3, 5.2, 1);
//        cube( 1,1,0.9);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslatef(6.5,15,5.2);
//        glScalef(3, 5.2, 1);
//
//        cube( 1,1,0.9);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslatef(3,15,5.2);
//        glScalef(3, 5.2, 1);
//        cube( 1,1,0.9);
//    glPopMatrix();
//
//    // CABINET style 1 from right to left nicher gula
//    glPushMatrix();
//        glTranslatef(10.4,3.2,5.2);
//        glScalef(3, 5.2, 1);
//        cube( 1,1,0.9);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslatef(6.9,3.2,5.2);
//        glScalef(3, 5.2, 1);
//        cube( 1,1,0.9);
//    glPopMatrix();
//
//
//
//    // CABINET  BOTTOM LEFT
//    glPushMatrix();
//        glTranslatef(2.5, 3, 10);
//        glScalef(5, 6, 9);
//        cube( 0.8,0.5,0.2);
//    glPopMatrix();
////cube( 0.8,0.1,0.2);
//
//    glPushMatrix();
//        glTranslatef(3, 6.8, 3);
////        glScalef(5, 6, 9);
//        teapot(1.5);
//    glPopMatrix();
//
//
//
//
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
//////////////////////////////////////////////
//
//    // stove
//    glPushMatrix();
//        glTranslatef(16, 5, 3);
//        glScalef(6, 1.2, 4);
//        cube( .7,.8,.7);
//    glPopMatrix();
//
//    // stove knob 1
//    glPushMatrix();
//        glTranslatef(14.5, 5, 5);
//        glScalef(0.5, 0.5, 0.5);
//        cube( .2,.2,.2);
//    glPopMatrix();
//
//    // stove knob 1
//    glPushMatrix();
//        glTranslatef(17.5, 5, 5);
//        glScalef(0.5, 0.5, 0.5);
//        cube( .2,.2,.2);
//    glPopMatrix();

    /////////////////////////////

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

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\floor.bmp"); //1
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\floor.bmp"); //2
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\floor.bmp"); //3
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\floor.bmp"); //4

    glutKeyboardFunc(myKeyboardFunc);
    //sndPlaySound("woo.wav",SND_ASYNC);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    //PlaySound(TEXT("woo.wav"),NULL, SND_SYNC);
    glutMainLoop();

    return 0;
}


