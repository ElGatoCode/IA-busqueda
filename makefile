CPP=g++

FLAGS=-g -std=c++11


################################################


bin/search: bin/Board.o bin/Node.o bin/Finder.o src/search.cpp include/Matrix.hpp
	$(CPP) $(FLAGS) src/search.cpp bin/Board.o bin/Node.o bin/Finder.o -o bin/search

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

