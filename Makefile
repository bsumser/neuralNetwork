src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)
CC = g++

CXXFLAGS = -Wall -g

main: $(obj)
	$(CC) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(obj) main
