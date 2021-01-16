#pragma once
#include"SQLHead.h"

class DatabaseControl
{
	
public:
	void DatabaseConnect();			/*数据库连接接口*/
	/*用构造函数启动Connect，使DBC类被调用的时候即与数据库连接*/
	DatabaseControl()
	{
		DatabaseConnect();
	}
	/*调出用户密码函数*/
	char*& PasswordSerch(int& choose, char(&ID)[100], DatabaseControl& con);
	
	/*修改用户密码函数*/
	short PasswordChange(std::string NewPassword, DatabaseControl& PW_con);

	/*图书查询函数*/
	void SerchBookInformation(std::string BookName, DatabaseControl& con);

	/*借书函数*/
	BOOL Borrow(std::string ISBN, DatabaseControl& borrow_con);

	~DatabaseControl()
	{
		/*释放句柄、断开连接*/
		ret = SQLDisconnect(hdbc);
		ret = SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
		ret = SQLFreeHandle(SQL_HANDLE_ENV, henv);
		//ret = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	}
private:
	SQLHANDLE henv = NULL;		//声明环境句柄
	SQLHANDLE hdbc = NULL;		//声明连接句柄
	SQLHANDLE hstmt = NULL;	//声明语句句柄
	SQLRETURN ret;

};