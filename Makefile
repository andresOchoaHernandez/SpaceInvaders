all: main

main: 
	@g++ -Wall  main.cpp -o game -lncurses
	@gnome-terminal -- ./game;
	
clean:
	@rm game