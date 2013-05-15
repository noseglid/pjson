CC      = clang++
CFLAGS  = -I.. -c -O0 -g3 -W -Wall -Werror -stdlib=libc++
LDFLAGS = -L../.libs -lpjson -stdlib=libc++

LIB      = pjson
SOURCES  = main.cpp
SOURCES += pjtestframework.cpp
SOURCES += JsonValueSuite.cpp
SOURCES += JsonBuilderSuite.cpp
SOURCES += JsonStringSuite.cpp
SOURCES += PjsonSuite.cpp
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
