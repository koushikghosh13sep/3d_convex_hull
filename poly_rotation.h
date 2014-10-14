#ifndef POLY_ROTATION_H
#define POLY_ROTATION_H

void drawPoint(float *);
void drawPolygon(float *, float *);
void gl_display(end_node *,int );
void gl_display(start_node *);
void gl_display(void);
void display2(void);
void spinPolygon();
void mouse(int, int, int, int );
void keyboard(unsigned char, int, int);
void reshape (int, int);
void draw_convex_hull(int);
#endif
