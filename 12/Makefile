all: tests run

solution: 12.c
	cc 12.c -Wall -Wextra -o solution

run: solution
	./solution input.txt
#	./solution input.txt 1000000

tests: solution
	./solution example.txt
#	./solution example.txt 10
#	./solution example.txt 100

check: cppcheck pvs-studio

cppcheck: 12.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 12.c
	cc -E 12.c -o 12.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 12.c --i-file 12.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
