a.out: main.o interprete.o diccionario.o hash.o avl.o
	g++ -o a.out main.o interprete.o diccionario.o hash.o avl.o

main.o: main.cpp interprete.h diccionario.h hash.h avl.h 
	g++ -c main.cpp

interprete.o: interprete.cpp interprete.h diccionario.h hash.h avl.h 
	g++ -c interprete.cpp

diccionario.o: diccionario.cpp diccionario.h hash.h avl.h
	g++ -c diccionario.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

avl.o: avl.cpp avl.h
	g++ -c avl.cpp
