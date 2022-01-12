//Ryan Novak
//105676203

/*
 Window Interaction Keys:
 esc = exit
 0 = reset view angle
 arrow keys to rotate view angle
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "CSCIx229.h"

//ex9 sin and cos definition
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

//  Globals modified from ex6
int th=0;       // Azimuth of view angle
int ph=0;       // Elevation of view angle
double dim=10;   // Dimension of orthogonal box

//light variables from ex13
int move=1;       //  Move light
// Light values
int light     =   1;  // Lighting
int distance  =   8;  // Light distance
int inc       =  10;  // Ball increment
int local     =   0;  // Local Viewer Model
int emission  =  10;  // Emission intensity (%)
int ambient   =  10;  // Ambient intensity (%)
int diffuse   =  50;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float xlight  =   1;  // Elevation of light

//textures
unsigned int brick;
unsigned int roof;
unsigned int glass;
unsigned int wood;
unsigned int plank;
unsigned int snow;
unsigned int porch;
unsigned int door;
unsigned int background;
unsigned int tree;

/*  ex13
 *  GLUT calls this routine when there is nothing else to do
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

//Print function taken from ex6
#define LEN 8192  // Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*  ex13
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*  ex13 for ball of light
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.5,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  yellow ball
   glColor3f(1,1,0);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

static void Lodge(double x, double y, double z, double r, double sx, double sy, double sz){
    glEnable(GL_TEXTURE_2D);
    //save transformation
    glPushMatrix();
    //offset
    glTranslated(x,y,z);
    glScaled(sx,sy,sz);
    glRotated(r,0,1,0);
    glColor4f(1,1,1,1);
    //  Front
    glBindTexture(GL_TEXTURE_2D,plank);
    glBegin(GL_POLYGON);
    glNormal3f(0,0,4);
    glTexCoord2f(0,0); glVertex3f(0,0,2);
    glTexCoord2f(1,0); glVertex3f(2,0,2);
    glTexCoord2f(1,1); glVertex3f(2,2,2);
    glTexCoord2f(0,1); glVertex3f(0,2.5,2);
    glEnd();
    //  Back
    glBindTexture(GL_TEXTURE_2D,plank);
    glBegin(GL_POLYGON);
    glNormal3f(0,1,-5);
    glTexCoord2f(0,0); glVertex3f(2,0,0);
    glTexCoord2f(1,0); glVertex3f(0,0,0);
    glTexCoord2f(1,1); glVertex3f(0,2.5,0);
    glTexCoord2f(0,1); glVertex3f(2,2,0);
    glEnd();
    //Right
    glBindTexture(GL_TEXTURE_2D,plank);
    glBegin(GL_POLYGON);
    glNormal3f(4,0,0);
    glTexCoord2f(0,0); glVertex3f(2,0,2);
    glTexCoord2f(1,0); glVertex3f(2,0,0);
    glTexCoord2f(1,1); glVertex3f(2,2,0);
    glTexCoord2f(0,1); glVertex3f(2,2,2);
    glEnd();
    //  Left windows
    glBindTexture(GL_TEXTURE_2D,glass);
    glBegin(GL_POLYGON);
    glNormal3f(-4,1,0);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(0,0,2);
    glTexCoord2f(1,1); glVertex3f(0,2,2);
    glTexCoord2f(0,1); glVertex3f(0,2,0);
    glEnd();
    //  Left wood
    glBindTexture(GL_TEXTURE_2D,plank);
    glBegin(GL_POLYGON);
    glNormal3f(0.98,1,0);
    glTexCoord2f(0,0); glVertex3f(0,2.49,0);
    glTexCoord2f(1,0); glVertex3f(0,2.49,2);
    glTexCoord2f(1,1); glVertex3f(0,2,2);
    glTexCoord2f(0,1); glVertex3f(0,2,0);
    glEnd();
    //  Left brick
    glBindTexture(GL_TEXTURE_2D,brick);
    glBegin(GL_POLYGON);
    glNormal3f(1,1,0);
    glTexCoord2f(0,0); glVertex3f(-0.05,0.5,0);
    glTexCoord2f(1,0); glVertex3f(-0.05,0.5,2);
    glTexCoord2f(1,1); glVertex3f(-0.05,0,2);
    glTexCoord2f(0,1); glVertex3f(-0.05,0,0);
    glEnd();
    //  Bottom
    glBindTexture(GL_TEXTURE_2D,brick);
    glBegin(GL_POLYGON);
    glNormal3f(0,-4,0);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(2,0,0);
    glTexCoord2f(1,1); glVertex3f(2,0,2);
    glTexCoord2f(0,1); glVertex3f(0,0,2);
    glEnd();
    //  Porch
    glBindTexture(GL_TEXTURE_2D,porch);
    glBegin(GL_POLYGON);
    glNormal3f(0,4,0);
    glTexCoord2f(0,0); glVertex3f(0,0.05,0);
    glTexCoord2f(1,0); glVertex3f(-2,0.05,0);
    glTexCoord2f(1,1); glVertex3f(-2,0.05,2);
    glTexCoord2f(0,1); glVertex3f(0,0.05,2);
    glEnd();
    //  Roof
    glBindTexture(GL_TEXTURE_2D,roof);
    glBegin(GL_POLYGON);
    glNormal3f(-1,4,0);
    glTexCoord2f(0,0); glVertex3f(0,2.5,0);
    glTexCoord2f(1,0); glVertex3f(2,2,0);
    glTexCoord2f(1,1); glVertex3f(2,2,2);
    glTexCoord2f(0,1); glVertex3f(0,2.5,2);
    glEnd();
    //  Roof extension
    glBindTexture(GL_TEXTURE_2D,roof);
    glBegin(GL_POLYGON);
    glNormal3f(-0.4,1,0);
    glTexCoord2f(1,0); glVertex3f(0,2.5,0);
    glTexCoord2f(1,1); glVertex3f(0,2.5,2);
    glTexCoord2f(0,0); glVertex3f(-0.5,2.7,2);
    glTexCoord2f(0,1); glVertex3f(-0.5,2.7,0);
    glEnd();
    glPopMatrix();
}

static void Entrance(double x, double y, double z, double r, double sx, double sy, double sz){
    glEnable(GL_TEXTURE_2D);
    //save transformation
    glPushMatrix();
    //offset
    glTranslated(x,y,z);
    glScaled(sx,sy,sz);
    glRotated(r,0,1,0);
    glColor4f(1,1,1,1);
    //  Front
    glBindTexture(GL_TEXTURE_2D,plank);
    glBegin(GL_POLYGON);
    glNormal3f(0,0,4);
    glTexCoord2f(0,0); glVertex3f(0,0,2);
    glTexCoord2f(1,0); glVertex3f(2,0,2);
    glTexCoord2f(1,1); glVertex3f(2,2,2);
    glTexCoord2f(0,1); glVertex3f(0,2.5,2);
    glEnd();
    //  Back
    glBindTexture(GL_TEXTURE_2D,plank);
    glBegin(GL_POLYGON);
    glNormal3f(0,0,-5);
    glTexCoord2f(0,0); glVertex3f(2,0,0);
    glTexCoord2f(1,0); glVertex3f(0,0,0);
    glTexCoord2f(1,1); glVertex3f(0,2.5,0);
    glTexCoord2f(0,1); glVertex3f(2,2,0);
    glEnd();
    //Right
    glBindTexture(GL_TEXTURE_2D,plank);
    glBegin(GL_POLYGON);
    glNormal3f(4,0,0);
    glTexCoord2f(0,0); glVertex3f(2,0,2);
    glTexCoord2f(1,0); glVertex3f(2,0,0);
    glTexCoord2f(1,1); glVertex3f(2,2,0);
    glTexCoord2f(0,1); glVertex3f(2,2,2);
    glEnd();
    //  Left windows
    glBindTexture(GL_TEXTURE_2D,plank);
    glBegin(GL_POLYGON);
    glNormal3f(-4.98,0,0);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(0,0,2);
    glTexCoord2f(1,1); glVertex3f(0,2.49,2);
    glTexCoord2f(0,1); glVertex3f(0,2.49,0);
    glEnd();
    //  Left brick
    glBindTexture(GL_TEXTURE_2D,brick);
    glBegin(GL_POLYGON);
    glNormal3f(0.35,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.05,0.5,0);
    glTexCoord2f(1,0); glVertex3f(-0.05,0.5,0.7);
    glTexCoord2f(1,1); glVertex3f(-0.05,0,0.7);
    glTexCoord2f(0,1); glVertex3f(-0.05,0,0);
    glEnd();
    //  Left brick
    glBindTexture(GL_TEXTURE_2D,brick);
    glBegin(GL_POLYGON);
    glNormal3f(0.35,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.05,0.5,1.3);
    glTexCoord2f(1,0); glVertex3f(-0.05,0.5,2);
    glTexCoord2f(1,1); glVertex3f(-0.05,0,2);
    glTexCoord2f(0,1); glVertex3f(-0.05,0,1.3);
    glEnd();
    //  Left Door
    glBindTexture(GL_TEXTURE_2D,door);
    glBegin(GL_POLYGON);
    glNormal3f(0.72,1,0);
    glTexCoord2f(0,0); glVertex3f(-0.05,1.2,0.7);
    glTexCoord2f(1,0); glVertex3f(-0.05,1.2,1.3);
    glTexCoord2f(1,1); glVertex3f(-0.05,0,1.3);
    glTexCoord2f(0,1); glVertex3f(-0.05,0,0.7);
    glEnd();
    //  Bottom
    glBindTexture(GL_TEXTURE_2D,brick);
    glBegin(GL_POLYGON);
    glNormal3f(0,-4,0);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(2,0,0);
    glTexCoord2f(1,1); glVertex3f(2,0,2);
    glTexCoord2f(0,1); glVertex3f(0,0,2);
    glEnd();
    //  Porch
    glBindTexture(GL_TEXTURE_2D,porch);
    glBegin(GL_POLYGON);
    glNormal3f(0,4,0);
    glTexCoord2f(0,0); glVertex3f(0,0.05,0);
    glTexCoord2f(1,0); glVertex3f(-2,0.05,0);
    glTexCoord2f(1,1); glVertex3f(-2,0.05,2);
    glTexCoord2f(0,1); glVertex3f(0,0.05,2);
    glEnd();
    //  Roof
    glBindTexture(GL_TEXTURE_2D,roof);
    glBegin(GL_POLYGON);
    glNormal3f(-1,4,0);
    glTexCoord2f(0,0); glVertex3f(0,2.5,0);
    glTexCoord2f(1,0); glVertex3f(2,2,0);
    glTexCoord2f(1,1); glVertex3f(2,2,2);
    glTexCoord2f(0,1); glVertex3f(0,2.5,2);
    glEnd();
    //  Roof extension
    glBindTexture(GL_TEXTURE_2D,roof);
    glBegin(GL_POLYGON);
    glNormal3f(-0.4,1,0);
    glTexCoord2f(1,0); glVertex3f(0,2.5,0);
    glTexCoord2f(1,1); glVertex3f(0,2.5,2);
    glTexCoord2f(0,0); glVertex3f(-0.5,2.7,2);
    glTexCoord2f(0,1); glVertex3f(-0.5,2.7,0);
    glEnd();
    glPopMatrix();
}


static void Pillar(double x, double y, double z, double r, double sx, double sy, double sz){
    glEnable(GL_TEXTURE_2D);
    //save transformation
    glPushMatrix();
    //offset
    glTranslated(x,y,z);
    glScaled(sx,sy,sz);
    glRotated(r,0,0,1);
    glColor4f(1,1,1,1);
    //  pillar front
    glBindTexture(GL_TEXTURE_2D,wood);
    glBegin(GL_POLYGON);
    glNormal3f(-0.75,2,0);
    glTexCoord2f(0,0); glVertex3f(-0.15,0,0);
    glTexCoord2f(1,0); glVertex3f(-0.15,0,0.2);
    glTexCoord2f(1,1); glVertex3f(-0.15,3.75,0.2);
    glTexCoord2f(0,1); glVertex3f(-0.15,3.75,0);
    glEnd();
    //  pillar left
    glBegin(GL_POLYGON);
    glNormal3f(0,1,0.555);
    glTexCoord2f(1,0); glVertex3f(0,0,0);
    glTexCoord2f(1,1); glVertex3f(0,3.7,0);
    glTexCoord2f(0,1); glVertex3f(-0.15,3.75,0);
    glTexCoord2f(0,0); glVertex3f(-0.15,0,0);
    glEnd();
    //  pillar right
    glBegin(GL_POLYGON);
    glNormal3f(-4,1,0);
    glTexCoord2f(1,0); glVertex3f(0,0,0.2);
    glTexCoord2f(1,1); glVertex3f(0,3.7,0.2);
    glTexCoord2f(0,1); glVertex3f(-0.15,3.75,0.2);
    glTexCoord2f(0,0); glVertex3f(-0.15,0,0.2);
    glEnd();
    //  pillar back
    glBegin(GL_POLYGON);
    glNormal3f(-0.75,1,0);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(0,0,0.2);
    glTexCoord2f(1,1); glVertex3f(0,3.75,0.2);
    glTexCoord2f(0,1); glVertex3f(0,3.75,0);
    glEnd();
    glPopMatrix();
}

static void Frame(double x, double y, double z, double r, double sx, double sy, double sz){
    glEnable(GL_TEXTURE_2D);
    //save transformation
    glPushMatrix();
    //offset
    glTranslated(x,y,z);
    glScaled(sx,sy,sz);
    glRotated(r,1,0,0);
    glColor4f(1,1,1,1);
    //  frame front
    glBindTexture(GL_TEXTURE_2D,wood);
    glBegin(GL_POLYGON);
    glNormal3f(-0.24,1,0);
    glTexCoord2f(0,0); glVertex3f(-0.15,-0.2,0);
    glTexCoord2f(1,0); glVertex3f(-0.15,-0.2,0.2);
    glTexCoord2f(1,1); glVertex3f(-0.15,1,0.2);
    glTexCoord2f(0,1); glVertex3f(-0.15,1,0);
    glEnd();
    //  frame left
    glBegin(GL_POLYGON);
    glNormal3f(0,1,0.18);
    glTexCoord2f(1,0); glVertex3f(0,-0.2,0);
    glTexCoord2f(1,1); glVertex3f(0,1,0);
    glTexCoord2f(0,1); glVertex3f(-0.15,1,0);
    glTexCoord2f(0,0); glVertex3f(-0.15,-0.2,0);
    //  frame right
    glBegin(GL_POLYGON);
    glNormal3f(0,1,-0.24);
    glTexCoord2f(1,0); glVertex3f(0,-0.2,0);
    glTexCoord2f(1,1); glVertex3f(0,1,0);
    glTexCoord2f(0,1); glVertex3f(0.2,1,0);
    glTexCoord2f(0,0); glVertex3f(0.2,-0.2,0);
    glEnd();
    glPopMatrix();
}

static void Ground(){
    //  flat ground
    glBindTexture(GL_TEXTURE_2D,snow);
    glBegin(GL_POLYGON);
    glNormal3f(0,216,0);
    glTexCoord2f(0,0); glVertex3f(-6,0,-8);
    glTexCoord2f(1,0); glVertex3f(6,0,-8);
    glTexCoord2f(1,1); glVertex3f(6,0,10);
    glTexCoord2f(0,1); glVertex3f(-6,0,10);
    glEnd();
    //front slope
    glBindTexture(GL_TEXTURE_2D,snow);
    glBegin(GL_POLYGON);
    glNormal3f(90,72,0);
    glTexCoord2f(0,0); glVertex3f(-10,-5,-8);
    glTexCoord2f(1,0); glVertex3f(-6,0,-8);
    glTexCoord2f(1,1); glVertex3f(-6,0,10);
    glTexCoord2f(0,1); glVertex3f(-10,-5,10);
    glEnd();
    //right slope
    glBindTexture(GL_TEXTURE_2D,snow);
    glBegin(GL_POLYGON);
    glNormal3f(0,0,60);
    glTexCoord2f(0,0); glVertex3f(6,0,10);
    glTexCoord2f(1,0); glVertex3f(-6,0,10);
    glTexCoord2f(1,1); glVertex3f(-10,-5,10);
    glTexCoord2f(0,1); glVertex3f(6,-5,10);
    glEnd();
    //left slope
    glBindTexture(GL_TEXTURE_2D,snow);
    glBegin(GL_POLYGON);
    glNormal3f(-5,0,-5);
    glTexCoord2f(0,0); glVertex3f(6,0,-8);
    glTexCoord2f(1,0); glVertex3f(-6,0,-8);
    glTexCoord2f(1,1); glVertex3f(-10,-5,-8);
    glTexCoord2f(0,1); glVertex3f(6,-5,-8);
    glEnd();
    //  Porch extension
    glBindTexture(GL_TEXTURE_2D,porch);
    glBegin(GL_POLYGON);
    glNormal3f(0,4.8,0);
    glTexCoord2f(0,0); glVertex3f(-2,0.05,3);
    glTexCoord2f(1,0); glVertex3f(1,0.05,3);
    glTexCoord2f(1,1); glVertex3f(1,0.05,4.6);
    glTexCoord2f(0,1); glVertex3f(-2,0.05,4.6);
    glEnd();
    //  Background
    glBindTexture(GL_TEXTURE_2D,background);
    glBegin(GL_POLYGON);
    glNormal3f(1,1,0);
    glTexCoord2f(0,0); glVertex3f(6,0,10);
    glTexCoord2f(1,0); glVertex3f(6,0,-8);
    glTexCoord2f(1,1); glVertex3f(6,8,-8);
    glTexCoord2f(0,1); glVertex3f(6,8,10);
    glEnd();
    glPopMatrix();
}

//picnic table
static void Tablebase(double x, double y, double z, double r, double sx, double sy, double sz){
    int k;
    glEnable(GL_TEXTURE_2D);
    //save transformation
    glPushMatrix();
    //offset
    glTranslated(x,y,z);
    glScaled(sx,sy,sz);
    glRotated(r,1,0,0);
    glColor4f(1,1,1,1);
    //  cylinder below for table base from ex 19
    glBindTexture(GL_TEXTURE_2D,wood);
    glBegin(GL_QUAD_STRIP);
    for (k=0;k<=360;k+=10)
    {
       glNormal3f(Cos(k),Sin(k),0);
       glTexCoord2f(0,0.5*k); glVertex3f(Cos(k),Sin(k),+1);
       glTexCoord2f(1,0.5*k); glVertex3f(Cos(k),Sin(k),-1);
    }
    glEnd();
    glPopMatrix();
}

//draw a tree
static void Tree(double x, double y, double z, double r, double sx, double sy, double sz, double shift){
    glEnable(GL_TEXTURE_2D);
    //save transformation
    glPushMatrix();
    //offset
    glTranslated(x,y,z);
    glScaled(sx,sy,sz);
    glRotated(r,1,0,0);
    glColor4f(1,1,1,1);
    glBindTexture(GL_TEXTURE_2D,tree);
    int teir;
    glTranslated(0,25*shift,0);
    for(teir=0;teir<=5;teir+=1){
        glTranslated(0,0,z);
        glutSolidCone(8-teir,3,10,10);
    }
    glPopMatrix();
}

/* modified from ex6 to display Lorenz *Modified from Lorenz hw
*  Display the scene
*/
void display()
{
   //  Clear the image ex8
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //  Enable Z-buffering in OpenGL ex8
   glEnable(GL_DEPTH_TEST);
   //  Reset previous transforms
   glLoadIdentity();
   //  Set view angle
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);
   gluLookAt(-4,.05,0,0,0,0,1,1,0);
   //  Light switch from ex13
    if (light)
    {
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {xlight,distance*Cos(zh),distance*Sin(zh),1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(1,1,0);
        ball(Position[0],Position[1],Position[2] , 0.5);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
    }
    else
        glDisable(GL_LIGHTING);

   //draw a lodge with normal vectors included for lighting
    Lodge(1,0,0,0,1.5,1.5,1.5);
    Entrance(2.4,0,3,0,0.8,0.8,0.8);
   
    //  Lodge pillars
    Pillar(1,0,0.02,0,1,1,1);
    Pillar(1,0,1,0,1,1,1);
    Pillar(1,0,2,0,1,1,1);
    Pillar(1,0,2.84,0,1,1,1);
    
    Pillar(1,0.8,0.02,15,0.6,0.89,0.6);
    Pillar(1,0.8,1,15,0.6,0.89,0.6);
    Pillar(1,0.8,2,15,0.6,0.89,0.6);
    Pillar(1,0.8,2.84,15,0.6,0.89,0.6);
    
    //Entrance Door
    Pillar(2.39,0,4.05,0,0.8,0.3,0.8);
    Pillar(2.39,0,3.4,0,0.8,0.3,0.8);
    Frame(2.3,1.1,3.5,90,0.8,0.3,0.8);
    
    //tables
    Pillar(-1,0.4,3.4,90,0.2,1,2);
    Tablebase(-1.4,0.1,3.6,90,0.15,0.2,0.15);
    Pillar(-1,0.4,2.5,90,0.2,1,2);
    Tablebase(-1.4,0.1,2.7,90,0.15,0.2,0.15);
    Pillar(-1,0.4,1.4,90,0.2,1,2);
    Tablebase(-1.4,0.1,1.6,90,0.15,0.2,0.15);
    Pillar(-1,0.4,0.2,90,0.2,1,2);
    Tablebase(-1.4,0.1,0.4,90,0.15,0.2,0.15);
    
    Pillar(0.2,0.4,3.4,90,0.2,1,2);
    Tablebase(-0.2,0.1,3.6,90,0.15,0.2,0.15);
    Pillar(0.2,0.4,2.5,90,0.2,1,2);
    Tablebase(-0.2,0.1,2.7,90,0.15,0.2,0.15);
    Pillar(0.2,0.4,1.4,90,0.2,1,2);
    Tablebase(-0.2,0.1,1.6,90,0.15,0.2,0.15);
    Pillar(0.2,0.4,0.2,90,0.2,1,2);
    Tablebase(-0.2,0.1,0.4,90,0.15,0.2,0.15);
    
    //Trees
    Tablebase(1,0,-1.78,90,0.15,0.8,0.15);
    Tree(1,0,2,-90,0.15,0.2,0.15,1);
    Tablebase(1,0,6.5,90,0.15,0.8,0.15);
    Tree(1,0,2,-90,0.15,0.2,0.15,-1.2);
    Tablebase(2,0,-5.5,90,0.15,0.8,0.15);
    Tree(2,0,2,-90,0.15,0.2,0.15,2);
    
    //Snow machine
    Pillar(-3,0,-5,0,0.6,0.89,0.6);
    Tablebase(-3,4,-5,330,0.3,0.8,0.3);
    
    //ground and background
    Ground();
    
   glDisable(GL_LIGHTING);
    
   //  Flush and swap
   glFlush();
   glutSwapBuffers();
}

/*  modified from ex6
 *  GLUT calls this routine when a key is pressed
 */
//For the user to interact with the model
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
     if (ch == 27)
        exit(0);
   //  Reset view angle
     else if (ch == '0')
        th = ph = 0;
    
    //light controls from ex13
     //  Toggle lighting
     else if (ch == 'l' || ch == 'L')
        light = 1-light;
     else if (ch == 'm' || ch == 'M')
        move = 1-move;
     //  Move light
     else if (ch == '<')
        zh += 1;
     else if (ch == '>')
        zh -= 1;
     //  Light elevation
     else if (ch=='[')
        xlight -= 0.1;
     else if (ch==']')
        xlight += 0.1;
     //  Ambient level
     else if (ch=='a' && ambient>0)
        ambient -= 5;
     else if (ch=='A' && ambient<100)
        ambient += 5;
     //  Diffuse level
     else if (ch=='d' && diffuse>0)
        diffuse -= 5;
     else if (ch=='D' && diffuse<100)
        diffuse += 5;
     //  Specular level
     else if (ch=='s' && specular>0)
        specular -= 5;
     else if (ch=='S' && specular<100)
        specular += 5;
     //  Emission level
     else if (ch=='e' && emission>0)
        emission -= 5;
     else if (ch=='E' && emission<100)
        emission += 5;
    //  Animate if requested ex13
    glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*  special function taken from ex6
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase azimuth by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease azimuth by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*  reshape function is taken from ex6
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection box adjusted for the
   //  aspect ratio of the window
   glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*  main function is modified from ex6
 *  Main
 */
int main(int argc, char *argv[])
{
    //  Initialize GLUT and process user parameters
     glutInit(&argc,argv);
     //taken from ex8
     glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
     //  Request 500 x 500 pixel window
     glutInitWindowSize(500,500);
     //  Create the window
     glutCreateWindow("Ryan Novak Final Project: Ski Lodge");
     //  Tell GLUT to call "display" when the scene should be drawn
     glutDisplayFunc(display);
    //  Tell GLUT to call "reshape" when the window is resized
     glutReshapeFunc(reshape);
     //  Tell GLUT to call "special" when an arrow key is pressed
     glutSpecialFunc(special);
     //  Tell GLUT to call "key" when a key is pressed
     glutKeyboardFunc(key);
     glutIdleFunc(idle);
     //load textures
     brick = LoadTexBMP("brick.bmp");
     roof = LoadTexBMP("roof.bmp");
     glass = LoadTexBMP("glass.bmp");
     wood = LoadTexBMP("wood.bmp");
     plank = LoadTexBMP("plank.bmp");
     snow = LoadTexBMP("snow.bmp");
     porch = LoadTexBMP("porch.bmp");
     door = LoadTexBMP("door.bmp");
     background = LoadTexBMP("back.bmp");
     tree = LoadTexBMP("tree.bmp");
     //  Pass control to GLUT so it can interact with the user
     glutMainLoop();
     //  Return code
   return 0;
}
