all: tests run

solution: 07.c
	cc 07.c -Wall -Wextra -o solution

run: solution
	./solution input.txt
	./solution input.txt 2

tests: solution
	# ./solution explain.txt
	./solution example.txt
	./solution example.txt 2

check: cppcheck pvs-studio

cppcheck: 07.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 07.c
	cc -E 07.c -o 07.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 07.c --i-file 07.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
