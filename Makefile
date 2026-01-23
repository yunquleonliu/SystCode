
CC=gcc
CFLAGS=-I./include -Wall -O2
LDFLAGS=-lpthread

all: help

help:
	@echo "Usage: make run PROBLEM=<problem_name>"
	@echo "Example: make run PROBLEM=aligned_malloc"

run:
	$(CC) $(CFLAGS) problems/$(PROBLEM)/*.c -o bin/$(PROBLEM)_test $(LDFLAGS)
	./bin/$(PROBLEM)_test
