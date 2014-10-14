
#include<iostream>
#include<cstdlib>

#include "edgelist.h"
#include "set_of_3d_points.h"

using namespace std;

start_node *start = NULL;

end_node *insert(end_node *temp_e, int data){
	if(temp_e == NULL)
		temp_e = new end_node(data);
	else{
		if(temp_e -> data == data)
			return temp_e;
		temp_e -> next = insert(temp_e -> next, data);
	}
	return temp_e; 
}
start_node *insert(start_node *temp_s, int data1, int data){
	if(temp_s == NULL){
		temp_s = new start_node(data1);
		temp_s -> adj_nodes = insert(temp_s -> adj_nodes,data);
	}
	else{
		if(temp_s -> data == data1){
			temp_s -> adj_nodes = insert(temp_s -> adj_nodes, data);
			return temp_s;
		}
		temp_s -> next_start = insert( temp_s -> next_start, data1, data);
	}
	return temp_s;
}
void insert(int n1, int n2){
	start = insert(start, n1, n2);
	start = insert(start, n2, n1);
}

end_node *del(end_node *temp_e, int no){
	if(temp_e -> data == no)
		return (temp_e -> next);
	else
		temp_e -> next = del(temp_e -> next, no);
	return temp_e;
}
start_node *del(start_node *temp_s, int n1, int n2){
	if(temp_s -> data == n1){
		temp_s -> adj_nodes = del(temp_s -> adj_nodes,n2);
		if(temp_s -> adj_nodes == NULL)
			temp_s = temp_s -> next_start;
	}
	else
		temp_s -> next_start = del(temp_s -> next_start, n1, n2);
	return temp_s;
}
void del(int n1,int n2){
	start = del(start,n1,n2);
//	start = del(start,n2,n1);
}

void display(end_node *n,int st){
	cout<<st<<"-->";
	for (end_node *temp = n; temp != NULL; temp = temp -> next){
//		cout<<st;
		cout << "\t" << temp -> data;
//		del( temp -> data, st);
	}
	cout<<endl;
}
void display(start_node *n){
	for (start_node *temp = n; temp != NULL; temp = temp -> next_start){
//		cout << temp -> data <<" ---> ";
		display(temp -> adj_nodes, temp -> data);
	}
	cout << endl;
}

/*
void gl_display(end_node *n,int st){
//	cout<<st<<"-->";
	float v1[3];
	float v2[3];

	for (end_node *temp = n; temp != NULL; temp = temp -> next){
//		cout<<st;
//		cout << "\t" << temp -> data<<endl;
//		v1[0] = get_point_loc(st).get_x_coord();
		v1[0] = set_of_points[st].get_x_coord();
		v1[1] = set_of_points[st].get_y_coord();
		v1[2] = set_of_points[st].get_z_coord();
		
		v2[0] = set_of_points[temp->data].get_x_coord();
		v2[1] = set_of_points[temp->data].get_y_coord();
		v2[2] = set_of_points[temp->data].get_z_coord();
		drawPolygon(v1,v2);
		del( temp -> data, st);
	}
	cout<<endl;
}
void gl_display(start_node *n){
	for (start_node *temp = n; temp != NULL; temp = temp -> next_start){
//		cout << temp -> data <<" ---> ";
		gl_display(temp -> adj_nodes, temp -> data);
	}
//	cout << endl;
}
void gl_display(){
	gl_display(start);
}
*/
