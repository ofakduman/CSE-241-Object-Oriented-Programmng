all: exe

exe:	main.o
	g++ main.o -o exe

main.o:	main.cpp
	g++ -c -O3 main.cpp

clean: 
	rm -rf *o main.o

