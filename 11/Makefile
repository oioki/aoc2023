all: tests run

solution: 11.c
	cc 11.c -Wall -Wextra -o solution

run: solution
	./solution input.txt 2
	./solution input.txt 1000000

tests: solution
	./solution example.txt 2
	./solution example.txt 10
	./solution example.txt 100

check: cppcheck pvs-studio

cppcheck: 11.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 11.c
	cc -E 11.c -o 11.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 11.c --i-file 11.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
