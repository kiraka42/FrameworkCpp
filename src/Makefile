CPP=g++ --std=c++11 -Wall -lsfml-graphics -lsfml-window -lsfml-system

all :  main

main : main.cpp
	$(CPP) Position.cpp Position.h Squares.h Grid.h TwoThousandAndFortyHeightGame.h main.cpp

clean :
	rm *.h.gch game

proper:
	rm *~
