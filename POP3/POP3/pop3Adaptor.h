#ifndef POP3
#define POP3
#include <iostream>
#include <fstream>
#include "User.h"
#include "MyContainer.h"
#include "MailMessage.h"
using namespace std;
/// This class responsible to fetch and management your mailbox.
/// this implemenation will the mail box stoarge will base on a file systems.

class Pop3Adaptor
{
private:
	User user;
	MyContainer<MailMessage> Messages;
	void Parsing(ifstream &myInput);
	int msgToDele;
	char *UserFile;
public:
	Pop3Adaptor(){ msgToDele = 0; UserFile = 0; };
	Pop3Adaptor(string name, string password);
	Pop3Adaptor(char *fileName);					//get data from file
	~Pop3Adaptor();


	Pop3Adaptor& operator=(const Pop3Adaptor& source)
	{
		if (this != &source)
		{
			Messages = source.Messages;
				user = source.user;
			msgToDele = source.msgToDele;
			UserFile = source.UserFile;
		}
		return *this;
	}
	Pop3Adaptor(const Pop3Adaptor& source) :user(source.user),
		msgToDele(source.msgToDele), UserFile(source.UserFile), Messages(source.Messages){};


	const string UserId(string userId);
	const string PASS(string password);
	const string STAT(int &messagNo, int &messageSize);
	const string LIST(string &list);
	const string RETR(int msgNumber,string &Data);
	const string DELE(int msgNumber);
	const string RSET();
	const string QUIT();
};
#endif

