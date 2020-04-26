.default: all

all: APT_A2

APT_A2: MainMenu.o main.o 
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -O -c $^

