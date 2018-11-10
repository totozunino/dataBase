todo: main.o bd.o
	g++ -Wall -o main bd.o tabla.o columna.o celda.o utilidades.o main.o
main.o: bd.o main.cpp bd.o
	g++ -Wall -c main.cpp
bd.o: bd.cpp bd.hh tabla.o
	g++ -Wall -c bd.cpp
tabla.o: tabla.hh tabla.cpp columna.o
	g++ -Wall -c tabla.cpp
columna.o: columna.hh columna.cpp celda.o
	g++ -Wall -c columna.cpp
celda.o: celda.hh celda.cpp utilidades.o
	g++ -Wall -c celda.cpp
utilidades.o: utilidades.cpp utilidades.hh
	g++ -Wall -c utilidades.cpp
clean:
	rm -f *.o
	rm -f main

