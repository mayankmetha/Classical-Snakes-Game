snakes_linux:
	mkdir exe exe/linux
	g++ -o ./exe/linux/snakes_linux ./CGProj/main.cpp ./CGProj/platforms.h ./CGProj/game.h ./CGProj/game.cpp -lglut -lGLU -lGL
clean:
	rm -rf exe/linux/*
	rmdir exe/linux exe