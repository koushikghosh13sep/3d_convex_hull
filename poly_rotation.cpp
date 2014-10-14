#include <GL/glut.h>
#include<cstdlib>
#include "point.h"
#include "edgelist.h"
#include "poly_rotation.h"

extern point_3d *set_of_points;
extern point_2d *array_of_2d_points;
extern start_node *start;

float theta[3] = {0.0, 0.0, 0.0};
float delta = 2.0;
GLint axis = 2;
int stop = 1;
int no_of_point;

void drawPoint(float *v){
    	glBegin(GL_POINTS);
		glColor3f(1.0,1.0,0.0);
		glVertex3fv(v);
    	glEnd(); 	
}

void drawPolygon(float *v1, float *v2){

	glBegin(GL_LINES);
		glColor3f(1.0,1.0,1.0);
		glVertex3fv(v1);
		glVertex3fv(v2);
	glEnd();
}

void gl_display(end_node *n,int st){
	float v1[3];
	float v2[3];

	for (end_node *temp = n; temp != NULL; temp = temp -> next){
		v1[0] = set_of_points[st].get_x_coord();
		v1[1] = set_of_points[st].get_y_coord();
		v1[2] = set_of_points[st].get_z_coord();
		
		v2[0] = set_of_points[temp->data].get_x_coord();
		v2[1] = set_of_points[temp->data].get_y_coord();
		v2[2] = set_of_points[temp->data].get_z_coord();
		drawPolygon(v1,v2);
//		del( temp -> data, st);
	}
}
void gl_display(start_node *n){
	for (start_node *temp = n; temp != NULL; temp = temp -> next_start){
		gl_display(temp -> adj_nodes, temp -> data);
	}
}
void gl_display(){
	float v[3];
	for(int i = 0; i < no_of_point; i++){
		v[0] = set_of_points[i].get_x_coord();
		v[1] = set_of_points[i].get_y_coord();
		v[2] = set_of_points[i].get_z_coord();
		drawPoint(v);
	}
	gl_display(start);
}
void display2(void){
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glLoadIdentity();
  	glRotatef(theta[0], 1.0, 0.0, 0.0);
  	glRotatef(theta[1], 0.0, 1.0, 0.0);
  	glRotatef(theta[2], 0.0, 0.0, 1.0);
	gl_display();

	glFlush();
  	glutSwapBuffers();
}


void spinPolygon(){
 	 /* spin cube delta degrees about selected axis */
  	theta[axis] += delta;
  	if (theta[axis] > 360.0) theta[axis] -= 360.0;
  	/* display result */
	system("sleep 0.05");
  	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y){
	if (btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void  keyboard(unsigned char key, int x, int y){
	if  (key=='q' || key == 'Q') exit(0);
	if  (key==' ') {stop = !stop;};
	if  (stop)
		glutIdleFunc(NULL);
	else
		glutIdleFunc(spinPolygon);
}


void reshape (int width, int height){
	/* Called when the window is created, moved or resized */
	glViewport (0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode (GL_PROJECTION); /* Select the projection matrix */
	glLoadIdentity ();             /* Initialise it */
// 	glOrtho(-150.0,150.0, -150.0,150.0, -150.0,150.0); /* The unit cube */
   	glOrtho(-1500.0,1500.0, -1500.0,1500.0, -1500.0,1500.0); /* The unit cube */
   	glMatrixMode (GL_MODELVIEW); /* Select the modelview matrix */
}


void draw_convex_hull(int size){
	int argc = 0;
	char **argv = '\0';
	no_of_point = size;
//	cout << "\nSuvam";
	glutInit (&argc,argv);      /* Initialise OpenGL */
//	init();
	glutInitDisplayMode (GLUT_DOUBLE);
	glutInitWindowSize (1000, 1000);      /* Set the window size */
  	glutInitWindowPosition (1000, 1000); /* Set the window position */
  	glutCreateWindow ("ROTATING POLYGON");    /* Create the window */
  	glutDisplayFunc (display2);   /* Register the "display2" function */
  	glutReshapeFunc (reshape);   /* Register the "reshape" function */
  	glutKeyboardFunc (keyboard); /* Register the "keyboard" function */
  	glutIdleFunc(spinPolygon);   /* Register the "spinPolygon" function */
  	glutMouseFunc(mouse);        /* Register the "mouse" function */
  	glutMainLoop ();             /* Enter the OpenGL main loop */
 }
