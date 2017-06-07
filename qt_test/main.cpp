#include <iostream>
#include <fstream>

#include <QApplication>

#include "form.h"

int main(int argc, char *argv[]) {
	using namespace std;
	
	QApplication app(argc, argv);
	MyForm form(0);
	
	form.plot_k = atoi(argv[1]);
	
	string table[10] = { "ba", "aapl_o", "cat", "csco_o", "cvx", "dd", "nke",
			"pg", "vz", "v_n", };
	
	string path = "";
	
	for (int i = 0; i < 10; i++) {
		path = "";
		path = table[i] + ".txt";
		
		ifstream input_file(path.c_str());
		
		for (int j = 0; j < 180; j++) {
			form.price[i][j] = 0.0;
			input_file >> form.price[i][j];
		}
	}
	
	form.plot();
	
	form.show();

	return app.exec();
}
