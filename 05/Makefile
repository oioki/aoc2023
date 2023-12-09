all: tests run

solution1: 05-1.c
	cc 05-1.c -Wall -Wextra -o solution1

solution2: 05-2.c
	cc 05-2.c -Wall -Wextra -o solution2

run: solution1 solution2
	./solution1 input.txt
	# ./solution input.txt 2

tests: solution1 solution2
	./solution1 example.txt
	./solution1 example2.txt

check: cppcheck pvs-studio

cppcheck: 05-1.c 05-2.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 05-1.c
	cc -E 05-1.c -o 05-1.i
	cc -E 05-2.c -o 05-2.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 05-1.c --i-file 05-1.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 05-2.c --i-file 05-2.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
