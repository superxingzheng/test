#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int segment_id = atoi(argv[1]);
	char* shared_memory;
	struct shmid_ds shmdescription;
	int segment_size;

	shared_memory = (char*) shmat(segment_id, 0, 0);
	printf("Shared memory attached at address %p\n", shared_memory);

	shmctl(segment_id, IPC_STAT, &shmdescription);
	segment_size = shmdescription.shm_segsz;
	printf("Segment size: %d\n", segment_size);
	
	sprintf(shared_memory, "%s", argv[2]);
	
	//printf("%s\n", shared_memory);
	
	shmdt(shared_memory);
	
	shmctl(segment_id, IPC_RMID, 0);

	return 0;
}
