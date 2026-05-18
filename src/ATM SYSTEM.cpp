#include<iostream>
#include<string>
#include<cctype>
#include<vector>
#include<fstream>
#include<iomanip>


using namespace std;


const string ClientFileName = "ClintsData.txt";

const string delim = "#//#";

struct stClientData
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
};


vector<stClientData> vClients;

size_t AlreadyPos=0;

//********************GENERAL******************
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


//---------------------TRANSACTION LIST-----------------



enum enChoiceTransactoins
{
	quickwithdraw = 1, normalwithdraw = 2,
	deposite = 3, checkbalance = 4,logout=5
};


//QuickWITHDRAW
enum enQucikWithDraw
{
	teweny=1,fifty=2
	,hundred=3,towH=4,
	fourH=5,sixH=6,
	eightH=7,Thousand=8,
	EXIT=9

};

int AmountOfQucikWithDraw(enQucikWithDraw choice)
{
	if (choice == enQucikWithDraw::teweny)
		return 20;
	else if (choice == enQucikWithDraw::fifty)
		return 50;
	else if (choice == enQucikWithDraw::hundred)
		return 100;
	else if (choice == enQucikWithDraw::towH)
		return 200;
	else if (choice == enQucikWithDraw::fourH)
		return 400;
	else if (choice == enQucikWithDraw::sixH)
		return 600;
	else if (choice == enQucikWithDraw::eightH)
		return 800;
	else if (choice == enQucikWithDraw::Thousand)
		return 1000;
	else
		return 0;


};

bool AskWithdrawClient()
{
	char chouse = 'n';

	cout << "\n Are you sure you want to Deposit amount? y/n? ";
	cin >> chouse;

	return (tolower(chouse) == 'y') ? 1 : 0;


}

bool IsamountAllow(int& amount, double original)
{
	if (amount >= original)
	{
		cout << "Amount Exceed the balance , you can withdraw up to : " << original << endl;
		
		return false;
	}

	return true;
}

enQucikWithDraw ReadChoiceQuickWithdraw()
{
	int c = 9;
	cout << "choose what to withdraw from [1] to [8] ? ";
	cin >> c;

	return (enQucikWithDraw)c;
}

void QuickWithdrawClint()
{
	int Amount = 0;
	enQucikWithDraw Choice ;

	do 
	{
		Choice = ReadChoiceQuickWithdraw();

		 Amount = AmountOfQucikWithDraw(Choice);

		 if (Choice == enQucikWithDraw::EXIT)
			 return;


	} while (!IsamountAllow(Amount, vClients.at(AlreadyPos).AccountBalance));

	vector<string> vClientsAsLines;

	if (  AskWithdrawClient())
	{
		vClients.at(AlreadyPos).AccountBalance -= Amount;


		cout << "Done Successfully New Balance = " << vClients.at(AlreadyPos).AccountBalance;

		for (stClientData& Client : vClients)
			vClientsAsLines.push_back(ConvertRecordToLine(Client, delim));



		LoadDataFromVectorToFile(ClientFileName, vClientsAsLines);
	}

	else
		cout << "Acount Still =" << vClients.at(AlreadyPos).AccountBalance;
}

void PrintHeaderOfQuickWithdraw()
{
	cout << "---------------------------------------\n";
	cout << "\t\t Quick WITHDRAW Screen\n";
	cout << "---------------------------------------\n";

	cout << "         [1] 20            [2] 50 \n"
		<< "         [3] 100           [4] 200  \n"
		<< "         [5] 400           [6] 600  \n"
		<< "         [7] 800           [8] 1000  \n"
		<< "         [8] Exit                    \n";
	cout << "---------------------------------------\n";

	cout << "Your Balance is " << vClients.at(AlreadyPos).AccountBalance << endl;

}

void QuickWithdraw()
{
	system("cls");

	PrintHeaderOfQuickWithdraw();

	QuickWithdrawClint();
}


//---------WITHDRAW--------

void WithdrawClint()
{
	int Amount = 0;
	cout << "Enter an amount multiple of 5,s ? ";
	cin >> Amount;


	while (!IsamountAllow(Amount, vClients.at(AlreadyPos).AccountBalance) || Amount%5!=0)
	{
		cout << "Not Valid!\n";
		cout << "Enter an amount multiple of 5,s ? ";
		cin >> Amount;

	}

	vector<string> vClientsAsLines;

	if (AskWithdrawClient())
	{
		vClients.at(AlreadyPos).AccountBalance -= Amount;


		cout << "Done Successfully New Balance = " << vClients.at(AlreadyPos).AccountBalance;

		for (stClientData& Client : vClients)
			vClientsAsLines.push_back(ConvertRecordToLine(Client, delim));



		LoadDataFromVectorToFile(ClientFileName, vClientsAsLines);
	}

	else
		cout << "Acount Still =" << vClients.at(AlreadyPos).AccountBalance;
}

void PrintHeaderOfWithdraw()
{
	cout << "---------------------------------------\n";
	cout << "\t\t  WITHDRAW Screen\n";
	cout << "---------------------------------------\n";

	cout << "Your Balance is " << vClients.at(AlreadyPos).AccountBalance << endl;

}

void NormalWithdraw()
{
	system("cls");

	PrintHeaderOfWithdraw();

	WithdrawClint();
}


//---------DEPOSIT--------
bool AskDepositClient()
{
	char chouse = 'n';

	cout << "\n Are you sure you want to Deposit amount? y/n? ";
	cin >> chouse;

	return (tolower(chouse) == 'y') ? 1 : 0;


}

void DepositClint()
{
	int Amount = 0;
	cout << "Enter an amount multiple of 5,s ? ";
	cin >> Amount;


	
	vector<string> vClientsAsLines;

	if (AskDepositClient())
	{
		vClients.at(AlreadyPos).AccountBalance += Amount;


		cout << "Done Successfully New Balance = " << vClients.at(AlreadyPos).AccountBalance;

		for (stClientData& Client : vClients)
			vClientsAsLines.push_back(ConvertRecordToLine(Client, delim));



		LoadDataFromVectorToFile(ClientFileName, vClientsAsLines);
	}

	else
		cout << "Acount Still =" << vClients.at(AlreadyPos).AccountBalance;
}

void PrintHeaderOfDeposit()
{
	cout << "---------------------------------------\n";
	cout << "\t\t  Deposit Screen\n";
	cout << "---------------------------------------\n";

	cout << "Your Balance is " << vClients.at(AlreadyPos).AccountBalance << endl;

}

void Deposit()
{
	system("cls");

	PrintHeaderOfDeposit();

	DepositClint();
}


//---------Check Balance-------
void CheckBalance() 
{
	system("cls");
	cout << "---------------------------------------\n";
	cout << "\t\t  Check Balance Screen\n";
	cout << "---------------------------------------\n";

	cout << "Your Balance is " << vClients.at(AlreadyPos).AccountBalance << endl;

}



//TRANSACTION
enChoiceTransactoins ReadChoiceATMScreen()
{
	int c = 5;

	cout << "Choose What do you want to do? [1 to 5]? ";
	cin >> c;

	return (enChoiceTransactoins)c;
}

void ShowAtmMenuScreen()
{
	cout << "===============================================================\n";
	cout << "\t\t\t ATM Main Menu Screen\n";
	cout << "===============================================================\n";
	cout << "\t\t[1] Quick Withdraw.\n";
	cout << "\t\t[2] Normal Withdraw.\n";
	cout << "\t\t[3] Deposit.\n";
	cout << "\t\t[4] Check Balance.\n";
	cout << "\t\t[5] Logout.\n";
	cout << "===============================================================\n";
}

void TransAction()
{
	enChoiceTransactoins  choice;

	do {
		system("cls");

		ShowAtmMenuScreen();

		choice = ReadChoiceATMScreen();

		switch (choice)
		{
		case enChoiceTransactoins::quickwithdraw:
			QuickWithdraw();
			break;

		case enChoiceTransactoins::normalwithdraw:
			NormalWithdraw();
			break;

		case enChoiceTransactoins::checkbalance:
			CheckBalance();
			break;

		case enChoiceTransactoins::deposite:
			Deposit();
			break;

		case enChoiceTransactoins::logout:
			cout << "\n\nOkay!";
			return;
		}

		cout << "\n\nPlease enter any key to go ";
		system("pause>0");

	} while (choice != enChoiceTransactoins::logout);
}


void ShowScreenLogin()
{

	cout << "---------------------------------------\n";
	cout << "\t\t Login Screen \n";
	cout << "---------------------------------------\n";

}

stClientData ReadAcountNumberAndPinCode()
{
	stClientData Clint;
	cout << "Enter Acount Number ? ";
	getline(cin >> ws, Clint.AccountNumber);
	cout << "Enter Pincode? ";
	cin >> Clint.PinCode;

	return Clint;
}

//And Load vData , Alreadypos
bool CheckAccountNameAndPincode(stClientData Clint)
{
	AlreadyPos = 0;
	vClients = LoadDataClintsFromFileToStrVector(ClientFileName, delim);

	for (stClientData ClintIn : vClients)
	{
		if (ClintIn.AccountNumber == Clint.AccountNumber && ClintIn.PinCode == Clint.PinCode)
		{
			
			return true;
		}
		AlreadyPos++;
	}

	
	return false;

}

void Login()
{
	int c = 1;

	do {
		system("cls");

		ShowScreenLogin();

		stClientData Clint = ReadAcountNumberAndPinCode();

		while (!CheckAccountNameAndPincode(Clint))
		{
			cout << "InValid Username/Password!\n";
			Clint = ReadAcountNumberAndPinCode();

		}
		TransAction();

	} while (c == 1);
}



int main()
{
	Login();

}

