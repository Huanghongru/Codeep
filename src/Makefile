CXX = g++
CXXFLAGS = -std=c++11
EXECUTABLE = codeep
OBJECTS = codeep.o utils.o core.o

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

clean:
	rm -f *.o $(EXECUTABLE)
