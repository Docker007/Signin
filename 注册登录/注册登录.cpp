#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
int UserNumber = 0;

int CheckUserName(string UserName);
int CheckPassword(string Password);
int SaveUser(string UserName, string Password);
int CheckProfile(string UserName, string Password);
int CheckRepetition(string UserName, string Password);
int main()	 
{
	int Select;
	string UserName;
	string Password;
	cout << "1.Sign up." << endl;
	cout << "2.Sign in." << endl;
	cout << "3.Exit." << endl;
	cout << "Select a function: " << endl;
	cin >> Select;
	switch (Select)
	{
	case 1: 
	{
		cout << "Input UserName: " << endl;
		getline(cin, UserName);
		cout << "Input password: " << endl;
		getline(cin, Password);
		CheckProfile(UserName, Password);
		break;
	}
	case 2:cout << "Sign in." << endl; break;
	default:
		break;
	}
	
	return 0;
}

int CheckUserName(string UserName)
{
	for (unsigned i = 0; i < UserName.size(); i++)
	{
		if (UserName[i]<48|| (UserName[i]>57&&UserName[i]<65)||
			(UserName[i]>90&&UserName[i]<95)||UserName[i]==96||UserName[i]>122)
		{
			return 0;
		}
	}
	return 1;
}

int CheckPassword(string Password)
{
	int upper_letter(0), lower_letter(0), number(0);
	for (unsigned  i = 0; i < Password.size(); i++)
	{
		if (Password[i] >= 'a' && Password[i] <= 'z')
			lower_letter++;
		if (Password[i] >= 'A'&&Password[i] <= 'Z')
			upper_letter++;
		if (Password[i] >= '0'&&Password[i] <= '9')
			number++;
		if(Password[i]==' ')
		{
			return 0;
		}
	}
	if (upper_letter == 0 || lower_letter == 0 || number == 0)
		return 0;
	return 1;
}

int SaveUser(string UserName, string Password)
{
	//vector<string> UserList;
	//vector<string> PsdList;
	ofstream outfileUserName("C:\\Users\\Hanxi\\Music\\login\\username.txt", ios_base::app);
	ofstream outfilePassword("C:\\Users\\Hanxi\\Music\\login\\password.txt", ios_base::app);
	outfileUserName << UserName << "\n";
	outfilePassword << Password << "\n";
	outfileUserName.close();
	outfilePassword.close();
	return 1;
}

int CheckProfile(string UserName, string Password)
{
	if (CheckUserName(UserName) == 0)
	{
		cout << "Username is invalid!" << endl;
	}
	else if (CheckPassword(Password) == 0)
	{
		cout << "Password is invalid!" << endl;
	}
	else
	{
		int CheckPepFlag = CheckRepetition(UserName, Password);
		if (CheckPepFlag == 0)
		{
			cout << "用户名已存在!" << endl;
			return 0;
		}
		int SaveFileFlag = SaveUser(UserName, Password);
		if (SaveFileFlag = 1)
		{
			cout << "Sign up sucessfully!" << endl;
			UserNumber++;
			cout << "当前共有" << UserNumber << "名用户" << endl;
		}
		else cout << "Sign up failed..." << endl;
	}
	return 0;
}

int CheckRepetition(string UserName, string Password)
{
	ifstream inputUserList;
	int count = 0;
	inputUserList.open("C:\\Users\\Hanxi\\Music\\login\\username.txt"); //打开文件
	vector<string> User;  //临时存储用户名
	string temp;
	while (getline(inputUserList,temp))  //将用户名从文件中写入临时vector中
	{
		User.push_back(temp);
		count++;
	}
	for (int i = 0; i < count; i++)   //输出测试
	{
		cout << User[i] << endl;
	}
	inputUserList.close();              //关闭文件
	for (int i = 0; i < count; i++)
	{
		if (UserName == User[i])
			return 0;
	}
	return 1;
}

