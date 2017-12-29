#include <iostream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

using namespace std;

int main(int argc, char** argv) {
	int fd;
	char* shm_ptr;

	struct stat sb;
	const char* shm_name = "/learning_shm";

	fd = shm_open(shm_name, O_RDWR, 0);

	if (-1 == fstat(fd, &sb)) {
		cerr << "fstat() returned -1." << endl;
		exit (EXIT_FAILURE);
	}
	const size_t region_size = sb.st_size;
	//cout << "region_size = " << region_size << endl;

	shm_ptr = (char*) mmap(0, region_size, PROT_READ | PROT_WRITE, MAP_SHARED,
			fd, 0);

	if (shm_ptr == MAP_FAILED) {
		cerr << "mmap() failed.\n";
		exit (EXIT_FAILURE);
	}

	close(fd);

	stringstream ss;
	
	/* Make a copy of the contents in shm with a string object. */
	string s(shm_ptr);

	/* Append new data to end the existing contents of the shm. */
	if (s.size() == 0) {
		ss << argv[1];
	} else {
		ss << s << ' ' << argv[1];
	}
	s = ss.str();

	/* Check if the updated contents exceed the size of the shm. */
	if (s.size() > region_size) {
		cerr << "Error: s.size() > region_size.\n";
		exit (EXIT_FAILURE);
	}

	/* Write the updated contents to the shm. */
	memcpy(shm_ptr, s.c_str(), s.size());
	cout << s.size() << " Bytes copied into shm region." << endl;

	munmap(shm_ptr, region_size);

	return 0;
}
