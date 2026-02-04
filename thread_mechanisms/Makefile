# Makefile for building demo applications.
# by Brian Fraser
#
# Edit this file to compile extra C files into their own program
# sum_on_thread sum_on_many_threads sum_using_malloc intro_on_thread main-threads main-processes mutex_thread thread_create_loop argumentThread trylockMutex conditionalVariablesMutex condBroadcastMutex
TARGETS = tryLockExample

CROSS_TOOL =
CC_CPP = $(CROSS_TOOL)g++
CC_C   = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -Werror -pthread

all: clean $(TARGETS)

$(TARGETS):
	$(CC_C) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(TARGETS)

