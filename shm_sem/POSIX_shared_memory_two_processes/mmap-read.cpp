#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

using namespace std;

int main(int argc, char** argv) {
	int fd;
	char* shm_ptr;

	const char* shm_name = "/learning_shm";
	const size_t region_size = sysconf(_SC_PAGE_SIZE);
	cout << "region_size = " << region_size << endl; // 4096 usually
	
	fd = shm_open(shm_name, O_CREAT | O_TRUNC | O_RDWR, 0666);

	if (0 != ftruncate(fd, region_size)) {
		cerr << "ftruncate() returned non-zero.\n";
		exit(EXIT_FAILURE);
	}

	shm_ptr = (char*) mmap(0, region_size, PROT_READ | PROT_WRITE, MAP_SHARED,
			fd, 0);

	if (shm_ptr == MAP_FAILED) {
		cerr << "mmap() failed.\n";
		exit(EXIT_FAILURE);
	}

	close(fd);
	
	string s1;
	string s2;
	
	for (int i = 0; i < 5; i++) {
		s1 = shm_ptr;
		stringstream ss;
		ss.str(s1);
		ss >> s2;
		cout << "s2 = " << s2 << endl;
		s1.clear();
		s2.clear();
		getline(ss, s1);
		
		memset(shm_ptr, 0, region_size);
		memcpy(shm_ptr, s1.c_str(), s1.size());
		cout << "shm_ptr points to " << shm_ptr << endl;
		usleep(5000000);
	}

	munmap(shm_ptr, region_size);
	shm_unlink(shm_name);

	return 0;
}
