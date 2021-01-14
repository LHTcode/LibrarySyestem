#include"SQLHead.h"
#include<iostream>
#include"DatabaseControl.h"
#include"UserInformation.h"
/***********数据库连接************/
#define	SQLSUCCESS(rc) ((rc == SQL_SUCCESS) || (rc == SQL_SUCCESS_WITH_INFO))
void DatabaseControl::DatabaseConnect()
{
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	/*连接到数据库*/
	ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	ret = SQLConnect(hdbc, (SQLCHAR*)"mysql", SQL_NTS, (SQLCHAR*)"sa", SQL_NTS, (SQLCHAR*)"010615", SQL_NTS);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	


}

char*& DatabaseControl::PasswordSerch(int& choose, char(&ID)[100],DatabaseControl& con)
{
	/*设置语句句柄*/
	SQLRETURN ret;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, con.hdbc, &con.hstmt);
	ret = SQLSetStmtAttr(con.hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	
	/*查找并返回学生/管理员密码*/
	switch (choose)
	{
	case 1:
	{/*学生端*/
		std::string swhere = "SELECT StuPassword FROM stuPassword WHERE StuID = ";
		std::string sID(ID);
		std::string combine = swhere + '\'' + sID + '\'';
		const char* SQLSentence = combine.c_str();
		ret = SQLPrepare(hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
		if (!SQLSUCCESS(ret))
		{
			exit(-1);
		}
		char* Password = new char[7];
		*Password = NULL;		//将Password置空
		long cbPassword = 0;
		ret = SQLBindCol(hstmt, 1, SQL_C_CHAR, Password, 7, &cbPassword);
		if (!SQLSUCCESS(ret))
		{
			exit(-1);
		}
		ret = SQLExecute(hstmt);

		while (ret = SQLFetchScroll(hstmt, SQL_FETCH_NEXT, 0) != SQL_NO_DATA_FOUND)
		{
			/*这里Password得到了用户密码*/;
		}
		return Password;
		break;
	}
	case 2:
	{/*管理员端*/
		std::string swhere = "SELECT AdminPassword FROM adminPassword WHERE adminID = ";
		std::string sID(ID);
		std::string combine = swhere + '\'' + sID + '\'';
		const char* SQLSentence = combine.c_str();
		ret = SQLPrepare(hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
		if (!SQLSUCCESS(ret))
		{
			exit(-1);
		}
		static char* Password = new char[7];
		*Password = NULL;		//将Password置空
		long cbPassword = 0;
		ret = SQLBindCol(hstmt, 1, SQL_C_CHAR, Password, 7, &cbPassword);
		if (!SQLSUCCESS(ret))
		{
			exit(-1);
		}
		ret = SQLExecute(hstmt);

		while (ret = SQLFetchScroll(hstmt, SQL_FETCH_NEXT, 0) != SQL_NO_DATA_FOUND)
		{
			/*这里Password得到了用户密码*/;
		}
		return Password;
		break;
	}

	}
	
}

short DatabaseControl::PasswordChange(std::string NewPassword, DatabaseControl& PW_con)
{
	SQLRETURN ret;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, PW_con.hdbc, &PW_con.hstmt);
	ret = SQLSetStmtAttr(PW_con.hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	switch (UserInformation::ReOrAdmin)
	{
	case 1:
	{/*学生端*/
		std::string set = "UPDATE stuPassword SET StuPassword = ";
		std::string combine1 = set + '\'' + NewPassword + '\'';
		std::string where = "WHERE StuID = ";
		std::string combine2 = where + '\'' + UserInformation::m_ID + '\'';
		std::string finalcombine = combine1 + combine2;
		const char* SQLSentence = finalcombine.c_str();
		char SQLPassword[20] = "";
		char SQLID[20] = "";
		short cnt = 0;
		long Plen = 0;
		long Ilen = 0;
		/*为了能将Password放进SQLBindParameter语句里面，将string换成char[]*/
		while (NewPassword[cnt] != NULL)
		{
			SQLPassword[cnt] = NewPassword[cnt];
			++cnt;
		}
		cnt = 0;
		while (UserInformation::m_ID[cnt] != NULL)
		{
			SQLID[cnt] = UserInformation::m_ID[cnt];
			++cnt;
		}
		ret = SQLPrepare(PW_con.hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
		if (!SQLSUCCESS(ret))
		{
			printf("SQLPrepare 错误！！");
			exit(-1);
		}
		ret = SQLBindParameter(PW_con.hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, SQLPassword, 20, &Plen);
		ret = SQLBindParameter(PW_con.hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, SQLID, 20, &Ilen);
		if (!SQLSUCCESS(ret))
		{
			printf("SQLBindParameter 错误！！");
			exit(-1);
		}
		ret = SQLExecute(PW_con.hstmt);
		if (!SQLSUCCESS(ret))
		{
			printf("SQLExecute 错误！！");
			exit(-1);
		}
		return ret;
	}
	case 2:
	{/*管理员端*/
		std::string set = "UPDATE adminPassword SET AdminPassword = ";
		std::string combine1 = set + '\'' + NewPassword + '\'';
		std::string where = "WHERE adminID = ";
		std::string combine2 = where + '\'' + UserInformation::m_ID + '\'';
		std::string finalcombine = combine1 + combine2;
		const char* SQLSentence = finalcombine.c_str();
		char SQLPassword[20] = "";
		char SQLID[20] = "";
		short cnt = 0;
		long Plen = 0;
		long Ilen = 0;
		/*为了能将Password放进SQLBindParameter语句里面，将string换成char[]*/
		while (NewPassword[cnt] != NULL)
		{
			SQLPassword[cnt] = NewPassword[cnt];
			++cnt;
		}
		cnt = 0;
		while (UserInformation::m_ID[cnt] != NULL)
		{
			SQLID[cnt] = UserInformation::m_ID[cnt];
			++cnt;
		}
		ret = SQLPrepare(PW_con.hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
		if (!SQLSUCCESS(ret))
		{
			exit(-1);
		}
		ret = SQLBindParameter(PW_con.hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, SQLPassword, 20, &Plen);
		ret = SQLBindParameter(PW_con.hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, SQLID, 20, &Ilen);
		if (!SQLSUCCESS(ret))
		{
			exit(-1);
		}
		ret = SQLExecute(PW_con.hstmt);
		if (!SQLSUCCESS(ret))
		{
			exit(-1);
		}
		return ret;
	}
	}
	


}




void DatabaseControl::SerchBookInformation(std::string BookName,DatabaseControl& BS_con)
{
	SQLRETURN ret;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, BS_con.hdbc, &BS_con.hstmt);
	ret = SQLSetStmtAttr(BS_con.hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	std::string select = "SELECT* FROM BOOK WHERE BookName = ";
	std::string combine = select + '\'' + BookName + '\'';
	const char* SQLSentence = combine.c_str();
	ret = SQLPrepare(BS_con.hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	char ISBN[20] = "", Name[20] = "", Author[20] = "", Isborrowed[5] = "",
		Permission[20] = "", Addr[25] = "", Press[20] = "", Introduction[1000] = "";
	long cbISBN = 0, cbName = 0, cbAuthor = 0, cbIsborrowed = 0,
		cbPermission = 0, cbAddr = 0, cbPress = 0, cbIntroduction = 0;
	
	ret = SQLBindCol(BS_con.hstmt, 1, SQL_C_CHAR, ISBN, 20, &cbISBN);
	ret = SQLBindCol(BS_con.hstmt, 2, SQL_C_CHAR, Name, 20, &cbName);
	ret = SQLBindCol(BS_con.hstmt, 3, SQL_C_CHAR, Author, 20, &cbAuthor);
	ret = SQLBindCol(BS_con.hstmt, 4, SQL_C_CHAR, Isborrowed, 5, &cbIsborrowed);
	ret = SQLBindCol(BS_con.hstmt, 5, SQL_C_CHAR, Permission, 20, &cbPermission);
	ret = SQLBindCol(BS_con.hstmt, 6, SQL_C_CHAR, Addr, 25, &cbAddr);
	ret = SQLBindCol(BS_con.hstmt, 7, SQL_C_CHAR, Press, 20, &cbPress);
	ret = SQLBindCol(BS_con.hstmt, 8, SQL_C_CHAR, Introduction, 1000, &cbIntroduction);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	ret = SQLExecute(BS_con.hstmt);
	while (ret = SQLFetchScroll(hstmt, SQL_FETCH_NEXT, 0) != SQL_NO_DATA_FOUND)
	{
		;
	}
	do
	{
		if (ISBN[0] == '\0')
		{
			printf("\n暂无此书信息\n");
			continue;
		}
		printf("\n书名：%s\n\nISBC号：%s\n\n作者：%s\n\n出版社：%s\n\n图书状态：%s\n\n本书馆藏地址：%s\n\n简介：%s\n\n", Name,
			ISBN, Author, Press, Permission, Addr, Introduction);
	} while (0);
}