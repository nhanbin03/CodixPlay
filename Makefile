all: compile link
	game

compile:
	g++ -w -Iinclude -c src/**/*.cpp

link:
	g++ *.o -o game -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

clean:
	rm *.o game