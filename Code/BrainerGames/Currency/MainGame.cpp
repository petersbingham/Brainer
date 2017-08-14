//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "DllRetCodes.h"  
#include "Numeric.h"

TMainGame::TMainGame()
{
  strcpy(mpc_GameName,"Currency");
  mi_Diff = EASY;
  mi_GameType = TEXTNUM;
  mi_TimeOut = 27;
#ifdef TEST
  mi_TimeOut = 999;
#endif

  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many euros in %.0f pounds (nearest euro). 1 euro = £%.2f",
                              0.8,
                              99,3
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many euros in %.0f pounds (nearest euro). 1 euro = £%.2f",
                              0.8,
                              299,99
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many euros in %.0f pounds (nearest euro). 1 euro = £%.2f",
                              0.85,
                              999,99
                           )
    ));
  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              false,
                              "How many pounds in %.0f euros (nearest pound). 1 euro = £%.2f",
                              0.8,
                              99,3
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              false,
                              "How many pounds in %.0f euros (nearest pound). 1 euro = £%.2f",
                              0.8,
                              299,99
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              false,
                              "How many pounds in %.0f euros (nearest pound). 1 euro = £%.2f",
                              0.85,
                              999,99
                           )
    ));


  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              false,
                              "How many dollars in %.0f pounds (nearest dollar). £1 = $%.2f",
                              1.6,
                              99,3
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              false,
                              "How many dollars in %.0f pounds (nearest dollar). £1 = $%.2f",
                              1.6,
                              299,99
                            ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              false,
                              "How many dollars in %.0f pounds (nearest dollar). £1 = $%.2f",
                              1.56,
                              999,99
                            )
    ));
  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many pounds in %.0f dollars (nearest pound). £1 = $%.2f",
                              1.6,
                              99,3
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many pounds in %.0f dollars (nearest pound). £1 = $%.2f",
                              1.6,
                              299,99
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many pounds in %.0f dollars (nearest pound). £1 = $%.2f",
                              1.56,
                              999,99
                           )
    ));

  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many zloty in %.0f pounds (nearest zloty). 1 zl = £%.2f",
                              0.2,
                              99,3
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many zloty in %.0f pounds (nearest zloty). 1 zl = £%.2f",
                              0.2,
                              299,99
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many zloty in %.0f pounds (nearest zloty). 1 zl = £%.2f",
                              0.19,
                              999,99
                           )
    ));
  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many pounds in %.0f zloty (nearest pound). £1 = %.2fzl",
                              5,
                              99,3
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many pounds in %.0f zloty (nearest pound). £1 = %.2fzl",
                              5,
                              299,99
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many pounds in %.0f zloty (nearest pound). £1 = %.2fzl",
                              5.3,
                              999,99
                           )
    ));
  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              false,
                              "How many forint in %.0f pounds. £1 = %.2fFt",
                              350,
                              25,3
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              false,
                              "How many forint in %.0f pounds. £1 = %.2fFt",
                              350,
                              999,99
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              false,
                              "How many forint in %.0f pounds. £1 = %.2fFt",
                              345,
                              999,99
                           )
    ));
  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many pounds in %.0f fillér (nearest pound). £1 = %.2fFt",
                              350,
                              350,8750
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many pounds in %.0f fillér (nearest pound). £1 = %.2fFt",
                              350,
                              8750,34500
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many pounds in %.0f fillér (nearest pound). £1 = %.2fFt",
                              345,
                              8750,34500
                           )
    ));
}

void TMainGame::GetGameName(unsigned int /*_ui_GameIndex*/, char* _pc_GameName)
{
  strcpy(_pc_GameName,mpc_GameName);
}

void TMainGame::GetGameType(unsigned int /*_ui_GameIndex*/, int* _pi_GameType)
{
  *_pi_GameType = mi_GameType;
}

int TMainGame::GetQA(unsigned int /*_ui_GameIndex*/, char* _pc_QA)
{
   mp_Conversion = new TConversion(_pc_QA);
  int i_GameType;
  
#ifndef TEST
  TNumeric::RandomInt(i_NOGAMES, &i_GameType);
#else
  //i_GameType = STERLINGTOEURO;
  //i_GameType = EUROTOSTERLING;
  //i_GameType = STERLINGTODOLLAR;
  //i_GameType = DOLLARTOSTERLING;
  //i_GameType = STERLINGTOZLOTY;
  //i_GameType = ZLOTYTOSTERLING;
  //i_GameType = STERLINGTOFORINT;
  i_GameType = FORINTTOSTERLING;
#endif

  getqueString(i_GameType);
  delete mp_Conversion;
  return TDllRetCodes::DLLRET_OK;
}

void TMainGame::SetDiff(unsigned int /*_ui_GameIndex*/, int _i_Diff)
{
  mi_Diff = _i_Diff;
}

void TMainGame::GetTimeLimit(unsigned int /*_ui_GameIndex*/, int* _pi_Secs)
{
  *_pi_Secs = mi_TimeOut;
}

void TMainGame::Reset(unsigned int /*_ui_GameIndex*/)
{
}

void TMainGame::getqueString(int _i_GameType)
{
  switch(_i_GameType) {
    case STERLINGTOEURO:
          ConversionHelper(mp_Conversion, AllConversionDiffParameters[STERLINGTOEURO].GetConversionParameters(mi_Diff));
          break;    
    case EUROTOSTERLING:
          ConversionHelper(mp_Conversion, AllConversionDiffParameters[EUROTOSTERLING].GetConversionParameters(mi_Diff));
          break;
    case STERLINGTODOLLAR:
          ConversionHelper(mp_Conversion, AllConversionDiffParameters[STERLINGTODOLLAR].GetConversionParameters(mi_Diff));
          break;
    case DOLLARTOSTERLING:
          ConversionHelper(mp_Conversion, AllConversionDiffParameters[DOLLARTOSTERLING].GetConversionParameters(mi_Diff));
          break;
    case STERLINGTOZLOTY:
          ConversionHelper(mp_Conversion, AllConversionDiffParameters[STERLINGTOZLOTY].GetConversionParameters(mi_Diff));
          break;
    case ZLOTYTOSTERLING:
          ConversionHelper(mp_Conversion, AllConversionDiffParameters[ZLOTYTOSTERLING].GetConversionParameters(mi_Diff));
          break;     
    case FORINTTOSTERLING:
          ConversionHelper(mp_Conversion, AllConversionDiffParameters[FORINTTOSTERLING].GetConversionParameters(mi_Diff));
          break;
    case STERLINGTOFORINT:
          ConversionHelper(mp_Conversion, AllConversionDiffParameters[STERLINGTOFORINT].GetConversionParameters(mi_Diff));
          break;
  }
}

//---------------------------------------------------------------------------
#pragma package(smart_init)