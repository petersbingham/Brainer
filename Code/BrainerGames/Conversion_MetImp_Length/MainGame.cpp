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
	strcpy(mpc_GameName,"Conversion_MetImp_Length");
	mi_Diff = EASY;
	mi_GameType = TEXTNUM;
	mi_TimeOut = 22;
#ifdef TEST
	mi_TimeOut = 999;
#endif

  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              true,
                              "How many millimeters in %.0f inches (nearest millimeter). 1 inch = %.0fmm",
                              25,
                              400,3
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1, 
                              false,
                              true,
                              "How many millimeters in %.0f inches (nearest millimeter). 1 inch = %.1fmm",
                              25.4,
                              400,11
                           ),

      TConversionParameters(  TConversion::TYPE_PRECISION, 1, 
                              false,
                              false,
                              "How many millimeters in %.0f inches (1 dp). 1 inch = %.1fmm",
                              25.4,
                              400,1
                           )
    ));
  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              true,
                              "How many inches in %.0f millimeters (nearest inch). 1 inch = %.0fmm",
                              25,
                              2000,30
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              true,
                              "How many inches in %.0f millimeters (nearest inch). 1 inch = %.1fmm",
                              25.4,
                              2000,30
                           ),

      TConversionParameters(  TConversion::TYPE_PRECISION, 1,
                              true,
                              false,
                              "How many inches in %.0f millimeters (1 dp). 1 inch = %.1fmm",
                              25.4,
                              2000,30
                           )
    ));
  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              true,
                              "How many kilometers in %.0f miles (nearest km). 1 kilometer = %.1fmiles",
                              0.6,
                              500,2
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              true,
                              "How many kilometers in %.0f miles (nearest km). 1 kilometer = %.2fmiles",
                              0.62,
                              500,2
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              true,
                              false,
                              "How many kilometers in %.0f miles (nearest km). 1 kilometer = %.3fmiles",
                              0.621,
                              500,2
                           )
    ));
  AllConversionDiffParameters.push_back( TConversionDiffParameters(
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,  
                              false,
                              true,
                              "How many miles in %.0f kilometers (nearest mile). 1 kilometer = %.1fmiles",
                              0.6,
                              500,2
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              true,
                              "How many miles in %.0f kilometers (nearest mile). 1 kilometer = %.2fmiles",
                              0.62,
                              500,2
                           ),
      TConversionParameters(  TConversion::TYPE_NEARESTINT, -1,
                              false,
                              false,
                              "How many miles in %.0f kilometers (nearest mile). 1 kilometer = %.3fmiles",
                              0.621,
                              500,2
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
	//i_GameType = MILLIMETERSININCHES;
	i_GameType = INCHESINMILLIMETERS; 
	//i_GameType = KILOMETERSINMILES;
	//i_GameType = MILESINKILOMETERS;
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
		case MILLIMETERSININCHES:
					ConversionHelper(mp_Conversion, AllConversionDiffParameters[MILLIMETERSININCHES].GetConversionParameters(mi_Diff));
					break;
		case INCHESINMILLIMETERS:
					ConversionHelper(mp_Conversion, AllConversionDiffParameters[INCHESINMILLIMETERS].GetConversionParameters(mi_Diff));
					break;
		case KILOMETERSINMILES:
					ConversionHelper(mp_Conversion, AllConversionDiffParameters[KILOMETERSINMILES].GetConversionParameters(mi_Diff));
					break;
		case MILESINKILOMETERS:
					ConversionHelper(mp_Conversion, AllConversionDiffParameters[MILESINKILOMETERS].GetConversionParameters(mi_Diff));
					break;
	}
}
