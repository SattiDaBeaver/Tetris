all: compile link

run: all exe

compile: 
	g++ -c main.cpp grid.cpp game.cpp globals.cpp -Isrc/include 

link : 
	g++ main.o game.o grid.o globals.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

exe:
	./main

clean:
	del -f game.o main.exe *.o 
