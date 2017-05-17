#include <iostream>
#include <sstream>

int main() {
	using namespace std;
	string s = "1 2 3 4.0 2.3*";
	stringstream ss;
	ss.str(s);
	float n = 0.0;
	int c = 0;
	do {
		c = ss.peek();
		if (c == '*') {
			cout << "Found *." << endl;
			cout << "c = " << c << endl;
		} else {
			ss >> n;
			cout << n << endl;
		}
	} while (c != '*');

	return 0;
}
