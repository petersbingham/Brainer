#include "stdafx.h"
#include <windows.h>

class TGamedllLoader
{
public:
  TGamedllLoader(char* _pc_Dll);
  ~TGamedllLoader();

  enum eDynamicLoaderError{eErrorOk=0, eErrorLibraryNotFound, eErrorLibraryLoadError};

  eDynamicLoaderError Open();
  eDynamicLoaderError Close();
  void* GetFunction(char* _pc_FunctionName);

private:
	char* mp_Dll;
 	HMODULE mp_Handle;
};