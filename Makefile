all:
	g++ -Isrc/include -Lsrc/lib utils.cpp Painter.cpp game.cpp bar.cpp items.cpp -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer