all: tests run

solution: 16.c
	cc 16.c -Wall -Wextra -o solution

run: solution
	./solution input.txt
	./solution input.txt 2

tests: solution
	./solution example.txt
	./solution example.txt 2

check: cppcheck pvs-studio

cppcheck: 16.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 16.c
	cc -E 16.c -o 16.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 16.c --i-file 16.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
