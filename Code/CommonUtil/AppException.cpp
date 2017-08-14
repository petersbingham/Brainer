#include "stdafx.h"
#include "AppException.h"
#include <string.h>

const unsigned short TAppException::APPEXCEPTION_DEFAULT					= 0x0000;
const unsigned short TAppException::APPEXCEPTION_UNABLETOFINDANYFILES			= 0x1001;
const unsigned short TAppException::APPEXCEPTION_UNABLETOLOADDLL			= 0x1002;

const unsigned short TAppException::APPEXCEPTION_GENERALMEMORYFAIL			= 0x2000;

const unsigned short TAppException::APPEXCEPTION_NOGAMESELECTED				= 0x3000;
const unsigned short TAppException::APPEXCEPTION_INDEXOUTSIDERANGE			= 0x3001;
const unsigned short TAppException::APPEXCEPTION_NOSUCHGAMETYPE				= 0x3002;
const unsigned short TAppException::APPEXCEPTION_EMPTYQUESTRING				= 0x3003;
const unsigned short TAppException::APPEXCEPTION_NOANSSTRING				= 0x3004;
const unsigned short TAppException::APPEXCEPTION_ANSSTRINGTOOLONG			= 0x3005;
const unsigned short TAppException::APPEXCEPTION_ANSRADIOOUTRANGE			= 0x3006;  

const unsigned short TAppException::APPEXCEPTION_HIGHSCRCORRUPT				= 0x4000; 

const unsigned short TAppException::APPEXCEPTION_DLLFUNCTIONRETURNERROR		= 0x5000; 

TAppException::TAppException()
{
	char* pc_Defaultmsg = "No message passed";
	mpc_errmsg = new char[strlen(pc_Defaultmsg)+1];
#ifdef _MSC_VER
	strcpy_s(mpc_errmsg,strlen(pc_Defaultmsg)+1,pc_Defaultmsg);
#else
	strcpy(mpc_errmsg,pc_Defaultmsg);
#endif
	mi_errcode = APPEXCEPTION_DEFAULT;
}

TAppException::TAppException(const int _i_errcode, const char* _pc_errsting)
{
	mpc_errmsg = new char[strlen(_pc_errsting)+1];
#ifdef _MSC_VER
	strcpy_s(mpc_errmsg,strlen(_pc_errsting)+1,_pc_errsting);
#else
	strcpy(mpc_errmsg,_pc_errsting);
#endif
	mi_errcode = _i_errcode;
}

TAppException::TAppException(const TAppException & copy)
{
	this->mi_errcode = copy.mi_errcode;
	if(copy.mpc_errmsg != NULL) {
		this->mpc_errmsg = new char[strlen(copy.mpc_errmsg)+1];
#ifdef _MSC_VER
		  strcpy_s(this->mpc_errmsg,strlen(copy.mpc_errmsg)+1,copy.mpc_errmsg);
#else
		  strcpy(this->mpc_errmsg,copy.mpc_errmsg);
#endif
	}
	else {
		this->mpc_errmsg = NULL;	
	}
}

TAppException::~TAppException()
{
	if(mpc_errmsg) {
		delete[] mpc_errmsg; 
	}
}

char* TAppException::GetMsg()
{
	return mpc_errmsg;
}

int TAppException::GetCode()
{
	return mi_errcode;
}
