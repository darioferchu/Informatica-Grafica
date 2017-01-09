COMPILAR=g++ -std=c++11 -Wall

all: ray-trace.exe

ray-trace.exe: Trazador.o Rayo.o Esfera.o Fuente.o Matriz.o VectorT.o 
	$(COMPILAR) -o ray-trace.exe Trazador.o Rayo.o Esfera.o Fuente.o Matriz.o VectorT.o 
	
Trazador.o: Trazador.cpp Trazador.h
	$(COMPILAR) -c Trazador.cpp
	
Rayo.o: Rayo.cpp Rayo.h
	$(COMPILAR) -c Rayo.cpp
	
Fuente.o: Fuente.cpp Fuente.h
	$(COMPILAR) -c Fuente.cpp

Esfera.o: Esfera.cpp Esfera.h
	$(COMPILAR) -c Esfera.cpp

Matriz.o: Matriz.cpp Matriz.h
	$(COMPILAR) -c Matriz.cpp

VectorT.o: VectorT.cpp VectorT.h
	$(COMPILAR) -c VectorT.cpp
	
clean:
	rm -f *.o
	rm -f ray-trace.exe
	
