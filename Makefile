snakes.exe:
	g++ -o exe/snakes_linux ./CGProj/main.cpp ./CGProj/platforms.h ./CGProj/game.h ./CGProj/game.cpp -lglut -lGLU -lGL
clean:
	rm -f *.o *.exe
