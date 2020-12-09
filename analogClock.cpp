#include <iostream>
#include <GLUT/glut.h>
#include <math.h>
#include <time.h>

int win_H, win_W;
time_t timer;
struct tm curr_time;


void
reshape(int w, int h)
{

    glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glScalef(1, -1, 1);
    glTranslatef(0, -h, 0);
}

void
display(void)
{
    //render circle clock face using trig
    const float twicePi = 2.0f * 3.14159f;
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(256, 256);
        for(int i = 0; i <= 360; i++){
            glVertex2f(
                       256 + (180 * cos(i *  twicePi / 360)),
                       256 + (180 * sin(i * twicePi / 360))
            );
        }
    glEnd();

    //render second hand
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(256.0f, 256.0f, 0.0f);
    glRotatef(curr_time.tm_sec*6.0, 0.0f, 0.0f, 256.0f);
    glTranslatef(-256.0f, -256.0f, 0.0f);
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(256, 256);
        glVertex2f(256, 146);
    glEnd();
    glPopMatrix();

    //render minute hand
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(256.0f, 256.0f, 0.0f);
    glRotatef((curr_time.tm_min*6.0)+(curr_time.tm_sec/10.0), 0.0f, 0.0f, 256.0f);
    glTranslatef(-256.0f, -256.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glColor3f(0.5, 0.5, 0.5);
        glVertex2f(262, 256);
        glVertex2f(250, 256);
        glVertex2f(256, 156);
    glEnd();
    glPopMatrix();

    //render hour hand
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(256.0f, 256.0f, 0.0f);
    glRotatef((curr_time.tm_hour*30.0)+(curr_time.tm_min/2.0)+(curr_time.tm_sec/120.0), 0.0f, 0.0f, 256.0f);
    glTranslatef(-256.0f, -256.0f, 0.0f);
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(266, 256);
        glVertex2f(246, 256);
        glVertex2f(261, 176);
        glVertex2f(251, 176);
    glEnd();
    glPopMatrix();

    glutSwapBuffers(); // swap the back buffer to front
}

void TimeEvent(int time_val)
{
    time(&timer); // get the current date and time from system
    localtime_r(&timer, &curr_time);
    glutPostRedisplay();
    glutTimerFunc(30, TimeEvent, 1);// By using a timed event, your application should run at the same speed on any machine.
}

int
main(int argc, char **argv)
{
    GLenum type;

    glutInit(&argc, argv);

    type = GLUT_DEPTH;
    type |= GLUT_RGB;
    type |= GLUT_DOUBLE;
    glutInitDisplayMode(type);

    time(&timer); // get current date and time
    localtime_r(&timer, &curr_time);

    // set window size and create a window for rendering
    win_W = 512;
    win_H = 512;
    glutInitWindowSize(win_H, win_W);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My clock");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(30, TimeEvent, 1);
    glutMainLoop();
    return 0;
}
