# SRC = src/main.cpp
SRC = src/pinyin.cpp
CXX = g++
CXXFLAGS = -Wall $(shell fltk-config --cxxflags) --std=c++20

LFLAGS = $(shell fltk-config --ldstaticflags)

OBJS = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(<) -o $(@)

EXE = build/chinese-dict

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(LFLAGS)

%.o: %.cpp *.h
	 $(CXX) -o $@ -c $< $(CXXFLAGS)

depend:
	makedepend -- $(CXXFLAGS) -- $(SRC)

strip: $(EXE)
	strip --strip-all $(EXE)

clean:
	rm -f $(EXE)

