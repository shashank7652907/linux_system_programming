#TARGETS = sig_int

TARGETS =  count_occurance_of_signal

CROSS_TOOL = 
CC_CPP = $(CROSS_TOOL)g++
CC_C   = $(CROSS_TOOL)gcc

CFLAGS =  -g -std=c99 

all: clean $(TARGETS)

$(TARGETS):
	$(CC_C) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(TARGETS)

