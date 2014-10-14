convexhull:polygon.o set_of_3d_points.o edgelist.o poly_rotation.o
	g++ polygon.o set_of_3d_points.o edgelist.o poly_rotation.o -lglut -o convexhull

polygon.o:polygon.cpp polygon.h
	g++ -c polygon.cpp polygon.h

poly_rotation.o:poly_rotation.cpp poly_rotation.h
	g++ -c poly_rotation.cpp 

edgelist.o:edgelist.cpp edgelist.h
	g++ -c edgelist.cpp 

set_of_3d_points.o:set_of_3d_points.cpp set_of_3d_points.h
	g++ -c set_of_3d_points.cpp

clean: 
	rm *.o
