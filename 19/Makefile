all: tests run

generator: 19.c
	cc 19.c -Wall -Wextra -o generator

run: solution
	./generator input.txt ranges.txt > lib.c 2>lib.h
	cc 19-2.c bubble.c lib.c -o solution
	./solution input.txt ranges.txt

tests: generator
	./generator example.txt ranges.txt > lib.c 2>lib.h
	cc 19-2.c bubble.c lib.c -o example
	./example example.txt ranges.txt

check: cppcheck pvs-studio

cppcheck: 19.c
	cppcheck --enable=all --suppress=missingIncludeSystem .

pvs-studio: 19.c 19-2.c
	cc -E 19.c -o 19.i
	cc -E 19-2.c -o 19-2.i
	rm -f ../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 19.c --i-file 19.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	pvs-studio --preprocessor=clang --source-file 19-2.c --i-file 19-2.i --lic-file ~/.config/PVS-Studio/PVS-Studio.lic --output-file=../pvs-studio-output.txt
	plog-converter -a 'GA;OP;CS;OWASP' -t html -o ../pvs-studio-report.html ../pvs-studio-output.txt
