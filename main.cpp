#include <iostream> 
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void staticMatrix();
void dynamicMatrix();
int posRows(vector<vector<int>> array, int rows, int columns);
void outArray(vector<vector<int>> array, int rows, int columns, string path);
string delSymbol(string str, char symbol);
string selPath();
vector<vector<int>> drawing(vector<vector<int>> matrix, int N);
const int nrows(5), ncolumns(5);


int main() {

	while (true) {

		string inp;
		int N;
		cout << "1. Static matrix" << endl << "2. Dynamic matrix" << endl << "3. Exit" << endl << "Choose an option: ";

		while (true) {

			cin >> inp;
			cout << endl;

			try {

				N = stoi(inp);

			}
			catch (exception) {

				cout << "You should enter a number from 1 to 3" << endl;
				continue;

			}
			if ((inp.find('.') != inp.npos) || (inp.find(',') != inp.npos)) {

				cout << "You should enter an integer from 1 to 3" << endl;
				continue;

			}
			if (N != 1 && N != 2 && N != 3) {

				cout << "You should enter a number from 1 to 3" << endl;
				continue;

			}

			break;

		}

		if (N == 1) {
			staticMatrix();
		}
		else if (N == 2) {
			dynamicMatrix();
		}
		else {
			break;
		}

	}

	cout << "See you later!" << endl;
	system("pause");
	return 0;

}

void staticMatrix() {

	string out_path = selPath();
	vector <vector<int>> array;
	ofstream out(out_path);
	string inputed;

	if (out.is_open()) {

		for (int i = 0; i < nrows; i++) {
			vector <int> v1;
			for (int k = 0; k < ncolumns; k++) {

				cout << "Row " << i + 1 << " column " << k + 1 << ": ";
				cin >> inputed;
				cout << endl;

				if ((inputed.find('.') != inputed.npos) || (inputed.find(',') != inputed.npos)) {

					cout << "Value must be integer" << endl;
					k--;
					continue;

				}

				try {

					v1.push_back(stoi(inputed));

				}
				catch (exception) {

					cout << "Invalid value" << endl;
					k--;
					continue;

				}

			}
			array.push_back(v1);
		}
		out.close();
		outArray(array, 5, 5, out_path);
		ofstream out(out_path, ios::app);
		cout << "Rows with unique numbers: " << posRows(array, 5, 5) << endl;
		out << "Rows with unique numbers: " << posRows(array, 5, 5) << endl;

	}
	else {

		cout << "Can't create output file" << endl;

	}

	cout << endl;

}

void dynamicMatrix() {

	string path, inpath;
	bool fstate(true);
	cout << "Output path: ";
	path = selPath();
	cout << "Input path: ";
	inpath = selPath();
	int side;

	ifstream ipath(inpath);
	if (ipath.is_open()) {
		string frow;
		int rcount(0);
		while (getline(ipath, frow)) {
			if (!frow.empty())
				rcount++;
		}
		if (rcount > 0) {
			ifstream ipath1(inpath);
			while (getline(ipath1, frow)) {
				if (!frow.empty()) {
					if (frow.find('.') != frow.npos || frow.find(',') != frow.npos) {
						cout << "Value must be integer" << endl;
						fstate = false;
						break;
					}
					try {
						side = stoi(frow);
					}
					catch (exception) {
						cout << "Invalid value" << endl;
						fstate = false;
						break;
					}
					if (side < 1) {
						cout << "Value must be positive" << endl;
						fstate = false;
						break;
					}
					break;
				}
			}
		}
		else {
			fstate = false;
		}

	}
	else {
		fstate = false;
	}
	if (!fstate) {
		cout << "An error occured while getting values from a file." << endl;
		string inconsole;
		while (true) {

			cout << "Enter matrix side: " << endl;
			cin >> inconsole;

			if (inconsole.find('.') != inconsole.npos || inconsole.find(',') != inconsole.npos) {
				cout << "Value must be integer" << endl;
				continue;
			}
			try {
				side = stoi(inconsole);
			}
			catch (exception) {
				cout << "Invalid value" << endl;
				continue;
			}
			if (side < 1) {
				cout << "Value must be positive" << endl;
				continue;
			}
			break;
		}
	}
	vector <vector<int>> matrix;
	for (int b = 0; b < side; b++) {

		vector<int> vtemp;
		for (int v = 0; v < side; v++) {

			vtemp.push_back(1);

		}
		matrix.push_back(vtemp);

	}

	matrix = drawing(matrix, side);
	ofstream out(path);
	for (int f = 0; f < side; f++) {
		for (int g = 0; g < side; g++) {

			cout << matrix[f][g] << " ";
			out << matrix[f][g] << " ";

		}
		cout << endl;
		out << endl;
	}

	cout << endl;

}

int posRows(vector<vector<int>> array, int rows, int columns) {

	vector <int> temparray(columns);
	int result(0);
	bool state(true);

	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < columns; k++) {

			temparray.at(k) = array[i][k];

			if (k == columns - 1) {

				for (int q = 0; q < columns; q++) {

					for (int j = 0; j < columns; j++) {

						if ((temparray.at(q) == temparray.at(j) && (q != j))) {

							state = false;
							break;

						}
						if (!state)break;

					}

				}

			}
		}
		if (state) {

			result++;
		}
		else {
			state = true;
		}
	}

	return result;
}

void outArray(vector<vector<int>> array, int rows, int columns, string path) {

	ofstream out(path.c_str(), ios::app);
	for (int s = 0; s < rows; s++) {
		for (int d = 0; d < columns; d++) {

			cout << array[s][d] << " ";
			out << array[s][d] << " ";

		}
		cout << endl;
		out << endl;
	}
	out.close();

}
string delSymbol(string str, char symbol) {

	int length = str.length();
	string newstr;

	for (int k = 0; k < length; k++) {

		if (str[k] != symbol) {
			newstr.append(1, str[k]);
		}

	}

	return newstr;
}

string selPath() {

	string ipath;
	while (true) {

		cout << "Enter path to the file:" << endl;
		cin >> ipath;
		cout << endl;

		int n = ipath.length();
		for (int i = 0; i < n; i++) {

			if (ipath[i] == '\\') {
				ipath[i] = '/';
			}

		}
		ipath = delSymbol(ipath, '\"');
		ipath = delSymbol(ipath, ' ');


		int n1 = ipath.length();
		if (n1 < 4 || (ipath[n1 - 1] != 't' && ipath[n1 - 2] != 'x' && ipath[n1 - 3] != 't' && ipath[n1 - 4] != '.')) {
			cout << "File must be .txt" << endl;
		}
		else {
			break;
		}

	}


	return ipath;
}

vector<vector<int>> drawing(vector<vector<int>> matrix, int N) {
	int y;
	if (N % 2 == 0)y = N / 2;
	if (N % 2 == 1)y = N / 2 + 1;

	for (int temp = 0; temp < y; temp++) {

		for (int k = 0; k < N; k++) {

			for (int u = 0; u < N; u++) {

				if ((k == 0 + temp && u == 0 + temp) || (k == 0 + temp && u == N - 1 - temp) || (k == N - 1 - temp && u == 0 + temp) || (k == N - 1 - temp && u == N - 1 - temp) || (k == 0 + temp && u > 0 + temp && u < N - 1 - temp) || (k == N - 1 - temp && u > 0 + temp && u < N - 1 - temp) || (k > 0 + temp && k < N - 1 - temp && u == 0 + temp) || (k > 0 + temp && k < N - 1 - temp && u == N - 1 - temp)) {
					matrix[u][k] = temp + 1;
				}

			}

		}
	}

	return matrix;
}