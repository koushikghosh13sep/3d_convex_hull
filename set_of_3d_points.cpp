
#include<iostream>
#include "point.h"
#include "edgelist.h"
#include "set_of_3d_points.h"
using namespace std;


point_2d *array_of_2d_points;
point_3d *set_of_points;

extern point_2d *array_of_2d_points;
extern point_3d *set_of_points;

three_d_points :: three_d_points(int n) {
	size = n, set_of_points = new point_3d [size]; 
	array_of_2d_points = new point_2d [size];
}

point_3d three_d_points::get_point_loc(int loc){
	return set_of_points[loc];
}
void three_d_points :: insert_points(){
	int x, y, z;
	
	for(int i = 0 ; i < size ; i++){
		cin >> x >> y >> z;
		set_of_points[i].set_points(x,y,z);
	}
}
void three_d_points :: make_3d_to_2d_points(float t){
 	for(int i = 0 ; i < size ; i++){
		float x = (float)set_of_points[i].get_x_coord();
		float y = (float)set_of_points[i].get_y_coord();
		float z = (float)set_of_points[i].get_z_coord();
		float a = z- t*y;
		array_of_2d_points[i].set_points(x, a);
	}
}

void three_d_points :: quicksort(int low , int high){
	if(low < high){
		int p = partition(low,high);
		quicksort(low,p-1);
		quicksort(p+1,high);
	}
}

int three_d_points :: partition(int low , int high){
	point_3d pivot = set_of_points[low];
	int i = low , j = high+1;

//cout<<low<<" "<<high<<endl;
	while(i < j){
		do{
			i++;
		}while(i <= high &&  pivot.get_x_coord() >= set_of_points[i].get_x_coord());
//	cout << i ;
		do{
			j--;
		}while(pivot.get_x_coord() <  set_of_points[j].get_x_coord());
//	cout << "                " << j << endl;
		if(i < j){
			point_3d temp =  set_of_points[i];
			set_of_points[i] = set_of_points[j];
			set_of_points[j] = temp;
		}
	}
	point_3d temp = set_of_points[low];
	set_of_points[low] = set_of_points[j];
	set_of_points[j] = temp;
	return j;
}
