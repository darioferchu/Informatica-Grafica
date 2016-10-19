all: trazador.exe

trazador.exe:
	g++ -std=c++0x -Wall -o trazador.exe *.cpp
	
clean:
	rm -f trazador.exe
	
