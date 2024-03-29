# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRC=src
OUT=target
HDR=header
FLA=-I$(HDR) -Wall
OBJ_FLA=-pedantic -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wundef -Werror -Wno-unused
CXX=g++ $(FLA)

ifneq ("$(wildcard /usr/lib64/qt-3.3/include/qapplication.h)","")
QT_INC=-I/usr/lib64/qt-3.3/include/ -L/usr/lib64/qt-3.3/lib/
LIB_FLA=-lqt-mt -lpthread
else
QT_INC=-I/usr/local/qt/include -I/usr/local/qt/mkspec/default
LIB_FLA=-lqt -lpthread
endif

# Get all files from the header dirs
FILES:=$(call rwildcard,$(SRC)/,*.cpp)

# Transform files (change .hpp to .o)
OBJ:=$(FILES:$(SRC)/%.cpp=$(OUT)/%.o)

.PHONY: build clean mkdir

build: | mkdir $(OUT)/main

release: FLA += -O2
release: | clean build

$(OUT)/main: main.cpp $(OBJ)
	$(CXX) $(QT_INC) $(LIB_FLA) -o $@ $^

$(OUT)/ui/%.o: $(SRC)/ui/%.cpp $(HDR)/ui/%.hpp
	$(CXX) $(QT_INC) -c -o $@ $<

$(OUT)/threading/%.o: $(SRC)/threading/%.cpp $(HDR)/threading/%.hpp
	$(CXX) $(OBJ_FLA) -c -o $@ $<

$(OUT)/%.o: $(SRC)/%.cpp $(HDR)/%.hpp
	$(CXX) $(OBJ_FLA) -c -o $@ $<

clean:
	rm -rf $(OUT)/

mkdir:
	python create_target.py
