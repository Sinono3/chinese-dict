SRC = src/main.cpp src/pinyin/syllable.cpp src/pinyin/word.cpp src/pinyin/pretty.cpp src/search.cpp src/csv.cpp
BUILDDIR = build
EXE = build/chinese-dict

CXX = g++
# For cross-compilation
# CXX = /opt/homebrew/Cellar/mingw-w64/12.0.0/bin/x86_64-w64-mingw32-gcc
CXXFLAGS = -Wall --std=c++20 $(shell fltk-config --cxxflags)
LFLAGS = $(shell fltk-config --ldstaticflags)

OBJS = $(SRC:%=$(BUILDDIR)/%.o)

all: $(EXE)
run: $(EXE)
	$(EXE)
clean:
	rm -rf $(BUILDDIR)
.PHONY: all run clean

$(BUILDDIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(LFLAGS)
