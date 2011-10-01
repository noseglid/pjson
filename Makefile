CC=g++
AR=ar
CFLAGS=-c -Wall -O0 -g3 -I/usr/local/boost/
LDFLAGS=

LIB      = libpjson
SOURCES  = PJsonValue.cpp
OBJECTS  = $(SOURCES:.cpp=.o)

default: $(LIB)

all: $(LIB) test

install:

test: $(LIB)
	make -C tests test

clean:
	rm -f $(LIB).a $(LIB).so $(OBJECTS)
	make -C tests clean

$(LIB): $(OBJECTS)
	$(CC) $(LDFLAGS) -shared $(OBJECTS) -o $(LIB).so
	$(AR) rvs $(LIB).a $(OBJECTS)

%.o: %.cpp
		$(CC) $(CFLAGS) $< -o $@
