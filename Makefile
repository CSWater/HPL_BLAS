SHELL = /bin/bash
.SUFFIXES:
.SUFFIXES: .c .o

CC=gcc
TOPDIR=$(shell pwd)
CFLAGS=-O3 -Wno-implicit-int -std=c99
INCLUDE_DIR=$(TOPDIR)/include
FRAME_DIR=$(TOPDIR)/frame
BUILD_DIR=$(TOPDIR)/build
BIN_DIR=$(TOPDIR)/bin

#SRCFILES=$(shell find $(FRAME_DIR) -name "*.c")
#OBJFILES := $(foreach bname, $(basename $(SRCFILES)), $(BUILD_DIR)/$(bname).o)
#OBJFILES     := $(patsubst $(FRAME_DIR)/%,$(BUILD_DIR)/%,$(SRCFILES:.c=.o))

all: main

main: $(BUILD_DIR)/main.o $(BUILD_DIR)/dgemm_naive.o
	$(CC) -I$(INCLUDE_DIR) $(CFLAGS) $^ -o $(BIN_DIR)/$@

$(BUILD_DIR)/%.o: $(FRAME_DIR)/%.c
	$(CC) -I$(INCLUDE_DIR) $(CFLAGS) $< -c -o $@

clean:
	rm $(BIN_DIR)/* -rf
	rm $(BUILD_DIR)/* -rf
