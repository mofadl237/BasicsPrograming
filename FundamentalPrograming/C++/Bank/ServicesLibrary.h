#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
namespace ServicesFunction {
	double readPositiveNumber(string str) {
		cout << str;
		double number;
		cin >> number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Enter Valid Number => ";
			cin >> number;

		}
		return number;
	}
	vector<string> splitString(string str, string delim = "#//#") {
		vector<string> vSplite;
		string word;
		short pos = 0;
		while ((pos = str.find(delim)) != string::npos) {
			word = str.substr(0, pos);
			if (word != "")
				vSplite.push_back(word);
			str.erase(0, pos + delim.length());
		}

		if (str != "") {
			vSplite.push_back(str);
		}

		return vSplite;
	}
	void printShapeHeader(char c, int count ) {
		cout << "\n\n";
		for (int i = 0;i < count;i++) {
			cout << c;
		}
		cout << "\n\n";
	}
	void printHeader(string str, char c, int count=50) {
		system("cls");
		printShapeHeader(c, count);
		cout << "\t"<<str;
		printShapeHeader(c, count);
	}
	int readChooseNumber() {
		int number;
		cout << "Choose What Do You Want To Do [1 To 6] ?";
		cin >> number;
		while (cin.fail()  || number < 1 || number > 6) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Enter Valid Number => ";
			cin >> number;
		}
		return number;
	}
}