# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRC=src
OUT=target
HDR=header
FLA=-I$(HDR) -Wall -Wextra
CXX=g++ $(FLA)

# Get all files from the header dir
FILES:=$(call rwildcard,$(HDR)/,*.hpp)

# Transform files (change .hpp to .o)
OBJ:=$(FILES:$(HDR)/%.hpp=$(OUT)/%.o)

.PHONY: build clean mkdir
.SILENT:

build: | mkdir $(OUT)/main

$(OUT)/main: main.cpp $(OBJ)
	echo Compiling $@...
	$(CXX) -o $@ $^

$(OUT)/%.o: $(SRC)/%.cpp $(HDR)/%.hpp
	echo Compiling $@...
	$(CXX) -c -o $@ $<

clean:
	rm -rf $(OUT)

mkdir:
	python create_target.py
