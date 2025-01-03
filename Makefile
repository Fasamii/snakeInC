exe: ./build/snake.o ./build/terminal.o ./build/draw.o dir
	gcc ./build/snake.o ./build/terminal.o ./build/draw.o -o exe
	./exe

./build/terminal.o : ./src/terminal.c dir
	gcc -c ./src/terminal.c -o ./build/terminal.o

./build/draw.o : ./src/draw.c dir
	gcc -c ./src/draw.c -o ./build/draw.o

./build/snake.o : ./src/snake.c dir
	gcc -c ./src/snake.c -o ./build/snake.o

dir :
	mkdir -p build

clean :
	rm -r ./build
	rm exe
