#pragma once

class _interface
{
public:
	std::string& FirstChoose();

	void Reader_Sign_Interface();
	
	void Administrator_Sign_Interface();
	
	/*�����û�����*/
	void ReaderInterface();
	
	/*����Ա�û�����*/
	void AdministratorInterface();

	/*��½����û�ѡ��*/
	void ReaderChoose();
	/*��½����û�ѡ��*/
	void AdministratorChoose();

	/*������һ��Ŀ¼����*/
	/*****��ϣ���ܹ�ʵ�ֲ��ִ�Сд�Ĺ��ܣ���������취*****/
	static void Exit(short, std::string str);		//���ڶ��߹���Ա����ѡ���˳�
	static void Exit(short, short, std::string str);//�����û���¼�����˳�
	static void Exit(short, short, short, std::string str);


};