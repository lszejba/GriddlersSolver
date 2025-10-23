# Simple Makefile for Solver_v2
# Place this file in Solver_v2/ and run `make` to build the executable `solver_v2`.
#
# Usage:
#   make        -> build release binary (O2)
#   make debug  -> build debug binary (-g -O0)
#   make run    -> build and run
#   make clean  -> remove built files and intermediate objects

CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -I. -MMD -MP
LDFLAGS :=

TARGET := solver

SRCS := $(wildcard *.cpp)
OBJDIR := .obj
OBJS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run debug

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

-include $(DEPS)

# build object files into .obj directory
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# ensure obj dir exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

run: all
	./$(TARGET)

debug: CXXFLAGS += -g -O0
debug: clean all

clean:
	rm -rf $(TARGET) $(OBJDIR)
