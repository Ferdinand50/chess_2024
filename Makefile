all:
	g++ -I src/include -L src/lib -o main main.cpp screen.cpp gamestate.cpp Movement.cpp opponent.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image