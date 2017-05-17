#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int fd = 0;

void handler(int s) {
	using namespace std;
	cout << "SIGPIPE received." << endl;
	close(fd);
	fd = 0;
}

int main(int argc, char** argv) {
	using namespace std;

	signal(SIGPIPE, handler);

	const char* path = "/tmp/fifo_test";

	int n = mkfifo(path, S_IRUSR | S_IWUSR | S_IXUSR);
	
	cout << "mkfifo() returned n = " << n << endl;
	if (n < 0) {
		cerr << strerror(errno) << endl;
	}

	//fd = open(path, O_WRONLY | O_NONBLOCK, 0);
	
	//cout << "open() returned fd =" << fd << endl;
	//if (fd < 0) {
	//	cerr << strerror(errno) << endl;
	//}

	char buf[5] = {'a', 'b', 'c', 'd', 'e'};

	int loop_cnt = 50;
	while(loop_cnt > 0) {
		loop_cnt--;
		if (fd <= 0) {
			fd = open(path, O_WRONLY | O_NONBLOCK, 0);
			cout << "open() returned fd =" << fd << endl;
			if (fd < 0) {
				cerr << strerror(errno) << endl;
				usleep(1000000);
			}
		}
		
		if (fd > 0) {
			n = write(fd, buf, 5);
			cout << "write() returned n = " << n << endl;
			if (n != 5) {
				cerr << strerror(errno) << endl;
			}
			usleep(500000);
		}
	}

	unlink(path);

	return 0;
}
