#ifndef SET_OF_POINTS_H
#define SET_OF_POINTS_H

#include "point.h"
//point_2d *array_of_2d_points;
//point_3d *set_of_points;

class three_d_points{
//	private:
	public:
//	point_3d *set_of_points;
	int size;
	public:

	three_d_points(int);/*	 size = n, set_of_points = new point_3d [size]; 
					  array_of_2d_points = new point_2d [size];
			 	}*/
	int get_size() { return size ; }
	void quicksort(int,int);
	int partition(int,int);
	void insert_points();
	void make_3d_to_2d_points(float);
	
	point_3d get_point_loc(int );// {return set_of_points[loc]; }
};
#endif
