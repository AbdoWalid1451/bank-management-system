#include<iostream>
#include<string>
#include<cctype>
#include<vector>
#include<fstream>
#include<iomanip>


using namespace std;


const string ClientFileName = "ClintsData.txt";

const string delim = "#//#";


//======== for data ======

enum enChoicesList
{
	showclientlist = 1, addnewclients = 2,
	deleteclient = 3, updateclientinfo = 4,
	findclient = 5, transactions = 6,
	manageusers = 7, logout = 8
};

struct stClientData
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
};

//******************** Helper Functions ******************
vector<string> SplitString(string s, string delim)
{
	vector<string> vSplit;

	size_t pos = 0;
	string sWord;

	while ((pos = s.find(delim)) != std::string::npos)
	{
		sWord = s.substr(0, pos);
		if (sWord != "")
			vSplit.push_back(sWord);

		s.erase(0, pos + delim.length());


	}

	if (s != "")
		vSplit.push_back(s);

	return vSplit;

}

stClientData ConvertLineToRecord(string line, string delim)
{
	vector<string> vData = SplitString(line, delim);

	stClientData ClientData;
	ClientData.AccountNumber = vData[0];
	ClientData.PinCode = vData[1];
	ClientData.Name = vData[2];
	ClientData.Phone = vData[3];
	ClientData.AccountBalance = stod(vData[4]);

	return ClientData;
}

vector<stClientData>  LoadDataClintsFromFileToStrVector(string filename, string delim)
{
	vector<stClientData> vClients;
	fstream myfile;

	myfile.open(filename, ios::in);

	if (myfile.is_open())
	{
		string line;
		while (getline(myfile, line))
		{
			vClients.push_back(ConvertLineToRecord(line, delim));

		}

		myfile.close();
	}
	return vClients;
}

string ConvertRecordToLine(stClientData ClientData, string delim)
{
	string str = "";
	str = ClientData.AccountNumber + delim
		+ ClientData.PinCode + delim
		+ ClientData.Name + delim
		+ ClientData.Phone + delim
		+ to_string(ClientData.AccountBalance);

	return str;
}

void LoadDataFromVectorToFile(string filename, vector<string>& vContentFile)
{
	fstream myfile;

	myfile.open(filename, ios::out);

	if (myfile.is_open())
	{

		for (string& n : vContentFile)
		{
			if (n != "")
				myfile << n << endl;
		}


		myfile.close();

	}

}

short FindClintUseAcountName(vector<stClientData> vClients, string AcountNumber)
{
	short pos = 0;

	for (stClientData& Client : vClients)
	{
		if (Client.AccountNumber == AcountNumber)
			return pos;

		pos++;
	}

	return -1;
}

string ReadNewAccountNumber()
{
	string AcNum;

	cout << "\nPlease enter Acount Number? ";
	getline(cin >> ws, AcNum);

	short pos = FindClintUseAcountName(LoadDataClintsFromFileToStrVector(ClientFileName, delim), AcNum);
	while (pos != -1)
	{
		cout << "Client With [" << AcNum << "] already exit\n";

		cout << "\nPlease enter Acount Number? ";
		getline(cin >> ws, AcNum);

		pos = FindClintUseAcountName(LoadDataClintsFromFileToStrVector(ClientFileName, delim), AcNum);

	}


	return AcNum;
}

short ReadAccountNumberExisted()
{
	string AcNum;

	cout << "\nPlease enter Acount Number? ";
	getline(cin >> ws, AcNum);

	short pos = FindClintUseAcountName(LoadDataClintsFromFileToStrVector(ClientFileName, delim), AcNum);
	while (pos == -1)
	{
		cout << "Client With [" << AcNum << "] does not Found\n";

		cout << "\nPlease enter Acount Number? ";
		getline(cin >> ws, AcNum);

		pos = FindClintUseAcountName(LoadDataClintsFromFileToStrVector(ClientFileName, delim), AcNum);

	}


	return pos;
}

void PrintClientRecord(stClientData Client)
{
	cout << "\nAccount number  : " << Client.AccountNumber << endl;
	cout << "Pin code        : " << Client.PinCode << endl;
	cout << "Name            : " << Client.Name << endl;
	cout << "Phone           : " << Client.Phone << endl;
	cout << "Account Balance : " << Client.AccountBalance << endl;


}







int main()
{


}




