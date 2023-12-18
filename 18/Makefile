all: tests run

solution: 18.c
	cc 18.c -Wall -Wextra -o solution

run: solution
	# ./solution input.txt
	# ./solution input.txt 2

tests: solution
	./solution example.txt
	# ./solution example.txt 2

check: cppcheck pvs-studio

cppcheck: 18.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 18.c
	cc -E 18.c -o 18.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 18.c --i-file 18.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
