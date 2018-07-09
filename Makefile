CXX = g++ -std=c++14
CXXFLAGS = -Wall -O -g -MMD
GTKFLAGS = `pkg-config gtkmm-3.0 --cflags`
GTKLIBS = `pkg-config gtkmm-3.0 --libs`
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = ${OBJECTS:.o=.d}
EXEC=straights

$(EXEC): $(OBJECTS)
	$(CXX) $(GTKFLAGS) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(GTKLIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(GTKFLAGS) $(CXXFLAGS) $(GTKLIBS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)

.PHONY: test
test: $(EXEC)
	./checkseed tests straights sample_straights

.PHONY: check
check: $(EXEC)
	./checkmemory tests straights
	cppcheck .
