#include "stdafx.h"
#include "IniFile.h"
#include "MiscUtils.h"
#include <stdio.h>

bool TIniFile::isOK(const char* _pc_keyName)
{
  bool b_ret = false;
  if(mpc_path && mpc_section && _pc_keyName) {
    b_ret = true;
  }
  return b_ret;
}

bool TIniFile::setString(const char* _pc_keyName, const char* _pc_keyValue)
{
	bool b_ret = false;
	if(isOK(_pc_keyName)) {
		if(WritePrivateProfileStringA(mpc_section, _pc_keyName, _pc_keyValue, mpc_path)) {
      b_ret = true;
		}
	}
	return b_ret;
}

bool TIniFile::getString(const char* _pc_keyName, char* _pc_keyValue, unsigned int _ui_buffSize)
{
	bool b_ret = false;
	if(isOK(_pc_keyName)) {
		if(GetPrivateProfileStringA(mpc_section, _pc_keyName, "", _pc_keyValue, _ui_buffSize, mpc_path)) {
      b_ret = true;
		}
	}
	return strlen(_pc_keyValue);
}

TIniFile::TIniFile(const char* _pc_path, const char* _pc_sectionName) 
{
  if(_pc_path) {
    mpc_path = new char[strlen(_pc_path)+1];
    strcpy_s(mpc_path, strlen(_pc_path)+1, _pc_path);
	  if(!TFileUtils::CheckFileExists(_pc_path)) {
      TFileUtils::CreateNewFile(_pc_path);     
	  }
  }
  else {
    mpc_path = NULL;
  }
  SetSection(_pc_sectionName);
}

TIniFile::~TIniFile()
{
  delete[] mpc_path;
  delete[] mpc_section;
}

void TIniFile::SetSection(const char* _pc_sectionName)
{
  if(_pc_sectionName) {
    mpc_section = new char[strlen(_pc_sectionName)+1];
    strcpy_s(mpc_section, strlen(_pc_sectionName)+1, _pc_sectionName);
  }
  else {
    mpc_section = NULL;
  }
}

bool TIniFile::SetInt(const char* _pc_keyName, int _i_value)
{
	bool b_ret = false;
  char pc_profileString[MAX_PATH];
  sprintf_s(pc_profileString, MAX_PATH, "%d", _i_value);
  if(setString(_pc_keyName, pc_profileString)) {
    b_ret = true;
  }
	return b_ret;
}

int TIniFile::GetInt(const char* _pc_keyName, int _i_default)
{
	int i_ret = false;
  char pc_profileString[MAX_PATH];
  if(getString(_pc_keyName, pc_profileString, MAX_PATH)) {
    if(!TMiscUtils::IntFromString(pc_profileString, i_ret)) {
      i_ret = _i_default;
    }
  }
  else {
    i_ret = _i_default;
  }
	return i_ret;
}