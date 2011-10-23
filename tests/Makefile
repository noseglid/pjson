CC      = g++
CFLAGS  = -I.. -c -O0 -g3 -W -Wall -Werror
LDFLAGS = -L../.libs -lpjson

LIB      = pjson
SOURCES  = main.cpp
SOURCES += JsonValueSuite.cpp
OBJECTS  = $(SOURCES:.cpp=.o)
BIN      = test-pjson

.PHONY: all test clean

all: $(BIN)

test: $(BIN)
	DYLD_LIBRARY_PATH=../.libs LD_LIBRARY_PATH=../.libs ./$<

clean:
	rm -f $(OBJECTS) $(BIN)

$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
		$(CC) $(CFLAGS) $< -o $@
