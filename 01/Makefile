all: tests run

solution: 01.c
	cc 01.c -Wall -Wextra -o solution

run: solution
	./solution input.txt 1
	./solution input.txt 2

tests: solution
	./solution example1.txt
	./solution example2.txt 2

check: cppcheck pvs-studio

cppcheck: 01.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 01.c
	cc -E 01.c -o 01.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --rules-config=../.pvsconfig --source-file *.c --i-file *.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
