SOURCES := $(wildcard sources/*.c)

main:
	gcc -o main $(SOURCES) -I headers

clean:
	rm main
