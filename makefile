inventory: main.o Product.o Store.o
	g++ main.o Product.o Store.o -o inventory

main.o: main.cpp
	g++ -c main.cpp

Product.o: Product.cpp
	g++ -c Product.cpp

Store.o: Store.cpp
	g++ -c Store.cpp