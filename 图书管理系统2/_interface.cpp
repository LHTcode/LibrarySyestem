#include<iostream>
#include<string>
#include"_interface.h"
#include"Sign.h"
#include"Reader.h"
#include<setjmp.h>
using namespace std;

string& _interface::FirstChoose()
{
	/*��¼����*/
	/*printf("\n");
	for (int i = 0;i < 30;++i)
	{
		printf(" ");
	}
	printf("***��ӭʹ��ͼ�����ϵͳ***\n");
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
	printf("A.���ߵ�¼\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("B.����Ա��¼\n\n");
	for (int i = 0;i < 10;++i)
	{
		printf(" ");
	}
	for (int i = 0;i < 70;++i)
	{
		printf("-");
	}*/
	printf("\n��ѡ��");

	static string choose;
	cin >> choose;
	unsigned int len = choose.length();
	while (len != 1)
	{
		cout << "������һ��A��B�����ַ�" << endl;
		cin >> choose;
		len = choose.length();		/*��֤�����һ���ַ�*/
	}
	/*��ջ�����*/
	char c;
	while (c = getchar() != '\n') {}
	return choose;
}

void _interface::Reader_Sign_Interface()
{
	system("cls");
	std::cout << "��ã����ߣ�\n"
		<< "����������ѧ�ź�����\n"
		<< std::endl;
}

void _interface::Administrator_Sign_Interface()
{
	system("cls");
	std::cout << "��ã�����Ա��\n"
		<< "���������Ĺ��ź����룺\n"
		<< std::endl;
}

void _interface::ReaderInterface()
{
	/*���飬���飬���飬���˻�����Ϣ����Ҫ����޸���������*/
	/*printf("\n");
	for (int i = 0;i < 30;++i)
	{
		printf(" ");
	}
	printf("***��ӭʹ��ͼ�����ϵͳ***\n");
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
	printf("A.���˻�����Ϣ\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("B.��Ҫ����\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("C.��Ҫ����\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("D.��Ҫ����\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("E.��Ҫ����\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("F.�޸�����\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("G.�˳�\n\n");
	for (int i = 0;i < 10;++i)
	{
		printf(" ");
	}
	for (int i = 0;i < 70;++i)
	{
		printf("-");
	}
	printf("\n��ѡ��");
	*/
}

void _interface::AdministratorInterface()
{
	printf("\n");
	for (int i = 0;i < 30;++i)
	{
		printf(" ");
	}
	printf("***��ӭʹ��ͼ�����ϵͳ***\n");
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
	printf("A.���˻�����Ϣ\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("B.ѧ����Ϣ����\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("C.ͼ����Ϣ����\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("D.�޸�����\n\n");
	for (int i = 0;i < 37;++i)
	{
		printf(" ");
	}
	printf("E.�˳�\n\n");
	for (int i = 0;i < 10;++i)
	{
		printf(" ");
	}
	for (int i = 0;i < 70;++i)
	{
		printf("-");
	}
	printf("\n��ѡ��");


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
			{/*��⵽exit�򷵻���һ��Ŀ¼*/
				_interface::Exit(1, 1, choose);
			} while (0);
			unsigned int len = choose.length();
			if (len != 1)
			{
				cout << "������һ���ַ�" << endl;
				continue;
			}
			break;
		} while (1);
		system("cls");
		/*��ջ�����*/
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
			printf("�ټ�������\n");
			exit(0);
			break;
		default:
			printf("������ѡ��");
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
				cout << "������һ���ַ�" << endl;
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
			printf("�ټ�������\n");
			exit(0);
			break;
		default:
			printf("������ѡ��");
			continue;
		}
		break;
	} while (1);
}

/*"������һ��Ŀ¼"ר��*/
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