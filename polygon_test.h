#ifndef POLYGON_H
#define POLYGON_H
#include "set_of_3d_points.h"
#include "edgelist.h"
#include "poly_rotation.h"
#include<cstdlib>
#include<iostream>

using namespace std;
class polygon{
    	CH_2d_point *points_head;
     	int size;
  	public:
	polygon(){ points_head = NULL;}
/*	~polygon(){
//		if(!points_head) cout << "\nBYE>>>>>>>>";
//		else{	//	cout << "DEST";
		CH_2d_point *last = points_head -> prev; 
//		last -> next = NULL ;
//		points_head -> prev = NULL;
		cout << points_head -> next << " ";
		while(points_head -> next != last){
//		cout << points_head -> next<<" ";
			CH_2d_point *temp;
			temp = points_head;
			points_head = points_head -> next;
//			temp -> next = NULL;
			delete temp;
//			points_head -> prev = NULL;
		}
//		delete temp;
		delete points_head;
//		free( points_head);
//		points_head = NULL;
	}*/

/*	void del(){
		CH_2d_point *last = points_head -> prev; 
		last -> next = NULL ;
		points_head -> prev = NULL;
//		cout << points_head -> next << " ";
		while(points_head -> next != last){
//		cout << points_head -> next<<" ";
			CH_2d_point *temp;
			temp = points_head;
			points_head = points_head -> next;
			temp -> next = NULL;
			temp -> prev = NULL;
			delete temp;
//			points_head -> prev = NULL;
		}
//		delete temp;
		delete points_head;
	}*/
	void del(){
		CH_2d_point *temp = points_head;
		CH_2d_point *temp1 = temp -> next;
		while(temp != temp1){
			temp -> prev -> next = temp1;
			temp1 -> prev = temp -> prev;
			temp -> prev = temp -> next = NULL;
			delete temp;
			points_head = temp = temp1;
			CH_2d_point *x = points_head; 
			temp1 = temp -> next;
		}
		delete temp;
//		delete this;
//		delete points_head ;
	}
	
	void insert_point(float,float,int);
     	void show_polygon();
     	void show_polygon1();
	CH_2d_point* find_left_most_point();
	CH_2d_point* find_right_most_point();
	void merge_polygon (polygon);
	friend polygon divide_conquer(int , int);
	friend polygon make_hull(int,int);
};

float cross_product(point_2d, point_2d, point_2d );
float cross_product(CH_2d_point, CH_2d_point, CH_2d_point);

void perturbation(int, int);
void projection();
#endif
