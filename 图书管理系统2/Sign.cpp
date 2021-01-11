#include <iostream>
#include<stdio.h>
#include"_Head.h"
#include "Sign.h"
#include "_interface.h"
#include "DatabaseControl.h"
#include"SQLHead.h"
#include<string>
#include"UserInformation.h"

void Sign::AorB(std::string& choose)
{
	_interface face;
	/*选择读者登录还是管理员登录*/
	while (1)
	{
		
		if (choose.find("A") != std::string::npos)
		{
			face.Reader_Sign_Interface();
			break;
		}
		else if (choose.find("B") != std::string::npos)
		{
			face.Administrator_Sign_Interface();
			break;
		}
		else
		{
			std::cout << "请选择AB其中一个：" << std::endl;
			std::cin >> choose;
			/*清空缓冲区*/
			char c;
			while (c = getchar() != '\n') {}

		}

	}
}

/*用户身份判断*/
short ClientJudgment(std::string& choose)
{
	if (choose.find("A") != std::string::npos)
	{
		/*读者*/
		return 1;
	}
	else if (choose.find("B") != std::string::npos)
	{
		/*管理员*/
		return 2;
	}
}

/*密码输入与判断函数*/
void PasswordEnterAndCheck(int choose)
{
	char ID[100] = "";
	char password[100] = "";
	short i = 0, j = 0;
	DatabaseControl con;
	//Sign sign;
	switch (choose)
	{
	case 1:
	{
		printf("学号：");
		char* Realpassword = NULL;
		do
		{
			gets_s(ID);			//输入10位学号
			do
			{
				/*检测到用户输入exit则返回上一级目录*/
				_interface::Exit(1, ID);
			} while (0);
			/*获取密码*/
			Realpassword = con.PasswordSerch(choose, ID, con);
			if (Realpassword[0] != NULL)
			{
				break;
			}
			else
			{
				printf("请重新输入学号：");
			}

		} while (1);
		printf("密码：");
		do
		{
			gets_s(password);	//输入6位密码
			do
			{
				/*检测到用户输入exit则返回上一级目录*/
				_interface::Exit(1, password);
			} while (0);
			/*密码核对*/
			int cnt = 0;
			for (int i = 0; i < 6;++i)
			{
				if (password[i] == Realpassword[i])
				{
					++cnt;
				}
			}
			if (cnt == 6 && password[6] == NULL)
			{
				printf("登陆成功！");
				delete Realpassword;
				//_interface inter;
				UserInformation::m_ID = ID;
				UserInformation::m_Password = password;
				Sleep(1000);
				system("cls");
				//inter.ReaderInterface();
				break;
			}
			else
			{
				printf("密码错误！\n请重新输入密码：");
			}
		} while (1);

		break;
	}
	case 2:
	{
		printf("工号：");
		int chances = 3;
		char* Realpassword = NULL;
		do
		{
			gets_s(ID);			//输入10位工号
			do
			{
				/*检测到用户输入exit则返回上一级目录*/
				_interface::Exit(1, ID);
			} while (0);
			/*获取密码*/
			Realpassword = con.PasswordSerch(choose, ID, con);
			if (Realpassword[0] != NULL)
			{
				break;
			}
			else
			{
				printf("请重新输入工号：");
			}
		} while (1);
		printf("密码：");		//管理员密码输入判断不提供exit返回上一级服务
		do
		{
			gets_s(password);	//输入6位密码
			/*密码核对*/
			int cnt = 0;
			for (int i = 0; i < 6;++i)
			{
				if (password[i] == Realpassword[i])
				{
					++cnt;
				}
			}
			if (cnt == 6 && password[6] == NULL && chances > 0)
			{
				printf("登陆成功！");
				delete[]Realpassword;
				//_interface inter;
				UserInformation::m_ID = ID;
				UserInformation::m_Password = password;
				Sleep(1000);
				system("cls");
				//inter.AdministratorInterface();
				break;
			}
			else
			{
				--chances;
				if (0 == chances)
				{
					std::cerr << "您用完了所有机会，请重启系统" << std::endl;
					Sleep(1000);
					exit(-1);
				}
				printf("密码错误！您还有%d次机会\n请重新输入密码：",chances);
			}
		} while (1);
	}
	}

}

/*密码判断主函数*/
void Sign::Password(std::string& choose)
{
	PasswordEnterAndCheck(ClientJudgment(choose));

}
