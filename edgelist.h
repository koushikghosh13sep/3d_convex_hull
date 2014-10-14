#ifndef EDGELIST_H
#define EDGELIST_H

struct end_node{
	int data;
	struct end_node *next;
	end_node(int no){
		data = no;
		next = NULL;
	}
};
struct start_node{
	int data;
	struct end_node *adj_nodes;
	struct start_node *next_start;
	start_node(int first){
		data = first;
		next_start = NULL;
		adj_nodes = NULL;
	}
};

//start_node *start = NULL;

end_node *insert(end_node *, int data);
start_node *insert(start_node *, int, int);
void insert(int, int);

end_node *del(end_node *, int);
start_node *del(start_node *, int , int );
void del(int ,int );
void display(end_node *,int);
void display(start_node *);
#endif
