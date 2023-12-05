all: tests run

solution: 05.c
	cc 05.c -Wall -Wextra -o solution

run: solution
	./solution input.txt
	# ./solution input.txt 2

tests: solution
	./solution example.txt
	# ./solution example.txt 2

check: cppcheck pvs-studio

cppcheck: 05.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 05.c
	cc -E 05.c -o 05.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 05.c --i-file 05.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
