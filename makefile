all: main
fp2.o: fp2.c
		gcc -c fp2.c
p2.o: p2.c
		gcc -c p2.c
main: fp2.o p2.o
	gcc -o main fp2.o p2.o
clean:
	rm -f main *.o
