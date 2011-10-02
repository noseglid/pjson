CC=g++
AR=ar
CFLAGS=-c -Wall -O0 -g3 -I/usr/local/boost/
LDFLAGS=

LIB      = libpjson
SOURCES  = JsonValue.cpp
OBJECTS  = $(SOURCES:.cpp=.o)

.PHONY: default all install doc test clean

default: $(LIB)

all: $(LIB) doc test

install:

doc:
	make -C doc doc

test: $(LIB)
	make -C tests test

clean:
	rm -f $(LIB).a $(LIB).so $(OBJECTS)
	make -C tests clean
	make -C doc clean

$(LIB): $(OBJECTS)
	$(CC) $(LDFLAGS) -shared $(OBJECTS) -o $(LIB).so
	$(AR) rvs $(LIB).a $(OBJECTS)

%.o: %.cpp
		$(CC) $(CFLAGS) $< -o $@
