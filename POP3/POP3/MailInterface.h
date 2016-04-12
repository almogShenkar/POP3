#ifndef MUI
#define MUI
#include "pop3Adaptor.h"
#include <fstream>
#include <string>


class MailInterface{

public:
	MailInterface(int ArraySize, char**filesNames);
	~MailInterface();
	bool Authenticate(Pop3Adaptor &account,string &userName);
	void GetMailStatus(Pop3Adaptor &account);
	void GetMailList(Pop3Adaptor &account);
	void GetOneMail(Pop3Adaptor &account);
	void DeleteMail(Pop3Adaptor &account);
	void Rset(Pop3Adaptor &account);
	void Quit(Pop3Adaptor &account);
private:
	int Size;
	Pop3Adaptor *Manager;
};

#endif