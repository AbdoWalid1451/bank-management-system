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



//-----------------UPDATE User DATA-------
void ReadUserDataUpdate(stUser& UserData)
{
	cout << "Enter Password? ";
	cin >> UserData.Password;


	UserData.Access = ReadPermisiion();

}

bool AskUpdateUser()
{
	char chouse = 'n';

	cout << "\n Are you sure you want to update User? y/n? ";
	cin >> chouse;

	return (tolower(chouse) == 'y') ? 1 : 0;


}

void UpdateInVectorAndFile(vector<stUser>& vUsers, short pos)
{

	ReadUserDataUpdate(vUsers.at(pos));

	vector<string> vUsersAsLines;

	for (stUser& User : vUsers)
		vUsersAsLines.push_back(ConvertRecordToLineForUser(User, delim));



	LoadDataFromVectorToFile(UserFileName, vUsersAsLines);
}

void UpdateUser()
{
	vector<stUser> vUsers = LoadDataUsersFromFileToStrVector(UserFileName, delim);

	size_t pos = ReadNameUserExisted();

	PrintUserRecord(vUsers.at(pos));

	if (AskUpdateUser())
	{
		UpdateInVectorAndFile(vUsers, pos);
		cout << "\n User Updated Successfully. \n";

	}
	else
		cout << "The User Still There\n";

}

void PrintHeaderOfUpdateUserInfo()
{
	cout << "---------------------------------------\n";
	cout << "\t\t Update User Screen\n";
	cout << "---------------------------------------\n";


}

void UpdateUserInfo()
{
	system("cls");

	PrintHeaderOfUpdateUserInfo();

	UpdateUser();
}


//-----------------FIND User---------
void ShowUserInfo()
{

	vector<stUser> vUsers = LoadDataUsersFromFileToStrVector(UserFileName, delim);

	short pos = ReadNameUserExisted();

	PrintUserRecord(vUsers.at(pos));
}

void PrintHeaderOfFindUser()
{
	cout << "---------------------------------------\n";
	cout << "\t\t Find User Screen\n";
	cout << "---------------------------------------\n";


}

void FindUser()
{
	system("cls");

	PrintHeaderOfFindUser();

	ShowUserInfo();
}





//***********MANAGEUSER*******************
enCoiceManageUser ReadChoiceManageUsers()
{
	int c = 6;

	cout << "Choose What do you want to do? [1 to 6]? ";
	cin >> c;

	return (enCoiceManageUser)c;
}

void ShowMangeUsersMenuScreen()
{
	cout << "===============================================================\n";
	cout << "\t\t Manage Users Main Menu Screen\n";
	cout << "===============================================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << "===============================================================\n";

}

void ManageUser()
{
	enCoiceManageUser  choice;

	do {
		system("cls");

		ShowMangeUsersMenuScreen();

		choice = ReadChoiceManageUsers();

		switch (choice)
		{
		case enCoiceManageUser::listusers:
			ShowUsersList();
			break;
		case enCoiceManageUser::addnewuser:
			AddNewUsers();
			break;
		case enCoiceManageUser::deleteuser:
			DeleteUsers();
			break;
		case enCoiceManageUser::updateuser:
			UpdateUserInfo();
			break;
		case enCoiceManageUser::finduser:
			FindUser();
			break;
		}
		if (choice != enCoiceManageUser::mainmenue)
		{
			cout << "\n\nPlease enter any key to go ";
			system("pause>0");
		}
	} while (choice != enCoiceManageUser::mainmenue);

}


//************SYSTEM****************
void ShowMenuScreen()
{
	cout << "===============================================================\n";
	cout << "\t\t\t\t Main Menu Screen\n";
	cout << "===============================================================\n";
	cout << "\t\t[1] Show Client List.\n";
	cout << "\t\t[2] Add New Client.\n";
	cout << "\t\t[3] Delete Client.\n";
	cout << "\t\t[4] Update Client Info.\n";
	cout << "\t\t[5] Find Client.\n";
	cout << "\t\t[6] Transactions.\n";
	cout << "\t\t[7] Manage Users.\n";
	cout << "\t\t[8] Logout.\n";
	cout << "===============================================================\n";

}

enChoicesList ReadChoiceUser()
{
	int c = 8;
	cout << "Choose What do you Want to do? [1 to 8]? ";
	cin >> c;
	return (enChoicesList)c;
}

void NotValid()
{
	system("cls");
	cout << "--------------------------------------\n";
	cout << "Access Denied,\nYou dont have permission to do this,\nplease contact your Admin.\n";
	cout << "--------------------------------------\n";
}

void BankSystem(stUser User)
{
	enChoicesList Choice;


	do {

		system("cls");

		ShowMenuScreen();

		Choice = ReadChoiceUser();

		int Acessess = User.Access;

		switch (Choice)
		{
		case enChoicesList::showclientlist:
			if ((Acessess & 1) == 1 || User.Access == -1)
				ShowClientList();

			else
				NotValid();
			break;

		case enChoicesList::addnewclients:
			if ((Acessess & 2) == 2 || User.Access == -1)
				AddNewClients();

			else
				NotValid();
			break;

		case enChoicesList::deleteclient:
			if ((Acessess & 4) == 4 || User.Access == -1)
				DeleteClient();

			else
				NotValid();
			break;

		case enChoicesList::updateclientinfo:
			if ((Acessess & 8) == 8 || User.Access == -1)
				UpdateClientInfo();

			else
				NotValid();
			break;
		case enChoicesList::findclient:
			if ((Acessess & 16) == 16 || User.Access == -1)
				FindClint();

			else
				NotValid();
			break;
		case enChoicesList::transactions:
			if ((Acessess & 32) == 32 || User.Access == -1)
				TransAction();

			else
				NotValid();
			break;
		case enChoicesList::manageusers:
			if ((Acessess & 64) == 64 || User.Access == -1)
				ManageUser();

			else
				NotValid();
			break;

		}


		cout << "\n\nPlease enter any key to go ";
		if (Choice != enChoicesList::logout)
			system("pause>0");

	} while (Choice != enChoicesList::logout);

}



//-----------LOGIN----------
void ShowScreenLogin()
{

	cout << "---------------------------------------\n";
	cout << "\t\t Login Screen \n";
	cout << "---------------------------------------\n";

}

stUser ReadNameUserAndPassword()
{
	stUser User;
	cout << "Enter Username? ";
	getline(cin >> ws, User.Name);
	cout << "Enter Password? ";
	cin >> User.Password;

	return User;
}

bool CheckUserNameAndPasswordRight(stUser& User)
{

	vector<stUser> vUsers = LoadDataUsersFromFileToStrVector(UserFileName, delim);
	for (stUser UserIn : vUsers)
	{
		if (UserIn.Name == User.Name && UserIn.Password == User.Password)
		{
			User = UserIn;
			return true;
		}
	}
	return false;

}

void Login()
{
	int c = 1;

	do {
		system("cls");

		ShowScreenLogin();

		stUser User = ReadNameUserAndPassword();

		while (!CheckUserNameAndPasswordRight(User))
		{
			cout << "InValid Username/Password!\n";
			User = ReadNameUserAndPassword();

		}
		BankSystem(User);

	} while (c == 1);
}



int main()
{
	Login();

}


