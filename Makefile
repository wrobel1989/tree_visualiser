DEBUGFLAGS=-g -O0
RELEASEFLAGS=-O3

FLAGS=$(DEBUGFLAGS)
GTEST_DIR=/usr/src/gtest

.PHONY: all tests clean

tests: tests/tests.cpp
	g++ $(FLAGS) -I./includes tests/tests.cpp src/treeimpl.c -o runtests -I$(GTEST_DIR) $(GTEST_DIR)/src/gtest-all.cc -lpthread

all: tests
