# build an executable named casesar from caesar.cpp

output: caesar.o
	g++ caesar.o -o output

caesar.o: caesar.cpp caesar.hpp
	g++ -c caesar.cpp

clean:
	rm *.o output	
