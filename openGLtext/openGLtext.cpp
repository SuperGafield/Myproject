// openGLtext.cpp : 

#include "stdafx.h"
#include <cstring>
#include <cstdio>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

void display();
void reshape(int w, int h);
void timer(int value);

inline void BuildList();
inline void DISPLAY_TEXT();


void DRAW_STRING(int x, int y, char *string, void *font = GLUT_BITMAP_TIMES_ROMAN_24);

using namespace std;


inline void GLUT_INIT()
{
glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
}

inline void GLUT_CALL_FUNC()
{
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutTimerFunc(1,timer,0);
}

inline void MY_INIT()
{
glClearColor(1.0, 1.0, 1.0, 1.0);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
BuildList(); 
}

int main(int argc, char **argv)
{
glutInit(&argc,argv);
GLUT_INIT();
glutCreateWindow("window name");
GLUT_CALL_FUNC();
MY_INIT();
glutMainLoop();

return 0;
}

GLfloat light_pos[] = { 0.0, 3.0, 5.0, 1.0 };
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
int list;

void display()
{
static int r = 0;
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLoadIdentity();
gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

glLightfv(GL_LIGHT0, GL_POSITION, light_pos);


glEnable(GL_DEPTH_TEST);

glPushMatrix();
glRotated((double)r, 0.0, 1.0, 0.0);
glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
glutSolidCube(1);

glPopMatrix();

glDisable(GL_DEPTH_TEST);
glDisable(GL_LIGHTING);
glDisable(GL_LIGHT0);

DISPLAY_TEXT(); 

glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);

glutSwapBuffers();

r = r + 1;
if(r > 360)
{
r= 0;
}
}

void reshape(int w, int h)
{
glViewport(0, 0, w, h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
glMatrixMode(GL_MODELVIEW);

}

void timer(int value)
{
glutPostRedisplay();
glutTimerFunc(1,timer,0); 
}

inline void BuildList()
{
list=glGenLists(1);
glNewList(list,GL_COMPILE);
DRAW_STRING(0, 0, "hello,gult bitmap strings.",GLUT_BITMAP_TIMES_ROMAN_24);
glEndList();
}

inline void DISPLAY_TEXT()
{
glPushAttrib(GL_ENABLE_BIT);
glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity(); 
gluOrtho2D(0, 200, 0, 200); 
glMatrixMode(GL_MODELVIEW); 
glPushMatrix(); 
glLoadIdentity(); 
glColor3f(1,0,1);
glCallList(list);
glPopMatrix(); 
glMatrixMode(GL_PROJECTION); 
glPopMatrix(); 
glPopAttrib(); 
glMatrixMode(GL_MODELVIEW); 
}


void DRAW_STRING(int x, int y, char *string, void *font)
{
int len, i;

y += 5; 
glRasterPos2f(x, y);
len = (int) strlen(string);
for (i = 0; i < len; i++)
{
glutBitmapCharacter(font, string[i]);
}

}