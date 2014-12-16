a.out : ./src/DecisionTreeTest.o ./src/DecisionTree.o
	g++ -o a.out ./src/DecisionTree.o ./src/DecisionTreeTest.o

DecisionTreeTest.o: ./src/DecisionTree.h ./src/DecisionTreeTest.cpp
	g++ -c ./src/DecisionTreeTest.cpp
DecisionTree.o : ./src/DecisionTree.h ./src/DecisionTree.cpp
	g++ -c ./src/DecisionTree.cpp
