main: main.o lib.o
	gcc -o main main.o lib.o
main.o: main_v2.c lib.h
	gcc -c main.c
lib.o: lib.c lib.h
	gcc -c lib.c
clean:
	rm *.o
