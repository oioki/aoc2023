all: tests run

solution: 19.c
	cc 19.c -Wall -Wextra -o solution

run: solution
	./solution input.txt > 1.c 2>1.h
	cc 1.c -o solution-1
	./solution-1
	# ./solution input.txt 2

tests: solution
	./solution example.txt > 1.c 2>1.h
	cc 1.c -o example-1
	./example-1
	# ./solution example.txt 2

check: cppcheck pvs-studio

cppcheck: 19.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 19.c
	cc -E 19.c -o 19.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 19.c --i-file 19.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
