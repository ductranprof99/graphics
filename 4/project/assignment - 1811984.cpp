/*
* 	Bai tap lon Do Hoa May Tinh
*	Ten: 	Tran Dinh Duc
* 	MSSV:	1811984
* 	Lop:	L01
*/


#include <math.h>
#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

using namespace std;

int		screenWidth = 900;
int		screenHeight= 600;
#define PI 3.14159265358979323846
#define	COLORNUM		14



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



class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	void set(Point3 &p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	void shift(float dx, float dy, float dz);
};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}
	void set(Color3 &c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}
};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy)
	{
		x = xx;
		y = yy;
	} // constructor 2
	void set(float xx, float yy)
	{
		x = xx;
		y = yy;
	}
	float getX() { return x; }
	float getY() { return y; }
	void draw()
	{
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}

private:
	float x, y;
};
class IntRect
{
public:
	IntRect()
	{
		l = 0;
		r = 100;
		b = 0;
		t = 100;
	} // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void draw()
	{
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int getWidth() { return (r - l); }
	int getHeight() { return (t - b); }

private:
	int l, r, b, t;
};

class RealRect
{
public:
	RealRect()
	{
		l = 0;
		r = 100;
		b = 0;
		t = 100;
	} // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	float getWidth() { return (r - l); }
	float getHeight() { return (t - b); }
	void draw()
	{
		glRectf(l, b, r, t);
		glFlush();
	}; // draw this rectangle using OpenGL
private:
	float l, r, b, t;
};

class Vector3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	void set(Vector3 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	void flip()
	{
		x = -x;
		y = -y;
		z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	Vector3(Vector3 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};


Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x*b.x + y*b.y + z*b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x*x + y*y + z*z);
	x = x/temp;
	y = y/temp;
	z = z/temp;
}

void Point3::shift(float dx, float dy, float dz){
		x += dx;
		y += dy;
		z += dz;
}



class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	Vector3		facenorm;
	
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}

	void setVerts(int vertexes){
		nVerts = vertexes;
		vert = new VertexID[nVerts];
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt;
	
	int		numFaces;
	Face*		face;
public:
	Mesh()
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
	void SetColor(int colorIdx);
	
	void Move_object(float x_move, float y_move, float z_move);
	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateBox(float width, float height, float depth);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateShape1(float gap, float height_foot, float height_head, float radius);
	void CreateShape2(float first_width, float second_width,float first_length, float second_length,float radius, float height, float shift_circle);

	void CreateShape3(float width, float length, float height);
	
	
	void CalculateFacesNorm();
	void Draw();
	void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness);
};



class Assignment_object
{
public:
	Mesh* total_object;
	int numObjs = 8;
	float x_angle;
	float y_angle;
	float z_angle;
	float object_2_x,object_2_z;
	float current_angle_rtt;
	float max_amplitude,current_sin_amplitude,current_cos_amplitude;
	Assignment_object(){
		x_angle = 0;
		y_angle = 0;
		z_angle = 0;
		current_angle_rtt = 0;
		object_2_x = 0, object_2_z = -0.85;
		total_object = new Mesh[8];
		max_amplitude = 1.75;
		current_sin_amplitude = -1.75;
		current_cos_amplitude = 0;
		
		total_object[0].CreateShape1(0.4,0.3,0.4,2.5);
		total_object[1].CreateShape2(0.6,0.42,0.8,1.9,0.2,0.2,0.9);
		total_object[1].Move_object(object_2_x,0.35,object_2_z);
		total_object[2].CreateShape3(0.5,0.8,0.25);
		total_object[2].Move_object(0,0.55,-0.4);
		total_object[3].CreateCylinder(20,0.31,0.15);
		for (int i = 0; i < 3; i+=2)
		{
			total_object[4+i].CreateCylinder(20, 0.23,0.15);
			total_object[5+i].CreateBox(0.4,0.2,0.4);
		}
		total_object[3].Move_object(0,0.67,-0.82);
		total_object[4].Move_object(0,0.45,current_sin_amplitude);
		total_object[6].Move_object(current_cos_amplitude,0.45,0);
		total_object[5].Move_object(0,0.25,current_sin_amplitude);
		total_object[7].Move_object(current_cos_amplitude,0.25,0);
		for (int i = 0; i < 8; i++)
		{
			total_object[i].CalculateFacesNorm();
		}
		
	}
	~Assignment_object(){
		delete[] total_object;
	}
	void moving_object_location(float x_a,float y_a,float z_a);
	void rotate_object(float additional_angle);
	void draw_object(bool);
};


Assignment_object obj;


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {0.90, 0.90, 0.90}};





void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts=nSegment*2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2*PI/nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight/2, 0);
	for(i = 0; i<nSegment; i++)
	{
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fHeight/2;
		pt[i+1].set(x, y, z);

		y = -fHeight/2;
		pt[i +1 + nSegment].set(x, y, z);
	}
	pt[numVerts-1].set(0, -fHeight/2, 0);

	numFaces= nSegment*3;
	face = new Face[numFaces];

	idx = 0;
	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		
		face[idx].vert[0].vertIndex = i+1;
		if(i <nSegment - 1)
			face[idx].vert[1].vertIndex = i+2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if(i < nSegment -1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}

void Mesh::CreateShape1(float gap, float height_foot, float height_head,float claudius)
{
	
	float fRadius = claudius;
	
	// phan dinh
	int headSegment_1_4 = 12;
	int numfaces_of_quaters = 16;
	int each_part_numVert = 28;
	int head_numVerts = 112;
	int head_totalFace = numfaces_of_quaters*4;
	Face * head_faces = new Face[(headSegment_1_4+4)*4];
	Point3 * head_pt = new Point3[head_numVerts];
	float alpha = asin(gap/(2*fRadius));
	float head_angle = ((PI/2)-(2*alpha))/headSegment_1_4;
	float center_coord = gap/2;
	head_pt[0].set(center_coord, (height_foot+height_head)/2, center_coord);
	head_pt[14].set(center_coord, height_foot/2, center_coord);
	head_pt[28].set(-center_coord, (height_foot+height_head)/2, center_coord);
	head_pt[42].set(-center_coord, height_foot/2, center_coord);
	head_pt[56].set(-center_coord, (height_foot+height_head)/2, -center_coord);
	head_pt[70].set(-center_coord, height_foot/2, -center_coord);
	head_pt[84].set(center_coord, (height_foot+height_head)/2, -center_coord);
	head_pt[98].set(center_coord, height_foot/2, -center_coord);
	int current_vertex_quarter = 0;
	int current_face = 0;
	
	for (; current_vertex_quarter < 4; current_vertex_quarter++)
	{
		float additional_angle = current_vertex_quarter*PI/2 + alpha;
		int base_index = current_vertex_quarter*each_part_numVert;
		for (int i = base_index+1; i < base_index+14; i++)
		{
			float x_coord = fRadius*cos(additional_angle+head_angle*(i-current_vertex_quarter*each_part_numVert-1));
			float z_coord = fRadius*sin(additional_angle+head_angle*(i-current_vertex_quarter*each_part_numVert-1));
			float y_coord = (height_foot+height_head)/2;
			head_pt[i].set(x_coord, y_coord, z_coord);
			y_coord = height_foot/2;
			head_pt[i+each_part_numVert/2].set(x_coord, y_coord, z_coord);
			
		}
		head_faces[current_face].setVerts(each_part_numVert/2);
		head_faces[current_face+1].setVerts(each_part_numVert/2);
		for (int j = base_index; j < base_index + each_part_numVert/2; j++)
		{

			head_faces[current_face].vert[j-base_index].vertIndex = j;
			head_faces[current_face+1].vert[j-base_index].vertIndex = j+each_part_numVert/2;
		}
		current_face += 2;
		for (int j = base_index; j < base_index + each_part_numVert/2; j++)
		{
			
			head_faces[current_face].setVerts(4);
			head_faces[current_face].vert[0].vertIndex = j;
			if (j < base_index + each_part_numVert/2 - 1)
				head_faces[current_face].vert[1].vertIndex = j+1;
			else
				head_faces[current_face].vert[1].vertIndex = base_index;
			head_faces[current_face].vert[2].vertIndex = head_faces[current_face].vert[1].vertIndex + each_part_numVert/2;
			head_faces[current_face].vert[3].vertIndex = head_faces[current_face].vert[0].vertIndex + each_part_numVert/2;
			current_face++;
		}
	}

	
	// phan de
	int footSegment = 10*4;
	int foot_numFaces = footSegment+2;
	// face mat la 0, face day la foot numFaces - 1
	int foot_numVerts=footSegment*2 + 2;
	Face* foot_faces = new Face[foot_numFaces];
	Point3 * foot_pt = new Point3[foot_numVerts];
	
	int		i;
	int		idx;
	float	fAngle = 2*PI/footSegment;
	float	x, y, z;
	foot_pt[0].set(0, height_foot/2, 0);
	//  tim dinh thong qua segment
	// 2 dinh : 0 va dinh cuoi (numverts - 1) bo
	for(i = 0; i<footSegment; i++)
	{
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = height_foot/2;
		foot_pt[i+1].set(x, y, z);

		y = -height_foot/2;
		foot_pt[i +1 + footSegment].set(x, y, z);
	}
	foot_pt[foot_numVerts-1].set(0, -height_foot/2, 0);

	// co foot_segment + 2 (dau va duoi cua cylinder) mat (face)
	
	idx = 0;
	foot_faces[idx].nVerts = footSegment;
	foot_faces[foot_numFaces-1].nVerts = footSegment;
	foot_faces[idx].vert = new VertexID[footSegment];
	foot_faces[foot_numFaces-1].vert = new VertexID[footSegment];
	for(i = 0; i<footSegment; i++)
	{
		foot_faces[idx].vert[i].vertIndex = head_numVerts+i+1;
		foot_faces[foot_numFaces-1].vert[i].vertIndex = head_numVerts+i+1+footSegment;
	}
	idx++;
	for(i = 0; i<footSegment; i++)
	{
		foot_faces[idx].nVerts = 4;
		foot_faces[idx].vert = new VertexID[foot_faces[idx].nVerts];
		
		foot_faces[idx].vert[0].vertIndex = head_numVerts+i+1;
		if(i <footSegment - 1)
			foot_faces[idx].vert[1].vertIndex = head_numVerts+i+2;
		else
			foot_faces[idx].vert[1].vertIndex = head_numVerts+1;
		foot_faces[idx].vert[2].vertIndex = foot_faces[idx].vert[1].vertIndex + footSegment;
		foot_faces[idx].vert[3].vertIndex = foot_faces[idx].vert[0].vertIndex + footSegment;

		idx++;
	}
	// face = foot_faces;
	// numFaces = foot_numFaces;
	// numVerts = foot_numVerts;
	// pt = foot_pt;
	face = new Face[foot_numFaces+head_totalFace];
	pt = new Point3[foot_numVerts+head_numVerts];
	numVerts = foot_numVerts+head_numVerts;  // head_numVerts is the number of vertices of the head
	numFaces = foot_numFaces+head_totalFace;
	for (int i = 0; i < head_numVerts; i++)
	{
		pt[i] = head_pt[i];
	}	
	for (int i = 0; i < foot_numVerts; i++)
	{
		pt[i+head_numVerts] = foot_pt[i];
	}
	for (int i = 0; i < head_totalFace; i++)
	{
		face[i] = head_faces[i];
	}
	for (int i = 0; i < foot_numFaces; i++)
	{
		face[i+head_totalFace] = foot_faces[i];
	}
}

void Mesh::CreateBox(float width, float height, float depth)
{
	int i;
	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-width/2, height/2, depth/2);
	pt[1].set(width/2, height/2, depth/2);
	pt[2].set(width/2, height/2, -depth/2);
	pt[3].set(-width/2, height/2, -depth/2);
	pt[4].set(-width/2, -height/2, depth/2);
	pt[5].set( width/2, -height/2, depth/2);
	pt[6].set( width/2, -height/2, -depth/2);
	pt[7].set(-width/2, -height/2, -depth/2);

	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;
}


void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateShape2(float first_width, float second_width,float first_length, float second_length,float radius, float height, float shift_z){
	int numofHalfCir = 20;
	int halfVert = 46;
	numVerts = 92;
	pt = new Point3[numVerts];
	numFaces = 48;
	face = new Face[numFaces];

	int i = 2;
	float alpha = PI/9.0;
	float fAngle_half1 = (PI-2.0*alpha) / numofHalfCir;
	float x_axis_C = first_width/2; // -0.5 is x axis of C1
	float z_axis_C = first_length/2; // -1 is z axis of D
	float x_axis_B = second_width/2; // -2.0 is x axis of B1
	float z_axis_B = second_length/2; // and its the radius of the half circle
	pt[0].set(x_axis_C, height, z_axis_C);  // first point is C
	pt[1].set(x_axis_B, height, z_axis_B);
	for (int j = 0; j < numofHalfCir-1; j++)
	{
		/* code */
		float	x_axis_of_point = radius * cos(alpha+fAngle_half1*(j+1));
		float	z_axis_of_point = radius * sin(alpha+fAngle_half1*(j+1));
		pt[i].set(x_axis_of_point, height, z_axis_of_point);
		pt[i].shift(0,0,shift_z);
		i++;
	}
	pt[i].set(-x_axis_B, height, z_axis_B);
	i++;
	pt[i].set(-x_axis_C, height, z_axis_C);
	i++;
	pt[i].set(-x_axis_C, height, -z_axis_C);
	i++;
	pt[i].set(-x_axis_B, height, -z_axis_B);
	i++;
	for (int j = 0; j < numofHalfCir-1; j++)
	{
		/* code */
		float	x_axis_of_point = radius * cos(alpha+PI+fAngle_half1*(j+1));
		float	z_axis_of_point = radius * sin(alpha+PI+fAngle_half1*(j+1));
		pt[i].set(x_axis_of_point, height, z_axis_of_point);
		pt[i].shift(0,0,-shift_z);
		i++;
	}

	pt[i].set(x_axis_B, height, -z_axis_B);
	i++;
	pt[i].set(x_axis_C, height, -z_axis_C);
	for(int count_vert = 0; count_vert < halfVert; count_vert++){
		pt[count_vert+halfVert] = Point3(pt[count_vert].x, 0, pt[count_vert].z);
	}
	
	int idx = 1;
	face[0].nVerts = halfVert;
	face[numFaces-1].nVerts = halfVert;
	face[0].vert = new VertexID[face[0].nVerts ];
	face[numFaces-1].vert = new VertexID[face[numFaces-1].nVerts ];
	for (int j=0; j<halfVert; j++)
	{
		face[0].vert[j].vertIndex = j;
		face[numFaces-1].vert[j].vertIndex = j+halfVert;
	}

	for (int j = 0; j < halfVert; j++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = j;
		if (j == halfVert-1)
			face[idx].vert[1].vertIndex = 0;
		else
			face[idx].vert[1].vertIndex = j+1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex+halfVert;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex+halfVert;
		idx++;
	}
	
}

void Mesh::CreateShape3(float width, float length, float height){
	numVerts = 58;
	pt = new Point3[numVerts];
	numFaces = 34;
	face = new Face[numFaces];
	// first 6 coordinate
	int bee_segs = 6;
	float angle_seg = 2*PI/bee_segs;
	float half_circle_seg = PI/20;
	int i = 0;
	float radius = 0.5 * width;
	for (i=i; i < 6; i++)
	{
		float x_axis = radius * cos(angle_seg*i);
		float z_axis = radius * sin(angle_seg*i);
		pt[i].set(x_axis, height*2, z_axis+(length/2.0));
		pt[i+6].set(x_axis, height, z_axis+(length/2.0));
	}
	i+=6;
	int special_index[8] = {6,7,8,9,12,13,14,15};
	for (i=i; i < 16; i++)
	{
		float x_axis = radius * cos(angle_seg*i);
		float z_axis = radius * sin(angle_seg*i);
		pt[i].set(x_axis, 0, z_axis+(length/2.0));
	}
	i = 16;
	int idx = 0;
	for (i=i; i < 37; i++)
	{
		float x_axis = radius *  cos(PI+half_circle_seg*idx);
		float z_axis = radius * sin(PI+half_circle_seg*idx);
		pt[i].set(x_axis, height, z_axis-(length/2.0));
		pt[i+21].set(x_axis, 0, z_axis-(length/2.0));
		idx++;
	}
	face[0].setVerts(6);
	for (int j = 0; j < 6; j++)
	{
		face[0].vert[j].vertIndex = j;
	}
	int face_counter = 1;
	int temp_counter = 0;
	for (face_counter=face_counter; face_counter < 7; face_counter++)
	{
		face[face_counter].setVerts(4);
		face[face_counter].vert[0].vertIndex = temp_counter;
		if (temp_counter == 5)
			face[face_counter].vert[1].vertIndex = 0;
		else
			face[face_counter].vert[1].vertIndex = temp_counter+1;
		face[face_counter].vert[2].vertIndex = face[face_counter].vert[1].vertIndex+ 6;
		face[face_counter].vert[3].vertIndex = face[face_counter].vert[0].vertIndex + 6;
		temp_counter++;
	}
	for (int j = 6; j < 9;j++){
		face[face_counter].setVerts(4);
		face[face_counter].vert[0].vertIndex = j;
		face[face_counter].vert[1].vertIndex = j+1;
		face[face_counter].vert[2].vertIndex = face[face_counter].vert[1].vertIndex+ 6;
		face[face_counter].vert[3].vertIndex = face[face_counter].vert[0].vertIndex + 6;
		face_counter++;
	}
	face_counter = 10;
	face[face_counter].setVerts(25);
	face[face_counter+1].setVerts(25);
	for (int j = 0; j < 25; j++)
	{
		if(j > 3){
			face[face_counter].vert[j].vertIndex = 12+j;
			face[face_counter+1].vert[j].vertIndex = face[face_counter].vert[j].vertIndex+21;
		}
		else
		{
			face[face_counter].vert[j].vertIndex = special_index[j];
			face[face_counter+1].vert[j].vertIndex = special_index[j+4];
		}
		
	}	
	face_counter+=2;
	face[face_counter].setVerts(4);
	face[face_counter].vert[0].vertIndex = 9;
	face[face_counter].vert[1].vertIndex = 16;
	face[face_counter].vert[2].vertIndex = 37;
	face[face_counter].vert[3].vertIndex = 15;
	face_counter++;
	face[face_counter].setVerts(4);
	face[face_counter].vert[0].vertIndex = 6;
	face[face_counter].vert[1].vertIndex = 36;
	face[face_counter].vert[2].vertIndex = 57;
	face[face_counter].vert[3].vertIndex = 12;
	face_counter++;
	for (int j = 16; j < 36; j++)
	{
		face[face_counter].setVerts(4);
		face[face_counter].vert[0].vertIndex = j;
		face[face_counter].vert[1].vertIndex = j+1;
		face[face_counter].vert[2].vertIndex = face[face_counter].vert[1].vertIndex+21;
		face[face_counter].vert[3].vertIndex = face[face_counter].vert[0].vertIndex + 21;
		face_counter++;
	}
}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}


void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}
void Mesh::CalculateFacesNorm()
{
	for (int f = 0; f < numFaces; f++)
	{
		float mx = 0, my = 0, mz = 0;
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int next = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
			mx += (pt[iv].y - pt[next].y) * (pt[iv].z + pt[next].z);
			my += (pt[iv].z - pt[next].z) * (pt[iv].x + pt[next].x);
			mz += (pt[iv].x - pt[next].x) * (pt[iv].y + pt[next].y);
		}
		face[f].facenorm.set(mx, my, mz);
		face[f].facenorm.normalize();
	}
}

// To mau cho doi tuong (Lab 5)
void Mesh::Draw()
{
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

// Thiet lap vat lieu cho doi tuong (Lab 5)
void Mesh::setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

void Mesh::Move_object(float _x, float _y, float _z)
{
	for (int i = 0; i < numVerts; i++)
	{
		pt[i].x += _x;
		pt[i].y += _y;
		pt[i].z += _z;
	}
}

void Mesh::SetColor(int colorIdx){
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Assignment_object::moving_object_location(float x_a,float y_a,float z_a){
	x_angle += x_a;
	y_angle += y_a;
	z_angle += z_a;
	for (int i = 0; i < numObjs; i++){
		total_object[i].Move_object(x_a, y_a, z_a);
	}
}

void Assignment_object::draw_object(bool drawWire){
	GLfloat shininess = 30.0;
	glPushMatrix();
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	total_object[0].setupMaterial(ambient, diffuse, specular, shininess);
	if (drawWire)
		total_object[0].Draw();
	else
		total_object[0].Draw();

	glPopMatrix();


	glPushMatrix();
	GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse1[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
	total_object[1].setupMaterial(ambient1, diffuse1, specular1, shininess);
	if (drawWire)
		total_object[1].Draw();
	else
		total_object[1].Draw();

	glPopMatrix();


	glPushMatrix();
	GLfloat ambient2[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse2[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat specular2[] = { 1.0, 1.0, 1.0, 1.0 };
	total_object[2].setupMaterial(ambient2, diffuse2, specular2, shininess);
	if (drawWire)
		total_object[2].Draw();
	else
		total_object[2].Draw();

	glPopMatrix();

	glPushMatrix();
	GLfloat ambient3[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse3[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular3[] = { 1.0, 1.0, 1.0, 1.0 };
	total_object[3].setupMaterial(ambient3, diffuse3, specular3, shininess);
	total_object[4].setupMaterial(ambient3, diffuse3, specular3, shininess);
	total_object[6].setupMaterial(ambient3, diffuse3, specular3, shininess);
	if (drawWire){
		total_object[3].Draw();
		total_object[4].Draw();
		total_object[6].Draw();
	}
	else{
		total_object[3].Draw();
		total_object[4].Draw();
		total_object[6].Draw();
	}
	glPopMatrix();

	glPushMatrix();
	GLfloat ambient4[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse4[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat specular4[] = { 1.0, 1.0, 1.0, 1.0 };
	total_object[5].setupMaterial(ambient4, diffuse4, specular4, shininess);
	total_object[7].setupMaterial(ambient4, diffuse4, specular4, shininess);
	if (drawWire){
		total_object[5].Draw();
		total_object[7].Draw();
	}
	else{
		total_object[5].Draw();
		total_object[7].Draw();
	}
	glPopMatrix();

}



void Assignment_object::rotate_object(float additional_angle){
	// truc 1 xoay theo Oy
	float temp_x, temp_z;
	for (int i = 0; i < total_object[2].numVerts; i++)
	{
		temp_x = total_object[2].pt[i].x;
		temp_z = total_object[2].pt[i].z;
		total_object[2].pt[i].x = temp_x * cos(additional_angle) + temp_z* sin(additional_angle);
		total_object[2].pt[i].z = - temp_x* sin(additional_angle) + temp_z* cos(additional_angle);
	}
	
	// truc 2 xoay theo Oy co bien doi vi tri
	// dua truc trung gian ve toa do 0
	total_object[1].Move_object(-object_2_x,0,-object_2_z);
	for (int i = 0; i < total_object[1].numVerts; i++)
	{
		temp_x = total_object[1].pt[i].x;
		temp_z = total_object[1].pt[i].z;
		total_object[1].pt[i].x = temp_x * cos(additional_angle) - temp_z * sin(additional_angle);
		total_object[1].pt[i].z = temp_x * sin(additional_angle) + temp_z * cos(additional_angle);
	}
	// xoay shift theo truc Oxz
	temp_x = object_2_x;
	temp_z = object_2_z;
	object_2_x = temp_x* cos(-additional_angle) - temp_z* sin(-additional_angle);
	object_2_z = temp_x* sin(-additional_angle) + temp_z* cos(-additional_angle);
	// dua doi tuong 2 ve vi tri moi
	total_object[1].Move_object(object_2_x,0,object_2_z);

	for (int i = 0; i < total_object[3].numVerts; i++)
	{
		temp_x = total_object[3].pt[i].x;
		temp_z = total_object[3].pt[i].z;
		total_object[3].pt[i].x = temp_x * cos(additional_angle) + temp_z * sin(additional_angle);
		total_object[3].pt[i].z = -temp_x * sin(additional_angle) + temp_z * cos(additional_angle);
	}
	current_angle_rtt += additional_angle;
	if(current_angle_rtt > 3.14*2){
		current_angle_rtt -= 3.14*2;
	}else if(current_angle_rtt < -3.14*2){
		current_angle_rtt += 3.14*2;
	}
	float new_current_amplitude ;
	new_current_amplitude = max_amplitude * sin((3.0*3.14159/2.0)+current_angle_rtt);
	total_object[4].Move_object(0,0,-current_sin_amplitude+new_current_amplitude);
	total_object[5].Move_object(0,0,-current_sin_amplitude+new_current_amplitude);
	current_sin_amplitude = new_current_amplitude;
	new_current_amplitude = max_amplitude * cos((3.0*3.14159/2.0)+current_angle_rtt);
	total_object[6].Move_object(current_cos_amplitude-new_current_amplitude,0,0);
	total_object[7].Move_object(current_cos_amplitude-new_current_amplitude,0,0);
	current_cos_amplitude = new_current_amplitude;
}


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

