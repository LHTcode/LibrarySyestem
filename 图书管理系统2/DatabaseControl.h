#pragma once
#include"SQLHead.h"

class DatabaseControl
{
	
public:
	void DatabaseConnect();			/*���ݿ����ӽӿ�*/
	/*�ù��캯������Connect��ʹDBC�౻���õ�ʱ�������ݿ�����*/
	DatabaseControl()
	{
		DatabaseConnect();
	}
	/*�����û����뺯��*/
	char*& PasswordSerch(int& choose, char(&ID)[100], DatabaseControl& con);
	
	/*�޸��û����뺯��*/
	void PasswordChange(char(&ID)[100]);
	~DatabaseControl()
	{
		/*�ͷž�����Ͽ�����*/
		ret = SQLDisconnect(hdbc);
		ret = SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
		ret = SQLFreeHandle(SQL_HANDLE_ENV, henv);
		ret = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	}
private:
	SQLHANDLE henv = NULL;		//�����������
	SQLHANDLE hdbc = NULL;		//�������Ӿ��
	SQLHANDLE hstmt = NULL;	//���������
	SQLRETURN ret;

};