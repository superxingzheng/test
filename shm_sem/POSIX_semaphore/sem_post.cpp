#include <iostream>
#include <stdlib.h>
//#include <unistd.h> // for sleep()
//#include <errno.h>
#include <semaphore.h>

using namespace std;

int main() {
	const char* sem_name = "test_sem";
	
	sem_t* semaphore = sem_open(sem_name, 0);
	
	if (semaphore == SEM_FAILED) {
		cerr << "Error: sem_open() returned SEM_FAILED." << endl;
		exit(EXIT_FAILURE);
	}
	
	//sleep(5);
	/*
	// The following section is used to test the maximum value of the semaphore.
	// Usually it is 2^31 = 2,147,483,648.
	int r = 0;
	long count = 0;
	
	while (r == 0) {
		r = sem_post(semaphore);
		count++;
	}
	cout << "count = " << count << endl;
	*/
	
	sem_post(semaphore);
	
	sem_close(semaphore);
	
	return 0;
}