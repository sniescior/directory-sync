SOURCES := $(wildcard sources/*.c)

all:
	gcc -o dir-sync $(SOURCES) -I headers

install: all
	cp dir-sync /usr/bin
	
uninstall:
	rm /usr/bin/dir-sync

clean:
	rm dir-sync
