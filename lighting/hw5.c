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
double dim=6;   // Dimension of orthogonal box

//light variables from ex13
int move=1;       //  Move light
// Light values
int light     =   1;  // Lighting
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  10;  // Ambient intensity (%)
int diffuse   =  50;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light

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

//Draw a wedge with normal vectors on each surface
static void Wedge(double x, double y, double z, double r){
    //save transformation
    glPushMatrix();
    //offset
    glTranslated(x,y,z);
    glRotated(r,0,1,0);
    //Top
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
    glNormal3f(1,1,0);
    glVertex3f(1,0,-1);
    glVertex3f(1,0,-2);
    glVertex3f(0,1,-2);
    glVertex3f(0,1,-1);
    glEnd();
    //side
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glNormal3f(0,0,-1);
    glVertex3f(1,0,-2);
    glVertex3f(0,1,-2);
    glVertex3f(0,0,-2);
    glEnd();
    //side
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glVertex3f(1,0,-1);
    glVertex3f(0,1,-1);
    glVertex3f(0,0,-1);
    glEnd();
    //bottom
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
    glNormal3f(0,-1,0);
    glVertex3f(0,0,-1);
    glVertex3f(1,0,-1);
    glVertex3f(1,0,-2);
    glVertex3f(0,0,-2);
    glEnd();
    //back
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
    glNormal3f(-1,0,0);
    glVertex3f(0,0,-1);
    glVertex3f(0,1,-1);
    glVertex3f(0,1,-2);
    glVertex3f(0,0,-2);
    glEnd();
    glPopMatrix();
}

static void House(double x, double y, double z, double r, double sx, double sy, double sz){
    //save transformation
    glPushMatrix();
    //offset
    glTranslated(x,y,z);
    glScaled(sx,sy,sz);
    glRotated(r,0,1,0);
    //  Front
    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glNormal3f(0,0,4);
    glVertex3f(0,0,2);
    glVertex3f(2,0,2);
    glVertex3f(2,2,2);
    glVertex3f(0,2,2);
    glEnd();
    //  Back
    glBegin(GL_POLYGON);
    glColor3f(0,0,2);
    glNormal3f(0,0,-2);
    glVertex3f(2,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,2,0);
    glVertex3f(2,2,0);
    glEnd();
    //Right
    glBegin(GL_POLYGON);
    glColor3f(1,1,0);
    glNormal3f(4,0,0);
    glVertex3f(2,0,2);
    glVertex3f(2,0,0);
    glVertex3f(2,2,0);
    glVertex3f(2,2,2);
    glEnd();
    //  Left
    glBegin(GL_POLYGON);
    glColor3f(0,1,0);
    glNormal3f(-4,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,2);
    glVertex3f(0,2,2);
    glVertex3f(0,2,0);
    glEnd();
    //  Bottom
    glBegin(GL_POLYGON);
    glColor3f(1,0,1);
    glNormal3f(0,4,0);
    glVertex3f(0,0,0);
    glVertex3f(2,0,0);
    glVertex3f(2,0,2);
    glVertex3f(0,0,2);
    glEnd();
    //roof left
    glBegin(GL_POLYGON);
    glColor3f(0,1,1);
    glNormal3f(-2,-2,0);
    glVertex3f(0,2,2);
    glVertex3f(1,3,2);
    glVertex3f(1,3,0);
    glVertex3f(0,2,0);
    glEnd();
    //roof right
    glBegin(GL_POLYGON);
    glColor3f(0,1,1);
    glNormal3f(2,2,2);
    glVertex3f(1,3,2);
    glVertex3f(1,3,0);
    glVertex3f(2,2,0);
    glVertex3f(2,2,2);
    glEnd();
    //roof front
    glBegin(GL_POLYGON);
    glColor3f(0,1,1);
    glNormal3f(0,0,2);
    glVertex3f(2,2,2);
    glVertex3f(0,2,2);
    glVertex3f(1,3,2);
    glEnd();
    //roof back
    glBegin(GL_POLYGON);
    glColor3f(0,1,1);
    glNormal3f(0,0,-2);
    glVertex3f(2,2,0);
    glVertex3f(0,2,0);
    glVertex3f(1,3,0);
    glEnd();
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
    
   //  Light switch from ex13
     if (light)
     {
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(0,1,1);
        ball(Position[0],Position[1],Position[2] , 0.1);
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

   //draw a wedge with normal vectors included for lighting
   Wedge(2,0,0,0);
   Wedge(-2,0,2,40);
   Wedge(0,2,0,120);
    
   House(1,0,0,0,1,1,1);
   House(0,0,0,0,0.2,0.2,0.2);
   House(2,0,4,0,0.2,0.2,0.2);
   House(4,0,4,0,0.2,0.2,0.2);
   House(4,0,2,0,0.2,0.2,0.2);
   House(4,0,0,0,0.2,0.2,0.2);
   House(0,0,2,0,0.2,0.2,0.2);
   House(0,0,4,0,0.2,0.2,0.2);
    
   glDisable(GL_LIGHTING);
    
   //  Draw axes in white
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3d(0,0,0);
   glVertex3d(5,0,0);
   glVertex3d(0,0,0);
   glVertex3d(0,5,0);
   glVertex3d(0,0,0);
   glVertex3d(0,0,5);
   glEnd();
   //  Label axes
   glRasterPos3d(5,0,0);
   Print("X");
   glRasterPos3d(0,5,0);
   Print("Y");
   glRasterPos3d(0,0,5);
   Print("Z");
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
        ylight -= 0.1;
     else if (ch==']')
        ylight += 0.1;
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
     glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
     //  Request 500 x 500 pixel window
     glutInitWindowSize(500,500);
     //  Create the window
     glutCreateWindow("Ryan Novak HW5: Lighting");
     //  Tell GLUT to call "display" when the scene should be drawn
     glutDisplayFunc(display);
    //  Tell GLUT to call "reshape" when the window is resized
     glutReshapeFunc(reshape);
     //  Tell GLUT to call "special" when an arrow key is pressed
     glutSpecialFunc(special);
     //  Tell GLUT to call "key" when a key is pressed
     glutKeyboardFunc(key);
     glutIdleFunc(idle);
     //  Pass control to GLUT so it can interact with the user
     glutMainLoop();
     //  Return code
   return 0;
}
