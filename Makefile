.PHONY: all test

all: bin/text_analyzer

clean:
	rm -rf bin/analyzer *.o

build/src/main.o: src/main.c
	gcc -Wall -Werror -c -o build/src/main.o src/main.c

build/src/functions.o: src/functions.c
	gcc -Wall -Werror -c -o build/src/functions.o src/functions.c

build/src/text_analyzer.o: src/text_analyzer.c
	gcc -Wall -Werror -c -o build/src/text_analyzer.o src/text_analyzer.c

bin/text_analyzer: build/src/main.o build/src/functions.o build/src/text_analyzer.o
	gcc -o bin/text_analyzer build/src/main.o build/src/functions.o build/src/text_analyzer.o