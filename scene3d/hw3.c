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

//  Globals modified from ex6
int th=0;       // Azimuth of view angle
int ph=0;       // Elevation of view angle
double dim=6;   // Dimension of orthogonal box

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

/*
 A Function to draw a house
 */
static void House(double x, double y, double z, double dx, double dy, double dz, double r){
    //3D object
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    glRotated(r,0,0,0);
    glScaled(dx,dy,dz);
    //four sides of the house
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    glVertex3f( 0, 0, 0);
    glVertex3f( 1, 0, 0);
    glVertex3f( 1, 1, 0);
    glVertex3f( 0.5, 1.5, 0.5);
    glVertex3f( 0, 1, 0);
    glVertex3f( 0, 0, 0);
    glEnd();
    
    //blue
    glColor3f(0,1,1);
    glBegin(GL_POLYGON);
    glVertex3f( 0, 0, 0);
    glVertex3f( 0, 1, 0);
    glVertex3f( 0.5, 1.5, 0.5);
    glVertex3f( 0, 1, 1);
    glVertex3f( 0, 0, 1);
    glVertex3f( 0, 0, 0);
    glEnd();
    
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
    glVertex3f( 1, 0, 0);
    glVertex3f( 1, 0, 1);
    glVertex3f( 1, 1, 1);
    glVertex3f( 0.5, 1.5, 0.5);
    glVertex3f( 1, 1, 0);
    glVertex3f( 1, 0, 0);
    glEnd();
    
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
    glVertex3f( 0, 0, 1);
    glVertex3f( 0, 1, 1);
    glVertex3f( 0.5, 1.5, 0.5);
    glVertex3f( 1, 1, 1);
    glVertex3f( 1, 0, 1);
    glVertex3f( 0, 0, 1);
    glEnd();
    //bottom of house
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    glVertex3f( 0, 0, 0);
    glVertex3f( 1, 0, 0);
    glVertex3f( 1, 0, 1);
    glVertex3f( 0, 0, 1);
    glVertex3f( 0, 0, 0);
    glEnd();
     
    //  Undo transformations
    glPopMatrix();
}

//Draw a wedge
static void Wedge(double x, double y, double z, double r){
    //save transformation
    glPushMatrix();
    //offset
    glTranslated(x,y,z);
    glRotated(r,0,1,0);
    //Top
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
    glVertex3f(1,0,-1);
    glVertex3f(1,0,-2);
    glVertex3f(0,1,-2);
    glVertex3f(0,1,-1);
    glEnd();
    //side
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(1,0,-2);
    glVertex3f(0,1,-2);
    glVertex3f(0,0,-2);
    glEnd();
    //side
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(1,0,-1);
    glVertex3f(0,1,-1);
    glVertex3f(0,0,-1);
    glEnd();
    //bottom
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
    glVertex3f(0,0,-1);
    glVertex3f(1,0,-1);
    glVertex3f(1,0,-2);
    glVertex3f(0,0,-2);
    glEnd();
    //back
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
    glVertex3f(0,0,-1);
    glVertex3f(0,1,-1);
    glVertex3f(0,1,-2);
    glVertex3f(0,0,-2);
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
    
   //Draw 3 houses
   House(0,0,0, 1,1,1, 0);
   House(2,1,3, 0.6,0.6,0.6, 45);
   House(3,0,1, 0.4,1.2,0.6, 0);
    
   //draw a wedge
   Wedge(0,3,0,0);
   Wedge(1,2,4,45);
    
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
     glutCreateWindow("Ryan Novak HW3: 3D Scene");
     //  Tell GLUT to call "display" when the scene should be drawn
     glutDisplayFunc(display);
    //  Tell GLUT to call "reshape" when the window is resized
     glutReshapeFunc(reshape);
     //  Tell GLUT to call "special" when an arrow key is pressed
     glutSpecialFunc(special);
     //  Tell GLUT to call "key" when a key is pressed
     glutKeyboardFunc(key);
     //  Pass control to GLUT so it can interact with the user
     glutMainLoop();
     //  Return code
   return 0;
}
