all: tests run

solution: 08.c
	cc 08.c -Wall -Wextra -o solution

run: solution
	./solution input.txt
	./solution input.txt 2

tests: solution
	./solution example.txt
	./solution example2.txt 2

check: cppcheck pvs-studio

cppcheck: 08.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 08.c
	cc -E 08.c -o 08.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 08.c --i-file 08.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
