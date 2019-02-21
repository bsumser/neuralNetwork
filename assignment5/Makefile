# build an executable named casesar from caesar.cpp

testCaesar.exe: testCaesar.o caesar.o
	g++ -o testCaesar.exe testCaesar.o caesar.o

testCaesar.o: testCaesar.cpp
	g++ -c testCaesar.cpp

caesar.o: caesar.cpp caesar.hpp
	g++ -c caesar.cpp

testDate.exe: testDate.o date.o
	g++ -o testDate.exe testDate.o date.o

testDate.o: testDate.cpp
	g++ -c testDate.cpp

date.o: date.cpp date.hpp
	g++ -c date.cpp
clean:
	-rm *.o testCaesar.exe testDate.exe	
