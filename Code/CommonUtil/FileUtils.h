//---------------------------------------------------------------------------
#ifndef FileUtilsH
#define FileUtilsH

#include <windows.h>

class TFileNames
{
public:
	TFileNames();
	~TFileNames();
	void AddFileName(char* _pc_FileName);
	int GetFileNameLength(int* _pi_FileNameLength, int _i_Index);
	int GetFileName(char* _pc_FileName, int _i_Index);
private:
	char* mpc_FileName;
	TFileNames* next;
};

class TFileUtils
{
  public:
	static unsigned int MAX_LINE_LEN;
    static void GetFilesInDir(const char* _pc_Path, int* _pi_DllsinDir, TFileNames* _p_FileNames, 
							  const char* _pc_PreID, const char* _pc_FileType);
	static bool CheckFileExists(const char* _pc_Path);
	static bool CreateNewFile(const char* _pc_Path);
	static bool CreateCWDPath(char* _pc_Path, unsigned int _ui_buffLen, const char* _pc_FileName = NULL);
	static int GetNumLinesInFile(char * _pc_FileName, int _i_MaxLineLength=MAX_LINE_LEN);
	static bool GetAllLinesInFile(char* _pc_FileName, char*** _ppc_allLines, int* _pi_NumLines, int _i_MaxLineLength=MAX_LINE_LEN);
};

//---------------------------------------------------------------------------
#endif
