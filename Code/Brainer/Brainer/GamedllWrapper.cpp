#include "stdafx.h"
#include <string.h>
#include "GamedllLoader.h"
#include "GamedllWrapper.h"
#include <stdio.h>

TGamedllWrapper::TGamedllWrapper(const char* _pc_DllPath, const char* _pc_DllName)
{
  int ilen = strlen(_pc_DllPath)+strlen(_pc_DllName)+2;
  char* pc_Dll = new char[strlen(_pc_DllPath)+strlen(_pc_DllName)+2];	
  if(pc_Dll) {
	int iRetCode;
	mb_DeviceOpened = false;
	mb_functionsOK = false;

	sprintf_s(pc_Dll,strlen(_pc_DllPath)+strlen(_pc_DllName)+2,"%s\\%s",_pc_DllPath,_pc_DllName);

	mp_GamedllLoader = new TGamedllLoader(pc_Dll);

	iRetCode = mp_GamedllLoader->Open();

	if (iRetCode == TGamedllLoader::eErrorOk) {
	  mb_DeviceOpened = true;
	  mb_functionsOK = loadFunctionPointers();
	}
  }
  delete[] pc_Dll;
}

TGamedllWrapper::~TGamedllWrapper()
{
  if(mp_GamedllLoader) {
	mp_GamedllLoader->Close();
	delete mp_GamedllLoader;
  }
}

bool TGamedllWrapper::loadFunctionPointers()
{
  fnptrGetNumberOfGames = (UINTPROCVOID)mp_GamedllLoader->GetFunction("fnGetNumberOfGames");
  fnGetNumberOfQuestions = (UINTPROCUINT)mp_GamedllLoader->GetFunction("fnGetNumberOfQuestions");
  fnptrGetGameName = (INTPROCUINTCHARPTR)mp_GamedllLoader->GetFunction("fnGetGameName");
  fnptrGetGameType = (INTPROCUINTINTPTR)mp_GamedllLoader->GetFunction("fnGetGameType"); 
  fnptrGetQA = (INTPROCUINTCHARPTR)mp_GamedllLoader->GetFunction("fnGetQA"); 
  fnptrSetDiff = (INTPROCUINTINT)mp_GamedllLoader->GetFunction("fnSetDiff");
  fnptrGetTimeLimit = (INTPROCUINTINTPTR)mp_GamedllLoader->GetFunction("fnGetTimeLimit"); 
  fnptrReset = (INTPROCUINT)mp_GamedllLoader->GetFunction("fnReset");

  if (fnptrGetNumberOfGames && fnGetNumberOfQuestions && fnptrGetGameName && fnptrGetGameType && fnptrGetQA && fnptrSetDiff && fnptrGetTimeLimit && fnptrReset)
		return true;
  else return false;
}