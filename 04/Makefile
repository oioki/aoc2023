all: tests run

solution: 04.c
	cc 04.c qsort.c -Wall -Wextra -o solution

run: solution
	./solution input.txt
	./solution input.txt 2

tests: solution
	./solution example.txt
	./solution example.txt 2

check: cppcheck pvs-studio

cppcheck: 04.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 04.c
	cc -E 04.c -o 04.i
	cc -E qsort.c -o qsort.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 04.c --i-file 04.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file qsort.c --i-file qsort.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
