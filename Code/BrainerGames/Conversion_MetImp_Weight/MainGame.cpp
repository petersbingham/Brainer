//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "Numeric.h"         
#include "DllRetCodes.h"
#include <vcl.h>

using namespace std;

TMainGame::TMainGame()
{
	strcpy(mpc_GameName,"Conversion_MetImp_Weight");
	mi_Diff = EASY;
	mi_GameType = TEXTNUM;
	mi_TimeOut = 18;
#ifdef TEST
	mi_TimeOut = 999;
#endif

  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              true,
                              "How many grams in %.0f ounces (nearest gram). 1 ounce = %.0fg",
                              30,
                              400,1
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              true,
                              "How many grams in %.0f ounces (nearest gram). 1 ounce = %.0fg",
                              28,
                              400,1
                           ),

      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1, 
                              false,
                              false,
                              "How many grams in %.0f ounces (nearest gram). 1 ounce = %.1fg",
                              28.3,
                              400,1
                           )
    ));
  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              true,
                              "How many ounces in %.0f grams (nearest ounce). 1 ounce = %.0fg",
                              30,
                              2000,30
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              true,
                              "How many ounces in %.0f grams (nearest ounce). 1 ounce = %.0fg",
                              28,
                              2000,30
                           ),

      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many ounces in %.0f grams (nearest ounce). 1 ounce = %.1fg",
                              28.3,
                              2000,30
                           )
    ));
  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              true,
                              "How many kilograms in %.0f stones (nearest kg). 1 stone = %.1fkilograms",
                              6.5,
                              100,2
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              false,
                              "How many kilograms in %.0f stones (nearest kg). 1 stone = %.2fkilograms",
                              6.35,
                              100,2
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTHALF, -1,
                              false,
                              false,
                              "How many kilograms in %.0f stones (nearest half kg). 1 stone = %.2fkilograms",
                              6.35,
                              100,2
                           )
    ));
  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              true,
                              "How many stones in %.0f kilograms (nearest stone). 1 stone = %.1fkilograms",
                              6.5,
                              100,2
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many stones in %.0f kilograms (nearest stone). 1 stone = %.2fkilograms",
                              6.35,
                              100,2
                           ),
      TConversionParameters(  TConversion::TYPE_PRECISION, 1,
                              true,
                              false,
                              "How many stones in %.0f kilograms (1 dp). 1 stone = %.2fkilograms",
                              6.35,
                              100,2
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
	//i_GameType = GRAMSINOUNCES;
	//i_GameType = OUNCESINGRAMS;
	//i_GameType = KILOGRAMSINSTONES;
	i_GameType = STONESINKILOGRAMS;
#endif

	float f_From, f_To;
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
		case GRAMSINOUNCES:
					ConversionHelper(mp_Conversion, AllConversionDiffParameters[GRAMSINOUNCES].GetConversionParameters(mi_Diff));
					break;
		case OUNCESINGRAMS:
					ConversionHelper(mp_Conversion, AllConversionDiffParameters[OUNCESINGRAMS].GetConversionParameters(mi_Diff));
					break;
		case KILOGRAMSINSTONES:
					ConversionHelper(mp_Conversion, AllConversionDiffParameters[KILOGRAMSINSTONES].GetConversionParameters(mi_Diff));
					break;
		case STONESINKILOGRAMS:
					ConversionHelper(mp_Conversion, AllConversionDiffParameters[STONESINKILOGRAMS].GetConversionParameters(mi_Diff));
					break;
	}
}
