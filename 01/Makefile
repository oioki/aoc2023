all: tests run

solution: 01.c
	cc 01.c -Wall -Wextra -o solution

run: solution
	./solution input.txt 1
	./solution input.txt 2

tests: solution
	./solution example1.txt
	./solution example2.txt 2
