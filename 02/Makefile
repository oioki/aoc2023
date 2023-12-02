all: tests run

solution: 02.c
	cc 02.c -Wall -Wextra -o solution

run: solution
	./solution input.txt 12 13 14
	./solution input.txt 12 13 14 2

tests: solution
	./solution example.txt 12 13 14
	./solution example.txt 12 13 14 2

check: cppcheck pvs-studio

cppcheck: 02.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 02.c
	cc -E 02.c -o 02.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file *.c --i-file *.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
