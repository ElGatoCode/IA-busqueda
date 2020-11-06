CPP=g++

FLAGS=-g -std=c++11


################################################


bin/main: bin/Board.o bin/Node.o bin/Finder.o src/main.cpp include/Matrix.hpp
	$(CPP) $(FLAGS) src/main.cpp bin/Board.o bin/Node.o bin/Finder.o -o bin/main

bin/Board.o: include/Board.hpp src/Board.cpp include/Matrix.hpp 
	$(CPP) -c $(FLAGS) src/Board.cpp -o bin/Board.o

bin/Node.o: include/Node.hpp src/Node.cpp 
	$(CPP) -c $(FLAGS) src/Node.cpp -o bin/Node.o

bin/Finder.o: include/Finder.hpp src/Finder.cpp
	$(CPP) -c $(FLAGS) src/Finder.cpp -o bin/Finder.o


.PHONY:

clean: #Clean all
	rm bin/*

clean-o:
	rm bin/*.o


#################################################

testing/main-tests.o: testing/tests-main.cpp
	$(CPP) -c $(FLAGS) testing/tests-main.cpp -o testing/main-tests.o