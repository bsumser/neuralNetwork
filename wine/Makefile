all: main

main: main.o Neuron.o Net.o
	g++ -g -Wall -std=c++11 -o main main.o Neuron.o Net.o

Neuron.o: Neuron.cpp
	g++ -c Neuron.cpp

Net.o: Net.cpp
	g++ -c Net.cpp

clean:
	rm main.o Neuron.o Net.o main
