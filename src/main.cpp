#include <GL/gl.h>
#include <GL/glu.h>

#include <GL/glut.h>
// #include <Transform.h>

int rotx=0,roty=0,rotz =0;
float transx = 0,transy = 0,transz = 0,scale = 0.001;
int w=1000,h=1000;
int ta = 0;

void drawCoordinates()
{
 
    // draw some lines
    glLineWidth(0.5);
    glColor3f(1,0,0); // red x
    glBegin(GL_LINES);
    // x aix
 
    glVertex3f(-50, 0, 0);
    glVertex3f(50, 0, 0);
 
    glVertex3f(50, 0, 0);
    glVertex3f(45, 5, 0);
 
    glVertex3f(50, 0, 0);
    glVertex3f(45, -5, 0);

    glEnd();
 
    // y 
    glColor3f(0,1,0); // green y
    glBegin(GL_LINES);
    glVertex3f(0, -50, 0);
    glVertex3f(0, 50, 0);
 
    glVertex3f(0, 50, 0);
    glVertex3f(5, 45, 0);
 
    glVertex3f(0, 50, 0);
    glVertex3f(-5, 45, 0);

    glEnd();
 
    // z 
    glColor3f(0,0,1); // blue z
    glBegin(GL_LINES);
    glVertex3f(0, 0, -50);
    glVertex3f(0, 0, 50);
 
 
    glVertex3f(0, 0, 50);
    glVertex3f(0, 5, 45);
 
    glVertex3f(0, 0, 50);
    glVertex3f(0, -5, 45);

    glEnd();
 
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glLoadIdentity ();

    gluLookAt (0, 0, 0.1, 0, 0, 0, 0, 1, 0);
    glScalef (0.3*scale, 0.3*scale, 0.3*scale);

    glTranslatef(transx, 0, 0);
    glTranslatef(0, transy, 0);
    glTranslatef(0, 0, transz);

    glRotatef(rotx, 1, 0, 0);
    glRotatef(roty, 0, 1, 0);
    glRotatef(rotz, 0, 0, 1);

    glColor3f(1,0,1);
    
    glLineWidth(0.5);
    glBegin(GL_POLYGON);
    glVertex3f(5+ta, 5, 0);
    glVertex3f(5+ta, -5, 0);
    glVertex3f(10+ta, 0, 0);
    glEnd();

    drawCoordinates();
    glFlush ();
}
 

void keyboard_action(unsigned char key, int x,int y)
{
    switch(key)
    {
        case 'r' :
                rotx = roty = rotz = 0;
                transx = transy = transz  = 0.0;
                scale = 0.001;
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
                transx = (transx + 5);
                glutPostRedisplay();
                break;
        case 'w' :
                transy = (transy + 5);
                glutPostRedisplay();
                break;
        case 'e' :
                transz = (transz + 5);
                glutPostRedisplay();
                break;        
        case 'a' :
                transx = (transx - 5);
                glutPostRedisplay();
                break;
        case 's' :
                transy = (transy - 5);
                glutPostRedisplay();
                break;
        case 'q' :
                transz = (transz - 5);
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

void reshape(int width,int height)
{
    // glViewport(0,0,widht,height);
    w = width;
    h = height;
    glViewport (0, 0, w,h);

    glMatrixMode (GL_PROJECTION);
    // glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/h, 0.0001f, 100.0f);

    // glMatrixMode (GL_PROJECTION);
    // glLoadIdentity ();
    // gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode (GL_MODELVIEW);
}


void init ()
{
     // select clearing (background) color
    glClearColor (0.0, 0.0, 0.0, 0.0);
    /*

    // // initialize viewing values */
    glMatrixMode (GL_PROJECTION);
    // glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/h, 0.0001f, 100.0f);

    // glMatrixMode (GL_PROJECTION);
    // glMatrixMode (GL_MODELVIEW);
    // glLoadIdentity ();
    // gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode (GL_MODELVIEW);
    // glLoadIdentity ();
    // glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void go()
{
    ta += 1;
}

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
    go();
    glutReshapeFunc(reshape);
    glutReshapeWindow(w, h);

    glutMainLoop();
    return 0;
}