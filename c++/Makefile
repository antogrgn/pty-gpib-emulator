CC=g++
CFLAGS=-c -std=c++11
LDFLAGS=
LIBRARIES=-lutil -lboost_system
SOURCES=PTY_Interface.cpp Prologix.cpp Device.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=

TEST_SRC=$(SOURCES) test.cpp
TEST_OBJ=$(TEST_SRC:.cpp=.o)
TEST_EXE=test

all: $(SOURCES) $(OBJECTS)

test: $(TEST_SRC) $(TEST_OBJ)

$(TEST_EXE):
	$(CC) $(LDFLAGS) $(TEST_OBJ) $(LIBRARIES) -o $(TEST_EXE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o *~ *.gch

