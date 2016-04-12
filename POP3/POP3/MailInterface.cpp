#include "MailInterface.h"

MailInterface::MailInterface(int ArraySize, char **filesNames){
	Size = ArraySize-1;
	Pop3Adaptor CurrentUser;
	Manager = new Pop3Adaptor[Size];
	for (int i = 0; i < Size; i++)
		Manager[i] =  Pop3Adaptor(filesNames[i+1]);
	bool foundUser=false;
	char select=0,i = 0;
	string userName, password;
	do
	{
		system("cls");
		cout <<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		cout<<"Welcome to Hotmail!" << endl;
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		cout<<"1) Authenticate"<<endl;
		cout<<"2) Get Mail Status"<<endl;
		cout<<"3) Get Mails List"<<endl;
		cout<<"4) Get One Mail" << endl;
		cout<<"5) Delete mail" << endl;
		cout<<"6) RSET" << endl;
		cout<<"7) Quit" << endl<<endl;
		cin >> select;
		if (select == '1')
		{
			if (foundUser = Authenticate(CurrentUser,userName))
			{
				system("cls");
				cout << "Welcome " << userName.substr(0, userName.find('@')) << "!" << endl;
				system("pause");
				continue;
			}
		}
		if (foundUser)
		{
			switch (select)
			{
			case '2':{GetMailStatus(CurrentUser); break; }
			case '3':{GetMailList(CurrentUser); break; }
			case '4':{GetOneMail(CurrentUser); break; }
			case '5':{DeleteMail(CurrentUser); break; }
			case '6':{Rset(CurrentUser); break; }
			}
			continue;
		}
		else
		if (select != '7')
		{
		system("cls");
		cout << "Not authenticated! sign-in/check user/password" << endl;
		system("pause");
		}
	} while (select != '7');
	Quit(CurrentUser);
	system("cls");
	cout << "Bye Bye!" << endl;
}

MailInterface::~MailInterface(){	
};

bool MailInterface::Authenticate(Pop3Adaptor &account,string &userName){
	int i = 0;
	system("cls");
	string username, password;
	cout << endl << "username: ";
	cin >> username;
	cout<<endl<< "password: ";
	cin >> password;
	while (i<Size)
	{
		if (Manager[i].UserId(username) == "+OK" && Manager[i].PASS(password) == "+OK")
		{
			account = Manager[i];
			userName = username;
			return true;
		}
		++i;
	}
	return false;
};

void MailInterface::GetMailStatus(Pop3Adaptor &account){
	system("cls");
	int messageNo=0, messageSize = 0;
	if(account.STAT(messageNo, messageSize)=="+OK")
		cout<<"+OK "<<messageNo<<" "<<messageSize<<endl;
	else
		cout << "-ERR" << endl;
	system("pause");
	system("cls");
};

void MailInterface::GetMailList(Pop3Adaptor &account){
	system("cls");
	string list="";
	if (account.LIST(list)=="+OK")
	cout << "+OK "<<list;
	else
		cout << "-ERR" << endl;
	system("pause");
	system("cls");
};

void MailInterface::GetOneMail(Pop3Adaptor &account){
	string Data = "";
	int msgNo;
	system("cls");
	cout << "select message number: " ;
	cin >> msgNo;
	if (account.RETR(msgNo,Data) == "+OK")
		cout<<Data;
	else
		cout << "-ERR" << endl;
	system("pause");
	system("cls");
};

void MailInterface::DeleteMail(Pop3Adaptor &account){
	int msgNo;
	system("cls");
	cout << "select message number: ";
	cin >> msgNo;
	if (account.DELE(msgNo) == "+OK")
		cout << "+OK"<<endl;
	else
		cout << "-ERR"<<endl;
	system("pause");
	system("cls");
};

void MailInterface::Rset(Pop3Adaptor &account){
	system("cls");
	account.RSET();
	cout << "+OK"<<endl;
	system("pause");
	system("cls");
};

void MailInterface::Quit(Pop3Adaptor &account){
	system("cls");
	if (account.QUIT() == "+OK")
		cout << "+OK" << endl;
	else
		cout << "-ERR" << endl;
	system("pause");
	system("cls");
};