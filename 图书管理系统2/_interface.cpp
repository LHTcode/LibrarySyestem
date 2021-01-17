#include<iostream>
#include<string>
#include"_interface.h"
#include"Sign.h"
#include"Reader.h"
#include<setjmp.h>
using namespace std;

string& _interface::FirstChoose()
{
	/*登录界面*/
	/*printf("\n");
	for (int i = 0;i < 30;++i)
	{
		printf(" ");
	}
	printf("***欢迎使用图书管理系统***\n");
	for (int i = 0;i < 10;++i)
	{
		printf(" ");
	}
	for (int i = 0;i < 70;++i)
	{
		printf("-");
	}
	printf("\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("A.读者登录\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("B.管理员登录\n\n");
	for (int i = 0;i < 10;++i)
	{
		printf(" ");
	}
	for (int i = 0;i < 70;++i)
	{
		printf("-");
	}*/
	printf("\n请选择：");

	static string choose;
	cin >> choose;
	unsigned int len = choose.length();
	while (len != 1)
	{
		cout << "请输入一个A、B其中字符" << endl;
		cin >> choose;
		len = choose.length();		/*保证输入仅一个字符*/
	}
	/*清空缓冲区*/
	char c;
	while (c = getchar() != '\n') {}
	return choose;
}

void _interface::Reader_Sign_Interface()
{
	system("cls");
	std::cout << "你好，读者！\n"
		<< "请输入您的学号和密码\n"
		<< std::endl;
}

void _interface::Administrator_Sign_Interface()
{
	system("cls");
	std::cout << "你好，管理员！\n"
		<< "请输入您的工号和密码：\n"
		<< std::endl;
}

void _interface::ReaderInterface()
{
	/*查书，借书，还书，个人基本信息，我要还款，修改密码等入口*/
	/*printf("\n");
	for (int i = 0;i < 30;++i)
	{
		printf(" ");
	}
	printf("***欢迎使用图书管理系统***\n");
	for (int i = 0;i < 10;++i)
	{
		printf(" ");
	}
	for (int i = 0;i < 70;++i)
	{
		printf("-");
	}
	printf("\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("A.个人基本信息\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("B.我要找书\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("C.我要借书\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("D.我要还书\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("E.我要还款\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("F.修改密码\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("G.退出\n\n");
	for (int i = 0;i < 10;++i)
	{
		printf(" ");
	}
	for (int i = 0;i < 70;++i)
	{
		printf("-");
	}
	printf("\n请选择：");
	*/
}

void _interface::AdministratorInterface()
{
	printf("\n");
	for (int i = 0;i < 30;++i)
	{
		printf(" ");
	}
	printf("***欢迎使用图书管理系统***\n");
	for (int i = 0;i < 10;++i)
	{
		printf(" ");
	}
	for (int i = 0;i < 70;++i)
	{
		printf("-");
	}
	printf("\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("A.个人基本信息\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("B.学生信息管理\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("C.图书信息管理\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("D.修改密码\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("E.退出\n\n");
	for (int i = 0;i < 10;++i)
	{
		printf(" ");
	}
	for (int i = 0;i < 70;++i)
	{
		printf("-");
	}
	printf("\n请选择：");


}


void _interface::ReaderChoose()
{
	Reader re;
	do
	{
		string choose = "";
		do
		{
			cin >> choose;
			do
			{/*检测到exit则返回上一级目录*/
				_interface::Exit(1, 1, choose);
			} while (0);
			unsigned int len = choose.length();
			if (len != 1)
			{
				cout << "请输入一个字符" << endl;
				continue;
			}
			break;
		} while (1);
		system("cls");
		/*清空缓冲区*/
		char c;
		while (c = getchar() != '\n') {}

		const char* ch = choose.c_str ();
		switch (*ch)
		{
		case 'A':

			break;
		case 'B':
			re.BookSerch();
			break;
		case 'C':
			re.BorrowBook();
			break;
		case 'D':

			break;
		case 'E':

			break;
		case 'F':
			re.ChangePassword();
			break;
		case 'G':
			printf("再见！！！\n");
			exit(0);
			break;
		default:
			printf("请重新选择：");
			continue;
		}
		break;
	} while (1);
	
}


void _interface::AdministratorChoose()
{
	do
	{
		string choose = "";
		do
		{
			cout << flush;
			cin >> choose;

			unsigned int len = choose.length();
			if (len != 1)
			{
				cout << "请输入一个字符" << endl;
				continue;
			}
			break;
		} while (1);

		const char* ch = choose.c_str();
		switch (*ch)
		{
		case 'A':

			break;
		case 'B':

			break;
		case 'C':

			break;
		case 'D':

			break;
		case 'E':
			printf("再见！！！\n");
			exit(0);
			break;
		default:
			printf("请重新选择：");
			continue;
		}
		break;
	} while (1);
}

/*"返回上一级目录"专区*/
jmp_buf home_page_jump;
void _interface::Exit(short, std::string str)
{
	
	if (str.find("exit")!=std::string::npos)
	{
		system("cls");
		longjmp(home_page_jump, 1);
	}
}

jmp_buf secondary_inerface_jump;
void _interface::Exit(short, short, std::string str)
{
	if (str.find("exit") != std::string::npos)
	{
		system("cls");
		longjmp(secondary_inerface_jump, 1);
	}
}

void _interface::autoExit(short,short)
{
	longjmp(secondary_inerface_jump, 1);
}