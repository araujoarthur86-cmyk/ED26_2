CXX ?= g++
CPPFLAGS ?= -Iinclude
CXXFLAGS ?= -std=c++11 -O2 -Wall -Wextra -pedantic
LDFLAGS ?=
LDLIBS ?=

TARGET := bin/tp2.out
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp,obj/%.o,$(SOURCES))
DEPFILES := $(OBJECTS:.o=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | bin
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

obj/%.o: src/%.cpp | obj
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

bin obj:
	mkdir -p $@

clean:
	rm -f $(OBJECTS) $(DEPFILES) $(TARGET)

-include $(DEPFILES)
