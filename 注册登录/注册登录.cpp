#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
int UserNumber = 0;

void ReadUserNumber(int &UserNumber);         //从文件中读取当前用户数
void WriteUserNumber(int &UserNumber);        //将当前用户数写入文件
bool CheckUserName(string UserName);           //检查用户名是合法
bool CheckPassword(string Password);            //检查密码是否合法
bool SaveUser(string UserName, string Password);//将用户名和密码保存至文件
bool CheckProfile(string UserName, string Password);//调用用户名检查函数与密码检查函数检查用户名与密码
bool CheckRepetition(string UserName);//检查用户名是否重复
bool CheckSigninPsd(string UserName, string Password); //检查登录时密码正确性 

int main()	                                        //主函数
{
	int Select;
	string UserName;
	string Password;
	cout << "1.注册." << endl;                   //功能选择
	cout << "2.登录." << endl;
	cout << "3.退出." << endl;
	cout << "选择一个功能: " << endl;
	cin >> Select;
	getchar();
	switch (Select)
	{
	case 1:
	{
		cout << "输入用户名: " << endl;
		getline(cin, UserName);
		cout << "输入密码: " << endl;
		getline(cin, Password);
		CheckProfile(UserName, Password);
		break;
	}
	case 2: 
	{
		cout << "输入用户名: ";
		getline(cin, UserName);
		cout << "输入密码: ";
		getline(cin, Password);
		int flag = CheckSigninPsd(UserName, Password);
		if (flag == 1)
			cout << "登录成功." << endl;
		else if(flag == 0)
			cout << "登录失败" << endl;
		break;
	}
	case 3:return 0;
	default:
		cout << "这个数不行，换个吧。。。" << endl; break;
	}
	system("pause");
	return 0;
}

void ReadUserNumber(int &UserNumber)
{
	ifstream UserNumberFile("C:\\Users\\Hanxi\\Music\\login\\UserNumber.txt");
	UserNumberFile >> UserNumber;
	cout << "当前共有" << UserNumber << "名用户。" << endl;
}

void WriteUserNumber(int& UserNumber)
{
	ofstream UserNumberFile("C:\\Users\\Hanxi\\Music\\login\\UserNumber.txt");
	UserNumberFile << UserNumber << endl;
	UserNumberFile.close();
	cout << "当前共有" << UserNumber << "名用户。" << endl;
}

bool CheckUserName(string UserName)
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

bool CheckPassword(string Password)
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

bool SaveUser(string UserName, string Password)
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

bool CheckProfile(string UserName, string Password)
{
	if (CheckUserName(UserName) == 0)
	{
		cout << "用户名不合法!" << endl;
	}
	else if (CheckPassword(Password) == 0)
	{
		cout << "密码不合法!" << endl;
	}
	else
	{
		int CheckPepFlag = CheckRepetition(UserName);
		if (CheckPepFlag == 0)
		{
			cout << "用户名已存在!" << endl;
			return 0;
		}
		int SaveFileFlag = SaveUser(UserName, Password);
		if (SaveFileFlag = 1)
		{
			cout << "您注册前";
			ReadUserNumber(UserNumber);
			cout << "注册成功!" << endl;
			UserNumber++;
			WriteUserNumber(UserNumber);
			cout << "您注册后";
			ReadUserNumber(UserNumber);
			
		}
		else cout << "注册失败" << endl;
	}
	return 0;
}

bool CheckRepetition(string UserName)
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
	//for (int i = 0; i < count; i++)   //输出测试
	//{
	//	cout << User[i] << endl;
	//}
	inputUserList.close();              //关闭文件
	for (int i = 0; i < count; i++)
	{
		if (UserName == User[i])
			return 0;
	}
	return 1;
}

bool CheckSigninPsd(string UserName, string Password)
{
	int count = 0;
	int flag = 0;           //ID是否已注册的标志
	int countUser = 0;
	int countPsd = 0;
	ifstream inputUserList;
	ifstream inputPsdList;
	inputPsdList.open("C:\\Users\\Hanxi\\Music\\login\\password.txt");
	inputUserList.open("C:\\Users\\Hanxi\\Music\\login\\username.txt");
	vector<string> User;
	vector<string> Psd;
	string tempUser;
	string tempPsd;
	while (getline(inputUserList, tempUser))
	{
		User.push_back(tempUser);
		countUser++;
	}
	while (getline(inputPsdList, tempPsd))
	{
		Psd.push_back(tempPsd);
		countPsd++;
	}
	inputUserList.close();
	inputPsdList.close();
	for (int i = 0; i < countUser; i++)
	{
		if (UserName == User[i])
		{
			count = i;
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "您还未注册！" << endl;
		return 0;
	}
	if (Password != Psd[count])
	{
		cout << "密码错误！" << endl;
		return 0;
	}
	return 1;
}
