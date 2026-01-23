
# TARGETS = multiple_fork bogosort fork_exec exec_with_env fork_thrice wait_fork process_id ipc_using_pipes ipc_using_pipe_example fifo_pipe ipc_using_fifo_2 ipc_using_fifo_1 two_way_ipc_using_pipe run_command
TARGETS = exit_status_fork_exec
CC     = gcc
CFLAGS = -Wall -g -std=c99 -Werror

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-$(RM) $(TARGETS) 