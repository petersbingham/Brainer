class TAppException
{
public:
	TAppException();
	TAppException(const int _i_errcode, const char* _pc_errsting);
	TAppException(const TAppException & copy);
	~TAppException();
	char* GetMsg();
	int GetCode();
	
	static const unsigned short APPEXCEPTION_DEFAULT;
	static const unsigned short APPEXCEPTION_UNABLETOFINDANYFILES;
	static const unsigned short APPEXCEPTION_UNABLETOLOADDLL;

  static const unsigned short APPEXCEPTION_GENERALMEMORYFAIL;

	static const unsigned short APPEXCEPTION_NOGAMESELECTED;
	static const unsigned short APPEXCEPTION_INDEXOUTSIDERANGE;
	static const unsigned short APPEXCEPTION_NOSUCHGAMETYPE;
	static const unsigned short APPEXCEPTION_EMPTYQUESTRING;
	static const unsigned short APPEXCEPTION_NOANSSTRING;
	static const unsigned short APPEXCEPTION_ANSSTRINGTOOLONG;
	static const unsigned short APPEXCEPTION_ANSRADIOOUTRANGE;

	static const unsigned short APPEXCEPTION_HIGHSCRCORRUPT;

	static const unsigned short APPEXCEPTION_DLLFUNCTIONRETURNERROR;

private:
	char* mpc_errmsg;
	int mi_errcode;
};