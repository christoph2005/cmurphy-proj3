//Name:Murphy,Chris
//Project :3
//Due:Thursday May 15, 2014
//Course :cs-445-01-sp14
/*
Modify the rotating hexagon program in 12-10 to allow a user to interactively 
choose a three dimensional object from a list of menu options to be rotated about
the y axis. Use a perspective projection to display the object.
*/

#include <stdlib.h>
#include <stdio.h> // printf

#ifdef _WIN32 
#include <GL/glut.h> 
#elif __APPLE__
#include <GLUT/glut.h> 
#elif __linux__
#include <GL/glut.h>
#endif 

#define _USE_MATH_DEFINES
#include <math.h> 


GLsizei winWidth = 500, winHeight = 500;
GLuint cube, dodecahedron, tetrahedron, octahedron, icosahedron;
GLuint cubeS, dodecahedronS, tetrahedronS, octahedronS, icosahedronS, curList;
GLfloat TWO_PI = M_PI * 2;
static GLfloat rotTheta = 0.0;

class scrPt{
public:
	GLint x, y, z;
};
scrPt center = { winWidth/2, winHeight/2, -150 };
static void init(void){
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0, 0, 0);

	GLint s = 100;
	/*  make cube display list */
	cube = glGenLists(1);
	glNewList(cube, GL_COMPILE);
	glTranslatef(center.x, center.y, center.z);
	glutWireCube(s);
	glEndList();
	/*  make cubeS display list */
	cubeS = glGenLists(1);
	glNewList(cubeS, GL_COMPILE);
	glTranslatef(center.x, center.y, center.z);
	glutSolidCube(s);
	glEndList();

	curList = cube;

	/*  make dodecahedron display list */
	dodecahedron = glGenLists(1);
	glNewList(dodecahedron, GL_COMPILE);
	glTranslatef(center.x, center.y, center.z);
	glScalef(s, s, s);
	glutWireDodecahedron();
	glEndList();
	/*  make dodecahedronS display list */
	dodecahedronS = glGenLists(1);
	glNewList(dodecahedronS, GL_COMPILE);
	glTranslatef(center.x, center.y, center.z);
	glScalef(s, s, s);
	glutSolidDodecahedron();
	glEndList();

	/*  make tetrahedron display list */
	tetrahedron = glGenLists(1);
	glNewList(tetrahedron, GL_COMPILE);
	glTranslatef(center.x, center.y, center.z);
	glScalef(s, s, s);
	glutWireTetrahedron();
	glEndList();
	/*  make tetrahedronS display list */
	tetrahedronS = glGenLists(1);
	glNewList(tetrahedronS, GL_COMPILE);
	glTranslatef(center.x, center.y, center.z);
	glScalef(s, s, s);
	glutSolidTetrahedron();
	glEndList();

	/*  make octahedron display list */
	octahedron = glGenLists(1);
	glNewList(octahedron, GL_COMPILE);
	glTranslatef(center.x, center.y, center.z);
	glScalef(s, s, s);
	glutWireOctahedron();
	glEndList();
	/*  make octahedronS display list */
	octahedronS = glGenLists(1);
	glNewList(octahedronS, GL_COMPILE);
	glTranslatef(center.x, center.y, center.z);
	glScalef(s, s, s);
	glutSolidOctahedron();
	glEndList();

	/*  make icosahedron display list */
	icosahedron = glGenLists(1);
	glNewList(icosahedron, GL_COMPILE);
	glTranslatef(center.x, center.y, center.z);
	glScalef(s, s, s);
	glutWireIcosahedron();
	glEndList();
	/*  make icosahedronS display list */
	icosahedronS = glGenLists(1);
	glNewList(icosahedronS, GL_COMPILE);
	glTranslatef(center.x, center.y, center.z);
	glScalef(s, s, s);
	glutSolidIcosahedron();
	glEndList();
}
GLfloat scale = 1;
GLint translateX = 0, translateY = 0, translateZ = 0;
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	gluLookAt(center.x, center.y + 160, 250, center.x, center.y, center.z, 0, 1, 0);
	glTranslatef(translateX, translateY, translateZ);
	glTranslatef(center.x, center.y, center.z);
	glScalef(scale, scale, scale);
	glRotatef(rotTheta, 0.0, 1.0, 0.0);
	glTranslatef(-center.y, -center.y, -center.z);
	glCallList(curList);
	glPopMatrix();


	glutSwapBuffers();

	glFlush();
}

int lastTime = 0;
int FPS = 30;
void rotate(void){
	GLfloat dt=glutGet(GLUT_ELAPSED_TIME) - lastTime;
	lastTime = glutGet(GLUT_ELAPSED_TIME);
	rotTheta +=(60*dt)/1000;
	if(rotTheta > 360.0)
		rotTheta -= 360.0;
	glutPostRedisplay();
}

void winReshapeFcn(GLint newWidth, GLint newHeight){
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, winWidth, 0, winHeight);
	gluPerspective(50, winWidth / winHeight, 0, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
}
void setShape(int v){
	curList = v;
}
void menu(int v){
	switch (v){
	case 0:
		exit(0);
		break;
	case 1:
		glColor3f(1, 0, 0);
		break;
	case 2:
		glColor3f(0, 1, 0);
		break;
	case 3:
		glColor3f(0, 0, 1);
		break;
	case 4:
		glColor3f(0, 0, 0);
		break;
	default:
		curList = -1;
		break;
	}
	glutPostRedisplay();
}
int submenu_id, menu_id,colorMenu_id;
void createMenu(void){
	//GLuint cube, dodecahedron, tetrahedron, octahedron, icosahedron;
	submenu_id = glutCreateMenu(setShape);
	glutAddMenuEntry("Cube", cube);
	glutAddMenuEntry("Dodecahedron", dodecahedron);
	glutAddMenuEntry("Tetrahedron", tetrahedron);
	glutAddMenuEntry("Octahedron", octahedron);
	glutAddMenuEntry("Icosahedron", icosahedron);
	glutAddMenuEntry("Solid - Cube", cubeS);
	glutAddMenuEntry("Solid - Dodecahedron", dodecahedronS);
	glutAddMenuEntry("Solid - Tetrahedron", tetrahedronS);
	glutAddMenuEntry("Solid - Octahedron", octahedronS);
	glutAddMenuEntry("Solid - Icosahedron", icosahedronS);
	colorMenu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	menu_id = glutCreateMenu(menu);
	glutAddSubMenu("Draw", submenu_id);
	glutAddSubMenu("Color", colorMenu_id);
	glutAddMenuEntry("Clear", -1);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutPostRedisplay();
}

void mouseFcn(GLint button, GLint action, GLint x, GLint y){
	switch(button){
	case GLUT_LEFT_BUTTON:
		if(action == GLUT_DOWN)
			glutIdleFunc(rotate);
		break;
	case GLUT_RIGHT_BUTTON:
		if(action == GLUT_DOWN)
			glutIdleFunc(createMenu);
		break;
	default:
		break;
	}
}

void keyFunc(unsigned char c, int x, int y){
	switch (c){
	case 'S':
		scale += .05;
		break;
	case 'X':
		translateX += 5;
		break;
	case 'Y':
		translateY += 5;
		break;
	case 'Z':
		translateZ += 5;
		break;
	case 'q':
		exit(0);
		break;
	case 's':
		scale -= .05;
		break;
	case 'x':
		translateX -= 5;
		break;
	case 'y':
		translateY -= 5;
		break;
	case 'z':
		translateZ -= 5;
		break;
	default:
		break;
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("project 3");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouseFcn);
	glutKeyboardFunc(keyFunc);
	glutMainLoop();

	return 0;
}

