// Bank.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "ServicesLibrary.h"

using namespace std;
using namespace ServicesFunction;
struct stClient {
	string accNumber;
	string Name;
	string Phone;
	string pinCode;
	double accBalance;
	bool markDeleted;
};
enum enShowMenue {
	eListClient=1,
	eAddClient=2,
	eDeleteClinet=3,
	eUpdateClient=4,
	eFindClient=5,
	eExit=6,
};
string FileName = "Clients.txt";

void showMainMenue();
bool findClients(string AccName, vector <stClient> vec, stClient& client);
void loadDataFromFileToVector(string FileName, vector <string>& vec);
void loadDataFromFileToVector(string FileName, vector <stClient>& vec);

string convertStructToString(stClient client, string delim = "#//#");
stClient convertStringToStruct(string str, string delim = "#//#");
void SaveRecordInFile(string FileName, string line);
void SaveDataInFile(string FileName, vector<stClient>vec);
void addClient();
void addAllClients();
stClient readClient();
stClient changeClient(string accNumber);

void printClient(stClient client);
void printHeaderShowList(int number);
void showClients();
void showAddClients();
void showDeleteClient();
void showUpdateClient();
void showFindClient();
void showExit();
void goBackToMain();
void chooseAnyFunction(enShowMenue Chose);
void PrintShowList();
void printClientRow(stClient client);
void printSentenceClient(string str, int number =10);

int main()
{
	showMainMenue();
	return 0;
}
bool updateClient(string accNumber, vector <stClient>& vec) {
	for (stClient& client : vec) {
		if (client.accNumber == accNumber) {
			client = changeClient(accNumber);
			return true;
		}
	}
	return false;
}
bool markDeleted(string AccNumber, vector<stClient> &vec) {
	
	for (stClient& client : vec) {
		if (client.accNumber == AccNumber) {
			client.markDeleted = true;
			return true;
		}

	}
	return false;
}
void printHeaderShowList(int number) {
	string headerShowList = "\n\t\t\t\tClients(" + to_string(number) + ").";
	if (number == 0) {
		printHeader("\n\t\t\tNot Clients Available .", '=', 100);
		return;
	}
	printHeader(headerShowList, '=', 100);
	printShapeHeader('-', 110);
	printSentenceClient("Account Number", 15);
	printSentenceClient("Pin Code",10);
	printSentenceClient("Name", 40);
	printSentenceClient("Phone", 15);
	printSentenceClient("Balance", 15);
	printShapeHeader('-', 110);
}
void PrintShowList() {
	vector <string> vClients;
	loadDataFromFileToVector(FileName, vClients);
	printHeaderShowList(vClients.size());
	for (string& client : vClients) {
		printClientRow(convertStringToStruct(client));
		cout << endl;
	}
}
void printSentenceClient(string str, int number ) {
	cout << "| " << setw(number) << left << str;
}
void printClientRow(stClient client) {
	printSentenceClient(client.accNumber, 15);
	printSentenceClient(client.pinCode,10);
	printSentenceClient(client.Name, 40);
	printSentenceClient(client.Phone, 15);
	printSentenceClient(to_string(client.accBalance), 15);
}
 string convertStructToString(stClient client, string delim ) {
	return client.accNumber + delim + client.pinCode + delim + client.Name + delim + client.Phone + delim + to_string(client.accBalance);
}
stClient convertStringToStruct(string str, string delim ) {
	vector<string> vSplite = splitString(str, delim);
	stClient client;
	client.accNumber = vSplite[0];
	client.pinCode = vSplite[1];
	client.Name = vSplite[2];
	client.Phone = vSplite[3];
	client.accBalance = stod(vSplite[4]);
	return client;
}
void SaveDataInFile(string FileName, vector<stClient>vec) {
	fstream myFile;
	string line;
	myFile.open(FileName, ios::out);
	if (myFile.is_open()) {
		for (stClient& client : vec) {
			if (client.markDeleted == false) {
				line = convertStructToString(client);
				myFile << line << endl;
			}
		}

		myFile.close();
	}
}
void SaveRecordInFile(string FileName, string line) {
	fstream myFile;

	myFile.open(FileName, ios::out | ios::app);
	if (myFile.is_open()) {

		myFile << line << endl;
		myFile.close();
	}
}
void loadDataFromFileToVector(string FileName, vector <string>& vec) {
	fstream myFile;
	string line;
	myFile.open(FileName, ios::in);
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			vec.push_back(line);
		}
		myFile.close();
	}
}
void loadDataFromFileToVector(string FileName, vector <stClient>& vec) {
	fstream myFile;
	string line;
	stClient tempClient;
	myFile.open(FileName, ios::in);
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			tempClient = convertStringToStruct(line);
			vec.push_back(tempClient);
		}
		myFile.close();
	}
}

void addClient() {
	cout << "\n\t\t\tAdding New Client.\n\n";
	stClient client = readClient();
	string line = convertStructToString(client);
	SaveRecordInFile(FileName, line);
}
void addAllClients() {
	char c = 'y';
	while (c == 'y' || c == 'Y') {
		addClient();
		cout << "Do You Want Add More Client(Y|N) ?";
		cin >> c;
	}
}
bool findClients(string AccName, vector <stClient> vec, stClient& client) {

	for (stClient& c : vec) {
		if (c.accNumber == AccName) {
			client = c;
			return true;
		}
	}

	return false;
}
stClient readClient() {
	stClient client;
	vector <stClient>vClient;
	loadDataFromFileToVector(FileName, vClient);
	cout << "\t Enter AccNumber ? ";
	cin >> client.accNumber;
	while (findClients(client.accNumber, vClient, client)) {
		cout << "\t This Account Number Alredy Exsist , Enter AccNumber ? ";
		cin >> client.accNumber;
	}
	cout << "\t Enter Pin Code ?";
	getline(cin >> ws, client.pinCode);
	cout << "\t Enter Name ?";
	getline(cin >> ws, client.Name);
	cout << "\t Enter Phone ?";
	getline(cin >> ws, client.Phone);
	client.accBalance = readPositiveNumber("\t Enter Account Balance ? ");
	client.markDeleted = false;


	return client;
}
stClient changeClient(string accNumber) {
	stClient client;
	client.accNumber = accNumber;
	cout << "\t Enter Pin Code ?";
	getline(cin >> ws, client.pinCode);
	cout << "\t Enter Name ?";
	getline(cin >> ws, client.Name);
	cout << "\t Enter Phone ?";
	getline(cin >> ws, client.Phone);
	client.accBalance = readPositiveNumber("\t Enter Account Balance ? ");
	client.markDeleted = false;


	return client;
}
void printClient(stClient client) {
	cout << "Account Number : " << client.accNumber << endl;
	cout << "Pin Code       : " << client.pinCode << endl;
	cout << "Name           : " << client.Name << endl;
	cout << "Phone          : " << client.Phone << endl;
	cout << "Account Balance: " << client.accBalance << endl;
}
void showClients() {
	printHeader("All Clients.", '-');
	PrintShowList();
}
void showAddClients() {
	printHeader("Add New Clients.", '-');
	addAllClients();
}
void showDeleteClient() {
	printHeader("Delete Client.", '-');
	char c = 'n';
	string accName;
	
	vector<stClient>vClient;
	stClient tempClient;
	loadDataFromFileToVector(FileName, vClient);
	cout << "Enter AccName ?";
	getline(cin >> ws, accName);
	if (findClients(accName,vClient, tempClient)) {
		printClient(tempClient);
		cout << "\n\tAre You Sure Delete(y|n)";
		cin >> c;
		if (c == 'y' || c == 'Y') {
			markDeleted(accName, vClient);
			SaveDataInFile(FileName, vClient);
			cout << "Deleted The Account [" << accName << "] .\n";
			
		}
		else {
			cout<<"Not Deleted The Account [" << accName << "] !.\n";
		}
	}
	else {
		cout << "\n\tNot Found Account Number[" << accName << "].\n";
	}
}
void showUpdateClient() {
	printHeader("Update Client.", '-');
	vector <stClient> vClients;
	string accNumber;
	char update = 'y';
	stClient tempClient;
	loadDataFromFileToVector(FileName, vClients);
	cout << "\t Enter Acc Number ? ";
	cin >> accNumber;
	if (findClients(accNumber ,vClients,tempClient) ) {
		printClient(tempClient);
		cout << "Do You Sure Change Data ?";
		cin >> update;
		if (update) {
			updateClient(accNumber, vClients);
			SaveDataInFile(FileName, vClients);
			cout << "Changed Data Success!!";

		}
		else {
			cout << "\t Not Changed Data!!.\n";
		}
	}
	else {
		cout << "\t Not Found AccNumber [" << accNumber << "] !.\n";
	}
}
void showFindClient() {
	printHeader("Find Client.", '-');
	string accName;
	stClient client;
	vector<stClient> vClients;
	loadDataFromFileToVector(FileName, vClients);
	cout << "\n\n\tEnter AccName => ";
	getline(cin >> ws, accName);
	if (findClients(accName, vClients, client)) {
		printClient(client);
	}
	else {
		cout << "Account Number [" << accName << "] Not Found ! \n";
	}
}
void showExit() {
	printHeader("Program Ends.", '-');
}
void goBackToMain() {
	cout << "Enter Any Key To return ...";
	system("pause>0");
	showMainMenue();
}
void chooseAnyFunction(enShowMenue Chose) {
	switch (Chose) {
	case eListClient: {
		showClients();
		goBackToMain();
		break;
	}
	case eAddClient: {
		showAddClients();
		goBackToMain();
		break;
	}case eDeleteClinet: {
		showDeleteClient();
		goBackToMain();
		break;
	}case eUpdateClient: {
		showUpdateClient();
		goBackToMain();
		break;
	}case eFindClient: {
		showFindClient();
		goBackToMain();
		break;
	}case eExit: {
		showExit();
		break;
	}
	}
}
void showMainMenue() {

	printHeader("Main Menue Screen.", '=');
	cout << "\n [1] Show Clients .\n";
	cout << " [2] Add Clients .\n";
	cout << " [3] Delete Client .\n";
	cout << " [4] Update Client .\n";
	cout << " [5] Find Clients .\n";
	cout << " [6] Exit .\n\n";
	chooseAnyFunction((enShowMenue)readChooseNumber());
}