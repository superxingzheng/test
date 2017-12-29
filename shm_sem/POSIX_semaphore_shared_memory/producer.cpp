#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>

static int produce(char* shm_ptr, const char* str,
		const size_t shm_region_size) {
	using namespace std;
	stringstream ss;
	string s(shm_ptr);
	if (s.size() == 0) {
		ss << str;
	} else {
		ss << s << ' ' << str;
	}
	s = ss.str();

	if (s.size() > shm_region_size) {
		cerr << "Error: s.size() > region_size.\n";
		return -1;
	}

	memcpy(shm_ptr, s.c_str(), s.size());
	//sleep(5);
	cout << s.size() << " Bytes copied into shm region." << endl;
	return 0;
}

int main(int argc, char** argv) {
	using namespace std;

	/*******************Get access to the shm and semaphores**********************/
	const char* shm_name = "/region_1_shm";
	const char* cnt_sem_name = "/region_1_counter";
	const char* mutex_sem_name = "/region_1_mutex";

	int shm_fd = shm_open(shm_name, O_RDWR, 0);
	if (shm_fd <= 0) {
		cerr << "Error: shm_open() failed." << endl;
		exit (EXIT_FAILURE);
	}
	struct stat shm_stat;
	if (fstat(shm_fd, &shm_stat) == -1) {
		cerr << "fstat() returned -1." << endl;
		exit (EXIT_FAILURE);
	}

	const size_t shm_region_size = shm_stat.st_size;

	char* shm_ptr = (char*) mmap(0, shm_region_size, PROT_READ | PROT_WRITE,
			MAP_SHARED, shm_fd, 0);
	if (shm_ptr == MAP_FAILED) {
		cerr << "mmap() failed.\n";
		exit (EXIT_FAILURE);
	}
	close(shm_fd);

	sem_t* cnt_sem = sem_open(cnt_sem_name, 0);
	sem_t* mutex_sem = sem_open(mutex_sem_name, 0);

	if (cnt_sem == SEM_FAILED || mutex_sem == SEM_FAILED) {
		cerr << "Error: sem_open() returned SEM_FAILED." << endl;
		exit (EXIT_FAILURE);
	}
	/****************************************************************************/

	sem_wait(mutex_sem);
	if (produce(shm_ptr, argv[1], shm_region_size) == 0) {
		sem_post(cnt_sem);
		sem_post(mutex_sem);
	} else {
		sem_post(mutex_sem);
	}

	sem_close(cnt_sem);
	sem_close(mutex_sem);
	munmap(shm_ptr, shm_region_size);

	return 0;
}
