#include <iostream>
#include <math.h>
#include <pqxx/pqxx>

float getS(pqxx::work &txn, std::string &s) {
	using namespace std;

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
	float y = 0.0;
	float z = 0.0;

	for (int i = 0; i < row_num; i++) {
		cout << "r[" << i << "] = ";
		for (int j = 0; j < column_num; j++) {
			cout << r[i][j].c_str() << " ";
		}
		cout << endl;
		r[0][9].to(x);
		r[0][12].to(y);
		//cout << x << endl;
		//cout << y << endl;
		z = (x + y) / 2.0;
	}

	//cout << "S = " << z << endl;

	return z;
}

float getR(float St, float Ss) {
	using namespace std;

	float r = 0.0;
	r = (St - Ss) / Ss;
	//cout << "R = " << r << endl;
	return r;
}

int getEquityReturn(std::string table_name, pqxx::work &txn, float* equity_return) {
	using namespace std;
	
	for (int i = 0; i < 18; i++) {
		string str[19] = {
			"'10:30:00'",
			"'10:40:00'",
			"'10:50:00'",
			"'11:00:00'",
			"'11:10:00'",
			"'11:20:00'",
			"'11:30:00'",
			"'11:40:00'",
			"'11:50:00'",
			"'12:00:00'",
			"'12:10:00'",
			"'12:20:00'",
			"'12:30:00'",
			"'12:40:00'",
			"'12:50:00'",
			"'13:00:00'",
			"'13:10:00'",
			"'13:20:00'",
			"'13:30:00'"
		};
		stringstream ss;
		string s;
		ss << "SELECT * FROM " << table_name << " WHERE EXTRACT(DOW FROM d) = 3 "
				"AND quote_time < TIME " << str[i]
				<< "ORDER BY quote_time DESC "
						"LIMIT 1";
		s = ss.str();
		ss.str(string());
		float St = getS(txn, s);
		ss << "SELECT * FROM " << table_name << " WHERE EXTRACT(DOW FROM d) = 3 "
				"AND quote_time < TIME " << str[i+1]
				<< "ORDER BY quote_time DESC "
						"LIMIT 1";
		s = ss.str();
		ss.str(string());
		float Ss = getS(txn, s);
		
		equity_return[i] = getR(St, Ss);
	}

	return 0;
}

float getMeanEquityReturn(float* equity_return) {
	float mean = 0.0;
	for (int i = 0; i < 18; i++) {
		mean = mean + equity_return[i];
	}
	mean = mean / 18.0;
	
	return mean;
}

float getStandardDeviation(float mean, float* equity_return) {
	float sd = 0.0;
	float tmp = 0.0;
	float sum = 0.0;
	for (int i = 0; i < 18; i++) {
		tmp = equity_return[i] - mean;
		tmp = pow(tmp, 2);
		sum = sum + tmp;
	}
	sd = sqrt(sum / 18.0);
	
	return sd;
}

int main(int argc, char** argv) {
	using namespace std;
	pqxx::connection c("user='roy' "
			"host='155.246.104.10' "
			"password='roy' "
			"dbname='DataFinance'");

	pqxx::work txn(c);

	float R[18];
	string table[10] = {
			"aapl_o",
			"ba",
			"cat",
			"csco_o",
			"cvx",
			"dd",
			"nke",
			"pg",
			"vz",
			"v_n",
	};
	
	for (int i = 0; i < 10; i++) {
		cout << "******************  " << table[i] << "  *******************" << endl;
		getEquityReturn(table[i], txn, R);

		cout << endl;
		cout << "10-Minute EquityReturn: " << endl;
		for (int i = 0; i < 18; i++) {
			cout << R[i] << endl;
		}
		
		float M = getMeanEquityReturn(R);
		
		cout << endl;
		cout << "Mean of EquityReturn = " << M << endl;
		
		float SD = getStandardDeviation(M, R);
		
		cout << endl;
		cout << "Standard Deviation of EquityReturn = " << SD << endl;
		cout << endl;
	}
	cout << endl;

	return 0;
}
