all: project

project: tourist.o bus.o Group.o Graph.o interface.o main.o
	g++ -o project main.o tourist.o bus.o Group.o Graph.o interface.o

main.o: main.cpp
	g++ -o main.o main.cpp -c -Wall -Werror -Wextra

tourist.o: tourist.cpp
	g++ -o tourist.o tourist.cpp -c -Wall -Werror -Wextra

bus.o: bus.cpp
	g++ -o bus.o bus.cpp -c -Wall -Werror -Wextra

Group.o: Group.cpp
	g++ -o Group.o Group.cpp -c -Wall -Werror -Wextra

Graph.o: Graph.cpp
	g++ -o Graph.o Graph.cpp -c -Wall -Werror -Wextra

interface.o: interface.cpp
	g++ -o interface.o interface.cpp -c -Wall -Werror -Wextra

clean:
	del -rf *.o *~ project.exe