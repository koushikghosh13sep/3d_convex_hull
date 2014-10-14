#ifndef POINT_H
#define POINT_H
#include<iostream>

using namespace std;

class point_3d{
	int x;
	int y;
	int z;
	public:
	void set_points(int a, int b, int c){  x = a , y = b , z = c ; }
	void show_point() { cout << "(" << x << "," << y << "," << z << ")" << endl; }
	int get_x_coord() {return x;}
	int get_y_coord() {return y;}
	int get_z_coord() {return z;}
};

class point_2d{
	float x;
	float y;
	public:
	void set_points(float a, float b){  x = a , y = b ;}
	void show_point() { cout << "(" << x << "," << y << ")" << endl; }
	float get_x_coord() {return x;} 
	float get_y_coord() {return y;}
};

struct CH_2d_point{
	struct CH_2d_point *prev; 
	float x;
	float y;
	int index;
	struct CH_2d_point *next;
};

typedef struct STACK_POINT{
	point_2d point;
	int index;
}STACK_POINT;

#endif
