CC      = g++
CFLAGS  = -I.. -c -O2 -g0 -W -Wall -Werror
LDFLAGS = -L../.libs -lpjson

LIB      = pjson
SOURCES  = main.cpp
SOURCES += pjtestframework.cpp
SOURCES += JsonValueSuite.cpp
SOURCES += JsonBuilderSuite.cpp
OBJECTS  = $(SOURCES:.cpp=.o)
BIN      = test-pjson

.PHONY: all test clean

all: $(BIN)

test: $(BIN)
	DYLD_LIBRARY_PATH=../.libs LD_LIBRARY_PATH=../.libs ./$<

debug: $(BIN)
	DYLD_LIBRARY_PATH=../.libs LD_LIBRARY_PATH=../.libst gdb ./$<

clean:
	rm -f $(OBJECTS) $(BIN)

$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
		$(CC) $(CFLAGS) $< -o $@
