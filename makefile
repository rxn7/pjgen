all:
	gcc src/pjgen.c -Isrc -std=gnu99 -o pjgen

install:
	make
	sudo cp ./pjgen /usr/bin/
