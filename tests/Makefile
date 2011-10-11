CC      = g++
CFLAGS  = -c -O2 -g0 -W -Wall -Werror
LDFLAGS = -lpjson

LIB      = pjson
SOURCES  = main.cpp
SOURCES += JsonValueSuite.cpp
OBJECTS  = $(SOURCES:.cpp=.o)
BIN      = test-pjson

.PHONY: all test clean

all: $(BIN)

test: $(BIN)
	./$<

clean:
	rm -f $(OBJECTS) $(BIN)

$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
		$(CC) $(CFLAGS) $< -o $@
