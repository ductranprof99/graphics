#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


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
	void CalculateFacesNorm();
	void Draw();
	void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness);
	void SetColor(int colorIdx);
	void Move_object(float x_move, float y_move, float z_move);
	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateBox(float width, float height, float depth);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateShape1(float gap, float height_foot, float height_head, float radius);
	void CreateShape2(float first_width, float second_width,float first_length, float second_length,float radius, float height, float shift_circle);

	void CreateShape3(float width, float length, float height);
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
		GLfloat diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
		GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat shininess = 40.0;
		total_object[0].CreateShape1(0.4,0.3,0.4,2.5);
		total_object[0].SetColor(2);
		total_object[0].setupMaterial(ambient, diffuse, specular, shininess);
		total_object[1].CreateShape2(0.6,0.42,0.8,1.9,0.2,0.2,0.9);
		total_object[1].Move_object(object_2_x,0.35,object_2_z);
		// total_object[1].SetColor(7);
		total_object[2].CreateShape3(0.5,0.8,0.25);
		total_object[2].Move_object(0,0.55,-0.4);
		// total_object[2].SetColor(2);
		total_object[3].CreateCylinder(20,0.31,0.15);
		total_object[3].SetColor(0);
		total_object[3].setupMaterial(ambient, diffuse, specular, shininess);
		for (int i = 0; i < 3; i+=2)
		{
			total_object[4+i].CreateCylinder(20, 0.23,0.15);
			total_object[4+i].setupMaterial(ambient, diffuse, specular, shininess);
			// total_object[4+i].SetColor(0);
			total_object[5+i].CreateBox(0.4,0.2,0.4);
			total_object[5+i].SetColor(1);
		}
		total_object[3].Move_object(0,0.67,-0.82);
		total_object[4].Move_object(0,0.45,current_sin_amplitude);
		total_object[6].Move_object(current_cos_amplitude,0.45,0);
		total_object[5].Move_object(0,0.25,current_sin_amplitude);
		total_object[7].Move_object(current_cos_amplitude,0.25,0);
	}
	void moving_object_location(float x_a,float y_a,float z_a);
	void rotate_object(float additional_angle);
	void draw_object(bool);
};


#endif