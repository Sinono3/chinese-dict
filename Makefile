SRC = src/main.cpp
BUILDDIR = build
EXE = build/chinese-dict

CXX = g++
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
