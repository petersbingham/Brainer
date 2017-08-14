//---------------------------------------------------------------------------
#include "stdafx.h"
#include "MiscUtils.h"
#include <sstream>
#include <string.h>
#include <cctype>
using namespace std;

bool TMiscUtils::IntFromString(const char* _pc_string, int& _i_int)
{
  bool b_ret = true;
  for(unsigned int i=0; i<strlen(_pc_string) && b_ret; ++i) {
    if(!isdigit(_pc_string[i])) {
      b_ret = false;  
    }
  }
  if(b_ret) {
    stringstream ss;
    ss << _pc_string;
    ss >> _i_int;
  }
  return b_ret;
}

void TMiscUtils::charTowchar(const char* _pc_in, wchar_t* _pwc_out)
{
    size_t origsize = strlen(_pc_in) + 1;
    _pwc_out = new wchar_t[origsize];
#ifdef _MSC_VER
    size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, _pwc_out, origsize, _pc_in, _TRUNCATE);
#else
		mbstowcs(_pwc_out, _pc_in, origsize);
#endif
}

void TMiscUtils::strToLowerCase(char* _pc_in)
{
	while (*_pc_in != '\0') {
		*_pc_in = char(tolower(int(*_pc_in)));
		_pc_in++;
	}
}

int TMiscUtils::caseIndepstrcmp(const char* str1, const char* str2)
{
	char* cp_str1cpy = new char[strlen(str1)+1];
	strcpy(cp_str1cpy, str1);
	TMiscUtils::strToLowerCase(cp_str1cpy);
	char* cp_str2cpy = new char[strlen(str2)+1];
	strcpy(cp_str2cpy, str2);
	TMiscUtils::strToLowerCase(cp_str2cpy);
	int ret = strcmp(cp_str1cpy, cp_str2cpy);
	delete[] cp_str1cpy;
	delete[] cp_str2cpy;
	return ret;
}