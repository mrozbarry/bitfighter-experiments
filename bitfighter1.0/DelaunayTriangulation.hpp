
/*
	I kidnapped this from http://www.box2d.org/forum/viewtopic.php?f=6&t=975&p=5800#p5800
	The only changes I've made are converting from the box2d vector type to
	cpVect (chipmunk implementation).
*/

#include <chipmunk/chipmunk.h>

#include <iostream>
#include <cstdlib> // for C qsort 
#include <cmath>
#include <ctime> // for random

#ifndef bitfighter_delaunaytriangulation_hpp
#define bitfighter_delaunaytriangulation_hpp	1

const double EPSILON = 0.000001;

struct ITRIANGLE {
	int p1, p2, p3;
};

struct IEDGE {
	int p1, p2;
};

struct XYZ {
	double x, y;
};


int XYZCompare(const void *v1, const void *v2);

int CircumCircle(double xp, double yp, double x1, double y1, double x2, 
				 double y2, double x3, double y3, double &xc, double &yc, double &r);

int Triangulate(int nv, XYZ pxyz[], ITRIANGLE v[], int &ntri);

int CreateDelaunayTriangulation( cpVect *verts, int n_verts, cpVect *extraPoints, int pointCount, cpVect *triangles);

#endif /* bitfighter_delaunaytriangulation_hpp */
