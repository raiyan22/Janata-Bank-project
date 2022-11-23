#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include<math.h>
#define PI 3.14167
#include<bits/stdc++.h>
#include "BmpLoader.h"


using namespace std;
int car_facing = 0;
double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1200, windowWidth=1400;
double gammaa = 0, sun = 0;
GLfloat alpha = 0.0, theta = 0.0, rot_Angle = 0.0, axis_x=0.0, axis_y=0.0, GM_door_x=-13, floor1_door_x=26, floor2_door_x=26, main_door_z=15, main_door_right_z=-15,  car_rot=0, car_x=100, car_z=20 ;
//GLfloat eye_x = 50.0, eye_y = 20.0, eye_z = 50.0;
//GLfloat lookat_x = 0.0, lookat_y = 0.0, lookat_z = 0.0;

// iso
//GLfloat eye_x = 46.0, eye_y = 30.0, eye_z = 50.0;
//GLfloat lookat_x = -4.0, lookat_y = 10.0, lookat_z = 0.0;

GLfloat eye_x = 50.0, eye_y = 20.0, eye_z = 50.0;
GLfloat lookat_x = .0, lookat_y = 10.0, lookat_z = 0.0;

//GLfloat eye_x = 0.0, eye_y = 0.0, eye_z = 60.0;
//GLfloat lookat_x = 0.0, lookat_y = 0.0, lookat_z = 0.0;

GLdouble up_x = 0.0;
GLdouble up_y = 1.0;
GLdouble up_z = 0.0;

//GLdouble sx=1.0,sy=1.0,sz=1.0;
GLdouble sx=0.2,sy=0.2,sz=0.2;


double anglePitch=0,angleYaw=90,angleRoll = 0;
// light0 = sun
// light1 = GM
// light2 = 2nd floor
// light3 = 1st floor
GLboolean bRotate = false, uRotate = false, GM_door_open = false, light0 = false,light1=true,light2=false, light3=false, light5=true, zRotate = false;
GLboolean floor1_door_open = false, floor2_door_open = false, main_door_open = false, fanRot = false;
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


static GLfloat v_pyramid[8][3] =
{
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {0.6, 1.0, 1.0},
    {-0.6, 1.0, 1.0},


    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {0.6, 1.0, -1.0},
    {-0.6,1.0, -1.0},
};

void slcube(GLfloat r,GLfloat g,GLfloat b, GLfloat emission=false)
{
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

    for (GLint i = 0; i <6; i++) {

        glBegin(GL_QUADS);
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
        glEnd();

    }
}



void cube(GLfloat r = 1,
          GLfloat g = 1,
          GLfloat b = 1,
          GLfloat emission = false
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

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_box[quadIndices[i][0]][0], v_box[quadIndices[i][0]][1], v_box[quadIndices[i][0]][2],
                    v_box[quadIndices[i][1]][0], v_box[quadIndices[i][1]][1], v_box[quadIndices[i][1]][2],
                    v_box[quadIndices[i][2]][0], v_box[quadIndices[i][2]][1], v_box[quadIndices[i][2]][2]);

        glVertex3fv(&v_box[quadIndices[i][0]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_box[quadIndices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_box[quadIndices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_box[quadIndices[i][3]][0]);
        glTexCoord2f(0,1);
    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);
}


void teapot(GLfloat r=0.3,
            GLfloat g=0.4,
            GLfloat b=0.5
           )
{

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
          GLboolean emission = false )
{

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


void sphereG(GLfloat r=0.3,
             GLfloat g=0.4,
             GLfloat b=0.5,
             GLboolean emission = false)
{

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
    gluQuadricTexture(qobj,1);
    gluSphere(qobj,0.1,40,40);

}

void sphere(GLfloat r=0.3,
            GLfloat g=0.4,
            GLfloat b=0.5,
            GLboolean emission = false)
{

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


    glutSolidSphere(.1,30,30);
}



void gold_stack()
{
// vault gold
    glPushMatrix();
    glTranslatef(0,0,0);

    glScalef(2,1*0.7, 1.5*0.7);
    glRotatef(90,0,1,0);
    slcube( 1, 1, 0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,3);

    glScalef(2,1*0.7, 1.5*0.7);
    glRotatef(90,0,1,0);
    slcube( 1, 1, 0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,6);

    glScalef(2,1*0.7, 1.5*0.7);
    glRotatef(90,0,1,0);
    slcube( 1, 1, 0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,0);

    glScalef(2,1*0.7, 1.5*0.7);
    glRotatef(90,0,1,0);
    slcube( 1, 1, 0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,3);

    glScalef(2,1*0.7, 1.5*0.7);
    glRotatef(90,0,1,0);
    slcube( 1, 1, 0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,6);

    glScalef(2,1*0.7, 1.5*0.7);
    glRotatef(90,0,1,0);
    slcube( 1, 1, 0.4);
    glPopMatrix();

    // gold base
    glPushMatrix();
    glTranslatef(2.5,-1.5,3);

    glScalef(5, 0.6, 5);
    cube( 1, 0.6, 0.4);
    glPopMatrix();

}


//void fan(GLfloat r=0.3,
//          GLfloat g=0.4,
//          GLfloat b=0.5,
//          GLboolean emission = false ) {
//
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { r, g, b, 1.0 };
//    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess[] = {60};
//
//    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};
//
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
//
//    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
//    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);
//
//    glPushMatrix();
//    glTranslatef(-1,-1,-1);
//    glScalef(0.3, 0.8, 3.8 );
//    glutSolidCube(1);
//    glPopMatrix();
//}


//void roll(){
//        up_x = 1.0 * ( sin(rolltheta * PI / (float)180));
//        up_y = 1.0 * ( cos(rolltheta * PI / (float)180));
//}

void outer_sphere(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
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
    gluQuadricTexture(qobj,1);
    gluSphere(qobj,10,25,25);
}

void table_help_desk()
{


// table top
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,8,0);
    glScalef(12,0.4,8);
    glBindTexture(GL_TEXTURE_2D,7);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // table leg 1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0+9,4,0);
    glScalef(0.4,4,7.8);
    glBindTexture(GL_TEXTURE_2D,6);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // table leg 1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0-9,4,0);
    glScalef(0.4,4,7.8);
    glBindTexture(GL_TEXTURE_2D,6);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

// for fire extinguisher
void cyl_f(GLfloat r=0.3,
           GLfloat g=0.4,
           GLfloat b=0.5,
           GLboolean emission = false )
{

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

void cyl(GLfloat r=0.3,
         GLfloat g=0.4,
         GLfloat b=0.5,
         GLboolean emission = false )
{

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
    gluCylinder(qobj,0.2,0.2,5,20,10);
}


void light(double x, double y, double z, bool lighton, GLenum Lights,bool sun, bool tube)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat moon_light_diffuse[]  = { 0.0, 0.0, 0.6, 1.0 };
    GLfloat moon_light_specular[] = { 0.0, 0.0, 0.6, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(Lights);

    if(lighton)
    {
        if (sun)
        {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, light_diffuse);
            glLightfv( Lights, GL_SPECULAR, light_specular);
            glLightfv( Lights, GL_POSITION, light_position);

            glPushMatrix();
            glTranslatef(x,y,z);
            glScalef(300, 300, 300);
            sphere(1,1,1,true);
            glPopMatrix();

        }
        else if (tube)
        {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, light_diffuse);
            glLightfv( Lights, GL_SPECULAR, light_specular);
            glLightfv( Lights, GL_POSITION, light_position);
        }


    }
    else
    {
        glLightfv( Lights, GL_AMBIENT, no_light);
        glLightfv( Lights, GL_DIFFUSE, no_light);
        glLightfv( Lights, GL_SPECULAR, no_light);
        glLightfv( Lights, GL_POSITION, no_light);
    }

}

void lightspot(double x, double y, double z, bool lighton, GLenum Lights, bool spot)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat moon_light_diffuse[]  = { 0.0, 0.0, 0.6, 1.0 };
    GLfloat moon_light_specular[] = { 0.0, 0.0, 0.6, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(Lights);

    if(spot)
    {
        GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
        glLightfv(Lights, GL_SPOT_DIRECTION, spot_direction);
        glLightf(Lights, GL_SPOT_CUTOFF, 50.0);
    }

}

int i = 1;
GLuint ID_[100];

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

void fire_extinguisher()
{
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90, 1, 0, 0 );
    glScalef(1, 1, 1.6);
    cyl_f( .6,0,0);
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


void chair()
{
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

void car()
{

    glPushMatrix();
    glTranslatef(3,5,0);
    glScalef(5,2,5);
    cube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glScalef(10,3,5);
    cube(1,0,0);
    glPopMatrix();
}

void wheel() {
    glPushMatrix();
    glColor3b(0,0,0);
    glutSolidTorus(1,2,30,30);
    glPopMatrix();
}

void car1()
{

    // TOP BACK LEFT
    glPushMatrix();
    glTranslatef(6,3.5,4);
    glRotatef(10,1,0,0);
    glScalef(5,2,2);
    cube(1,0.7,0.1);
    glPopMatrix();
    // TOP BACK RIGHTT
    glPushMatrix();
    glTranslatef(6,3.5,-4);
    glRotatef(-10,1,0,0);
    glScalef(5,2,2);
    cube(1,0.7,0.1);
    glPopMatrix();

    // BASE TOP 1 BACK
    glPushMatrix();
    glTranslatef(4,2,0);
    glScalef(9,2.5,7);
    cube(1,0.7,0.1);
    glPopMatrix();

    // BASE TOP 1 ENGINE WING 1
    glPushMatrix();
    glTranslatef(6,2.3,0);
    glRotatef(25,0,0,1);
    glScalef(5,1,5);
    cube(1,1,0);
    glPopMatrix();

    // BASE TOP 1 ENGINE WING 2
    glPushMatrix();
    glTranslatef(6-1.5*1,2.3,0);
    glRotatef(25,0,0,1);
    glScalef(5,1,5);
    cube(1,1,0);
    glPopMatrix();

    // BASE TOP 1 ENGINE WING 3
    glPushMatrix();
    glTranslatef(6 - 1.5 * 2 ,2.3,0);
    glRotatef(25,0,0,1);
    glScalef(5,1,5);
    cube(1,1,0);
    glPopMatrix();

    // BASE TOP 1 ENGINE WING 4
    glPushMatrix();
    glTranslatef(6 - 1.5 * 3 ,2.3,0);
    glRotatef(25,0,0,1);
    glScalef(5,1,5);
    cube(1,1,0);
    glPopMatrix();

    // BASE TOP 1 ENGINE WING 5
    glPushMatrix();
    glTranslatef(6 - 1.5 * 4 ,2.3,0);
    glRotatef(25,0,0,1);
    glScalef(5,1,5);
    cube(1,1,0);
    glPopMatrix();

    // BASE TOP 1 ENGINE WING 6
    glPushMatrix();
    glTranslatef(6 - 1.5 * 5 ,2.3,0);
    glRotatef(25,0,0,1);
    glScalef(5,1,5);
    cube(1,1,0);
    glPopMatrix();

    // BASE TOP 1 FRONT
    glPushMatrix();
    glTranslatef(5 - 1.5 * 10 ,2.3,0);
    glRotatef(13,0,0,1);
    glScalef(6.5,1,6.9);
    cube(1,0.7,0.1);
    glPopMatrix();

    // BASE TOP 1 FRONT WINDSHIELD TEXTURE
    glPushMatrix();
    glTranslatef(2.3+5 - 1.5 * 10 ,2.5+0.5,0);
    glRotatef(13,0,0,1);
    glScalef(2.4,0.9,6.1);
    cube(1,1,0.1);
    glPopMatrix();

    // BASE TOP 1 FRONT LIGHTT 1
    glPushMatrix();
    glTranslatef(-0.7+5 - 1.5 * 10 -2 ,2.1,-4);
    glScalef(2.4,0.9,1);
    cube(1,0.7,0.1);
    glPopMatrix();

    // BASE TOP 1 FRONT LIGHTT 1
    glPushMatrix();
    glTranslatef(-0.7+5 - 1.5 * 10 -2 ,2.1,4);
    glScalef(2.4,0.9,1);
    cube(1,0.7,0.1);
    glPopMatrix();

    // BASE TOP 1 UNDER THE FRONT
    glPushMatrix();
    glTranslatef(6 - 1.5 * 10 ,1,0);
    glScalef(6.5,1,6.9);
    cube(1,0.7,0.1);
    glPopMatrix();

    // BASE TOP 1 UNDER THE FRONT
    glPushMatrix();
    glTranslatef(10 - 1.5 * 10 ,2,0);
    glScalef(3,1,6.9);
    cube(1,0.7,0.1);
    glPopMatrix();

    // BASE
    glPushMatrix();
    glTranslatef(-2,-0.3,0);
    glScalef(15,0.5,7);
    cube(1,0.7,0.1);
    glPopMatrix();

    // SLANTED BACK
    glPushMatrix();
    glTranslatef(13,2,0);
    glRotatef(-15,0,0,1);
    glScalef(1,2.5,6);
    cube(1,0.7,0.1);
    glPopMatrix();

    // SPOILER
    glPushMatrix();
    glTranslatef(14,6,0);
    glRotatef(-10,0,0,1);
    glRotatef(90,1,0,0);
    glRotatef(90,0,1,0);
    glScalef(0.3,6,1.5);
    cube(1,0.7,0.1);
    glPopMatrix();


    // SPOILER SUPPORT 1
    glPushMatrix();
    glTranslatef(14,5,4);
    glRotatef(-10,0,0,1);
    glRotatef(90,1,0,0);
    glRotatef(90,0,1,0);
    glScalef(0.8,0.2,1);
    cube(1,0.7,0.1);
    glPopMatrix();

    // SPOILER SUPPORT 2
    glPushMatrix();
    glTranslatef(14,5,-4);
    glRotatef(-10,0,0,1);
    glRotatef(90,1,0,0);
    glRotatef(90,0,1,0);
    glScalef(0.8,0.2,1);
    cube(1,0.7,0.1);
    glPopMatrix();

    // WHEELS

    // black demo cube
    glPushMatrix();
    glScalef(0.01,0.01,0.01);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8,-0.3,6+1);
    glScalef(1,1,1);
    wheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8,-0.3,7+1);
    glScalef(20,20,0.2);
    sphere(0.9,0.9,0.9);
    glPopMatrix();

    // black demo cube
    glPushMatrix();
    glScalef(0.01,0.01,0.01);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8,-0.3,6+1);
    glScalef(1,1,1);
    wheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8,-0.3,7+1);
    glScalef(20,20,0.2);
    sphere(0.9,0.9,0.9);
    glPopMatrix();

    // black demo cube
    glPushMatrix();
    glScalef(0.01,0.01,0.01);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8,-0.3,6+1);
    glScalef(1,1,1);
    wheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8,-0.3,7+1);
    glScalef(20,20,0.2);
    sphere(0.9,0.9,0.9);
    glPopMatrix();

    // black demo cube
    glPushMatrix();
    glScalef(0.01,0.01,0.01);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8,-0.3,-6-1);
    glScalef(1,1,1);
    wheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8,-0.3,-7-1);
    glScalef(20,20,0.2);
    sphere(0.9,0.9,0.9);
    glPopMatrix();

    // black demo cube
    glPushMatrix();
    glScalef(0.01,0.01,0.01);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8,-0.3,-6-1);
    glScalef(1,1,1);
    wheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8,-0.3,-7-1);
    glScalef(20,20,0.2);
    sphere(0.9,0.9,0.9);
    glPopMatrix();






}

void atm()
{
    // atm base
    glPushMatrix();
    glTranslatef(0,3,0);
    glScalef(4,2,4);
    cube(1,1,0.8);
    glPopMatrix();

    // atm top of base
    glPushMatrix();
    glTranslatef(0,7,0);
    glScalef(4,1,4);
    cube(1,1,0.8);
    glPopMatrix();

    // atm left between
    glPushMatrix();
    glTranslatef(-3,6,0);
    glScalef(4/3,1,4);
    cube(1,1,0.8);
    glPopMatrix();

    // atm right between
    glPushMatrix();
    glTranslatef(3,6,0);
    glScalef(4/3,1,4);
    cube(1,1,0.8);
    glPopMatrix();

    // atm taka
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,5.5,4); // z param will go from 0 to 4 if clicked a button
    glScalef(4/2.9,0.3,0.7);
    glBindTexture(GL_TEXTURE_2D, 20); // 1
    cube(0,0.8,0.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // atm screen
    glPushMatrix();
    glTranslatef(0,8,-2.5);
    glRotatef(60,1,0,0);
    glScalef(4,3,3);
    cube(1,1,0.8);
    glPopMatrix();

    // atm screen tex
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,8.4,-2);
    glRotatef(60,1,0,0);
    glScalef(3.8,2.8,2.8);
    glBindTexture(GL_TEXTURE_2D, 22); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // atm numpad tex 21
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,7.3,2.5);
    glScalef(3.8,0.8,1.3);
    glBindTexture(GL_TEXTURE_2D, 21); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // atm backside
    glPushMatrix();
    glTranslatef(0,5,-3.5);
    glScalef(4,4,3);
    cube(1,1,0.8);
    glPopMatrix();
}

void atm2()
{
    // atm base
    glPushMatrix();
    glTranslatef(0,3,0);
    glScalef(4,2,4);
    cube(1,1,0.5);
    glPopMatrix();

    // atm top of base
    glPushMatrix();
    glTranslatef(0,7,0);
    glScalef(4,1,4);
    cube(1,1,0.5);
    glPopMatrix();

    // atm left between
    glPushMatrix();
    glTranslatef(-3,6,0);
    glScalef(4/3,1,4);
    cube(1,1,0.5);
    glPopMatrix();

    // atm right between
    glPushMatrix();
    glTranslatef(3,6,0);
    glScalef(4/3,1,4);
    cube(1,1,0.5);
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
    cube(1,1,0.5);
    glPopMatrix();

    // atm screen tex
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,8.4,-2);
    glRotatef(60,1,0,0);
    glScalef(3.8,2.8,2.8);
    glBindTexture(GL_TEXTURE_2D, 22); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // atm numpad tex
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,7.3,2.5);
    glScalef(3.8,0.8,1.3);
    glBindTexture(GL_TEXTURE_2D, 21); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // atm backside
    glPushMatrix();
    glTranslatef(0,5,-3.5);
    glScalef(4,4,3);
    cube(1,1,0.5);
    glPopMatrix();
}

void fan_blade()
{
    // FAN FAN FAN FAN FAN
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(-90,0,1,0);
    glScalef(1, 4, 0.08);
    slcube( 1, 1, 0.4);
    glPopMatrix();


}

void fan()
{

    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(15, 4, 15);
    sphere( 0.9,.1,0.9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2, 0);
    glRotatef(90, 1, 0, 0 );
    glScalef(1, 1, 0.4);
    cyl( 1,1,1);
    glPopMatrix();

    // BLADE 1
    glPushMatrix();
    glTranslatef(0,0,3);
    glRotatef(90,1,0,0);
    glRotatef(90,0,1,0);
    fan_blade();

    glTranslatef(0,-5,3);
    glRotatef(120,1,0,0);
    fan_blade();

    glTranslatef(0,-5,2.5);
    glRotatef(120,1,0,0);
    fan_blade();
    glPopMatrix();


}

void monitor()
{
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

void keyboard_mouse()
{
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

void tube_light()
{
    // Tube Light
    glPushMatrix();
//    glTranslatef(-22,21.6,-35);
    glTranslatef(0,0,0);
    glScalef(1.2,1.2,3);
    cyl( 1,1,1);
    glPopMatrix();

    glPushMatrix();
//    glTranslatef(-22,21.6,-35);
    glTranslatef(-0.25,0,7.5);
    glScalef(0.1,0.4,7.8);
    cube( 1,1,0);
    glPopMatrix();

    glPushMatrix();
//    glTranslatef(-22,21.6,-35);
    glTranslatef(-0.08,0,-0.25);
    glScalef(0.3,0.4,0.1);
    cube( 1,1,0);
    glPopMatrix();

    glPushMatrix();
//    glTranslatef(-22,21.6,-35);
    glTranslatef(-0.08,0,-0.25+7.5*2+0.5);
    glScalef(0.3,0.4,0.1);
    cube( 1,1,0);
    glPopMatrix();
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-5, 5, -5, 5, 4, 100);
    gluPerspective(50,1,4,1000);
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


//    glPushMatrix();
//    glTranslatef(0,0,0);
//    cube(0.1,1,1);
//    glPopMatrix();

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
    glBindTexture(GL_TEXTURE_2D, 34); // 1
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

    //WALL 2 right of cashier
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

    //WALL 3 GM right side
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-27,12,-21);
    glScalef(13,12,0.9);
    glBindTexture(GL_TEXTURE_2D, 8); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // GM_door_object
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(GM_door_x,11.8,-21);
    glScalef(13,11.8,0.5);
    glBindTexture(GL_TEXTURE_2D, 19); // 1
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

    // cashier front wall
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(20,6,-10);
    glScalef(20,6,2);
    glBindTexture(GL_TEXTURE_2D, 7); // 1
    cube(1,1,0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // cashier top WALL with roof
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(20,22,-10);
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

    // extended FLOOR under the main building
    glPushMatrix();
    glTranslatef(-0.5,-25.5,0.5);
    glScalef(40.5,1.4,66);
    cube(1,1,1);
    glPopMatrix();


    //////////////////////////////////
    ////// 1st floor
    //////////////////////////

    // FLOOR of 1st floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-24,0);
    glRotatef(180, 0,1,0);
    glScalef(39.9,0.4,64.5);
    glBindTexture(GL_TEXTURE_2D, 34); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // HELP DESK
    glPushMatrix();
    glTranslatef(-22,-25,0);
    glRotatef(90,0,1,0);
    glScalef(1,1,1);
    table_help_desk();
    glPopMatrix();

    // HELP DESK CHAIR
    glPushMatrix();
    glTranslatef(-3,-25,15);
    glRotatef(-90, 0,1,0);
    chair();
    glPopMatrix();


    // BACK WALL
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-40,0,0);
    glScalef(0.4,24,65);
    glBindTexture(GL_TEXTURE_2D, 33); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // BACK WALL WITH STAIRS
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-21,0,81-0.4);
    glScalef(0.4,24,15);
    glBindTexture(GL_TEXTURE_2D, 33); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // FRONT WALL IN FRONT OF STAIRS
//    glEnable(GL_TEXTURE_2D);
//    glPushMatrix();
//    glTranslatef(40,0,81-0.4);
//    glScalef(0.4,24,15);
//    glBindTexture(GL_TEXTURE_2D, 33); // 1
//    cube(1,1,1);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);

    // FRONT WALL UPPER
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(40,12,0);
    glScalef(0.4,12,65);
    glBindTexture(GL_TEXTURE_2D, 33); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // FRONT WALL LOWER
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(40,-12,0+45);
    glScalef(0.4,12,21);
    glBindTexture(GL_TEXTURE_2D, 33); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // FRONT WALL LOWER RIGHT
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(40,-12,0-44);
    glScalef(0.4,12,21);
    glBindTexture(GL_TEXTURE_2D, 33); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // front deco frame
    glPushMatrix();
    glTranslatef(40,-25.5,0.5);
    glScalef(1.5,1.5,66);
    cube(1,1,1);
    glPopMatrix();

    // front deco frame
    glPushMatrix();
    glTranslatef(40,0,0.5);
    glScalef(1.5,1.5,66);
    cube(1,1,1);
    glPopMatrix();

    // front deco frame
    glPushMatrix();
    glTranslatef(40,23,0.5);
    glScalef(1.5,1.5,66);
    cube(1,1,1);
    glPopMatrix();

    // main door
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(40,-12, main_door_z);              // main door main_door_z //////// between 15 to 35
    glScalef(0.3,12,15);
    glBindTexture(GL_TEXTURE_2D, 19); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // main door right
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(40,-12,main_door_right_z);       // between -15 and -35
    glScalef(0.3,12,15);
    glBindTexture(GL_TEXTURE_2D, 19); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



//    DOOOOOOOR
    // floor1_door_object
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
//    glTranslatef(floor1_door_x,11.8,-21);
//    glTranslatef(26,-12.5,65.5-0.4);
    glTranslatef(floor1_door_x,-12.5,65.5-0.4); // between 13 to 26
    glScalef(8,11.5,0.5);
    glBindTexture(GL_TEXTURE_2D, 19); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // floor2_door_object
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
//    glTranslatef(floor1_door_x,11.8,-21);
//    glTranslatef(26,-12.5,65.5-0.4);
    glTranslatef(floor2_door_x,12,65.5-0.4); // between 13 to 26
    glScalef(8,11.5,0.5);
    glBindTexture(GL_TEXTURE_2D, 19); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // LEFT WALL
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-10,0,65);
    glScalef(30,24,0.9);
    glBindTexture(GL_TEXTURE_2D, 33); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // LEFT WALL ARTWORK ????????????
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
//    glTranslatef(floor1_door_x,11.8,-21);
//    glTranslatef(26,-12.5,65.5-0.4);
    glTranslatef(0,12,65.5-1.1); // between 13 to 26
    glScalef(9,6,0.5);
    glBindTexture(GL_TEXTURE_2D, 32); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // LEFT WALL DOORSIDE
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(37,0,65);
    glScalef(3,24,0.9);
    glBindTexture(GL_TEXTURE_2D, 33); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // LEFT WALL INCLUDING STAIRS
    // JANATA BANK
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(10,-1,95);
    glScalef(30,25,0.4);
    glBindTexture(GL_TEXTURE_2D, 33); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // RIGHT WALL
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-65);
    glScalef(40,24,0.4);
    glBindTexture(GL_TEXTURE_2D, 33); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    //////////////////////////////////
    ////// roof roof
    //////////////////////////
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,24,0);
    glScalef(40,0.4,65);
    glBindTexture(GL_TEXTURE_2D, 8); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // sb frame top
    glPushMatrix();
    glTranslatef(34,48,0);
    glScalef(1,1,41);
    cube(1,1,1);
    glPopMatrix();
    // sb frame bottom
    glPushMatrix();
    glTranslatef(34,40-8,0);
    glScalef(1,1,41);
    cube(1,1,1);
    glPopMatrix();

    // sb frame right
    glPushMatrix();
    glTranslatef(34,40,-41);
    glScalef(1,9,1);
    cube(1,1,1);
    glPopMatrix();

    // sb frame left
    glPushMatrix();
    glTranslatef(34,40,41);
    glScalef(1,9,1);
    cube(1,1,1);
    glPopMatrix();

    // sign board
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(34,40,0);
    glScalef(0.6,8,40);
    glBindTexture(GL_TEXTURE_2D, 8); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // sign board back panel
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(34-0.3,40,0);
    glScalef(0.6,8,40);
    glBindTexture(GL_TEXTURE_2D, 9); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // sb frame left stand
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(34,40-13,41-15);
    glScalef(0.9,5,1);
    glBindTexture(GL_TEXTURE_2D, 7); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // sb frame left stand
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(34,40-13,-41+15);
    glScalef(0.9,5,1);
    glBindTexture(GL_TEXTURE_2D, 7); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // ATM with cash
    glPushMatrix();
    glTranslatef(-10,-25,50);
    glRotatef(180,0,1,0);
    atm();
    glPopMatrix();

    // ATM 2 static
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


    ////////////////////////////////////

    // vault cabinet
    glPushMatrix();
    glTranslatef(20,10,-60);
    glScalef(10,10,4);
    cube(0.8,0.8,0.6);
    glPopMatrix();

    // vault Cabinet style
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(20,10,0.5-60);
    glScalef(9.8,9.8,3.8);
    glBindTexture(GL_TEXTURE_2D,9);
    cube(0.8,0.8,0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // gold
    glPushMatrix();
    glTranslatef(30,20,-48);
    gold_stack();
    glPopMatrix();

    // gold 2
    glPushMatrix();
    glTranslatef(30,15,-48);
    gold_stack();
    glPopMatrix();

    // gold 3
    glPushMatrix();
    glTranslatef(30,10,-48);
    gold_stack();
    glPopMatrix();


    // cash stack 1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(30,3.5,-46);
    glScalef(6,3.5,4);
    glBindTexture(GL_TEXTURE_2D,18);
    cube(0.8,1,0.8);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // cash stack 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(15,3.5,-46);
    glScalef(6,3.5,4);
    glBindTexture(GL_TEXTURE_2D,18);
    cube(0.8,1,0.8);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // FAN
    glPushMatrix();
    glTranslatef(-25,21.6,20);
    glRotatef(rot_Angle, 0,1,0);
    glScalef(1,1,1);
    fan();
    glPopMatrix();

    // GM FAN
    glPushMatrix();
    glTranslatef(-22,21.6,-35);
    glRotatef(rot_Angle, 0,1,0);
    glScalef(1,1,1);
    fan();
    glPopMatrix();


    /////////////////////////////////
    // WORLD
    /////////////////////////////////

    // GRASS
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-28,0);
    glScalef(70,1,110);
    glBindTexture(GL_TEXTURE_2D, 23); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // GRASS BEYOND THE ROAD
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-28.5,0);
    glScalef(900,1,900);
    glBindTexture(GL_TEXTURE_2D, 23); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // PARKING
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(90+5,-28,0);
    glScalef(25,1,110);
    glBindTexture(GL_TEXTURE_2D, 30); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // PARKING WALL FRONT
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(119,-22,0);
    glScalef(2,6,110);
    glBindTexture(GL_TEXTURE_2D, 31); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // PARKING WALL BACK
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-68,-22,0);
    glScalef(2,6,110);
    glBindTexture(GL_TEXTURE_2D, 31); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // PARKING WALL RIGHT
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,-22,-108);
    glRotatef(90,0,1,0);
    glScalef(2,6,93.2);
    glBindTexture(GL_TEXTURE_2D, 31); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // PARKING WALL LEF
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-22,108);
    glRotatef(90,0,1,0);
    glScalef(2,6,93.2*2/3 + 6);
    glBindTexture(GL_TEXTURE_2D, 31); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // FRONT ROAD
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(150,-28,0);
    glScalef(30,1,110);
    glBindTexture(GL_TEXTURE_2D, 24); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // FRONT ROAD BOUNDARY
    glPushMatrix();
    glTranslatef(182,-27,0);
    glScalef(1.5,2,173);
//    glBindTexture(GL_TEXTURE_2D, 24); // 1
    cube(1,1,1);
    glPopMatrix();



    // FRONT ROAD CORNER LEFT
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(150,-28,140);
    glScalef(30,1,30);
    glBindTexture(GL_TEXTURE_2D, 26); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // FRONT ROAD CORNER RIGHT
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(150,-28,-140);
    glScalef(30,1,30);
    glBindTexture(GL_TEXTURE_2D, 27); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // BACK ROAD CORNER LEFT
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-100,-28,140);
    glScalef(30,1,30);
    glBindTexture(GL_TEXTURE_2D, 28); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // BACK ROAD CORNER RIGHT
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-100,-28,-140);
    glScalef(30,1,30);
    glBindTexture(GL_TEXTURE_2D, 29); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // BACK ROAD
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-100,-28,0);
    glScalef(30,1,110);
    glBindTexture(GL_TEXTURE_2D, 24); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // BACK ROAD BOUNDARY
    glPushMatrix();
    glTranslatef(-132,-27,0);
    glScalef(1.5,2,173);
//    glBindTexture(GL_TEXTURE_2D, 24); // 1
    cube(1,1,1);
    glPopMatrix();

    // LEFT ROAD BOUNDARY
    glPushMatrix();
    glTranslatef(25,-27,172);
    glScalef(158,2,1.5);
//    glBindTexture(GL_TEXTURE_2D, 24); // 1
    cube(1,1,1);
    glPopMatrix();

    // RIGHT ROAD BOUNDARY
    glPushMatrix();
    glTranslatef(25,-27,-172);
    glScalef(158,2,1.5);
//    glBindTexture(GL_TEXTURE_2D, 24); // 1
    cube(1,1,1);
    glPopMatrix();

    // LEFT ROAD
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,-28,140);
    glScalef(95,1,30);
    glBindTexture(GL_TEXTURE_2D, 25); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // RIGHT ROAD
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,-28,-140);
    glScalef(95,1,30);
    glBindTexture(GL_TEXTURE_2D, 25); // 1
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);








    // TUBE LIGHT
    // GM
    glPushMatrix();
    glTranslatef(-38.5,21.6,-45);
    tube_light();
    glPopMatrix();

    // 2nd floor
    glPushMatrix();
//    glTranslatef(-10,0,65);
    glTranslatef(-10,21.6,63.8);
    glRotatef(90,0,1,0);
    tube_light();
    glPopMatrix();

    // 1st floor
    glPushMatrix();
//    glTranslatef(-10,0,65);
    glTranslatef(-10,-5,63.8);
    glRotatef(90,0,1,0);
    tube_light();
    glPopMatrix();










    // glTranslatef(150,-20,0);
    // CAR
    glPushMatrix();

    glTranslatef(car_x, -24, car_z);
    glRotatef(car_rot, 0, 1, 0 );
    car1();
    glPopMatrix();

    // SUN LIGHT

    glPushMatrix();
    glRotatef(sun,1,0,0);
    light(-500, 500, 0,light0,GL_LIGHT0,true,false);
    glPopMatrix();

    // GM LIGHT

    glPushMatrix();
    light(-38.5,21.6,-45,light1,GL_LIGHT1,false,true);
    glPopMatrix();

    //glTranslatef(-10,21.6,63.8); // 2
    //glTranslatef(-10,-5,63.8); // 1

    // 2nd floor LIGHT

    glPushMatrix();
    light(-10,21.6,63.8,light2,GL_LIGHT2,false,true);
    glPopMatrix();

    // 1st floor LIGHT

    glPushMatrix();
    light(-10,-5,63.8,light3,GL_LIGHT3,false,true);
    glPopMatrix();




    // SPOT LIGHT
//     spotlight cone

    GLfloat sl_z = 65, sl_x=45;

    glPushMatrix();
    glTranslatef(23-sl_x, 10, 5-sl_z);
    glRotatef(220, 1, 0, 0 );
    glScalef(8, 8, 8);
    cone( .9,.1,.9);
    glPopMatrix();

    // spot stand base
    glPushMatrix();
    glTranslatef(23-sl_x, 0.4, 2.2-sl_z);
    glScalef(20, 1, 20);
    sphere( 0.9,.1,0.9);
    glPopMatrix();

    // sport stand stand
    glPushMatrix();
    glTranslatef(23-sl_x, 12, 2.2-sl_z);
    glRotatef(90, 1, 0, 0 );
    glScalef(1, 1, 2.3);
    cyl( 0.6,.1,0.6);
    glPopMatrix();

    // spotlight bulb
    glPushMatrix();
    glTranslatef(23-sl_x, 10, 5-sl_z);
//        glRotatef(220, 1, 0, 0 );
    glScalef(8, 8, 8);
    sphere( .9,.9,.9);
    glPopMatrix();

    // outer globe
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(2800*3,2200*3,2800*3);
    glBindTexture(GL_TEXTURE_2D, 33); // 1
    sphereG(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /////////////////////////////////////
    //////////// end ////////////////
    //////////////////////////////////////

//    // FIRE EXTINGUISHER
    glPushMatrix();
    glTranslatef(38,-25.6+10,70);
    glRotatef(90,0,1,0);
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



//    light(1,18,24, GL_LIGHT0,light0);
//    light(23,10,5.2,GL_LIGHT1,light1);
//    light(-15,4,28,GL_LIGHT2,light2,false,true);


    // SPOT LIGHT
    glPushMatrix();
//    light(23-65,10,5-45,light4,GL_LIGHT4,false,false,true);
    lightspot(0,0,0, light5, GL_LIGHT5, true);
    glPopMatrix();

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
            lookat_z++;
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


    // SUN
    case '1':
        light0 = !light0;
        glutPostRedisplay();
        break;

    // GM LIGHT
    case '3':
        light1 = !light1;
        glutPostRedisplay();
        break;
    // 2nd floor light
    case '4':
        light2 = !light2;
        glutPostRedisplay();
        break;
    // 1st floor light
    case '5':
        light3 = !light3;
        glutPostRedisplay();
        break;
    // SPOT light
    case 'q':
        light5 = !light5;
        glutPostRedisplay();
        break;

    // FAN
    case '6':
        fanRot = !fanRot;
        glutPostRedisplay();
        break;

    // GM door
    case 'v':
        GM_door_open = !GM_door_open;
        glutPostRedisplay();
        break;

    case 'b':
        floor1_door_open = !floor1_door_open;
        glutPostRedisplay();
        break;
    case 'n':
        floor2_door_open = !floor2_door_open;
        glutPostRedisplay();
        break;

    case 'm':
        main_door_open = !main_door_open;
        glutPostRedisplay();
        break;

    //for sun rotate
    case '2':
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

// car facing
//          0
//         -X
//          |
//          |
// 3 +Z ---- ----- -Z 1
//          |
//          |
//         +X
//          2
//     BANK FRONT
//
// -X 0
// -Z 1
// +X 2
// +Z 3



void SpecialInput(int key, int x, int y)
{
//    car_facing = 0;
    if( car_facing == 0 )
    {
        switch(key)
        {
        case GLUT_KEY_UP:

            car_x-=1;

            break;
        case GLUT_KEY_DOWN:
            //do something here
            car_x+=1;

            break;
        case GLUT_KEY_LEFT:
            //do something here
            car_rot += 90;
            car_facing =3;


            break;
        case GLUT_KEY_RIGHT:
            //do something here
            car_rot -= 90;
            car_facing = 1;

            break;
        }
    }
    if( car_facing == 1 )
    {
        switch(key)
        {
        case GLUT_KEY_UP:
            car_z-=1;

            break;
        case GLUT_KEY_DOWN:
            //do something here
            car_z+=1;

            break;
        case GLUT_KEY_LEFT:
            //do something here
            car_rot += 90;
            car_facing = 0;

            break;
        case GLUT_KEY_RIGHT:
            //do something here
//                    car_rot += -90;
//                    car_facing = 2;
            break;
        }
    }




    if( car_facing == 3 )
    {
        switch(key)
        {
        case GLUT_KEY_UP:
            car_z+=1;

            break;
        case GLUT_KEY_DOWN:
            //do something here
            car_z-=1;

            break;
        case GLUT_KEY_LEFT:
            //do something here
//                    car_rot += 90;
//                    car_facing = 2;

            break;
        case GLUT_KEY_RIGHT:
            //do something here
            car_rot += -90;
            car_facing = 0;
            break;
        }
    }

//    cout<<"Starting Point "<<ttx<<", "<<tty<<", "<<ttz<<" \n";
//    cout<<"Scale Sizes "<<ssx<<", "<<ssy<<", "<<ssz<<" \n";

    glutPostRedisplay();
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

    if (fanRot == true)
    {
        rot_Angle += 01;
        if(rot_Angle > 360.0)
            rot_Angle -= 360.0 * floor(rot_Angle/360.0);
    }

    if (zRotate == true)
    {
        sun += 0.5;
        if(sun > 360.0)
            sun -= 360.0*floor(sun/360.0);
    }

    if( GM_door_open == true)
    {
        if(GM_door_x < -13)
        {
            GM_door_x += 0.08;
        }
    }

    if (GM_door_open == false)
    {
        if(GM_door_x > -26)
        {
            GM_door_x -= 0.08;
        }
    }

    if( floor1_door_open == true)
    {
        if(floor1_door_x < 26)
        {
            floor1_door_x += 0.08;
        }
    }

    if (floor1_door_open == false)
    {
        if(floor1_door_x > 13)
        {
            floor1_door_x -= 0.08;
        }
    }

    if( floor2_door_open == true)
    {
        if(floor2_door_x < 26)
        {
            floor2_door_x += 0.08;
        }
    }

    if (floor2_door_open == false)
    {
        if(floor2_door_x > 13)
        {
            floor2_door_x -= 0.08;
        }
    }

    if( main_door_open == true)
    {
        if(main_door_z < 35)
        {
            main_door_z += 0.4;
        }

        if(main_door_right_z > -33)
        {
            main_door_right_z -= 0.4;
        }


    }
    if (main_door_open == false)
    {
        if(main_door_z > 15)
        {
            main_door_z -= 0.4;
        }


        if(main_door_right_z < -15)
        {
            main_door_right_z += 0.4;
        }
    }


//    cout << "eye pos "<< eye_x << " " << eye_y << " " << eye_z << endl;
//    cout << "lookat "<< lookat_x << " " << lookat_y << " " << lookat_z << endl;
//    cout << "sxsysz "<< sx << " " << sy << " " << sz << endl;
    glutPostRedisplay();

}

//eye pos -6 15 50
//lookat -56 -5 0
//sxsysz 1.4 1.4 1.4


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Janata Bank, KUET");
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

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\cash_tex.bmp"); // 18

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\GM_door.bmp"); // 19
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\dollar.bmp"); // 20


    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\numpad.bmp"); // 21
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\atm_screen.bmp"); // 22
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\grass.bmp"); // 23

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\straight_road.bmp"); // 24
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\straight_road_rot.bmp"); // 25

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\straight_road_corner_fl.bmp"); // 26
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\straight_road_corner_fr.bmp"); // 27
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\straight_road_corner_bl.bmp"); // 28
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\straight_road_corner_br.bmp"); // 29

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\parking.bmp"); // 30

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\brick.bmp"); // 31
    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\starry_night.bmp"); // 32

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\n1.bmp"); // 33

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\nfloor.bmp"); // 34

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\nfloor.bmp"); // 35 // janata bank banner

    LoadTexture("C:\\Users\\Raiyan\\Desktop\\ogl\\nfloor.bmp"); // 36 // janata bank logo side wall




    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(SpecialInput);
    //sndPlaySound("woo.wav",SND_ASYNC);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    //PlaySound(TEXT("woo.wav"),NULL, SND_SYNC);
    glutMainLoop();

    return 0;
}



