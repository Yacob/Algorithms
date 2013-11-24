#our makefile for doing stuff

eecs477: main.cpp util.h
	        g++ -pedantic -Wall -g -std=c++11 main.cpp -o eecs477

run0: eecs477
	        ./eecs477 < test0.dat
run1: eecs477
		./eecs477 < test1.dat
run2: eecs477
		./eecs477 < test2.dat
run3: eecs477
		./eecs477 < test3.dat
run4: eecs477
		./eecs477 < test4.dat
runSimple: eecs477
		./eecs477 < simple.dat
clean:
	        rm eecs477
