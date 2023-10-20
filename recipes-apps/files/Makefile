SRC = seg7_src.cpp main.cpp

all: build


build: 
	aarch64-linux-gnu-g++ $(SRC) -o test

clean: 
	rm test

send:
	scp test  root@192.168.1.12:~

