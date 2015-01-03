a.out : ./src/main.o ./src/Network.o
	g++ -o a.out ./src/main.o ./src/Network.o

main.o: ./src/Network.h ./src/main.cpp
	g++ -c ./src/main.cpp
Network.o : ./src/Network.h ./src/main.cpp
	g++ -c ./src/Network.cpp
