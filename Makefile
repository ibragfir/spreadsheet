all: 
	make compile;
	make doc;
	make run;

compile:
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c -o src/sheet.o src/sheet.cpp
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c -o src/cell.o src/cell.cpp
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c -o src/classes.o src/classes.cpp
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c -o src/main.o src/main.cpp
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -o ibragfir src/main.o src/sheet.o src/cell.o src/classes.o -lncurses

run: 
	./ibragfir

clean: 
	rm -rf doc/ ibragf* src/*.o

doc: 
	doxygen;
