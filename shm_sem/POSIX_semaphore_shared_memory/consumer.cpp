#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <semaphore.h>

static inline void consume(char* shm_ptr, size_t shm_size) {
	using namespace std;

	string s1;
	string s2;

	s1 = shm_ptr;
	stringstream ss;
	ss.str(s1);
	ss >> s2;
	cout << "Signal Consumed: " << s2 << endl;
	s2.clear();
	s1.clear();

	getline(ss, s1);
	memset(shm_ptr, 0, shm_size);
	memcpy(shm_ptr, s1.c_str(), s1.size());
}

int main(int argc, char** argv) {
	using namespace std;

	/********************Initialize shm and semaphores*********************/
	const char* shm_name = "/region_1_shm";
	const char* cnt_sem_name = "/region_1_counter";
	const char* mutex_sem_name = "/region_1_mutex";
	size_t shm_region_size = sysconf(_SC_PAGE_SIZE);

	int shm_fd = shm_open(shm_name, O_CREAT | O_TRUNC | O_RDWR,
			S_IRUSR | S_IWUSR | S_IXUSR);
	if (shm_fd <= 0) {
		cerr << "Error: shm_open() failed." << endl;
		exit (EXIT_FAILURE);
	}
	if (ftruncate(shm_fd, shm_region_size) != 0) {
		cerr << "ftruncate() returned non-zero." << endl;
		exit (EXIT_FAILURE);
	}
	char* shm_ptr = (char*) mmap(0, shm_region_size, PROT_READ | PROT_WRITE,
			MAP_SHARED, shm_fd, 0);
	if (shm_ptr == MAP_FAILED) {
		cerr << "mmap() failed." << endl;
		exit (EXIT_FAILURE);
	} else {
		close(shm_fd);
	}

	sem_t* cnt_sem = sem_open(cnt_sem_name, O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IXUSR, 0);
	sem_t* mutex_sem = sem_open(mutex_sem_name, O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IXUSR, 1); // initial value equals 1
	if (cnt_sem == SEM_FAILED || mutex_sem == SEM_FAILED) {
		cerr << "Error: sem_open() returned SEM_FAILED." << endl;
		exit (EXIT_FAILURE);
	}
	/*********************************************************************/

	int loop_cnt = 10;

	while (loop_cnt > 0) {
		loop_cnt--;
		sem_wait(cnt_sem);
		cout << "cnt_sem is decreased by 1" << endl;
		sem_wait(mutex_sem);
		consume(shm_ptr, shm_region_size);
		//sleep(5);
		sem_post(mutex_sem);
	}

	sem_close(cnt_sem);
	sem_close(mutex_sem);

	sem_unlink(cnt_sem_name);
	sem_unlink(mutex_sem_name);

	munmap(shm_ptr, shm_region_size);
	shm_unlink(shm_name);

	return 0;
}
