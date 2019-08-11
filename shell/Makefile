#
# Copyright (C) 2017,2018 Free Software Foundation, Inc.
#
# This is  Makefile of c shell.
#
#

VERSION = 0001
PATCHLEVEL = 01
SUBLEVEL = 01

CC := gcc

CFLAGS := -std=gnu99 -Wall -O2   -o

LD := -lreadline

TARGET = csh

PWD = $(shell pwd)
INCLUDE := -I$(PWD)/include

SRC = $(wildcard , *.c shell_c)
SHELLS := $(wildcard , *.c shell_c/*.c)
SHELLS += $(wildcard , *.c common/*.c)
OBJS  := $(patsubst %.c,%.o,$(SHELLS))


$(TARGET):$(OBJS)
	@echo "link  execute file csh ..."
	$(CC) $(CFLAGS) $@  $^ $(LD)
shell_c/%.o:shell_c/%.c	
	$(CC) $(CFLAGS) $@ -c $^ $(INCLUDE)
common/%.o:common/%.c	
	$(CC) $(CFLAGS) $@ -c $^ $(INCLUDE)
.PHONY:clean
clean:
	rm -rf $(OBJS) $(TARGET)
 
