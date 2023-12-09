all: tests run

solution: 09.c
	cc 09.c -Wall -Wextra -o solution

run: solution
	./solution input.txt
	# ./solution input.txt 2

tests: solution
	./solution example.txt
	# ./solution example2.txt 2

check: cppcheck pvs-studio

cppcheck: 09.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 09.c
	cc -E 09.c -o 09.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 09.c --i-file 09.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
