# Template for multi-processes with fork()

fork() into a number of Child Processes

Parent process does nothing but responding to status changes of child processes

waitpid() in SIGCHLD handler to handle every change of every child process
