all: main.c main.h
	gcc main.c -o semaphone

write: write.c
	gcc write.c -o write

clean:
	rm -f *.o
	rm -f *~
	rm -f *#