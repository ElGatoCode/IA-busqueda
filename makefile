CPP=g++

FLAGS=-g -std=c++14

OBJS=bin/Board.o bin/Node.o bin/Finder.o bin/cmd_line.o bin/interactive.o
################################################


bin/search: src/search.cpp $(OBJS)
	$(CPP) $(FLAGS) src/search.cpp $(OBJS) -o bin/search

bin/Board.o: include/Board.hpp src/Board.cpp include/Matrix.hpp 
	$(CPP) -c $(FLAGS) src/Board.cpp -o bin/Board.o

bin/Node.o: include/Node.hpp src/Node.cpp 
	$(CPP) -c $(FLAGS) src/Node.cpp -o bin/Node.o

bin/Finder.o: include/Finder.hpp src/Finder.cpp
	$(CPP) -c $(FLAGS) src/Finder.cpp -o bin/Finder.o

bin/cmd_line.o: include/handlers/cmd_line.hpp include/setup.hpp src/handlers/cmd_line.cpp bin/Finder.o
		$(CPP) -c $(FLAGS) src/handlers/cmd_line.cpp -o bin/cmd_line.o

bin/interactive.o: include/handlers/interactive.hpp include/setup.hpp src/handlers/interactive.cpp bin/Finder.o
		$(CPP) -c $(FLAGS) src/handlers/interactive.cpp -o bin/interactive.o


.PHONY:

clean: #Clean all
	rm bin/*

clean-o:
	rm bin/*.o


#################################################

