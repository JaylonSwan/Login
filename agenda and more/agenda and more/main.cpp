#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <stdlib.h>

//todo add a overide function
//add register page
//make a user panle
//make an admin page
//much more

using namespace std;

int NumberOfUser()
{
	ifstream file;
	string cdata;


	int lines = 0;
	file.open("Data.csv");
	if (file.is_open())
	{

		while (!file.eof())
		{
			getline(file, cdata);
			lines++;

		}



	}

	file.close();
	return lines;
}

string ReadDataFromId(int id, string cat)
{
	ifstream file;
	string cdata;
	string data;

	int lines = 0;
	file.open("Data.csv");
	if (file.is_open())
	{

		while (!file.eof())
		{
			getline(file, cdata);
			lines++;
			if (id == lines)
			{
				data = cdata;
				file.close();

			}

		}



	}
	int wcat = 0;
	string final;
	string line = data;
	int ccat = 0;
	
	if (cat == "username")
	{
		wcat = 2;

	}
	else if (cat == "password")
	{

		wcat = 3;
	}
	istringstream iss(line);
	while (getline(iss, final, ','))
	{
		ccat++;
		if (ccat == wcat)
		{
			return final;

		}
	}

}

void CreateNewUser(string username, string password)
{
	ifstream readfile;
	ofstream writefile;
	string cdata;
	string data;
	string FormatedNewUser = to_string(NumberOfUser() + 1) + ", " + username + ", " + password;
	string FormatedData = "";

	readfile.open("Data.csv");
	if (readfile.is_open())
	{

		while (!readfile.eof())
		{
			getline(readfile, cdata);
			FormatedData = FormatedData + cdata + "\n";
		}
	}
	FormatedData += FormatedNewUser;
	readfile.close();

	writefile.open("Data.csv");
	if (writefile.is_open())
	{
		if (FormatedData != "")
		{
			writefile << FormatedData;

		}

	}
}

int NameToId(string name)
{  
	name = " " + name;
	int i = 0;
	while (i < NumberOfUser())
	{
		i++;
		if (ReadDataFromId(i, "username") == name)
		{

			return i;
		}

	}

}

void CoutCentered(std::string text) {


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO lpScreenInfo = new CONSOLE_SCREEN_BUFFER_INFO();
	GetConsoleScreenBufferInfo(hConsole, lpScreenInfo);
	COORD NewSBSize = lpScreenInfo->dwSize;

	if (NewSBSize.X > text.size()) {
		int newpos = ((NewSBSize.X - text.size()) / 2);
		for (int i = 0; i < newpos; i++) std::cout << " ";
	}

	std::cout << text;
}

void login()
{
	string username;
	string password;
	system("cls");
	CoutCentered("Student Login\n");
	CoutCentered("Enter Username:");
	cin >> username;
	CoutCentered("Enter Password:");
	cin >> password;

	password = " " + password;

	if (NameToId(username) != 69)
	{
		if (ReadDataFromId(NameToId(username), "password") == password)
		{
			CoutCentered("Loged in as " + username + " |Id: " + to_string(NameToId(username)));
		}
		else {
			CoutCentered("username or password was wrong please try agian\n");
			CoutCentered("4\n");
			Sleep(500);
			CoutCentered("3\n");
			Sleep(500);
			CoutCentered("2\n");
			Sleep(500);
			CoutCentered("1\n");
			Sleep(500);

			login();

		}

	}
	else
	{
		CoutCentered("username or password was wrong please try agian\n");
		CoutCentered("4\n");
		Sleep(500);
		CoutCentered("3\n");
		Sleep(500);
		CoutCentered("2\n");
		Sleep(500);
		CoutCentered("1\n");
		Sleep(500);
		login();
	}



}

void RegisterUsername(string password)
{
	system("cls");
	string username;
	CoutCentered("Username is in use please select a new one");
	CoutCentered("Enter Username:");
	cin >> username;

	if (NameToId(username) == 69)
	{
		CreateNewUser(username, password);


	}

}

void Register()
{
	string username;
	string password;
	string spassword;
	system("cls");
	CoutCentered("Student Register\n");
	CoutCentered("Enter Username:");
	cin >> username;
	CoutCentered("Enter Password:");
	cin >> password;
	CoutCentered("Enter Password again:");
	cin >> spassword;

	if (password == spassword)
	{
		if (NameToId(username) == 69)
		{
			CreateNewUser(username, password);
		}
		else
		{
			RegisterUsername(password);
			CoutCentered("lol");

		}
		//pass dont match


	}


}

int main()
{
	int option;
	CoutCentered("Student Main Page\n");
	CoutCentered("1.Login\n");
	CoutCentered("2.Register\n");
	CoutCentered("3.back)\n");

	CoutCentered("Option:");

	cin >> option;

	switch (option)
	{
	case 1:
		login();
		break;
	case 2:
		Register();
		break;
	default:
		break;
	}
	return 0;
}
