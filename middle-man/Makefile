CC=g++
CFLAGS=-c -std=c++11
LDFLAGS=
LIBRARIES=-lutil
SOURCES=MiddleMan.cpp simple.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=simple

all: $(SOURCES) $(OBJECTS) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBRARIES)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@  $(LIBRARIES)

clean:
	rm *.o *~ *.gch

