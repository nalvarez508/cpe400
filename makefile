Routing:	main.o Router.o
	g++ main.o Router.o -o Routing

main.o:			main.cpp Router.h Router.cpp
	g++ -c main.cpp

Router.o:	Router.h Router.cpp
	g++ -c Router.cpp
