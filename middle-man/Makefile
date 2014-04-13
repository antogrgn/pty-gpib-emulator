CC=g++
CFLAGS=-c -std=c++11
LDFLAGS=
LIBRARIES=-lutil
SOURCES=MiddleMan.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mid

all: $(SOURCES) $(OBJECTS)


$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o *~ *.gch

