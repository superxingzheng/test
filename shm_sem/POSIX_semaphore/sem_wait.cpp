#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
//#include <unistd.h> // fore sleep()
//#include <errno.h>
#include <semaphore.h>

using namespace std;

int main() {
	const char* sem_name = "/test_sem";

	/* 
	 * Create a POSIX semaphore with the name of "sem_name".
	 * If the semaphore already exists, return an error.
	 * Set the file mode bits to rwx by owner.
	 */
	sem_t* semaphore = sem_open(sem_name, O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IXUSR, 0);

	if (semaphore == SEM_FAILED) {
		cerr << "Error: sem_open() returned SEM_FAILED." << endl;
		exit(EXIT_FAILURE);
	}

	//sleep(5);
	for (int i = 0; i < 5; i++) {
		sem_wait(semaphore);
		cout << "Got one signal." << endl;
		//sleep(10);
	}
	
	sem_close(semaphore);
	sem_unlink(sem_name);

	return 0;
}
