CC=g++
AR=ar
CFLAGS=-c -I.. -O0 -g3
LDFLAGS=-L.. -lcpptest -lpjson

LIB      = pjson
SOURCES  = main.cpp
SOURCES += PJsonValueSuite.cpp
OBJECTS  = $(SOURCES:.cpp=.o)
BIN      = test-pjson

all: test

test: $(BIN)
	DYLD_LIBRARY_PATH=.. ./$(BIN)

clean:
	rm -f $(OBJECTS) $(BIN)

$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
		$(CC) $(CFLAGS) $< -o $@
