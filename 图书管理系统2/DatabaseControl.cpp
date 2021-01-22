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
	if(ret = SQLFetchScroll(borrow_con->hstmt,SQL_FETCH_NEXT,0) != SQL_NO_DATA_FOUND)
	{ 

	}
	std::string sBookName(BookName);
	if (sBookName.empty())
	{
		std::cerr << "该书不存在！" << std::endl;
		Sleep(700);
		system("cls");
		return 0;
	}
	
	if (!sBookName.empty())
	{
		std::cout << "是否确认借 " << BookName << " 这本书？" << std::endl;
		std::cout << "是      否" << std::endl;
		std::getline(std::cin,YesorNot);
		if (YesorNot.find("是") == std::string::npos)
		{
			return 0;
		}
	}

	delete borrow_con;		//释放句柄和环境
	borrow_con = new DatabaseControl();		//重置句柄和环境
	ret = SQLAllocHandle(SQL_HANDLE_STMT, borrow_con->hdbc, &borrow_con->hstmt);
	ret = SQLSetStmtAttr(borrow_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	std::string swhere1 = "SELECT BorrowedBookNum,BorrowedBookName FROM StuBook WHERE StuID = ";
	combine1 = swhere1 + '\'' + UserInformation::m_ID + '\'';
	SQLSentence = combine1.c_str();
	/*得到用户借书数量和书名*/
	ret = SQLPrepare(borrow_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	char cnum[10] = "";
	char cname[30] = "";
	long cnum_len = 0, cname_len = 0;
	ret = SQLBindCol(borrow_con->hstmt, 1, SQL_C_CHAR, cnum, 10, &cnum_len);
	ret = SQLBindCol(borrow_con->hstmt, 2, SQL_C_CHAR, cname, 30, &cname_len);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	ret = SQLExecute(borrow_con->hstmt);
	if (!SQLSUCCESS(ret))
	{
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
	std::string combine2 = swhere2 + '\'' + ISBN + '\'';
	SQLSentence = combine2.c_str();
	ret = SQLPrepare(borrow_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	if (!SQLSUCCESS(ret))
	{
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
	std::string snum(cnum), sname(cname);
	sname += ',' + sBookName;
	/*将用户结束数量加1*/
	int inum = stoi(snum);
	snum = std::to_string(++inum);
	/*开始修改数据库信息*/
	std::string update1 = "begin tran UPDATE BOOK SET Isborrowed = 0 ";
	std::string uwhere1 = "WHERE ISBN = ";
	combine1 = update1 + uwhere1 + '\'' + ISBN + '\'';
	std::string update2 = "UPDATE StuBook SET BorrowedBookNum = ";
	std::string uwhere2 = "WHERE StuID = ";
	combine2 = update2 + snum + uwhere2 + '\'' + UserInformation::m_ID + '\'';
	std::string update3 = " UPDATE StuBook SET BorrowedBookName = ";
	std::string uwhere = "WHERE StuID = ";
	std::string combine3 = update3 + '\'' + sBookName + " \'" + uwhere + '\'' + UserInformation::m_ID + '\'';
	std::string finalcombine = combine1 + combine2 + combine3 + " commit tran";
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
	cnt = 0;
	while (snum[cnt] != NULL)
	{
		BookNum[cnt] = snum[cnt];
		++cnt;
	}
	
	ret = SQLBindParameter(borrow_con->hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 2, 0, Isborrowed, 2, &ISlen);
	ret = SQLBindParameter(borrow_con->hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 1000, 0, cBookName, 1000, &BNamelen);
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

void DatabaseControl::SelfInformationPrint(DatabaseControl*& selfinfor_con)
{
	/*用户信息包括：
	  学号、名字、性别、专业班级、学院、借书数量、借书书名、违规次数、欠款金额、信誉分值*/
	SQLRETURN ret;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, selfinfor_con->hdbc, &selfinfor_con->hstmt);
	ret = SQLSetStmtAttr(selfinfor_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	std::string select1 = "SELECT* FROM Student WHERE StuID = ";
	std::string combine1 = select1 + '\'' + UserInformation::m_ID + " \'";
	const char* SQLSentence = combine1.c_str();
	
	

	SQLPrepare(selfinfor_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	char StuID[15] = "", StuName[25] = "", Sex[5] = "", SpecialityAndClass[30] = "",
		Department[30] = "", BorrowedBookNum[5] = "", BorrowedBookName[1000] = "",
		Violations[5] = "", Arrearage[5] = "", Feedback_score[4] = "";
	long StuID_len = 0, StuName_len = 0, Sex_len = 0, SpecialityAndClass_len = 0, 
		Department_len = 0,BorrowedBookNum_len = 0, BorrowedBookName_len = 0, 
		Violations_len = 0, Arrearage_len = 0,Feedback_score_len = 0;
	SQLBindCol(selfinfor_con->hstmt, 1, SQL_C_CHAR, StuID, 15, &StuID_len);
	SQLBindCol(selfinfor_con->hstmt, 2, SQL_C_CHAR, StuName, 25, &StuName_len);
	SQLBindCol(selfinfor_con->hstmt, 3, SQL_C_CHAR, Sex, 5, &Sex_len);
	SQLBindCol(selfinfor_con->hstmt, 4, SQL_C_CHAR, Department, 30, &Department_len);
	SQLBindCol(selfinfor_con->hstmt, 5, SQL_C_CHAR, SpecialityAndClass, 30, &SpecialityAndClass_len);
	SQLExecute(selfinfor_con->hstmt);
	while (ret = SQLFetchScroll(selfinfor_con->hstmt, SQL_FETCH_NEXT, 0) != SQL_NO_DATA_FOUND)
	{
		;
	}
	delete selfinfor_con;

	selfinfor_con = new DatabaseControl();;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, selfinfor_con->hdbc, &selfinfor_con->hstmt);
	ret = SQLSetStmtAttr(selfinfor_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	std::string select2 = "SELECT* FROM StuFeedback_score WHERE StuID = ";
	std::string combine2 = select2 + '\'' + UserInformation::m_ID + " \'";
	SQLSentence = combine2.c_str();
	SQLPrepare(selfinfor_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	SQLBindCol(selfinfor_con->hstmt, 1, SQL_C_CHAR, StuID, 15, &StuID_len);
	SQLBindCol(selfinfor_con->hstmt, 2, SQL_C_CHAR, Feedback_score, 4, &Feedback_score_len);
	SQLBindCol(selfinfor_con->hstmt, 3, SQL_C_CHAR, Violations, 5, &Violations_len);
	SQLBindCol(selfinfor_con->hstmt, 4, SQL_C_CHAR, Arrearage, 5, &Arrearage_len);
	SQLExecute(selfinfor_con->hstmt);
	while (ret = SQLFetchScroll(selfinfor_con->hstmt, SQL_FETCH_NEXT, 0) != SQL_NO_DATA_FOUND)
	{
		;
	}
	delete selfinfor_con;
	
	selfinfor_con = new DatabaseControl();
	ret = SQLAllocHandle(SQL_HANDLE_STMT, selfinfor_con->hdbc, &selfinfor_con->hstmt);
	ret = SQLSetStmtAttr(selfinfor_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	std::string select3 = "SELECT* FROM StuBook WHERE StuID = ";
	std::string combine3 = select3 + '\'' + UserInformation::m_ID + " \'";
	SQLSentence = combine3.c_str();
	SQLPrepare(selfinfor_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	SQLBindCol(selfinfor_con->hstmt, 1, SQL_C_CHAR, StuID, 15, &StuID_len);
	SQLBindCol(selfinfor_con->hstmt, 2, SQL_C_CHAR, BorrowedBookNum, 5, &BorrowedBookNum_len);
	SQLBindCol(selfinfor_con->hstmt, 3, SQL_C_CHAR, BorrowedBookName, 1000, &BorrowedBookName_len);
	SQLExecute(selfinfor_con->hstmt);
	while (ret = SQLFetchScroll(selfinfor_con->hstmt, SQL_FETCH_NEXT, 0) != SQL_NO_DATA_FOUND)
	{
		;
	}

	printf("姓名：%s\t学号%s\t性别：%s\t学院：%s\t专业班级：%s\n书籍在借数量：%s\n借用书籍名：%s\n违规次数：%s\n欠款金额：%s\n信誉分值：%s\n",
		StuName, StuID, Sex, Department, SpecialityAndClass, BorrowedBookNum,
		BorrowedBookName, Violations, Arrearage, Feedback_score);
	system("pause");
	system("cls");
	delete selfinfor_con;
}



BOOL DatabaseControl::ReturnBook(std::string ISBN, DatabaseControl*& returnbook_con)
{
	SQLRETURN ret;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, returnbook_con->hdbc, &returnbook_con->hstmt);
	ret = SQLSetStmtAttr(returnbook_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	/*获得ISBN对应的书籍名，以及书籍借用状态*/
	std::string YesorNot;
	std::string swhere1 = "SELECT BookName,Isborrowed FROM BOOK WHERE ISBN = ";
	std::string combine1 = swhere1 + '\'' + ISBN + '\'';
	const char* SQLSentence = combine1.c_str();
	ret = SQLPrepare(returnbook_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	char BookName[30] = "";
	char Isborrowed[2] = "";
	long BookName_len = 0, Isborrowed_len = 0;
	ret = SQLBindCol(returnbook_con->hstmt, 1, SQL_C_CHAR, BookName, 30, &BookName_len);
	ret = SQLBindCol(returnbook_con->hstmt, 2, SQL_C_CHAR, Isborrowed, 2, &Isborrowed_len);
	ret = SQLExecute(returnbook_con->hstmt);
	if (ret = SQLFetchScroll(returnbook_con->hstmt, SQL_FETCH_NEXT, 0) != SQL_NO_DATA_FOUND)
	{

	}
	if (atoi(Isborrowed) == 1)
	{
		printf("该书已归还！");
		Sleep(700);
		delete returnbook_con;
		system("cls");
		return 0;
	}
	Isborrowed[0] = '1';
	std::string sBookName(BookName);
	if (sBookName.empty())
	{
		std::cerr << "该书不存在！" << std::endl;
		Sleep(700);
		system("cls");
		return 0;
	}

	if (!sBookName.empty())
	{
		std::cout << "是否确认归还 " << BookName << " 这本书？" << std::endl;
		std::cout << "是      否" << std::endl;
		std::getline(std::cin, YesorNot);
		if (YesorNot.find("是") == std::string::npos)
		{
			return 0;
		}
	}
	delete returnbook_con;		//释放句柄和环境

	returnbook_con = new DatabaseControl();
	ret = SQLAllocHandle(SQL_HANDLE_STMT, returnbook_con->hdbc, &returnbook_con->hstmt);
	ret = SQLSetStmtAttr(returnbook_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	/*先获取用户已借书籍数量和书名*/
	swhere1 = "SELECT BorrowedBookNum,BorrowedBookName FROM StuBook WHERE StuID = ";
	combine1 = swhere1 + '\'' + UserInformation::m_ID + '\'';
	SQLSentence = combine1.c_str();
	ret = SQLPrepare(returnbook_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	char cnum[10] = "";
	char cname[100] = "";
	long cnum_len = 0, cname_len = 0;
	ret = SQLBindCol(returnbook_con->hstmt, 1, SQL_C_CHAR, cnum, 10, &cnum_len);
	ret = SQLBindCol(returnbook_con->hstmt, 2, SQL_C_CHAR, cname, 100, &cname_len);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	ret = SQLExecute(returnbook_con->hstmt);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	if (ret = SQLFetch(returnbook_con->hstmt) != SQL_NO_DATA_FOUND)
	{

	}
	delete returnbook_con;

	/*用户借书数量-1*/
	int inum = atoi(cnum);
	--inum;
	_itoa_s(inum, cnum, 10);
	/*将该书从用户借书单中除去*/
	//std::string lendedbook_buffer(cname);
	//std::string returnbookname_buffer(BookName);
	int wordsnum = 0;
	while (cname[wordsnum] != NULL)
	{
		++wordsnum;
	}
	char* lendedbook_list_buffer = new char[wordsnum + 1];
	for (int i = 0;i < wordsnum;++i)
	{
		lendedbook_list_buffer[i] = cname[i];
	}
	lendedbook_list_buffer[wordsnum] = '\0';
	/*for (int i = 0;i < wordsnum;++i)
	{
		lendedbook_list[i] = lendedbook_buffer[i];
	}
	lendedbook_list[wordsnum] = '\0';
	*/
	wordsnum = 0;
	while (BookName[wordsnum] != NULL)
	{
		++wordsnum;
	}
	char* returnbook_name_buffer = new char[wordsnum + 1];
	for (int i = 0;i < wordsnum;++i)
	{
		returnbook_name_buffer[i] = BookName[i];
	}
	returnbook_name_buffer[wordsnum] = '\0';
	/*for (int i = 0;i < wordsnum;++i)
	{
		returnbook_name[i] = returnbookname_buffer[i];
	}
	returnbook_name[wordsnum] = '\0';
	*/
	std::string lendedbook_list(lendedbook_list_buffer);
	std::string returnbook_name(returnbook_name_buffer);
	int front = lendedbook_list.find(returnbook_name);		//计算借书名册中归还书籍名前的字符数
	int behine = lendedbook_list.length() - front - 1;		//计算结束名册中归还书籍名后的字符数，-1是为了减去书之间的空格
	char* newlendedbook_list_char = new char[front + behine + 1];//+1是加上'\0'
	int i = 0;
	//这里是为了录入借书名册中归还书籍名前的书名
	for (;i < front;++i)
	{
		newlendedbook_list_char[i] = lendedbook_list[i];
	}
	//这里是为了跳过录入归还书籍书名
#define skip_that_book front + returnbook_name.length() + 1
#define the_hole_length lendedbook_list.length()
	if (skip_that_book == the_hole_length)
	{
		newlendedbook_list_char[0] = NULL;
	}
	for (int spot = skip_that_book;spot < the_hole_length;++spot)//+1是为了加上书名之间的空格
	{
		newlendedbook_list_char[i] = lendedbook_list[spot];
		++i;
	}
	std::string newlendedbook_list_string(newlendedbook_list_char);//将char[]转为string方便后面合并语句

	delete[]lendedbook_list_buffer;
	delete[]returnbook_name_buffer;

	/*修改用户借书信息*/
	returnbook_con = new DatabaseControl();
	ret = SQLAllocHandle(SQL_HANDLE_STMT, returnbook_con->hdbc, &returnbook_con->hstmt);
	ret = SQLSetStmtAttr(returnbook_con->hstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, SQL_IS_INTEGER);
	/*1.更改借书数量
	  2.更改借书单
	  3.更改书籍借用状态*/
	
	/*3.*/
	std::string update1 = "begin tran UPDATE BOOK SET Isborrowed = 1 WHERE ISBN = ";
	combine1 = update1 + '\'' + ISBN + '\'';
	/*2.*/
	std::string update2 = "UPDATE StuBook SET BorrowedBookName = ";
	std::string combine2 = update2 + '\'' + newlendedbook_list_string + '\'';
	std::string upwhere = " WHERE StuID = ";
	std::string combine3 = combine2 + upwhere + '\'' + UserInformation::m_ID + '\'';
	/*1.*/
	std::string update3 = "UPDATE StuBook SET BorrowedBookNum = ";
	std::string combine4 = update3 + cnum;
	std::string finalcombine = combine1 + combine2 + combine3 + combine4 + "commit tran";
	SQLSentence = finalcombine.c_str();
	ret = SQLPrepare(returnbook_con->hstmt, (SQLCHAR*)SQLSentence, SQL_NTS);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}

	int newlendedbook_list_size = front + behine + 1;
	Isborrowed_len = 0;
	long newlendedbook_list_len = 0, cnum_lem = 0;
	ret = SQLBindParameter(returnbook_con->hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 2, 0, Isborrowed, 2, &Isborrowed_len);
	ret = SQLBindParameter(returnbook_con->hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, newlendedbook_list_size, 0, newlendedbook_list_char, newlendedbook_list_size, &newlendedbook_list_len);
	ret = SQLBindParameter(returnbook_con->hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 10, 0, cnum, 10, &cnum_lem);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}
	ret = SQLExecute(returnbook_con->hstmt);
	if (!SQLSUCCESS(ret))
	{
		exit(-1);
	}


	delete[]newlendedbook_list_char;
	delete returnbook_con;
}