CC = g++ -std=c++11
all: build/main
build/main:
	$(CC) src/main.cpp -o build/main

.PHONY:
clean: 
	rm -r build/*