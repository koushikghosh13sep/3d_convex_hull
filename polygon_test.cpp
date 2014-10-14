#include<iostream>
#include<cstdlib>
#include <cmath>
#include "set_of_3d_points.h"
#include "edgelist.h"
#include "poly_rotation.h"
#include "polygon_test.h"
#define pi 3.141593

extern point_3d *set_of_points;
extern point_2d *array_of_2d_points;
extern start_node *start;
using namespace std;

void polygon ::insert_point(float x,float y,int index){
	CH_2d_point *temp;
//	temp = (CH_2d_point*)malloc(sizeof(CH_2d_point));
	temp = new CH_2d_point;
	temp -> x = x;
	temp -> y = y;
	temp -> index = index;

	if(points_head == NULL){
		temp -> next = temp;
		temp -> prev = temp;
		points_head = temp;
	}
	else{
		temp -> prev = points_head -> prev; 
		points_head -> prev -> next = temp;
		temp -> next = points_head;
		points_head -> prev = temp;
	}
}

void polygon :: show_polygon(){
	CH_2d_point *temp;
	temp = points_head;
	do{
//		cout<< temp -> x <<" "<< temp -> y <<"\t\t"<< temp -> index <<" -> "<< temp-> next -> index << endl;
		insert(temp->index,temp->next->index);
		temp = temp -> next;
	}while(temp != points_head);
}
void polygon :: show_polygon1(){
	CH_2d_point *temp;
	temp = points_head;
	do{
//		cout<< temp -> x <<" "<< temp -> y <<"\t\t"<< temp -> index <<" -> "<< temp-> next -> index << endl;
		temp = temp -> next;
	}while(temp != points_head);
}

CH_2d_point* polygon :: find_left_most_point(){
	CH_2d_point *temp;
	CH_2d_point *left;
	left = temp = points_head;	
	do{
		if(left -> x > temp -> x)
			left = temp;
		temp = temp -> next;
	}while(temp != points_head);
	return left;
}	

CH_2d_point* polygon :: find_right_most_point(){
	CH_2d_point *temp;
	CH_2d_point *right;
	right = temp = points_head;	
	do{
		if(right -> x <= temp -> x)
			right = temp;
		temp = temp -> next;
	}while(temp != points_head);
	return right;
}

float cross_product(point_2d p1, point_2d p2, point_2d p3){
	float x1 = p1.get_x_coord();
	float y1 = p1.get_y_coord();
	float x2 = p2.get_x_coord();
	float y2 = p2.get_y_coord();
	float x3 = p3.get_x_coord();
	float y3 = p3.get_y_coord();
	return ((x2-x1)*(y3-y1) - (x3-x1)*(y2-y1));
}
float cross_product(CH_2d_point *p1, CH_2d_point *p2, CH_2d_point *p3){
	float x1 = p1 -> x;
	float y1 = p1 -> y;
	float x2 = p2 -> x;
	float y2 = p2 -> y;
	float x3 = p3 -> x;
	float y3 = p3 -> y;
	return ((x2-x1)*(y3-y1) - (x3-x1)*(y2-y1));
}

void polygon :: merge_polygon (polygon B){
	CH_2d_point *p1 = find_right_most_point();
	CH_2d_point *p2 = B.find_left_most_point();
	
//cout<<"ok";
	while(!(cross_product(p1, p2, p2 -> prev) >= 0 && cross_product(p1, p2, p2 -> next) >= 0 && 
		cross_product(p1, p2, p1 -> prev) >= 0 && cross_product(p1, p2, p1 -> next) >= 0) ) {
		while(!(cross_product(p1, p2, p2 -> prev) >= 0 && cross_product(p1, p2, p2 -> next) >= 0 ) ) {
			p2 = p2 -> prev;
		}	
		while(!(cross_product(p1, p2, p1 -> prev) >= 0 && cross_product(p1, p2, p1 -> next) >= 0 ) ){
			p1 = p1 -> next;
		}
	}	
	CH_2d_point *p_lower = p1;
	CH_2d_point *p_B_lower = p2;

	p1 = find_right_most_point();
	p2 = B.find_left_most_point();

	while(!(cross_product(p1, p2, p2 -> prev) <= 0 && cross_product(p1, p2, p2 -> next) <= 0 &&
		cross_product(p1, p2, p1 -> prev) <= 0 && cross_product(p1, p2, p1 -> next) <= 0) ) {
		while(!(cross_product(p1, p2, p2 -> prev) <= 0 && cross_product(p1, p2, p2 -> next) <= 0) ) {

			p2 = p2 -> next;
		}
		while(!(cross_product(p1, p2, p1 -> prev) <= 0 && cross_product(p1, p2, p1 -> next) <= 0) ) {

			p1 = p1 -> prev;
		}
	}
	CH_2d_point *p_upper = p1;
	CH_2d_point *p_B_upper = p2;
	p_upper -> next = p_B_upper;
	p_B_upper -> prev = p_upper;
	p_B_lower -> next = p_lower;
	p_lower -> prev = p_B_lower;
}

polygon make_hull(int low , int high){
	int count_low , count_up;
	STACK_POINT *upper_stack = new STACK_POINT [high - low + 1];
	upper_stack[0].point = array_of_2d_points[low];
	upper_stack[0].index = low;
	upper_stack[1].point = array_of_2d_points[low+1];
	upper_stack[1].index = low+1;
	count_up = 2;

	for(int i = 2 ; i < high - low + 1 ; i++){

		while(count_up >= 2 && (cross_product(upper_stack[count_up - 2].point,upper_stack[count_up-1].point,array_of_2d_points[low + i]) >= 0 )){
			count_up--;
		}	
		upper_stack[count_up].point = array_of_2d_points[low + i];
		upper_stack[count_up].index = low + i;
		count_up++;
	}
	STACK_POINT *lower_stack = new STACK_POINT [high - low + 1];
	lower_stack[0].point = array_of_2d_points[low];
	lower_stack[0].index = low;
 	lower_stack[1].point = array_of_2d_points[low+1];
 	lower_stack[1].index = low+1;
	count_low = 2;
		
	for(int i = 2 ; i < high - low + 1 ; i++) {

		while(count_low >= 2 && (cross_product(lower_stack[count_low-2].point,lower_stack[count_low - 1].point,array_of_2d_points[low+i]) < 0)){
			count_low--;
		}
		lower_stack[count_low].point = array_of_2d_points[low + i];
		lower_stack[count_low].index = low + i;
		count_low++; 
	}
	
	polygon A;

	for(int i = 0 ; i < count_up ; i++){
		A.insert_point(upper_stack[i].point.get_x_coord(), upper_stack[i].point.get_y_coord(),upper_stack[i].index);
	}
	
	
	if(upper_stack[count_up-2].point.get_x_coord()==lower_stack[count_low-2].point.get_x_coord() && 
		upper_stack[count_up-2].point.get_y_coord()==lower_stack[count_low-2].point.get_y_coord())
		return A;

	for(int i = count_low - 2 ; i > 0 ; i--){
		A.insert_point(lower_stack[i].point.get_x_coord(),lower_stack[i].point.get_y_coord(),lower_stack[i].index);
	}
	return A;	  
}
void perturbation(int low, int high ){
	float x,y,r;
	int i = low;
	for(int i = low; i <= high - 2 ; i++){
		if( (array_of_2d_points[i].get_x_coord()==array_of_2d_points[i+1].get_x_coord()) &&
		    (array_of_2d_points[i+1].get_x_coord() == array_of_2d_points[i+2].get_x_coord()) ) {
			float k = .00001;
			int j = i+1;
//			for(int j = i + 1 ; j < high; j++){
				x = array_of_2d_points[j].get_x_coord();
				y = array_of_2d_points[j].get_y_coord();
//				y = y+2*k; 
				x = x + k;
				array_of_2d_points[j].set_points(x,y);
//				k = k + .00001;
//			}
		}
		if( (array_of_2d_points[i].get_y_coord()==array_of_2d_points[i+1].get_y_coord()) &&
		    (array_of_2d_points[i+1].get_y_coord() == array_of_2d_points[i+2].get_y_coord()) ) {
			float k = .00001;
			int j = i+1;
//			for(int j = i + 1 ; j < high; j++){
				x = array_of_2d_points[j].get_x_coord();
				y = array_of_2d_points[j].get_y_coord();
				y = y+2*k; 
				x = x + k;
				array_of_2d_points[j].set_points(x,y);
//				k = k + .00001;
		}	
	}
}

/*void perturbation(int low, int high){
	float k;
	for(int i = low ; i <= high - 1 ; i++)
		for(int j = i+1,k = 0.00001 ; j <= high ; j++)
				if((array_of_2d_points[i].get_x_coord()==array_of_2d_points[j].get_x_coord())){
					float x = array_of_2d_points[j].get_x_coord();
					float y = array_of_2d_points[j].get_y_coord();
					y = y+2*k; 
					x = x + k;
					array_of_2d_points[j].set_points(x,y);
					k = k + .00001;
				}
		
}*/	

polygon divide_conquer(int low, int high){	
//cout<<"ok";
	if(high - low+1 <= 5){
//		perturbation(low, high);
		polygon con_hull = make_hull(low,high);
		return con_hull;
	}
	else{
		int mid = (low + high) / 2 ;
		polygon A = divide_conquer(low , mid);
		polygon B = divide_conquer(mid + 1 , high);
	
		A.merge_polygon(B);
//		B.del();
		return A;
	}
}

void projection(){
	int no = 200;
	three_d_points p(no);
	p.insert_points();
	p.quicksort(0,no - 1);
cout<<"quick sort\n";
//float i = -89.01;
	for(float i = -89.01; i < 90.0; i+=.01){
//cout<<"make 3d";
		polygon convex_hull;
		float ans,re;
		re = i*(pi/180);
		ans = tan(re);
		p.make_3d_to_2d_points(ans);
//cout<<"make 3d to 2d";
		convex_hull = divide_conquer(0,no - 1);
		convex_hull.show_polygon();
		convex_hull.del();
//		convex_hull.show_polygon1();
//		~convex_hull;
//		cout<<"ok";
//		convex_hull;
	}
//	display(start);
	draw_convex_hull();
//	gl_display();
}
main(){

//	cout << "\nOKKKKKKKKKKK" ;
	projection();
}
