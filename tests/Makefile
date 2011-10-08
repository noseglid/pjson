CC=g++
AR=ar
CFLAGS=-c -O0 -g3
LDFLAGS=-lcpptest -lpjson

LIB      = pjson
SOURCES  = main.cpp
SOURCES += JsonValueSuite.cpp
OBJECTS  = $(SOURCES:.cpp=.o)
BIN      = test-pjson

.PHONY: all test clean

all: test

test: $(BIN)
	./$<

clean:
	rm -f $(OBJECTS) $(BIN)

$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
		$(CC) $(CFLAGS) $< -o $@
