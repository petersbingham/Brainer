#include "stdafx.h"
#include "GameContainer.h"
#include "GamedllWrapper.h"
#include "FileUtils.h"
#include "AppException.h"
#include <direct.h>
#include <string.h>
#include <tchar.h>

TGameContainer::TGameContainer()
{
	memset(mpc_cwd,'/0',PATHLEN);
	mpp_GameWrappers = NULL;
	mi_NoDlls = 0;
}

TGameContainer::~TGameContainer()
{
	if(mpp_GameWrappers) {
		for(int i=0;i<mi_NoDlls;i++) {
			delete	mpp_GameWrappers[i]; 
		}
		delete[] mpp_GameWrappers; 
	}
}

void TGameContainer::Setup()
{
	_getcwd(mpc_cwd,PATHLEN);
	TFileNames* p_FileNames = new TFileNames();
	try {
		TFileUtils::GetFilesInDir(mpc_cwd,&mi_NoDlls,p_FileNames,"BGame_","dll");
		mpp_GameWrappers = new TGamedllWrapper*[mi_NoDlls];
		for(int i=0;i<mi_NoDlls;i++) {
			int i_DllSize;
			int iret = p_FileNames->GetFileNameLength(&i_DllSize,i+1);
			if(iret != RET_OK) {
				mi_NoDlls = i;
				break;
			}
			char *cp_FileName = new char[i_DllSize+1];
			iret = p_FileNames->GetFileName(cp_FileName,i+1);
			if(iret != RET_OK) {
				delete[] cp_FileName; 
				mi_NoDlls = i;
				break;
			}
			mpp_GameWrappers[i] = new TGamedllWrapper(mpc_cwd,cp_FileName);
			delete[] cp_FileName;
			if(mpp_GameWrappers[i]->getDeviceOpened() && mpp_GameWrappers[i]->getDllLoaded()) {
				continue;
			}
			else {
				throw TAppException(TAppException::APPEXCEPTION_UNABLETOLOADDLL,"Unable to Load dll");
			}
		}
	}
	catch(TAppException _AppExp) {
		delete p_FileNames;
		throw _AppExp;
	}
	delete p_FileNames;
}

int TGameContainer::GetNumberOfGames()
{
	int i_NoGames = 0;
	for(int i=0; i<mi_NoDlls; ++i) {
	  i_NoGames += mpp_GameWrappers[i]->fnptrGetNumberOfGames();	
	}
    return i_NoGames;
}

int TGameContainer::GetNumberOfQuestions(int i_GameIndex)
{
	int iret = -1;
	if(i_GameIndex<GetNumberOfGames() && i_GameIndex>-1) {
		iret = mpp_GameWrappers[mapGameIndexToDllIndex(i_GameIndex)]->fnGetNumberOfQuestions(mapGameIndexToDllGameIndex(i_GameIndex));
	}
	return iret;	
}

int TGameContainer::GetGameName(string &GameName, int i_GameIndex)
{
	int iret = RET_RANGEERR;
	if(i_GameIndex<GetNumberOfGames() && i_GameIndex>-1) {
		char *cp_GameName = new char[STRSIZE];
		cp_GameName[STRSIZE-1] = '\0';
		if(mpp_GameWrappers[mapGameIndexToDllIndex(i_GameIndex)]->
		fnptrGetGameName(mapGameIndexToDllGameIndex(i_GameIndex),cp_GameName) != RET_OK) {
			iret = RET_DLLFUNCTIONRETURNERROR;
		}
		else {
			GameName = cp_GameName; 
			iret = RET_OK;	
		}
		delete[] cp_GameName; 
	}
	return iret;	
}

int TGameContainer::GetGameType(int* _pi_GameType, int i_GameIndex)
{
	int iret = RET_RANGEERR;
	if(i_GameIndex<GetNumberOfGames() && i_GameIndex>-1) {
		if(mpp_GameWrappers[mapGameIndexToDllIndex(i_GameIndex)]
		->fnptrGetGameType(mapGameIndexToDllGameIndex(i_GameIndex),_pi_GameType) != RET_OK) {
			iret = RET_DLLFUNCTIONRETURNERROR;
		}
		else {
			iret = RET_OK;
		}
	}
	return iret;
}

int TGameContainer::GetQA(char* _pc_QA, int i_GameIndex)
{
	int iret = RET_RANGEERR;
	if(i_GameIndex<GetNumberOfGames() && i_GameIndex>-1) {
		if(mpp_GameWrappers[mapGameIndexToDllIndex(i_GameIndex)]
		->fnptrGetQA(mapGameIndexToDllGameIndex(i_GameIndex),_pc_QA) != RET_OK) {
			iret = RET_DLLFUNCTIONRETURNERROR;
		}
		else {
			iret = RET_OK;
		}
	}
	return iret;
}

int TGameContainer::SetDiff(int _i_Diff, int i_GameIndex)
{
	int iret = RET_RANGEERR;
	if(i_GameIndex<GetNumberOfGames() && i_GameIndex>-1) {
		if(mpp_GameWrappers[mapGameIndexToDllIndex(i_GameIndex)]
		->fnptrSetDiff(mapGameIndexToDllGameIndex(i_GameIndex),_i_Diff) != RET_OK) {
			iret = RET_DLLFUNCTIONRETURNERROR;
		}
		else {
			iret = RET_OK;
		}
	}
	return iret;
}

int TGameContainer::GetTimeLimit(int* _pi_TimeLimit, int i_GameIndex)
{
	int iret = RET_RANGEERR;
	if(i_GameIndex<GetNumberOfGames() && i_GameIndex>-1) {
		if(mpp_GameWrappers[mapGameIndexToDllIndex(i_GameIndex)]
		->fnptrGetTimeLimit(mapGameIndexToDllGameIndex(i_GameIndex),_pi_TimeLimit) != RET_OK) {
			iret = RET_DLLFUNCTIONRETURNERROR;
		}
		else {
			iret = RET_OK;
		}
	}
	return iret;
}

int TGameContainer::Reset(int i_GameIndex)
{
	int iret = RET_RANGEERR;
	if(i_GameIndex<GetNumberOfGames() && i_GameIndex>-1) {
		if(mpp_GameWrappers[mapGameIndexToDllIndex(i_GameIndex)]->
		fnptrReset(mapGameIndexToDllGameIndex(i_GameIndex))!=RET_OK) {
			iret = RET_DLLFUNCTIONRETURNERROR;
		}
		else {
			iret = RET_OK;	
		}
	}
	return iret;
}

void TGameContainer::mapGameIndexToDllIndex(int i_GameIndex, unsigned int& ui_DllIndex, unsigned int& ui_DllGameIndex)
{
	ui_DllIndex = 0;
	ui_DllGameIndex = 0;

	int i_NoGames = 0; 
	for(int i=0; i<mi_NoDlls; ++i) {
	  int i_NoGamesLast = i_NoGames;
	  i_NoGames += mpp_GameWrappers[i]->fnptrGetNumberOfGames();
	  if(i_GameIndex < i_NoGames) {
		ui_DllIndex = (unsigned int)i;
        ui_DllGameIndex = i_GameIndex - i_NoGamesLast;
		break;
	  }
	}
}

unsigned int TGameContainer::mapGameIndexToDllIndex(int i_GameIndex)
{
	unsigned int ui_DllIndex = 0;
	unsigned int ui_DllGameIndex = 0;
    mapGameIndexToDllIndex(i_GameIndex, ui_DllIndex, ui_DllGameIndex);
	return ui_DllIndex;
}

unsigned int TGameContainer::mapGameIndexToDllGameIndex(int i_GameIndex)
{
	unsigned int ui_DllIndex = 0;
	unsigned int ui_DllGameIndex = 0;
    mapGameIndexToDllIndex(i_GameIndex, ui_DllIndex, ui_DllGameIndex);
	return ui_DllGameIndex;
}