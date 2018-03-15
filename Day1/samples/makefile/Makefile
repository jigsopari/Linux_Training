# Makefile to build program

edimh:	main.o edit.o
	gcc -o edimh main.o edit.o

main.o:	main.c
	gcc -c main.c

edit.o:	edit.c
	gcc -c edit.c

clean:
	rm *.o edimh
