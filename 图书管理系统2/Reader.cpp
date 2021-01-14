#include"_Head.h"
#include"SQLHead.h"
#define	SQLSUCCESS(rc) ((rc == SQL_SUCCESS) || (rc == SQL_SUCCESS_WITH_INFO))

void Reader::ReaderOperate() const 
{
	_interface inter;
	inter.ReaderInterface();	
	this->inter->ReaderChoose();
}

void Reader::ChangePassword() const
{
	std::string OldPassword;
	std::string first_NewPassword = "";
	std::string second_NewPassword = "";
	system("cls");
	printf("***注意***\n密码为6位数\n\n");
	printf("请输入原始密码：");
	while (1)
	{
		std::getline(std::cin, OldPassword);
		if (OldPassword != UserInformation::m_Password)
		{
			printf("密码错误！请重试：");
		}
		else
		{
			break;
		}
	}
	while (1)
	{
		printf("请输入新密码：");
		std::getline(std::cin, first_NewPassword);
		/*检查用户输入是否为6位*/
		while (first_NewPassword.length()!=6)
		{
			printf("密码仅为6位字符，请重新输入：");
			std::getline(std::cin, first_NewPassword);
		}
		printf("请再次输入新密码：");
		std::getline(std::cin, second_NewPassword);
		if (first_NewPassword == second_NewPassword)
		{
			break;
		}
		printf("两次密码不一致！请重新设置密码");
	}
	/***连接数据库改密码接口***/
	DatabaseControl PW_con;
	short ret = 0;
	ret = PW_con.PasswordChange(second_NewPassword, PW_con);
	if (!SQLSUCCESS(ret))
	{
		std::cerr << "修改密码失败！请联系管理员" << std::endl;
	}
	else
	{
		std::cout << "修改成功！" << std::endl;
		UserInformation::m_Password = second_NewPassword;
		Sleep(1000);
	}
	system("cls");
	_interface::autoExit();

}


void Reader::BookSerch() const
{
	DatabaseControl BS_con;
	std::string BookName;
	std::string BookInformation;
	while (1)
	{
		printf("请输入你想查询的图书全名：");
		std::getline(std::cin, BookName);
		/*要实现查书需要几个步骤：
			1.我输入需要的书名；
			2.系统从Database中调取该书的信息反馈给我
			3.用system("pause")提示用户按任意键继续，用户按任意键后清屏，再次弹出查询界面
			4.需要有exit返回上一级目录功能*/

		_interface::Exit(1, 1, BookName);

		BS_con.SerchBookInformation(BookName, BS_con);
		system("pause");
		system("cls");
	}

}