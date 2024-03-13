build:
	gcc ./src/*.c -L/usr/lib -lSDL2 -o slime.out

mac:
	gcc ./src/*.c -I/opt/homebrew/include -L/opt/homebrew/lib -lsdl2 -o slime.out

run:
	./slime.out

clean:
	rm slime.out
