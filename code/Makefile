all: project

project: main.o tourist.o bus.o Group.o
	g++ -o project main.o tourist.o bus.o Group.o

main.o: main.cpp
	g++ -o main.o main.cpp -c -Wall -Werror -Wextra

tourist.o: tourist.cpp
	g++ -o tourist.o tourist.cpp -c -Wall -Werror -Wextra

bus.o: bus.cpp
	g++ -o bus.o bus.cpp -c -Wall -Werror -Wextra

Group.o: Group.cpp
	g++ -o Group.o Group.cpp -c -Wall -Werror -Wextra

Graph.o: Graph.h
	g++ -o Graph.o Graph.h -c -Wall -Werror -Wextra

clean:
	rm -rf *.o *~ main