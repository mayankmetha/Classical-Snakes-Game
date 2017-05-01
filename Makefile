snakes.exe:
	g++ -o snakes.exe ./CGProj/main.cpp ./CGProj/platforms.h ./CGProj/game.h ./CGProj/game.cpp -lglut -lGLU -lGL
clean:
	rm -f *.o *.exe
