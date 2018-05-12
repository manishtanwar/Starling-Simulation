#include <GL/gl.h>
#include <GL/glu.h>

#include <GL/glut.h>
#include "../include/boid.h"
#include "../include/properties.h"
#include<bits/stdc++.h>

int rotx=0,roty=0,rotz =0;
float transx = 0,transy = 0,transz = 0,scale = 0.001;
int w=1000,h=1000;
int ta = 0;
int qw = 0;

std::vector<boid> v;
clock_t time_now;
double start;
tuple avg_force;

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
    
    tuple avg_velocity(0,0,0);
    double KE = 0.0, ke1;
    qw++; qw %= freq_pankh;
    // if(qw == 0)
    // ta = 1-ta;


    for(int i=0;i< v.size() ;i++)
    {
        // glBegin(GL_POLYGON);
        // v[i].position = v[i].position + v[i].velocity;
        // glVertex3f(10 + v[i].position.x, 0 + v[i].position.y, 0  + v[i].position.z);
        // glVertex3f(5  + v[i].position.x, 2 + v[i].position.y, -2 + v[i].position.z);
        // glVertex3f(6  + v[i].position.x, v[i].position.y, 0  + v[i].position.z);
        // glVertex3f(5  + v[i].position.x, -2 + v[i].position.y, -2 + v[i].position.z);
        // glEnd();
        v[i].position = v[i].position + v[i].velocity;
        avg_velocity = avg_velocity + v[i].velocity;
        ke1 = v[i].velocity.magnitude();
        // std::cout<<v[i].velocity.x<<' '<<v[i].velocity.y<<' '<<v[i].velocity.z<<'\n';
        KE +=  ((ke1 * ke1) * 0.07) / (2.0 * v.size());
        // std::cout<<ke1<<'\n';
        // std::cout<<"K! "<<KE<<'\n';

        tuple v1,v2,v3,v4,tmp,vel,vel1,vel2,vel3;
        vel = v[i].velocity;

        vel.make_it_unit_vector();
        vel1 = vel;

        if(vel1.z != 0)
        vel2 = tuple(1,1,0),
        vel2.z = (-(vel2.x*vel1.x)-(vel2.y*vel1.y))/vel1.z;
        else if(vel1.y != 0)
        vel2 = tuple(1,0,1),
        vel2.y = (-(vel2.x*vel1.x))/vel1.y;
        else
        vel2 = tuple(0,1,0);
        vel2.make_it_unit_vector();
        vel3 = cross_product(vel1,vel2);
        vel3.make_it_unit_vector();

        v1 = tuple(6,0,0);
        v1 = v1 + v[i].position;

        v2 = vel1*(4.0);
        // (5,2,-2) - (6,0,0) = (-1,2,-2)
        // (5,-2,-2) - (6,0,0) = (-1,-2,-2)
        if(ta%2)
        v3 = vel1*(-1.0) + vel2*(2.0) + vel3*(-2.0),
        v4 = vel1*(-1.0) + vel2*(-2.0) + vel3*(-2.0);
        else
        v3 = vel1*(-1.0) + vel2*(2.0) + vel3*(2.0),
        v4 = vel1*(-1.0) + vel2*(-2.0) + vel3*(2.0);

        v2 = v2 + tuple(6,0,0);
        v3 = v3 + tuple(6,0,0);
        v4 = v4 + tuple(6,0,0);
        // std::cout<<v3.x<<' '<<v3.y<<' '<<v3.z<<'\n';
        v2 = v2 + v[i].position;
        v3 = v3 + v[i].position;
        v4 = v4 + v[i].position;

        v1 = v1*(0.2);
        v2 = v2*(0.2);
        v3 = v3*(0.2);
        v4 = v4*(0.2);
        tuple sar;
        sar = v2*(3.0) + v1;
        sar = sar * (1.0/4);

        glPushMatrix();
        glTranslatef(sar.x, sar.y, sar.z);
        glutSolidSphere(0.1,10,10);
        glutSolidCone(0.1,0.5,10,10);
        glPopMatrix();

        glBegin(GL_POLYGON);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v4.x, v4.y, v4.z);
        glEnd();
    }
    avg_velocity = avg_velocity * (1.0/v.size());
    // KE /= 2.0;
    // KE *= 70.0/1000.0;

    // std::cout<<std::setprecision(25);
    // std::cout<<"avg_velocity -> "<<avg_velocity.x<<"i + "<<avg_velocity.y<<"j + "<<avg_velocity.z<<"k\n";
    // std::cout<<"avg_force -> "<<avg_force.x<<"i + "<<avg_force.y<<"j + "<<avg_force.z<<"k\n";

    // std::cout<<"KE "<<KE<<'\n';
    
    time_now = clock();
    double period = time_now - start;
    start = time_now;
    // std::cout<<period<<'\n';
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
                rotx = (rotx+1)%360;
                glutPostRedisplay();
                break;
        case 'y' :
                roty = (roty+1)%360;
                glutPostRedisplay();
                break;
        case 'z' :
                rotz = (rotz+1)%360;
                glutPostRedisplay();
                break;
        case 'd' :
                transx = (transx + 1);
                glutPostRedisplay();
                break;
        case 'w' :
                transy = (transy + 1);
                glutPostRedisplay();
                break;
        case 'e' :
                transz = (transz + 1);
                glutPostRedisplay();
                break;        
        case 'a' :
                transx = (transx - 1);
                glutPostRedisplay();
                break;
        case 's' :
                transy = (transy - 1);
                glutPostRedisplay();
                break;
        case 'q' :
                transz = (transz - 1);
                glutPostRedisplay();
                break;

        default :
                break;
    }
}

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

void go(int a)
{
    avg_force = change_it(v);
    // std::cout<<avg_force.x<<' '<<avg_force.y<<' '<<avg_force.z<<'\n';
    glutPostRedisplay();
    glutTimerFunc(100,go,0);
}

int main(int argc, char** argv)
{
    for(int i=0;i<NO_OF_BOIDS;i++){
        boid new_boid;
        v.pb(new_boid);
    }
    time_now = clock();
    start = time_now;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (1000, 1000);
    glutInitWindowPosition (50, 50);
    glutCreateWindow ("boids");
    init ();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKey_action);
    glutKeyboardFunc(keyboard_action);
    
    go(0);
    // glutTimerFunc(1000, go, 0);
    glutReshapeFunc(reshape);
    glutReshapeWindow(w, h);

    glutMainLoop();
    return 0;
}