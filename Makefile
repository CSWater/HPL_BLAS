SHELL = /bin/bash
.SUFFIXES:
.SUFFIXES: .c .o

CC=gcc
CFLAGS=-O3 -Wno-implicit-int -std=c99 -march=core-avx2
LDFLAGS= -fopenmp -ldl
TOPDIR=$(shell pwd)
INCLUDE_DIR=$(TOPDIR)/include
FRAME_DIR=$(TOPDIR)/frame
BUILD_DIR=$(TOPDIR)/build
BIN_DIR=$(TOPDIR)/bin
TEST_DIR=$(TOPDIR)/test

SRCFILES=$(shell find $(FRAME_DIR) -name "*.c")
#OBJFILES := $(foreach bname, $(basename $(SRCFILES)), $(BUILD_DIR)/$(bname).o)
OBJFILES     := $(patsubst $(FRAME_DIR)/%,$(BUILD_DIR)/%,$(SRCFILES:.c=.o))

all: main test

#main: $(BUILD_DIR)/main.o $(BUILD_DIR)/dgemm_naive.o
main: $(OBJFILES)
	$(CC) -I$(INCLUDE_DIR) $(LDFLAGS) $(CFLAGS) $^ -o $(BIN_DIR)/$@

$(BUILD_DIR)/%.o: $(FRAME_DIR)/%.c 
	$(CC) -I$(INCLUDE_DIR) -I/home/scy/software/hygon/include $(LDFLAGS) $(CFLAGS) $< -c -o $@

test: $(BUILD_DIR)/test_macro.o
	$(CC) -I$(INCLUDE_DIR) $^ -o $(BIN_DIR)/test_macro
$(BUILD_DIR)/test_macro.o: $(TEST_DIR)/macro/test_macro.c
	$(CC) -I$(INCLUDE_DIR) $< -c -o $@

clean:
	rm $(BIN_DIR)/* -rf
	rm $(BUILD_DIR)/* -rf
