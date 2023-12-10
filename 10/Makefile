all: tests run

solution: 10.c
	cc 10.c -Wall -Wextra -o solution

run: solution
	./solution input.txt
	# ./solution input.txt 2

tests: solution
	# ./solution example1.txt
	# ./solution example2.txt

check: cppcheck pvs-studio

cppcheck: 10.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 10.c
	cc -E 10.c -o 10.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 10.c --i-file 10.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
