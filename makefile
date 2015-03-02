# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRC=src
OUT=target
HDR=header
FLA=-Og -I$(HDR)
QT_FLA=-I/usr/lib64/qt-3.3/include/ -L/usr/lib64/qt-3.3/lib/ -lqt-mt -lpthread
OBJ_FLA=-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Werror -Wno-unused
CXX=g++ $(FLA)

# Get all files from the header dirs
FILES:=$(call rwildcard,$(SRC)/,*.cpp)

# Transform files (change .hpp to .o)
OBJ:=$(FILES:$(SRC)/%.cpp=$(OUT)/%.o)

.PHONY: build clean mkdir

build: | mkdir $(OUT)/main
ui:    | mkdir $(OUT)/T

release: FLA += -O2
release: | clean build ui

$(OUT)/main: main.cpp $(OBJ)
	$(CXX) $(QT_FLA) -o $@ $^

$(OUT)/T: T.cpp $(OBJ)
	$(CXX) $(QT_FLA) -o $@ $^

$(OUT)/ui/%.o: $(SRC)/ui/%.cpp $(HDR)/ui/%.hpp
	$(CXX) $(QT_FLA) -c -o $@ $<

$(OUT)/%.o: $(SRC)/%.cpp $(HDR)/%.hpp
	$(CXX) $(OBJ_FLA) -c -o $@ $<

clean:
	rm -rf $(OUT)/

mkdir:
	python create_target.py
