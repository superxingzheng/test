#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv) {
	using namespace std;

	string str = "1 0 0 0 0.0 0.0*";
	int str_len = str.size();
	char buffer[str_len + 1];
	strcpy(buffer, str.c_str());

	int fd = open("/tmp/ImpulseNode_INPUT_test", O_WRONLY | O_SYNC);
	
	while (1) {
		cout << "Press any key to coninue." << endl;
		cin.get();
		string str = "1 0 0 0 0.2 0.2*";
		strcpy(buffer, str.c_str());
		write(fd, &str_len, sizeof(str_len));
		write(fd, buffer, str_len);
		
		cin.get();
		str = "1 0 0 0 0.0 0.0*";
		strcpy(buffer, str.c_str());
		write(fd, &str_len, sizeof(str_len));
		write(fd, buffer, str_len);
	}
	
	close(fd);

	return 0;
}
