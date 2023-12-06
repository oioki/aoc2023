all: tests run

solution: 06.c
	cc 06.c -Wall -Wextra -o solution

run: solution
	./solution input.txt
	./solution input2.txt 2

tests: solution
	./solution example.txt
	./solution example2.txt 2

check: cppcheck pvs-studio

cppcheck: 06.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 06.c
	cc -E 06.c -o 06.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 06.c --i-file 06.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
