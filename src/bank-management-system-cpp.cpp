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



//----------------- FIND CLIENT --------
void ShowClintInfo()
{

	vector<stClientData> vClients = LoadDataClintsFromFileToStrVector(ClientFileName, delim);

	short pos = ReadAccountNumberExisted();

	PrintClientRecord(vClients.at(pos));
}

void PrintHeaderOfFindClient()
{
	cout << "---------------------------------------\n";
	cout << "\t\t Find Client Screen\n";
	cout << "---------------------------------------\n";


}

void FindClint()
{
	system("cls");

	PrintHeaderOfFindClient();

	ShowClintInfo();
}




//---------------------TRANSACTION LIST-----------------


enum enChoiceTransactoins
{
	deposit = 1, withdraw = 2,
	totalbalances = 3, mainMenu = 4
};

//BALANCES LIST
void PrintClientBalanceAsLine(stClientData Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;

	cout << "| " << left << setw(40) << Client.Name;

	cout << "| " << left << setw(12) << Client.AccountBalance;
	cout << endl;

}

void PrintHeadOfBalanceList()
{
	cout << "----------------------------------------------------------------------------------------------------\n";

	cout << "| " << left << setw(15) << "Acount Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance\n";

	cout << "------------------------------------------------------------------------------------------------------\n\n";

}

void ShowBalanceClientsList()
{
	system("cls");
	vector<stClientData> vClients = LoadDataClintsFromFileToStrVector(ClientFileName, delim);

	cout << "\t\t\t\t\t Clients List (" << vClients.size() << ") Client(s).\n";

	PrintHeadOfBalanceList();

	for (stClientData Client : vClients)
		PrintClientBalanceAsLine(Client);

}



//WITHDRAW
bool AskWithdrawClient()
{
	char chouse = 'n';

	cout << "\n Are you sure you want to Deposit amount? y/n? ";
	cin >> chouse;

	return (tolower(chouse) == 'y') ? 1 : 0;


}

bool IsamountAllow(double& amount, double original)
{
	while (amount >= original)
	{
		cout << "Amount Exceed the balance , you can withdraw up to : " << original << endl;
		cout << "Please enter another amount? ";
		cin >> amount;
	}

	return true;
}

void WithdrawClient()
{
	double amount = 0;

	vector<stClientData> vClients = LoadDataClintsFromFileToStrVector(ClientFileName, delim);

	vector<string> vClientsAsLines;

	short pos = ReadAccountNumberExisted();

	PrintClientRecord(vClients.at(pos));

	cout << "\nPlease enter Withdraw amount? ";
	cin >> amount;

	if (IsamountAllow(amount, vClients.at(pos).AccountBalance) && AskWithdrawClient())
	{
		vClients.at(pos).AccountBalance -= amount;


		cout << "Done Successfully New Balance = " << vClients.at(pos).AccountBalance;

		for (stClientData& Client : vClients)
			vClientsAsLines.push_back(ConvertRecordToLine(Client, delim));



		LoadDataFromVectorToFile(ClientFileName, vClientsAsLines);
	}

	else
		cout << "Acount Still =" << vClients.at(pos).AccountBalance;
}

void PrintHeaderOfWithdraw()
{
	cout << "---------------------------------------\n";
	cout << "\t\t WITHDRAW Screen\n";
	cout << "---------------------------------------\n";

}

void Withdraw()
{
	system("cls");

	PrintHeaderOfWithdraw();

	WithdrawClient();
}




//DEPOSIT.
bool AskDepositClient()
{
	char chouse = 'n';

	cout << "\n Are you sure you want to Deposit amount? y/n? ";
	cin >> chouse;

	return (tolower(chouse) == 'y') ? 1 : 0;


}

void DepositClient()
{
	double amount = 0;

	vector<stClientData> vClients = LoadDataClintsFromFileToStrVector(ClientFileName, delim);

	vector<string> vClientsAsLines;

	short pos = ReadAccountNumberExisted();

	PrintClientRecord(vClients.at(pos));

	cout << "\nPlease enter deposit amount? ";
	cin >> amount;

	if (AskDepositClient())
	{
		vClients.at(pos).AccountBalance += amount;


		cout << "Done Successfully New Balance = " << vClients.at(pos).AccountBalance;

		for (stClientData& Client : vClients)
			vClientsAsLines.push_back(ConvertRecordToLine(Client, delim));



		LoadDataFromVectorToFile(ClientFileName, vClientsAsLines);
	}

	else
		cout << "Acount Still =" << vClients.at(pos).AccountBalance;
}

void PrintHeaderOfDeposit()
{
	cout << "---------------------------------------\n";
	cout << "\t\t Deposit Screen\n";
	cout << "---------------------------------------\n";

}

void Deposit()
{
	system("cls");

	PrintHeaderOfDeposit();

	DepositClient();
}



//TRANSACTION
enChoiceTransactoins ReadChoiceTransaction()
{
	int c = 4;

	cout << "Choose What do you want to do? [1 to 4]? ";
	cin >> c;

	return (enChoiceTransactoins)c;
}

void ShowTransactionMenuScreen()
{
	cout << "===============================================================\n";
	cout << "\t\t\t\t Transactions Menu Screen\n";
	cout << "===============================================================\n";
	cout << "\t\t[1] Deposit.\n";
	cout << "\t\t[2] Withdraw.\n";
	cout << "\t\t[3] Total Balances.\n";
	cout << "\t\t[4] Main Menu.\n";
	cout << "===============================================================\n";
}

void TransAction()
{
	enChoiceTransactoins  choice;

	do {
		system("cls");

		ShowTransactionMenuScreen();

		choice = ReadChoiceTransaction();

		switch (choice)
		{
		case enChoiceTransactoins::deposit:
			Deposit();
			break;
		case enChoiceTransactoins::withdraw:
			Withdraw();
			break;
		case enChoiceTransactoins::totalbalances:
			ShowBalanceClientsList();
			break;
		case enChoiceTransactoins::mainMenu:
			cout << "\n\nOkay!";
			return;
		}

		cout << "\n\nPlease enter any key to go ";
		system("pause>0");

	} while (choice != enChoiceTransactoins::mainMenu);
}




// ********************MANAGE USERS*************

enum enCoiceManageUser
{
	listusers = 1, addnewuser = 2,
	deleteuser = 3, updateuser = 4,
	finduser = 5, mainmenue = 6
};

struct stUser
{
	string Name = "";
	int Password = 0;
	int Access = 0;
};


string UserFileName = "data/UsersData.txt";


//---------- helper functions --------
stUser ConvertLineToRecordForUser(string line, string delim)
{
	vector<string> vData = SplitString(line, delim);

	stUser UserData;
	UserData.Name = vData[0];
	UserData.Password = stoi(vData[1]);
	UserData.Access = stoi(vData[2]);


	return UserData;
}

vector<stUser>  LoadDataUsersFromFileToStrVector(string filename, string delim)
{
	vector<stUser> vUsers;
	fstream myfile;

	myfile.open(filename, ios::in);

	if (myfile.is_open())
	{
		string line;
		while (getline(myfile, line))
		{
			vUsers.push_back(ConvertLineToRecordForUser(line, delim));

		}

		myfile.close();
	}
	return vUsers;
}

string ConvertRecordToLineForUser(stUser UserData, string delim)
{
	string str = "";
	str = UserData.Name + delim
		+ to_string(UserData.Password) + delim
		+ to_string(UserData.Access);

	return str;
}

short FindUseUseName(vector<stUser> vUsers, string Name)
{
	short pos = 0;

	for (stUser& User : vUsers)
	{
		if (User.Name == Name)
			return pos;

		pos++;
	}

	return -1;
}

string ReadNewUser()
{
	string Name;

	cout << "\nPlease enter Username? ";
	getline(cin >> ws, Name);

	short pos = FindUseUseName(LoadDataUsersFromFileToStrVector(UserFileName, delim), Name);
	while (pos != -1)
	{
		cout << "User With [" << Name << "] already exit\n";

		cout << "\nPlease enter New UserName? ";
		getline(cin >> ws, Name);

		pos = FindUseUseName(LoadDataUsersFromFileToStrVector(UserFileName, delim), Name);

	}


	return Name;
}

short ReadNameUserExisted()
{
	string Name;

	cout << "\nPlease enter User Name ? ";
	getline(cin >> ws, Name);

	short pos = FindUseUseName(LoadDataUsersFromFileToStrVector(UserFileName, delim), Name);
	while (pos == -1)
	{
		cout << "User With [" << Name << "] does not Found\n";

		cout << "\nPlease enter User Name? ";
		getline(cin >> ws, Name);

		pos = FindUseUseName(LoadDataUsersFromFileToStrVector(UserFileName, delim), Name);

	}


	return pos;
}

void PrintUserRecord(stUser User)
{
	cout << "\nName User : " << User.Name << endl;
	cout << "Password     : " << User.Password << endl;
	cout << "Permisiion     : " << User.Access << endl;

}

int ReadPermisiion()
{
	int access = 0;
	char agree = 'n';

	cout << "Do you want to give full access?y/n? ";
	cin >> agree;

	if (tolower(agree) == 'y')
		return -1;

	cout << "Do you want to give access to: \n";

	cout << "\n Show Clint list? y/n? ";
	cin >> agree;
	if (tolower(agree) == 'y')
		access += 1;

	cout << "\n Add New Clint ? y/n? ";
	cin >> agree;
	if (tolower(agree) == 'y')
		access += 2;

	cout << "\n Delete Clint ? y/n? ";
	cin >> agree;
	if (tolower(agree) == 'y')
		access += 4;

	cout << "\n Update Clint ? y/n? ";
	cin >> agree;
	if (tolower(agree) == 'y')
		access += 8;

	cout << "\n Find Clint?  y/n? ";
	cin >> agree;
	if (tolower(agree) == 'y')
		access += 16;

	cout << "\n Transactions? y/n? ";
	cin >> agree;
	if (tolower(agree) == 'y')
		access += 32;

	cout << "\n Manage User ? y/n? ";
	cin >> agree;
	if (tolower(agree) == 'y')
		access += 64;


	return access;
}



//---------USERS LIST-------------
void PrintUserAsLine(stUser User)
{
	cout << "| " << left << setw(15) << User.Name;

	cout << "| " << left << setw(15) << User.Password;

	cout << "| " << left << setw(15) << User.Access;
	cout << endl;

}

void PrintHeadOfUsersList()
{
	cout << "----------------------------------------------------------------------------------------------------\n";

	cout << "| " << left << setw(15) << "Name";
	cout << "| " << left << setw(15) << "Password ";
	cout << "| " << left << setw(15) << "Access\n";

	cout << "------------------------------------------------------------------------------------------------------\n\n";

}

void ShowUsersList()
{
	system("cls");
	vector<stUser> vUsers = LoadDataUsersFromFileToStrVector(UserFileName, delim);

	cout << "\t\t\t\t\t Users List (" << vUsers.size() << ") User(s).\n";

	PrintHeadOfUsersList();

	for (stUser User : vUsers)
		PrintUserAsLine(User);

}



//---------ADDING USERS-----------
stUser ReadUsertData()
{
	stUser UserData;

	UserData.Name = ReadNewUser();

	cout << "Enter Password? ";
	cin >> UserData.Password;


	UserData.Access = ReadPermisiion();

	return UserData;
}

void AddNewUser()
{
	stUser UserData;

	UserData = ReadUsertData();

	SendLintToFile(UserFileName, ConvertRecordToLineForUser(UserData, delim));


}

void AddUsers()
{

	char more = 'n';

	do
	{

		AddNewUser();

		cout << "User Added Successfuly, do you want add more Users?(Y||N)? ";
		cin >> more;

	} while (more == 'y' || more == 'Y');

}

void PrintHeadOfAddUsers()
{
	cout << "---------------------------------------\n";
	cout << "\tAdd New Users Screen\n";
	cout << "---------------------------------------\n";
	cout << "Adding New User\n";


}

void AddNewUsers()
{
	system("cls");

	PrintHeadOfAddUsers();

	AddUsers();
}


//----------------DELETE Users--------
bool AskDeleteUser()
{
	char chouse = 'n';

	cout << "\n Are you sure you want to delete user? y/n? ";
	cin >> chouse;

	return (tolower(chouse) == 'y') ? 1 : 0;


}

void DeleteFromVectorAndFile(vector<stUser> vUsers, short pos)
{
	vector<string> vUsersAsLines;

	for (stUser& User : vUsers)
		vUsersAsLines.push_back(ConvertRecordToLineForUser(User, delim));

	vUsersAsLines.at(pos) = "";

	LoadDataFromVectorToFile(UserFileName, vUsersAsLines);
}

void DeleteUser()
{

	size_t pos = ReadNameUserExisted();
	if (pos == 0)
		cout << "This the Admin , We cant delete him\n";


	else
	{
		vector<stUser> vUsers = LoadDataUsersFromFileToStrVector(UserFileName, delim);

		PrintUserRecord(vUsers.at(pos));

		if (AskDeleteUser())
		{
			DeleteFromVectorAndFile(vUsers, pos);
			cout << "\n User Deleted Successfully. \n";

		}
		else
			cout << "The User Still There\n";
	}
}

void PrintHeaderOfDeleteUser()
{
	cout << "---------------------------------------\n";
	cout << "\t\t Delete User Screen\n";
	cout << "---------------------------------------\n";

}

void DeleteUsers()
{
	system("cls");

	PrintHeaderOfDeleteUser();

	DeleteUser();
}





int main()
{


}




