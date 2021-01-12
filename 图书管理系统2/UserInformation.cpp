#include<iostream>
#include"UserInformation.h"

std::string UserInformation::m_ID = "";
std::string UserInformation::m_Password = "";
/*1代表学生，2代表管理员*/
short UserInformation::ReOrAdmin;