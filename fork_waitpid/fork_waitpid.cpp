/*
 *  fork_waitpid.cpp
 *  Updated on: Aug. 4, 2017
 *  Updated by: Zheng Xing <zxing@robohome.org>
 *  
 */

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

void sigchld_handler(int sig) {
	using namespace std;

	pid_t pid;
	int status;

	//int change_cnt = 0;

	/*
	 * waitpid(): on success, returns the process ID of the child whose
	 * state has changed; if WNOHANG was specified and one or more
	 * children specified by pid exist, but have not yet changed state,
	 * then 0 is returned. On error, -1 is returned.
	 * (in this case pid is -1, meaning any child)
	 */
	while ((pid = waitpid(-1, &status, WNOHANG)) != -1) {
		if (pid == 0) {
			// nothing happend
			//cout << "Nothing happened." << endl;
			break;
		} else if (pid > 0) {
			//change_cnt++;
			//cout << "change_cnt = " << change_cnt << endl;

			// child process pid's status has changed.
			if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
				cerr << "Child process pid: " << pid << " failed." << endl;
				//kill(0, SIGTERM);
				//exit (EXIT_FAILURE);
			} else {
				cout << "Child process pid: " << pid << " succeeded." << endl;
			}
		}
	}

	// If you want to terminate the parent process when all child processes
	// have terminated, enable the following.
	if (pid == -1) {
		cout << "Exiting parent process: " << strerror(errno) << endl;
		exit (EXIT_SUCCESS);
	}
}

int main(int argc, char** argv) {
	using namespace std;

	int process_num = 2;

	pid_t pid[process_num];

	for (int i = 0; i < process_num; i++) {

		pid[i] = fork();

		if (pid[i] == 0) {
			// CHILD PROCESS

			switch (i) {
			case 0:
				cout << "In child process numer " << i << endl;
				sleep(10);
				break;
			case 1:
				cout << "In child process numer " << i << endl;
				//exit(EXIT_FAILURE);
				sleep(10);
				break;
			default:
				break;
			}

			exit (EXIT_SUCCESS); // Never forget this.

		} else if (pid[i] > 0) {
			// PARENT PROCESS
			cout << "Parent process: waiting for child process " << pid[i]
					<< endl;

			struct sigaction act;
			memset(&act, 0, sizeof(act));
			act.sa_handler = sigchld_handler;
			sigaction(SIGCHLD, &act, NULL);
		} else {
			cerr << "Error: failed to fork() in launch()" << endl;
			// In case of fork() failure, terminate all processes in group
			// before exit()
			//kill(0, SIGTERM);
			//exit (EXIT_FAILURE);
		}
	}
	
	while(1) {
		sleep(10);
	}

	// The following can be used as a timeout setting.
	/*for (int i = 0; i < 30; i++) {
		sleep(1);
	}*/

	return 0;
}

