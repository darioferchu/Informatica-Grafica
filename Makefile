COMPILAR=g++ -std=c++11 -Wall

all: trazador.exe

trazador.exe: Trazador.o Rayo.o Esfera.o Fuente.o Objeto.o Imagen.o Matriz.o VectorT.o 
	$(COMPILAR) -o trazador.exe Trazador.o Rayo.o Esfera.o Fuente.o Objeto.o Imagen.o Matriz.o VectorT.o 
	
Trazador.o: Trazador.cpp Trazador.h
	$(COMPILAR) -c Trazador.cpp
	
Rayo.o: Rayo.cpp Rayo.h
	$(COMPILAR) -c Rayo.cpp

Esfera.o: Esfera.cpp Esfera.h
	$(COMPILAR) -c Esfera.cpp
	
Fuente.o: Fuente.cpp Fuente.h
	$(COMPILAR) -c Fuente.cpp

Objeto.o: Objeto.cpp Objeto.h
	$(COMPILAR) -c Objeto.cpp

Imagen.o: Imagen.cpp Imagen.h
	$(COMPILAR) -c Imagen.cpp

Matriz.o: Matriz.cpp Matriz.h
	$(COMPILAR) -c Matriz.cpp

VectorT.o: VectorT.cpp VectorT.h
	$(COMPILAR) -c VectorT.cpp
	
clean:
	rm -f *.o
	rm -f trazador.exe
	
