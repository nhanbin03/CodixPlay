all: compile link
	game

compile: $(shell find ./ -type f -name '*.cpp')
	g++ -w -Iinclude -c $^

link:
	g++ *.o -o game -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

clean:
	rm *.o game