//---------------------------------------------------------------------------
#include "stdafx.h"
#include "AppException.h"
#include "FileUtils.h"
#include <stdio.h>
#include <direct.h>

TFileNames::TFileNames()
{
	next = NULL;
	mpc_FileName = NULL;
}

TFileNames::~TFileNames()
{
	if(mpc_FileName) {
		delete mpc_FileName;
	}
	if(next) {
		delete next;
	}
}

void TFileNames::AddFileName(char* _pc_FileName)
{
	if(mpc_FileName == NULL) {
		mpc_FileName = new char[strlen(_pc_FileName)+1];
#ifdef _MSC_VER
		strcpy_s(mpc_FileName,strlen(_pc_FileName)+1,_pc_FileName);
#else 
		strcpy(mpc_FileName,_pc_FileName);
#endif
	}
	else if (next == NULL){
		next = new TFileNames();
		next->AddFileName(_pc_FileName);
	}
	else {
		next->AddFileName(_pc_FileName);
	}
}

int TFileNames::GetFileNameLength(int* _pi_FileNameLength, int _i_Index)
{
	int iret = RET_RANGEERR;
	if(_i_Index==1) {
		*_pi_FileNameLength = strlen(mpc_FileName);
		iret = RET_OK;
	}
	else if(next != NULL) {
		iret = next->GetFileNameLength(_pi_FileNameLength,_i_Index-1);	
	}
	return iret;
}

int TFileNames::GetFileName(char* _pc_FileName, int _i_Index)
{
	int iret = RET_RANGEERR;
	if(_i_Index==1) {
#ifdef _MSC_VER
		strcpy_s(_pc_FileName,strlen(mpc_FileName)+1,mpc_FileName);
#else 
		strcpy(_pc_FileName,mpc_FileName);
#endif
		iret = RET_OK;
	}
	else if(next != NULL) {
		iret = next->GetFileName(_pc_FileName,_i_Index-1);	
	}
	return iret;
}

unsigned int TFileUtils::MAX_LINE_LEN = 512;

void TFileUtils::GetFilesInDir(const char* _pc_Path,
							   int* _pi_DllsinDir, TFileNames* _p_FileNames, 
							   const char* _pc_PreID, const char* _pc_FileType)
{
	*_pi_DllsinDir = 0;
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind;
	
	char* cp_FileNames = new char[strlen(_pc_PreID)+strlen(_pc_FileType)+5];
#ifdef _MSC_VER
    sprintf_s(cp_FileNames,strlen(_pc_PreID)+strlen(_pc_FileType)+5, "\\%s*.%s", _pc_PreID, _pc_FileType);
#else
    sprintf(cp_FileNames, "\\%s*.%s", _pc_PreID, _pc_FileType);
#endif
	char* cp_SearchString = new char[strlen(_pc_Path)+strlen(cp_FileNames)+5];
	int iDestSize = strlen(cp_SearchString);

	if (cp_SearchString) {
#ifdef _MSC_VER
		sprintf_s(cp_SearchString,strlen(_pc_Path)+strlen(cp_FileNames)+5,"%s%s",_pc_Path,cp_FileNames);
#else
		sprintf(cp_SearchString,"%s%s",_pc_Path,cp_FileNames);
#endif
	}

	if(cp_SearchString) {
		hFind = FindFirstFileA(cp_SearchString, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
		{
			delete[] cp_SearchString;
			int iError = GetLastError();
			throw TAppException(TAppException::APPEXCEPTION_UNABLETOFINDANYFILES,"Unable to find any files"); 
		} 
		else
		{
			(*_pi_DllsinDir)++;
			_p_FileNames->AddFileName((char*)FindFileData.cFileName);
			int iret = 1;
			while(iret) {
				iret = FindNextFileA(hFind, &FindFileData);
				if(iret) {
					_p_FileNames->AddFileName((char*)FindFileData.cFileName);
					(*_pi_DllsinDir)++;
				}
			}
		}
		FindClose(hFind);
	}
	delete[] cp_SearchString;
	delete[] cp_FileNames;
}

bool TFileUtils::CheckFileExists(const char* _pc_Path)
{  
	bool b_ret = true;
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = FindFirstFileA(_pc_Path, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
      b_ret = false;
	}
	else {
	  FindClose(hFind);
	}
	return b_ret;
}

bool TFileUtils::CreateNewFile(const char* _pc_Path)
{
	bool b_ret = true;
    HANDLE hFind = CreateFileA(_pc_Path, (GENERIC_READ | GENERIC_WRITE), 
			                   0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFind == INVALID_HANDLE_VALUE) {
      b_ret = false;
	}
	else {
	  FindClose(hFind);
	}
	return b_ret;
}

bool TFileUtils::CreateCWDPath(char* _pc_Path, unsigned int _ui_buffLen, const char* _pc_FileName)
{
  bool b_ret = false;
  if(_getcwd(_pc_Path, _ui_buffLen)) {
    b_ret = true;
    if(_pc_FileName) {
#ifdef _MSC_VER
      sprintf_s(_pc_Path,_ui_buffLen,"%s\\%s",_pc_Path,_pc_FileName);
#else
      sprintf(_pc_Path,"%s\\%s",_pc_Path,_pc_FileName);
#endif
    }
  }
  else {
    _pc_Path = NULL;
  }
  return b_ret;
}

int TFileUtils::GetNumLinesInFile(char* _pc_FileName, int _i_MaxLineLength)
{
  FILE *fp = fopen(_pc_FileName,"r");
  int i_numLines = 0;
  if (fp != NULL) {
	char* stringptr = new char[_i_MaxLineLength];
	while (true) {
	  if (fgets(stringptr, _i_MaxLineLength, fp) == NULL) break;
	  i_numLines++;
	  if (feof(fp)) break;
	}
	delete[] stringptr;
	fclose(fp);
  }
  return i_numLines;
}

bool TFileUtils::GetAllLinesInFile(char* _pc_FileName, char*** _ppc_allLines, int* _pi_NumLines, int _i_MaxLineLength)
{
  int i_numLines = GetNumLinesInFile(_pc_FileName, _i_MaxLineLength);
  *_pi_NumLines = 0;
  if (i_numLines>0) {
	FILE *fp = fopen(_pc_FileName,"r");
	if (fp != NULL) {
	  *_ppc_allLines = new char*[i_numLines];

	  for (int i=0;i<i_numLines;++i) {
		*(*_ppc_allLines+i) = new char[_i_MaxLineLength];
		if (fgets(*(*_ppc_allLines+i), _i_MaxLineLength, fp) == NULL) break;
		if (feof(fp)) break;
	  }
	  fclose(fp);
	  *_pi_NumLines = i_numLines;
	  return true;
	}
  }
  return false;
}
