CC=gcc

make:
	gcc -o smithcr.adventure smithcr.adventure.c

clean:
	rm -fr smithcr.rooms.*