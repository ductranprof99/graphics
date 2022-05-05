

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

int		screenWidth = 900;
int		screenHeight= 600;
#define PI 3.14159265358979323846

Assignment_object obj;

float camera_angle = 0.0f; // init
float camera_height = 0.0f; // equal object y
float camera_dis = 7.0f;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;
float rotate;

bool		isWire = false;
bool 		camera_y_look_down = false;
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
		if(key == 'w' || key == 'W')
			isWire = !isWire;
		if(key == 'v' || key == 'V')
			camera_y_look_down = !camera_y_look_down;
		if(key == '+' && !camera_y_look_down){
			camera_dis += 0.1;
			camera_Z = camera_dis * cos(camera_angle);
			camera_X = camera_dis * sin(camera_angle);
			}
		if(key == '-'&& !camera_y_look_down){
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
	if(key == GLUT_KEY_RIGHT && !camera_y_look_down){
		camera_angle += 0.1;
		if(camera_angle > 2*3.1415926)
			camera_angle -= 2*3.1415926;
	}
	else if(key == GLUT_KEY_LEFT && !camera_y_look_down){
		camera_angle -= 0.1;
		if(camera_angle < -2*3.1415926)
			camera_angle += 2*3.1415926;
	}
	else if(key == GLUT_KEY_UP && !camera_y_look_down)
		camera_height += 0.1;
	else if(key == GLUT_KEY_DOWN && !camera_y_look_down)
		camera_height -= 0.1;
	camera_Z = camera_dis * cos(camera_angle);
	camera_X = camera_dis * sin(camera_angle);
	camera_Y = camera_height;
	glutPostRedisplay();
}

void rotate_point_60(float &x, float &y, float &z){
	float temp = x;
	x = y * cos(PI/3) - z * sin(PI/3);
	z = temp * sin(PI/3) + z * cos(PI/3);

}

void drawSnow(float x, float y, float z, float R, float alpha)
{
	// glColor4f(0.3, 1.0, 1.0, alpha); this color for another one
	// silver glColor4f(0.75, 0.75, 0.75, alpha);
	// black  glColor4f(0.0, 0.0, 0.0, alpha);
	float R2 = R * 0.6;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glColor4f(0.75, 0.75, 0.75, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x + R, y, z);
	glVertex3f(x +  R2*sin(60 * PI / 180), y, z + R2/2);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.0, 0.0, 0.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x +  R2*sin(60 * PI / 180), y, z + R2/2);
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glEnd();

	// color cyan

	glBegin(GL_TRIANGLES);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R, y, z);
	glVertex3f(x +  R2*sin(60 * PI / 180), y, z + R2/2);
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glEnd();

	glBegin(GL_LINES);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x+ R, y, z);
	glVertex3f(x+ R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glEnd();
	//////////////////////////////////////////////////////////////////////////

	glBegin(GL_TRIANGLES);
	glColor4f(0.75, 0.75, 0.75, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glVertex3f(x, y, z+R2);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.0, 0.0, 0.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z+R2);
	glVertex3f(x - R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glEnd();


	// color cyan

	glBegin(GL_TRIANGLES);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x+ R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glVertex3f(x, y, z+R2);
	glVertex3f(x- R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glEnd();

	glBegin(GL_LINES);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glVertex3f(x - R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glEnd();

	//////////////////////////////////////////////////////////////////////////

	glBegin(GL_TRIANGLES);
	glColor4f(0.75, 0.75, 0.75, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x - R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glVertex3f(x - R2*sin(60 * PI / 180), y, z + R2/2);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor4f(0.0, 0.0, 0.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x - R2*sin(60 * PI / 180), y, z + R2/2);
	glVertex3f(x - R, y, z);
	glEnd();

	// color cyan

	glBegin(GL_TRIANGLES);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x - R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glVertex3f(x - R2*sin(60 * PI / 180), y, z + R2/2);
	glVertex3f(x - R, y, z);
	glEnd();

	glBegin(GL_LINES);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x - R * cos(60 * PI / 180), y, z + R* sin(60 * PI / 180));
	glVertex3f(x - R, y, z);
	glEnd();
	//////////////////////////////////////////////////////////////////////////

	glBegin(GL_TRIANGLES);
	glColor4f(0.75, 0.75, 0.75, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x - R, y, z);
	glVertex3f(x - R2*sin(60 * PI / 180), y, z - R2/2);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor4f(0.0, 0.0, 0.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x - R2*sin(60 * PI / 180), y, z - R2/2);
	glVertex3f(x - R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glEnd();


	// color cyan

	glBegin(GL_TRIANGLES);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x - R, y, z);
	glVertex3f(x - R2*sin(60 * PI / 180), y, z - R2/2);
	glVertex3f(x - R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glEnd();

	glBegin(GL_LINES);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x - R, y, z);
	glVertex3f(x - R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glEnd();

	//////////////////////////////////////////////////////////////////////////

	glBegin(GL_TRIANGLES);
	glColor4f(0.75, 0.75, 0.75, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x - R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glVertex3f(x, y, z - R2);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor4f(0.0, 0.0, 0.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z - R2);
	glVertex3f(x + R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glEnd();

	// color cyan

	glBegin(GL_TRIANGLES);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x - R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glVertex3f(x, y, z - R2);
	glVertex3f(x + R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glEnd();

	glBegin(GL_LINES);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x - R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glVertex3f(x + R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glEnd();

	//////////////////////////////////////////////////////////////////////////

	glBegin(GL_TRIANGLES);
	glColor4f(0.75, 0.75, 0.75, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x + R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glVertex3f(x +  R2*sin(60 * PI / 180), y, z - R2/2);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor4f(0.0, 0.0, 0.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x +  R2*sin(60 * PI / 180), y, z - R2/2);
	glVertex3f(x + R , y, z );
	glEnd();

	// color cyan

	glBegin(GL_TRIANGLES);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glVertex3f(x +  R2*sin(60 * PI / 180), y, z - R2/2);
	glVertex3f(x + R , y, z );
	glEnd();

	glBegin(GL_LINES);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(60 * PI / 180), y, z - R* sin(60 * PI / 180));
	glVertex3f(x + R , y, z );
	glEnd();
	
	
}

void drawSan(float alpha)
{
	float y = -3.5;
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	float d = 0.7, R = d / cos(PI / 6);
	int i = 0;
	for (float x = -50; x < 50; x += R + R * cos(PI / 3))
	{
		float z = (i % 2 == 0) ? -20 : (-20 - d);
		for (; z < 20; z += 2 * d)
			drawSnow(x, y, z, R, alpha);
		i++;
	}
	glEnable(GL_LIGHTING);
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

	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(!camera_y_look_down)
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
	else
		gluLookAt(0, 10, 0, lookAt_X, lookAt_Y, lookAt_Z, 0, 0,-1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, screenWidth, screenHeight);


	// static things here
	drawSan(1.0f);


	glRotatef(angle_y, 0, 1, 0);
	glRotatef(angle_z, 0, 0, 1);


	obj.draw_object(isWire);

	glFlush();
    glutSwapBuffers();
	
}


void myInit()
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	const float ar = (float)screenWidth / (float)screenHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	// glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);


	GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat position1[] = { 4.0, 4.0, -10.0, 0.0 };
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
	glutCreateWindow("Tran Dinh Duc - 1811984"); // open the screen window
	myInit();
    glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutMainLoop();
	return 0;
}

