

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

int		screenWidth = 900;
int		screenHeight= 600;

Assignment_object obj;

float camera_angle = 0.0f; // init
float camera_height = 0.0f; // equal object y
float camera_dis = 7.0f;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;
float rotate;

bool		isWire = false;
float angle_y = 0;
float angle_z = 0;

void myKeyboard(unsigned char key, int x, int y){
	if(key != 'q' && key != 'Q' ){
		if (key=='1')
			angle_y += 1;
		if (key=='2')
			angle_y += -1;
		if (key=='3')
			angle_z += 1;
		if (key=='4')
			angle_z += -1;
		if (key=='5')
			obj.rotate_object(0.1);
		if (key=='6')
			obj.rotate_object(-0.1);
		if(key == 'w' || key == 'W'){
			isWire = !isWire;
			cout << "isWire = " << isWire << endl;
			}
		if(key == '+'){
			camera_dis += 0.1;
			camera_Z = camera_dis * cos(camera_angle);
			camera_X = camera_dis * sin(camera_angle);
			}
		if(key == '-'){
			camera_dis -= 0.1;
			camera_Z = camera_dis * cos(camera_angle);
			camera_X = camera_dis * sin(camera_angle);
		}
		glutPostRedisplay();
	}
	else exit(0);
}

void mySpecialKeyboard(int key, int x, int y){
	if(key != GLUT_KEY_UP && key != GLUT_KEY_DOWN && key != GLUT_KEY_LEFT && key != GLUT_KEY_RIGHT){
		return;
	}
	if(key == GLUT_KEY_RIGHT){
		camera_angle += 0.1;
		if(camera_angle > 2*3.1415926)
			camera_angle -= 2*3.1415926;
	}
	else if(key == GLUT_KEY_LEFT){
		camera_angle -= 0.1;
		if(camera_angle < -2*3.1415926)
			camera_angle += 2*3.1415926;
	}
	else if(key == GLUT_KEY_UP)
		camera_height += 0.1;
	else if(key == GLUT_KEY_DOWN)
		camera_height -= 0.1;
	camera_Z = camera_dis * cos(camera_angle);
	camera_X = camera_dis * sin(camera_angle);
	camera_Y = camera_height;
	glutPostRedisplay();
}

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(4, 0, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 4, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 4);
	glEnd();
}


void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);

	glViewport(0, 0, screenWidth, screenHeight);
	// static things here
	
	drawAxis();
	
	glRotatef(angle_y, 0, 1, 0);
	glRotatef(angle_z, 0, 0, 1);

	

	// moving things here
	obj.draw_object(isWire);
	glFlush();
    glutSwapBuffers();
	
}


void myInit()
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
	glFrustum(-1.5, 1.5, -0.8, 0.8, 1, 100000);
	GLfloat	lightDiffuse[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat	lightSpecular[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat	lightAmbient[]={0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat 	light_position1[]={6.0f, 6.0f, 6.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 


	GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat position1[] = { -10.0, 10.0, -10.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1); 

}

int main(int argc, _TCHAR* argv[])
{
	cout << "1, 2     :  Xoay ban quay xung quanh truc Y cuc bo\n";
	cout << "3, 4     :  Xoay ban quay xung quanh truc X cuc bo\n";
	cout << "5, 6     :  Xoay tay quay\n";
	cout << "W, w  :  Chuyen doi qua lai giua che do khung day va to mau\n";
	cout << "V, v  :  Chuyen doi qua lai giua che do 2D va 3D\n";
	cout << "+   : Tang khoang cach camera\n";
	cout << "-   : Giam khoang cach camera\n";
	cout << "up arrow  : Tang chieu cao camera\n";
	cout << "down arrow: Giam chieu cao camera\n";
	cout << "<-        : Quay camera theo chieu kim dong ho\n";
	cout << "->        : Quay camera nguoc chieu kim dong ho";

	camera_Z = camera_dis * cos(camera_angle);
	camera_X = camera_dis * sin(camera_angle);
	camera_Y = camera_height;
	lookAt_X = 0;
	lookAt_Y = 0;
	lookAt_Z = 0;
	rotate = 0;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab 2"); // open the screen window
	myInit();
    glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutMainLoop();
	return 0;
}

