# The $(shell ..) function runs a command on the shell
# In this case we use the find command to find all directories
# in the ./include directory
INCDIR := $(shell find ./include -type d)

CXX := g++
CXXFLAGS := -std=c++20 $(addprefix -I, $(INCDIR)) -Wall -g
LDFLAGS := 

SRCDIR := ./src
BUILDDIR := ./build

SRCS := $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# Variable to define the .d files for each .o file
DEPS := $(OBJS:.o=.d)

TARGET := main.out

.PHONY: all build clean run

all: build

run: $(TARGET)
	./$(TARGET)

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $(TARGET) $(LDFLAGS)

# The -MMD option generates .d files in the buid directory
# These files contain make rules that specify the .o file
# header dependencies

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $< -MMD -c -o $@ $(CXXFLAGS)

# This line includes the generated .d files as
# make rules 

-include $(DEPS)

clean:
	rm $(OBJS) $(TARGET) $(DEPS)