﻿all: project

project: tourist.o bus.o Group.o Graph.o interface.o graphviewer.o connection.o TouristOrganizer.o main.o
	g++ -o project main.o tourist.o bus.o Group.o Graph.o graphviewer.o connection.o interface.o TouristOrganizer.o

main.o: main.cpp
	g++ -o main.o main.cpp -c -Wall -Wextra -lws2_32

tourist.o: tourist.cpp
	g++ -o tourist.o tourist.cpp -c -Wall -Wextra -lws2_32

bus.o: bus.cpp
	g++ -o bus.o bus.cpp -c -Wall -Wextra -lws2_32

Group.o: Group.cpp
	g++ -o Group.o Group.cpp -c -Wall -Wextra -lws2_32

Graph.o: Graph.cpp
	g++ -o Graph.o Graph.cpp -c -Wall -Wextra -lws2_32

interface.o: interface.cpp
	g++ -o interface.o interface.cpp -c -Wall -Wextra -lws2_32

graphviewer.o: graphviewer.cpp 
	g++ -o graphviewer.o graphviewer.cpp  -c -Wall -Wextra -lws2_32

connection.o: connection.cpp
	g++ -o connection.o connection.cpp -c -Wall -Wextra -lws2_32

TouristOrganizer.o: TouristOrganizer.cpp
	g++ -o TouristOrganizer.o TouristOrganizer.cpp -c -Wall -Wextra -lws2_32


clean:
	del -rf *.o *~ project.exe
