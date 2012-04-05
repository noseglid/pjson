.PHONY: all doc clean

CXX     = g++
CFLAGS  = -I.. -c
LDFLAGS = -L../.libs -lpjson
DOXYGEN = doxygen
RM      = rm

SRC  = doc-array.cpp doc-basic.cpp doc-object.cpp doc-strjson-pretty.cpp
SRC += doc-strjson-minified.cpp doc-deserialize.cpp
OBJ  = $(SRC:.cpp=.o)
BIN  = $(SRC:.cpp=)

doc: $(BIN)
	$(DOXYGEN) doxygen.cfg

all: doc

clean:
	$(RM) -rf $(OBJ) $(BIN) html $(BIN:%=%.out)

doc-%: doc-%.o
	$(CXX) $(LDFLAGS) -o $@ $<
	DYLD_LIBRARY_PATH=../.libs LD_LIBRARY_PATH=../.libs ./$@ > $@.out

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@
