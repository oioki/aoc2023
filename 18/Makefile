all: tests run

solution1: 18.c
	cc 18.c -Wall -Wextra -o solution1

solution2: 18-2.c
	cc 18-2.c -Wall -Wextra -o solution2

run: solution1 solution2
	./solution1 input.txt
	# ./solution2 input.txt

tests: solution1 solution2
	./solution1 example.txt
	# ./solution2 example.txt

check: cppcheck pvs-studio

cppcheck: 18.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 18.c
	cc -E 18.c -o 18.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 18.c --i-file 18.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
