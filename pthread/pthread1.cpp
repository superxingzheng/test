/*
 * Updated on: Aug.30, 2017
 *
 * Reference: http://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_message_function(void* ptr);

int main(int argc, char** argv) {
	using namespace std;

	pthread_t thread1, thread2;
	const char* message1 = "Thread 1";
	const char* message2 = "Thread 2";

	int iret1, iret2;

	iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
	iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("Thread 1 returned: %d\n", iret1);
	printf("Thread 2 returned: %d\n", iret2);

	return 0;
}

void* print_message_function(void* ptr) {
	char *message;
	message = (char*) ptr;
	printf("%s\n", message);
}
