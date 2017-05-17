#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv) {
	using namespace std;

	const char* path = "/tmp/fifo_test";

	int fd = open(path, O_RDONLY | O_NONBLOCK, 0);
	cout << "open() returned fd = " << fd << endl;
	if (fd < 0) {
		cerr << strerror(errno) << endl;
		return -1;
	}

	char buf[5];
	
	int loop_cnt = 10;
	int n;
	while(fd > 0 && loop_cnt > 0) {
		loop_cnt--;
		n = read(fd, buf, 5);
		cout << "read() returned n = " << n << endl;
		usleep(500000);
	}

	return 0;
}
