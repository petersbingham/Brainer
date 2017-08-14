#include "stdafx.h"
#include "GamedllLoader.h"

TGamedllLoader::TGamedllLoader(char* _pc_Dll)
{
  mp_Handle = NULL;
  mp_Dll = new char[strlen(_pc_Dll)+1];
  strcpy_s(mp_Dll,strlen(_pc_Dll)+1,_pc_Dll);
}

TGamedllLoader::~TGamedllLoader()
{
	if(mp_Dll) {
		delete[] mp_Dll;
	}
}

TGamedllLoader::eDynamicLoaderError TGamedllLoader::Open()
{
  if(mp_Handle!=NULL)
    return eErrorOk;

  mp_Handle = LoadLibraryA(mp_Dll);

  int err = GetLastError();

  if (mp_Handle==NULL){
    return eErrorLibraryLoadError;
  }

  return eErrorOk;
}

TGamedllLoader::eDynamicLoaderError TGamedllLoader::Close()
{
  if (mp_Handle!=NULL)
    FreeLibrary(mp_Handle);

  return eErrorOk;
}

void* TGamedllLoader::GetFunction(char* _pc_FunctionName)
{
  void* retptr = NULL;
  retptr = GetProcAddress(mp_Handle, _pc_FunctionName);

  int err = GetLastError();

  return retptr;
}