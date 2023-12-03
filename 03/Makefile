all: tests run

solution: 03.c
	cc 03.c -Wall -Wextra -o solution

run: solution
	./solution input.txt
	./solution input.txt 2

tests: solution
	./solution example.txt
	./solution example.txt 2

check: cppcheck pvs-studio

cppcheck: 03.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 03.c
	cc -E 03.c -o 03.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file *.c --i-file *.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
