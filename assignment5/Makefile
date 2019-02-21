# build an executable named casesar from caesar.cpp

testCaesar.exe: testCaesar.o caesar.o
	g++ -o testCaesar.exe testCaesar.o caesar.o

testCaesar.o: testCaesar.cpp
	g++ -c testCaesar.cpp

caesar.o: caesar.cpp caesar.hpp
	g++ -c caesar.cpp

clean:
	rm *.o output	
