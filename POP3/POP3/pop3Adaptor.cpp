#include "pop3Adaptor.h"

void Pop3Adaptor::Parsing(ifstream &myInput){
	char *username,*password,line[300],*ID,*From,*To,*Data,*dateTime;
	int lineCounter=1;
	while (myInput.getline(line,300))
	{
		if (line[0] == '#' || line[0]=='\0') continue; 
		if (lineCounter == 1)							//line username and password
		{
			username = strtok(line, ", ");
			password = strtok(NULL, ", ");
			++lineCounter;
			user = User(username, password);
			continue;
		}
		else
		{
			ID = strtok(line, ", ");
			From = strtok(NULL, ", ");
			To = strtok(NULL, ", ");
			dateTime =strtok(NULL, ",  ");
			string dates = dateTime;
			dates.erase(0, dates.find_first_not_of(" "));
			dates = dates.substr(0,dates.find_last_of(", "));
			dates;
			Data =strtok(NULL, "\0");
			string data = Data;
			data.erase(0,data.find_first_not_of(", "));
			int size = data.size();
			DateTime date(dates);
			MailMessage msg(ID, From, To, data, date, size);
			Messages.push(msg);
			++lineCounter;
		}
	}

}

Pop3Adaptor::Pop3Adaptor(char *fileName) :msgToDele(0){
	UserFile = fileName;
	ifstream inputData(fileName);
	Parsing(inputData);
	inputData.close();
}

Pop3Adaptor::Pop3Adaptor(string name, string password) : user(name, password), msgToDele(0){}

Pop3Adaptor::~Pop3Adaptor(){}

const string Pop3Adaptor::UserId(const string userId){
	if (user.getUsername()==userId)
	return "+OK";
	return "-ERR";
};

const string Pop3Adaptor::PASS(const string password){
	if (user.getPassword() == password)
	return "+OK";
	return "-ERR";
};

const string Pop3Adaptor::STAT(int &messagNo,int &messageSize){
	messagNo = Messages.size();
	for (MyContainer<MailMessage>::Iterator my = Messages.begin(); my != Messages.end(); ++my)
		messageSize+=my->getSize();
	if (messagNo && messageSize)
	return "+OK";
	return "-ERR";
};

const string Pop3Adaptor::LIST(string &list){
	list = to_string(Messages.size())+"\n";
	int i = 1;
	for (MyContainer<MailMessage>::Iterator my = Messages.begin(); my != Messages.end(); ++my, ++i)
		list += to_string(i) + " "+to_string(my->getSize()) + "\n";
	if (list!="")
	return "+OK";
	return "-ERR";
};


const string Pop3Adaptor::RETR(int msgNumber,string &Data){
	if (--msgNumber>=Messages.size())
		return "-ERR";
	Data=Messages[msgNumber].getData()+"\n";
	if (Data!="")
	return "+OK";
	return "-ERR";
};

const string Pop3Adaptor::DELE(int msgNumber){
	if (Messages.size() >= msgNumber)
	{
		msgToDele = msgNumber;
		return "+OK";
	}
	else
	return "-ERR (msg not exsit)";
};


const string Pop3Adaptor::RSET(){
	msgToDele = 0;
	return "+OK";
	return "-ERR";
};

const string Pop3Adaptor::QUIT(){
	if (!msgToDele) return "+OK";
	ofstream File;
	File.open(UserFile);
	int i = Messages.size();
	if (msgToDele!=0 && msgToDele <= Messages.size())
	{
		MyContainer<MailMessage>::Iterator my = Messages.begin();
		File << "#USERNAME : " << user.getUsername() << ", ";
		File << "PASSWORD : " << user.getPassword() << endl;
		File << user.getUsername() << ", " << user.getPassword() << endl << endl;
		while (my != Messages.end() && stoi(my->getID()) != msgToDele)
		{
			File << my->getID() << ", " << my->getFrom() << ", " << my->getTo() << ", " << my->getMailTime().getD() <<
				my->getMailTime().getM() << my->getMailTime().getY() << my->getMailTime().getH() << my->getMailTime().getMin()
				<< my->getMailTime().getS() << ", " << my->getData() << endl;
			++my;
		}
		if (stoi(my->getID()) == msgToDele && my != Messages.end())
			for (MyContainer<MailMessage>::Iterator my2 = my; my2 < Messages.end(); my2++)
				my2->setID(stoi(my2->getID()) - 1);
		++my;
		while (my != Messages.end())
		{
		    File << my->getID() << ", " << my->getFrom() << ", " << my->getTo() << ", " << my->getMailTime().getD() <<
				my->getMailTime().getM() << my->getMailTime().getY() << my->getMailTime().getH() << my->getMailTime().getMin()
				<< my->getMailTime().getS() << ", " << my->getData() << endl;
			++my;
		}
		return "+OK";
	}
	return "-ERR";
}
