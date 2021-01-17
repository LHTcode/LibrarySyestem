#include"SQLHead.h"
#include<iostream>
#include<string>
#include"DatabaseControl.h"
#include"UserInformation.h"
#include"_interface.h"
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


BOOL DatabaseControl::Borrow(std::string ISBN,DatabaseControl*& borrow_con)
{
	SQLRETURN ret;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, borrow_con->hdbc, &borrow_con->hstmt);
	ret = SQLSetStmtAttr(borrow_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	/*事务控制：查询该书籍状态，状态为可借用则用户借书数量+1，
	并将书名存入用户借书名称数据中，修改该书籍的状态为不可借*/
	std::string YesorNot;
	std::string swhere = "SELECT BookName FROM BOOK WHERE ISBN = ";
	std::string combine1 = swhere + '\'' + ISBN + '\'';
	const char* SQLSentence = combine1.c_str();
	ret = SQLPrepare(borrow_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	char BookName[30] = "";
	long BookName_len = 0;
	ret = SQLBindCol(borrow_con->hstmt, 1, SQL_C_CHAR, BookName, 30, &BookName_len);
	ret = SQLExecute(borrow_con->hstmt);
	if (!SQLSUCCESS(ret))
	{
		std::cerr << "该书不存在！" << std::endl;
		Sleep(700);
		system("cls");
		return 0;
	}
	if(ret = SQLFetchScroll(borrow_con->hstmt,SQL_FETCH_NEXT,0) != SQL_NO_DATA_FOUND)
	{ 

	}
	if (BookName != "")
	{
		std::cout << "是否确认借 " << BookName << " 这本书？" << std::endl;
		std::cout << "是      否" << std::endl;
		std::cin >> YesorNot;
		if (YesorNot.find("是") == std::string::npos)
		{
			return 0;
		}
	}

	delete borrow_con;
	/***从这里开始就失败了！！！！！！！！！！！！！！！！！！***/
	borrow_con = new DatabaseControl();
	ret = SQLAllocHandle(SQL_HANDLE_STMT, borrow_con->hdbc, &borrow_con->hstmt);
	ret = SQLSetStmtAttr(borrow_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	ret = SQLAllocHandle(SQL_HANDLE_STMT, borrow_con->hdbc, &borrow_con->hstmt);
	ret = SQLSetStmtAttr(borrow_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	std::string swhere1 = "SELECT BorrowedBookNum,BorrowedBookName FROM StuBook WHERE StuID = ";
	combine1 = swhere1 + '\'' + UserInformation::m_ID + '\'';
	SQLSentence = combine1.c_str();
	/*得到用户借书数量和书名*/
	ret = SQLPrepare(borrow_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	if (!SQLSUCCESS(ret))
	{
		printf("prepare failed !");
		exit(-1);
	}
	char cnum[10] = "";
	char cname[30] = "";
	long cnum_len = 0, cname_len = 0;
	ret = SQLBindCol(borrow_con->hstmt, 1, SQL_C_CHAR, cnum, 10, &cnum_len);
	ret = SQLBindCol(borrow_con->hstmt, 2, SQL_C_CHAR, cname, 30, &cname_len);
	if (!SQLSUCCESS(ret))
	{
		printf("bindcol1 failed!!");
		exit(-1);
	}
	ret = SQLExecute(borrow_con->hstmt);
	if (!SQLSUCCESS(ret))
	{
		printf("execute1 failed!");
		exit(-1);
	}
	if (ret = SQLFetch(borrow_con->hstmt) != SQL_NO_DATA_FOUND)
	{

	}
	delete borrow_con;
	/*得到书籍借用状态*/
	borrow_con = new DatabaseControl();
	ret = SQLAllocHandle(SQL_HANDLE_STMT, borrow_con->hdbc, &borrow_con->hstmt);
	ret = SQLSetStmtAttr(borrow_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	std::string swhere2 = " SELECT Isborrowed FROM BOOK WHERE ISBN = ";
	std::string combine2 = combine1 + swhere2 + '\'' + ISBN + '\'';
	SQLSentence = combine2.c_str();
	ret = SQLPrepare(borrow_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	if (!SQLSUCCESS(ret))
	{
		printf("prepare2 failed !");
		exit(-1);
	}
	char Isborrowed[5] = "";
	long Isborrowed_len = 0;
	
	ret = SQLBindCol(borrow_con->hstmt, 1, SQL_C_CHAR, Isborrowed, 5, &Isborrowed_len);
	ret = SQLExecute(borrow_con->hstmt);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	if(ret = SQLFetch(borrow_con->hstmt)!=SQL_NO_DATA_FOUND)
	{

	}

	if (atoi(Isborrowed) == 0)
	{
		printf("该书已被借用！");
		Sleep(700);
		system("cls");
		delete borrow_con;
		return 0;
	}
	delete borrow_con;
	/*将用户借书书名录入借用书籍栏*/
	borrow_con = new DatabaseControl();
	ret = SQLAllocHandle(SQL_HANDLE_STMT, borrow_con->hdbc, &borrow_con->hstmt);
	ret = SQLSetStmtAttr(borrow_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	std::string snum(cnum), sname(cname), sBookName(BookName);
	sname += ',' + sBookName;
	/*将用户结束数量加1*/
	int inum = stoi(snum);
	snum = std::to_string(++inum);
	/*开始修改数据库信息*/
	std::string update1 = "begin tran UPDATE BOOK SET Isborrowed = 0 UPDATE StuBook SET BorrowedBookNum = ";
	combine1 = update1 + snum;
	std::string update2 = " UPDATE StuBook SET BorrowedBookName = ";
	std::string finalcombine = combine1 + update2 + '\'' + sname + '\'' + " commit tran";
	SQLSentence = finalcombine.c_str();
	ret = SQLPrepare(borrow_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	/*string->char[]转换*/
	Isborrowed[0] = '0';
	char cBookName[1000] = "";
	char BookNum[10] = "";
	long ISlen = 0, BNamelen = 0, BNumlen = 0;
	int cnt = 0;
	while (sname[cnt] != NULL)
	{
		cBookName[cnt] = sname[cnt];
		++cnt;
	}
	for (cnt = 0;cnt < 10; ++cnt)
	{
		BookNum[cnt] = snum[cnt];
	}
	ret = SQLBindParameter(borrow_con->hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 2, 0, Isborrowed, 2, &ISlen);
	ret = SQLBindParameter(borrow_con->hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 30, 0, cBookName, 1000, &BNamelen);
	ret = SQLBindParameter(borrow_con->hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 10, 0, BookNum, 10, &BNumlen);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	ret = SQLExecute(borrow_con->hstmt);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	delete borrow_con;
	return 1;

}