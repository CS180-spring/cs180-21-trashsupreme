
output: server.o 
	g++ server.o -o output

server.o: src/server.cpp
	g++ -std=c++17 -c $$(pkg-config --cflags --libs asio) src/server.cpp

clean: 
	rm *.o output


# include ./include/asio/asio.hpp