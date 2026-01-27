TARGETS = mutex semaphore
CC     = gcc
CFLAGS = -Wall -g -std=c99 -Werror

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-$(RM) $(TARGETS) 
