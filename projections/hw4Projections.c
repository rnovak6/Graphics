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
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//ex9 sin and cos definition
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

//  Globals modified from ex6
int th=0;       // Azimuth of view angle
int ph=0;       // Elevation of view angle
double dim=6;   // Dimension of orthogonal box
char view = 'p';   // mode from ex9
int fov=55;       //  Field of view (for perspective) ex9
double asp=1;     //  Aspect ratio ex9

//camera
vec3 cameraPos   = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp    = vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float yaw   = -90.0f;    // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

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

/* Taken from ex9
 *  Set projection
 */
static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (view == 'p')
      gluPerspective(fov,asp,dim/4,4*dim);
   //  Orthogonal projection
   else if (view == 'o')
      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
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
    
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
    glVertex3f( 0, 0, 0);
    glVertex3f( 0, 1, 0);
    glVertex3f( 0.5, 1.5, 0.5);
    glVertex3f( 0, 1, 1);
    glVertex3f( 0, 0, 1);
    glVertex3f( 0, 0, 0);
    glEnd();
    
    glColor3f(0,1,1);
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
    //perspective taken from ex9
    if (view == 'p')
    {
       double Ex = -2*dim*Sin(th)*Cos(ph);
       double Ey = +2*dim        *Sin(ph);
       double Ez = +2*dim*Cos(th)*Cos(ph);
       gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
    }
    //  Orthogonal - set world orientation
    else if (view == 'o')
    {
       //  Set view angle
       glRotatef(ph,1,0,0);
       glRotatef(th,0,1,0);
    }
    //first person
    else if (view == 'f'){
        /*
webstie         */
        glulookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }
        
   //  Set view angle
   glRotated(ph,1,0,0);
   glRotated(th,0,1,0);
    
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
   glWindowPos2i(20,20);
    //Print("Projection=%s",view?"Perpective":"Orthogonal":"First Person");
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
   //switch between displays ex9
   else if (ch == 'o')
       view = 'o';
   else if (ch == 'f')
       view = 'f';
   else if (ch == 'p')
       view = 'p';
   Project();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*  special function taken from ex6
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase azimuth by 5 degrees
    if (key == GLUT_KEY_RIGHT){
        th += 5;
        xrot += 5;
    }
   //  Left arrow key - decrease azimuth by 5 degrees
    else if (key == GLUT_KEY_LEFT){
        th -= 5;
        xrot -= 5;
    }
   //  Up arrow key - increase elevation by 5 degrees
    else if (key == GLUT_KEY_UP){
        ph += 5;
        yrot += 5;
    }
   //  Down arrow key - decrease elevation by 5 degrees
    else if (key == GLUT_KEY_DOWN){
        ph -= 5;
        yrot -= 5;
    }
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //ex9
    Project();
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    vec3 front;
    front.x = cos(radians(yaw)) * cos(radians(pitch));
    front.y = sin(radians(pitch));
    front.z = sin(radians(yaw)) * cos(radians(pitch));
    cameraFront = normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
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
     //taken from ex8
     glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
     //  Create the window
     glutCreateWindow("Ryan Novak HW4: Projections");
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
