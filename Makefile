.default: all

all: APT_A2

APT_A2: MainMenu.o Tile.o Node.o LinkedList.o Player.o GameBoard.o main.o 
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -O -c $^

