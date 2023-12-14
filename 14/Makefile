all: tests run

solution: 14.c
	cc 14.c md5.c -Wall -Wextra -o solution

run: solution
	./solution input.txt
	./solution input.txt 2

tests: solution
	./solution example.txt
	# ./solution example.txt 2

check: cppcheck pvs-studio

cppcheck: 14.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 14.c
	cc -E 14.c -o 14.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 14.c --i-file 14.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
