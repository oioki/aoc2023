all: tests run

solution: 15.c
	cc 15.c -Wall -Wextra -o solution

run: solution
	./solution input.txt 1
	# ./solution input.txt 2

tests: solution
	./solution example.txt 1
	# ./solution example.txt 2

check: cppcheck pvs-studio

cppcheck: 15.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 15.c
	cc -E 15.c -o 15.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 15.c --i-file 15.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
