mainFile = main.cpp
libFile = bullets.cpp

bullets.o: $(libFile)
	g++ -c $(libFile)

main.o: $(mainFile)
	g++ -c $(mainFile)

build: bullets.o main.o
	g++ bullets.o main.o -lsfml-graphics -lsfml-window -lsfml-system -o bullets