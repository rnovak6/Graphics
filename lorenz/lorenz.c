//Ryan Novak
//105676203
/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 */

/*
 Window Interaction Keys:
 esc = exit
 0 = reset view angle
 arrow keys to rotate view angle
 
 Line Color Interaction Keys:
 1 = light blue     color(0,1,1)
 2 = yellow         color(1,1,0)
 3 = purple         color(1,0,1)
 4 = red            color(1,0,0)
 5 = green          color(0,1,0)
 6 = dark blue      color(0,0,1)
 
 Lorenz Variables Interaction Keys:
 i = r+1
 d = r-1
 a = s+1
 b = s-1
 j = b+0.2
 f = b-0.2
 r = reset lorenz variables to initial values
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
double dim=40;   // Dimension of orthogonal box
//variables to control the color of the line
int c1 = 1;
int c2 = 0;
int c3 = 0;

/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;

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

/* modified from ex6 to display Lorenz
*  Display the scene
*/
void display()
{
   //  Clear the image
   glClear(GL_COLOR_BUFFER_BIT);
   //  Reset previous transforms
   glLoadIdentity();
   //  Set view angle
   glRotated(ph,1,0,0);
   glRotated(th,0,1,0);
    //draw the lorenz model
   glBegin(GL_LINES);
   int i;
   /*  Coordinates  */
   double x = 1;
   double y = 1;
   double z = 1;
   /*  Time step  */
   double dt = 0.001;

   /*  Lorenz equations are from the provided lorenz.c file
    *  Integrate 50,000 steps (50 time units with dt = 0.001)
    *  Explicit Euler integration
    */
   for (i=0;i<50000;i++)
   {
       double dx = s*(y-x);
       double dy = x*(r-z)-y;
       double dz = x*y - b*z;
       x += dt*dx;
       y += dt*dy;
       z += dt*dz;
       //Draw Lorenz model (default red or user input for color)
       glColor3f(c1,c2,c3);
       glVertex3d(x,y,z);
   }
   glEnd();
    
   //  Draw axes in white
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3d(0,0,0);
   glVertex3d(40,0,0);
   glVertex3d(0,0,0);
   glVertex3d(0,40,0);
   glVertex3d(0,0,0);
   glVertex3d(0,0,40);
   glEnd();
   //  Label axes
   glRasterPos3d(40,0,0);
   Print("X");
   glRasterPos3d(0,40,0);
   Print("Y");
   glRasterPos3d(0,0,40);
   Print("Z");
   //  Display parameters
   glWindowPos2i(20,20);
    Print("r, s, b = %.1f  ,  %.1f  ,  %.2f ",r,s,b);
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
    //entering 1 through 6 will change the color of the line
   else if (ch == '1'){
        c1 = 0;
        c2 = 1;
        c3 = 1;
   }
   else if (ch == '2'){
        c1 = 1;
        c2 = 1;
        c3 = 0;
   }
   else if (ch == '3'){
        c1 = 1;
        c2 = 0;
        c3 = 1;
   }
   else if (ch == '4'){
        c1 = 1;
        c2 = 0;
        c3 = 0;
   }
   else if (ch == '5'){
        c1 = 0;
        c2 = 1;
        c3 = 0;
   }
   else if (ch == '6'){
        c1 = 0;
        c2 = 0;
        c3 = 1;
   }
    //allow the user to change the lorenz variables
   else if (ch == 'i'){
       r += 1;
   }
   else if (ch == 'd'){
       r -= 1;
   }
   else if (ch == 'a'){
       s += 1;
   }
   else if (ch == 'b'){
       s -= 1;
   }
   else if (ch == 'f'){
       b -= 0.2;
   }
   else if (ch == 'j'){
       b += 0.2;
   }
    //reset variables to intial values
   else if (ch == 'r'){
       s  = 10;
       b  = 2.6666;
       r  = 28;
   }
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
     //  Request double buffered, true color window
     glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
     //  Request 500 x 500 pixel window
     glutInitWindowSize(500,500);
     //  Create the window
     glutCreateWindow("Lorenz");
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
