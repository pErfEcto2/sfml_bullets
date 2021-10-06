mainFile = bullets.cpp

bullets.o: $(mainFile)
	g++ -c $(mainFile)

build: bullets.o
	g++ bullets.o -lsfml-graphics -lsfml-window -lsfml-system -o bullets