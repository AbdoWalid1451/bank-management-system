#include<iostream>
#include<string>
#include<cctype>
#include<vector>
#include<fstream>
#include<iomanip>


using namespace std;


const string ClientFileName = "data/ClintsData.txt";

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




//---------------- SHOW CLIENT LIST ---------
void PrintClientRecordAsLine(stClientData Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;
	cout << endl;

}

void PrintHeadOfClientList()
{
	cout << "----------------------------------------------------------------------------------------------------\n";

	cout << "| " << left << setw(15) << "Acount Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance\n";

	cout << "------------------------------------------------------------------------------------------------------\n\n";

}

void ShowClientList()
{
	system("cls");
	vector<stClientData> vClients = LoadDataClintsFromFileToStrVector(ClientFileName, delim);

	cout << "\t\t\t\t\t Clients List (" << vClients.size() << ") Client(s).\n";

	PrintHeadOfClientList();

	for (stClientData Client : vClients)
		PrintClientRecordAsLine(Client);

}



//------------------ ADD CLIENTS --------------
stClientData ReadClientData()
{
	stClientData ClientData;

	ClientData.AccountNumber = ReadNewAccountNumber();


	cout << "Enter Pin Code? ";
	getline(cin >> ws, ClientData.PinCode);

	cout << "Enter Name? ";
	getline(cin, ClientData.Name);

	cout << "Enter Phone? ";
	getline(cin, ClientData.Phone);

	cout << "Enter AcountBalance? ";
	cin >> ClientData.AccountBalance;

	return ClientData;
}

void SendLintToFile(string FileName, string DataClientline)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << DataClientline << endl;

		MyFile.close();
	}

}

void AddNewClient()
{
	stClientData ClientData;

	ClientData = ReadClientData();

	SendLintToFile(ClientFileName, ConvertRecordToLine(ClientData, delim));


}

void AddClients()
{

	char more = 'n';

	do
	{

		AddNewClient();

		cout << "Client Added Successfuly, do you want add more clients?(Y||N)? ";
		cin >> more;

	} while (more == 'y' || more == 'Y');

}

void PrintHeadOfAddClients()
{
	cout << "---------------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "---------------------------------------\n";
	cout << "Adding New Client\n";


}

void AddNewClients()
{
	system("cls");

	PrintHeadOfAddClients();

	AddClients();
}




//---------------- DELETE CLIENTS -----------
bool AskDeleteAccount()
{
	char chouse = 'n';

	cout << "\n Are you sure you want to delete account? y/n? ";
	cin >> chouse;

	return (tolower(chouse) == 'y') ? 1 : 0;


}

void DeleteFromVectorAndFile(vector<stClientData> vClients, short pos)
{
	vector<string> vClientsAsLines;

	for (stClientData& Client : vClients)
		vClientsAsLines.push_back(ConvertRecordToLine(Client, delim));

	vClientsAsLines.at(pos) = "";

	LoadDataFromVectorToFile(ClientFileName, vClientsAsLines);
}

void Delete()
{

	short pos = ReadAccountNumberExisted();

	vector<stClientData> vClients = LoadDataClintsFromFileToStrVector(ClientFileName, delim);

	PrintClientRecord(vClients.at(pos));

	if (AskDeleteAccount())
	{
		DeleteFromVectorAndFile(vClients, pos);
		cout << "\nClient Deleted Successfully. \n";

	}
	else
		cout << "The Account Still There\n";

}

void PrintHeaderOfDeleteClint()
{
	cout << "---------------------------------------\n";
	cout << "\t\t Delete Client Screen\n";
	cout << "---------------------------------------\n";

}

void DeleteClient()
{
	system("cls");

	PrintHeaderOfDeleteClint();

	Delete();
}



//----------------- UPDATE CLIENT DATA --------
void ReadClientDataUpdate(stClientData& ClientData)
{


	cout << "Enter Pin Code? ";
	getline(cin >> ws, ClientData.PinCode);

	cout << "Enter Name? ";
	getline(cin, ClientData.Name);

	cout << "Enter Phone? ";
	getline(cin, ClientData.Phone);

	cout << "Enter AcountBalance? ";
	cin >> ClientData.AccountBalance;


}

bool AskUpdateAccount()
{
	char chouse = 'n';

	cout << "\n Are you sure you want to update account? y/n? ";
	cin >> chouse;

	return (tolower(chouse) == 'y') ? 1 : 0;


}

void UpdateInVectorAndFile(vector<stClientData>& vClients, short pos)
{

	ReadClientDataUpdate(vClients.at(pos));

	vector<string> vClientsAsLines;

	for (stClientData& Client : vClients)
		vClientsAsLines.push_back(ConvertRecordToLine(Client, delim));



	LoadDataFromVectorToFile(ClientFileName, vClientsAsLines);
}

void Update()
{
	vector<stClientData> vClients = LoadDataClintsFromFileToStrVector(ClientFileName, delim);

	short pos = ReadAccountNumberExisted();

	PrintClientRecord(vClients.at(pos));

	if (AskUpdateAccount())
	{
		UpdateInVectorAndFile(vClients, pos);
		cout << "\nClient Updated Successfully. \n";

	}
	else
		cout << "The Account Still There\n";

}

void PrintHeaderOfUpdateClientInfo()
{
	cout << "---------------------------------------\n";
	cout << "\t\t Update Client Screen\n";
	cout << "---------------------------------------\n";


}

void UpdateClientInfo()
{
	system("cls");

	PrintHeaderOfUpdateClientInfo();

	Update();
}










int main()
{


}




