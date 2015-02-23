# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRC=src
OUT=target
HDR=header
FLA=-Og -I$(HDR) -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Werror -Wno-unused
CXX=g++ $(FLA)

# Get all files from the header dir
FILES:=$(call rwildcard,$(HDR)/,*.hpp)

# Transform files (change .hpp to .o)
OBJ:=$(FILES:$(HDR)/%.hpp=$(OUT)/%.o)

.PHONY: build clean mkdir

build: | mkdir $(OUT)/main

release: FLA += -O2
release: | clean build

$(OUT)/main: main.cpp $(OBJ)
	$(CXX) -o $@ $^

$(OUT)/%.o: $(SRC)/%.cpp $(HDR)/%.hpp
	$(CXX) -c -o $@ $<

clean:
	rm -rf $(OUT)/

mkdir:
	python create_target.py
