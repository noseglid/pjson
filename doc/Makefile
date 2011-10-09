.PHONY: all doc clean

CXX     = g++
DOXYGEN = doxygen
RM      = rm

SRC = doc-array.cpp doc-basic.cpp doc-object.cpp
OBJ = $(SRC:.cpp=.o)
BIN = doc-array doc-basic doc-object

doc: $(BIN)
	$(DOXYGEN) doxygen.cfg

all: doc

clean:
	$(RM) -rf $(OBJ) $(BIN) html $(BIN:%=%.out)

doc-%: doc-%.o
	$(CXX) -lpjson -o $@ $<
	./$@ > $@.out

%.o: %.cpp
	$(CXX) -c $< -o $@
