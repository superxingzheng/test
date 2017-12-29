#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	int segment_id;
	char* shared_memory;
	struct shmid_ds shmdescription;
	int segment_size;

	const int shared_segment_size = 0x6400;

	segment_id = shmget(IPC_PRIVATE, shared_segment_size,
			IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	printf("Segment ID is %d\n", segment_id);

	shared_memory = (char*) shmat(segment_id, 0, 0);
	printf("Shared memory attached at address %p\n", shared_memory);

	shmctl(segment_id, IPC_STAT, &shmdescription);
	segment_size = shmdescription.shm_segsz;
	printf("Segment size: %d\n", segment_size);

	sprintf(shared_memory, "Hello world.");
	
	while(1) {
		printf("%s\n", shared_memory);
		sleep(1);
	}
	
	//shmdt(shared_memory);
	
	//shmctl(segment_id, IPC_RMID, 0);

	return 0;
}
