all: compile link

run: all exe

compile: 
	g++ -c main.cpp grid.cpp game.cpp blocks.cpp block.cpp colors.cpp position.cpp -Isrc/include 

link : 
	g++ main.o game.o grid.o blocks.o block.o position.o colors.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

exe:
	./main

clean:
	del -f game.o main.exe *.o 
