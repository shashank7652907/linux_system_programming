
# TARGETS = multiple_fork bogosort fork_exec exec_with_env fork_thrice wait_fork process_id ipc_using_pipes ipc_using_pipe_example fifo_pipe ipc_using_fifo_2 ipc_using_fifo_1 two_way_ipc_using_pipe run_command exit_status_fork_exec stdout_redirect signal_intro sigstop_sigcont job_control ipc_using_signal array_through_pipe string_through_pipe
TARGETS =  shell_pipe_sim
CC     = gcc
CFLAGS = -Wall -g -std=c99 -Werror

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-$(RM) $(TARGETS) 