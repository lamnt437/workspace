main_v2: main_v2.o lib.o
	gcc -o main_v2 main.o lib.o
main.o: main_v2.c lib.h
	gcc -c main_v2.c
lib.o: lib.c lib.h
	gcc -c lib.c
clean:
	rm *.o
