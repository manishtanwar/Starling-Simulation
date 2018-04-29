#include <GL/gl.h>
#include <GL/glu.h>

#include <GL/glut.h>
// #include <Transform.h>


void drawCoordinates(){
 
    // draw some lines
    glLineWidth(1.2);
    glColor3f(1.0,0.0,0.0); // red x
    glBegin(GL_LINES);
    // x aix
 
    glVertex3f(-0.5, 0.0f, 0.0f);
    glVertex3f(0.5, 0.0f, 0.0f);
 
    glVertex3f(0.5, 0.0f, 0.0f);
    glVertex3f(0.45, 0.05f, 0.0f);
 
    glVertex3f(0.5, 0.0f, 0.0f);
    glVertex3f(0.45, -0.05f, 0.0f);

    // glVertex3f(-0.5, 0.0f, 0.0f);
    // glVertex3f(-0.45, -0.05f, 0.0f);
 
    // glVertex3f(-0.5, 0.0f, 0.0f);
    // glVertex3f(-0.45, 0.05f, 0.0f);
    glEnd();
    // glFlush();
 
    // y 
    glColor3f(0.0,1.0,0.0); // green y
    glBegin(GL_LINES);
    glVertex3f(0.0, -0.5f, 0.0f);
    glVertex3f(0.0, 0.5f, 0.0f);
 
    glVertex3f(0.0, 0.5f, 0.0f);
    glVertex3f(0.05, 0.45f, 0.0f);
 
    glVertex3f(0.0, 0.5f, 0.0f);
    glVertex3f(-0.05, 0.45f, 0.0f);

    // glVertex3f(0.0, -0.5f, 0.0f);
    // glVertex3f(0.05, -0.45f, 0.0f);
 
    // glVertex3f(0.0, -0.5f, 0.0f);
    // glVertex3f(-0.05, -0.45f, 0.0f);
    glEnd();
 
    // z 
    glColor3f(0.0,0.0,1.0); // blue z
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0f ,-0.5f );
    glVertex3f(0.0, 0.0f ,0.5f );
 
 
    glVertex3f(0.0, 0.0f ,0.5f );
    glVertex3f(0.0, 0.05f ,0.45f );
 
    glVertex3f(0.0, 0.0f ,0.5f );
    glVertex3f(0.0, -0.05f ,0.45f );

    // glVertex3f(0.0, 0.0f ,-0.5f );
    // glVertex3f(0.0, 0.05f ,-0.45f );
 
    // glVertex3f(0.0, 0.0f ,-0.5f );
    // glVertex3f(0.0, -0.05f ,-0.45f );
    glEnd();
 
}

// void display()
// {
// /* clear all pixels */
// glClear (GL_COLOR_BUFFER_BIT);

// *
// draw white polygon (rectangle) with corners at
// (0.45, 0.45, 0.0) and (0.75, 0.75, 0.0)
// http://heron.cc.ukans.edu/ebt-bin/nph-dweb/dyna...G/@Generic__BookTextView/622;cs=fullhtml;pt=532 (10 of 16) [4/28/2000 9:44:16 PM]OpenGL Programming Guide (Addison-Wesley Publishing Company)

// // glColor3f (1.0, 1.0, 0.0);
// // glBegin(GL_POLYGON);
// // glVertex3f (0.0, 0.45,0.0);
// // glVertex3f (0.75, 0.45,0.0);
// // glVertex3f (0.75, 0.75,0.0);
// // glVertex3f (0.45, 0.75,0.0);
// // glEnd();

// drawCoordinates();


// /* don't wait!
// * start processing buffered OpenGL routines
// */
// // glFlush ();
// }
int rotx=0,roty=0,rotz =0;
float transx = 0,transy = 0,scale = 1;


void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);
  glColor3f (1.0, 1.0, 1.0);
  glLoadIdentity ();
  
  glTranslatef(transx, 0, 0);
  glTranslatef(0, transy, 0);
  // glTranslatef(0, 0, transz);
  
  // glRotatef(rs.cameraX, 1, 0, 0);
  // glTranslatef(transx, transy, transz);
  glRotatef(rotx, 1, 0, 0);
  glRotatef(roty, 0, 1, 0);
  glRotatef(rotz, 0, 0, 1);
  gluLookAt (0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  // glScalef (0.3, 0.3, 0.3);
  glScalef (0.3*scale, 0.3*scale, 0.3*scale);
  // glutWireCube (1.0);
  drawCoordinates();
  // gluLookAt (5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
 
  glFlush ();

}
 

void keyboard_action(unsigned char key, int x,int y)
{
    switch(key)
    {
        case 'r' :
                rotx = roty = rotz = 0;
                transx = transy  = 0.0;
                scale = 1.0;
                glutPostRedisplay();
                break;
        case 'x' :
                rotx = (rotx+5)%360;
                glutPostRedisplay();
                break;
        case 'y' :
                roty = (roty+5)%360;
                glutPostRedisplay();
                break;
        case 'z' :
                rotz = (rotz+5)%360;
                glutPostRedisplay();
                break;
        case 'd' :
                transx = (transx+0.05);
                glutPostRedisplay();
                break;
        case 'w' :
                transy = (transy+0.05);
                glutPostRedisplay();
                break;
        case 'a' :
                transx = (transx-0.05);
                glutPostRedisplay();
                break;
        case 's' :
                transy = (transy-0.05);
                glutPostRedisplay();
                break;
        default :
                break;
    }
}
// int amount = 5;
// const vec3 eye(0.1, 0.1, 0.1);
// const vec3 up(0.0, 0.0, 1.0);
// Arrow key functionality
void specialKey_action(int key, int x, int y)
{
	switch (key)
	{
        case 101 :
                scale = 1.1*(scale);
                glutPostRedisplay();
                break;
        case 103 :
                scale = 0.9*(scale);
                glutPostRedisplay();
                break;
	}
}






void init ()
{
 // select clearing (background) color
glClearColor (0.0, 0.0, 0.0, 0.0);
/*

// initialize viewing values */
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}
/*
*
*
*
*
*
*/
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (1000, 1000);
glutInitWindowPosition (50, 50);
glutCreateWindow ("boids");
init ();
glutDisplayFunc(display);
glutSpecialFunc(specialKey_action);
glutKeyboardFunc(keyboard_action);


// void glutSolidSphere(GLdouble 0.5, GLint 1000, GLint 1);
glutMainLoop();
return 0;
/* ISO C requires main to return int. */
}