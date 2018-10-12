appname := myapp

CXX := g++
CXXFLAGS := -std=c++11

srcfiles := $(shell find . -name "*.cpp")
headerFiles := $(shell find . -name "*.h")
objects  := $(patsubst %.C, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles) $(headerFiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;
    
clean:
	rm -f $(objects)

dist-clean: clean
	rm -f *~ .depend

include .depend