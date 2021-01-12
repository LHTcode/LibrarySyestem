#include"_Head.h"
#include"SQLHead.h"
#define	SQLSUCCESS(rc) ((rc == SQL_SUCCESS) || (rc == SQL_SUCCESS_WITH_INFO))

void Reader::ReaderOperate()
{
	_interface inter;
	inter.ReaderInterface();	
	this->inter->ReaderChoose();
}

jmp_buf password_jump;
void Reader::ChangePassword()
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
	longjmp(password_jump, 1);

}
/****1月12日修改：
解决了跳转bug问题，完成了读者端的密码修改模块
下一步将完成管理员端的密码修改模块，并完成读者查询图书模块****/