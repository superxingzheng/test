#include <iostream>
#include <fstream>
#include <math.h>
#include <pqxx/pqxx>

int getMinutePrice(std::string table_name, pqxx::work &txn, float* price) {
	using namespace std;

	for (int p = 0; p < 180; p++) {
		price[p] = 0.0;
	}
	
	stringstream ss;
	string str[3][60];
	for (int i = 10; i <= 12; i++) {
		for (int j = 0; j <= 29; j++) {
			// example: 10:30:10.244
			ss << i << ":" << j + 30;
			str[i - 10][j] = ss.str();
			ss.str(string());
			cout << "time = " << str[i - 10][j] << endl;

			if (j > 0) {
				string s;
				ss << "SELECT * FROM " << table_name
						<< " WHERE EXTRACT(DOW FROM d) = 3 "
								"AND t > TIME '" << str[i - 10][j - 1]
						<< "' AND t < TIME '" << str[i - 10][j]
						<< "' AND price > 0" << "ORDER BY price DESC "
								"LIMIT 1";
				s = ss.str();
				ss.str(string());

				pqxx::result r = txn.exec(s);
				if (r.size() == 0) {
					cout << "Query returned nothing..." << endl;
					return -1;
				}
				//cout << "r.size() = " << r.size() << endl;
				//int row_num = r.size();
				int row_num = 1;
				int column_num = r[0].size();
				//cout << "column_num = " << column_num << endl;

				float x = 0.0;

				for (int k = 0; k < row_num; k++) {
					for (int m = 0; m < column_num; m++) {
						cout << r[k][m].c_str() << " ";
					}
					cout << endl;

					r[0][6].to(x);

					cout << "price = " << x << endl;

					int index = (i - 10) * 60 + j;
					price[index] = x;
				}
			}
		}
		for (int j = 30; j <= 59; j++) {
			ss << i + 1 << ":" << j - 30;
			str[i - 10][j] = ss.str();
			ss.str(string());
			cout << "time = " << str[i - 10][j] << endl;

			if (j < 59 && j > 30) {
				string s;
				ss << "SELECT * FROM " << table_name
						<< " WHERE EXTRACT(DOW FROM d) = 3 "
								"AND t > TIME '" << str[i - 10][j - 1]
						<< "' AND t < TIME '" << str[i - 10][j]
						<< "' AND price > 0" << "ORDER BY price DESC "
								"LIMIT 1";
				s = ss.str();
				ss.str(string());

				pqxx::result r = txn.exec(s);
				if (r.size() == 0) {
					cout << "Query returned nothing..." << endl;
					return -1;
				}
				//cout << "r.size() = " << r.size() << endl;
				//int row_num = r.size();
				int row_num = 1;
				int column_num = r[0].size();
				//cout << "column_num = " << column_num << endl;

				float x = 0.0;

				for (int k = 0; k < row_num; k++) {
					for (int m = 0; m < column_num; m++) {
						cout << r[k][m].c_str() << " ";
					}
					cout << endl;

					r[0][6].to(x);

					cout << "price = " << x << endl;

					int index = (i - 10) * 60 + j;
					price[index] = x;
				}
			}
		}
	}

	return 0;
}

int updatePlot(std::string &path, float* price) {
	using namespace std;

	std::ofstream outfile(path.c_str());

	for (int i = 0; i < 180; i++) {
		outfile << i << ' ' << price[i] << endl;
	}

	outfile.close();

	return 0;
}

int main(int argc, char** argv) {
	using namespace std;
	pqxx::connection c("user='roy' "
			"host='155.246.104.10' "
			"password='roy' "
			"dbname='DataFinance'");

	pqxx::work txn(c);

	string table[10] = { "ba", "aapl_o", "cat", "csco_o", "cvx", "dd", "nke",
			"pg", "vz", "v_n", };

	for (int i = 0; i < 10; i++) {
		cout << "******************  " << table[i] << "  *******************"
				<< endl;

		float price[180];
		getMinutePrice(table[i], txn, price);
		string path = table[i] + ".txt";
		updatePlot(path, price);

		cout << endl;
	}

	return 0;
}
