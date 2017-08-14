//---------------------------------------------------------------------------

#pragma hdrstop

#include "Conversion.h"
#include "AnswerStringHelper.h"
#include "Numeric.h"
#include <stdio.h>

#define SMALL_PATH 28
#define EXLARGE_PATH 1024
#define STRSIZE 128

void ConversionHelper(TConversion* _p_Conversion, const TConversionParameters& _ConversionParameters)
{
  if(_p_Conversion) {
    if(_ConversionParameters.mi_Precision<0) {
      _p_Conversion->SetType(_ConversionParameters.mui_Type);
    }
    else {
      _p_Conversion->SetType(_ConversionParameters.mui_Type, _ConversionParameters.mi_Precision);
    }
    _p_Conversion->SetFromRounding(_ConversionParameters.mb_Rounding);
    _p_Conversion->SetInverseConversion(_ConversionParameters.mb_Invert);
    _p_Conversion->GetQuestionString( _ConversionParameters.mpc_Base,
                                      _ConversionParameters.md_Conversion,
                                      _ConversionParameters.mi_Maximum,
                                      _ConversionParameters.mi_Minimum);
  }
}

void TConversionParameters::commonCopy(const TConversionParameters & copy)
{
  this->mui_Type = copy.mui_Type;
  this->mi_Precision = copy.mi_Precision;
  this->mb_Invert = copy.mb_Invert;
  this->mb_Rounding = copy.mb_Rounding;
  this->md_Conversion = copy.md_Conversion;
  this->mi_Maximum = copy.mi_Maximum;
  this->mi_Minimum = copy.mi_Minimum;
}

TConversionParameters::TConversionParameters() :
  mui_Type(0),
  mi_Precision(0),
  mb_Invert(0),
  mb_Rounding(0),
  mpc_Base(0),
  md_Conversion(0),
  mi_Maximum(0),
  mi_Minimum(0)
{};

TConversionParameters::TConversionParameters (unsigned int _ui_Type,
                                              int _i_Precision,
                                              bool _b_Invert,
                                              bool _b_Rounding,
                                              char* _pc_Base,
                                              double _d_Conversion,
                                              int _i_Maximum,
                                              int _i_Minimum) :
mui_Type(_ui_Type),
mi_Precision(_i_Precision),
mb_Invert(_b_Invert),
mb_Rounding(_b_Rounding),
mpc_Base(_pc_Base),
md_Conversion(_d_Conversion),
mi_Maximum(_i_Maximum),
mi_Minimum(_i_Minimum)
{
  mpc_Base = new char[strlen(_pc_Base)+1];
  strcpy(mpc_Base, _pc_Base);
}

TConversionParameters::~TConversionParameters()
{
  if(mpc_Base) {
    delete[] mpc_Base;
  }
}

TConversionParameters::TConversionParameters (const TConversionParameters & copy)
{
  commonCopy(copy);
  if (copy.mpc_Base != 0) {
    this->mpc_Base = new char[strlen (copy.mpc_Base)+1];
    strcpy (this->mpc_Base, copy.mpc_Base);
  }
  else {
    this->mpc_Base = 0;
  }
}

TConversionParameters& TConversionParameters::operator=(const TConversionParameters & copy)
{
  commonCopy(copy);
  if(this != &copy)
  {
    if (this->mpc_Base != 0) {
      delete this->mpc_Base;
      this->mpc_Base = 0;
    }
    if (copy.mpc_Base != 0) {
      this->mpc_Base = new char[strlen(copy.mpc_Base)+1];
      strcpy (this->mpc_Base, copy.mpc_Base);
    }
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////


TConversionDiffParameters::TConversionDiffParameters() :
  mp_ConversionParameters(0)
{
}

TConversionDiffParameters::TConversionDiffParameters(const TConversionParameters& _p_EasyConversion,
                          const TConversionParameters& _p_MediumConversion,
                          const TConversionParameters& _p_HardConversion)
{
  mp_ConversionParameters = new TConversionParameters[uiNoDiffs];
  mp_ConversionParameters[EASY] = _p_EasyConversion;
  mp_ConversionParameters[MEDIUM] = _p_MediumConversion;
  mp_ConversionParameters[HARD] = _p_HardConversion;
}

TConversionDiffParameters::~TConversionDiffParameters()
{
  delete[] mp_ConversionParameters;
}

TConversionDiffParameters::TConversionDiffParameters (const TConversionDiffParameters & copy)
{
  if(copy.mp_ConversionParameters) {
    this->mp_ConversionParameters = new TConversionParameters[uiNoDiffs];
    this->mp_ConversionParameters[EASY] = copy.mp_ConversionParameters[EASY];
    this->mp_ConversionParameters[MEDIUM] = copy.mp_ConversionParameters[MEDIUM];
    this->mp_ConversionParameters[HARD] = copy.mp_ConversionParameters[HARD];
  }
  else {
    this->mp_ConversionParameters = 0;
  }
}

TConversionDiffParameters & TConversionDiffParameters::operator=(const TConversionDiffParameters & copy)
{
  if(this != &copy)
  {
    if(this->mp_ConversionParameters != 0) {
      delete[] mp_ConversionParameters;
      mp_ConversionParameters = 0;
    }
    if (copy.mp_ConversionParameters != 0) {
      this->mp_ConversionParameters = new TConversionParameters[uiNoDiffs];
      this->mp_ConversionParameters[EASY] = copy.mp_ConversionParameters[EASY];
      this->mp_ConversionParameters[MEDIUM] = copy.mp_ConversionParameters[MEDIUM];
      this->mp_ConversionParameters[HARD] = copy.mp_ConversionParameters[HARD];
    }
  }
  return *this;
}

TConversionParameters TConversionDiffParameters::GetConversionParameters(unsigned int _ui_diff)
{
  if(mp_ConversionParameters && _ui_diff<uiNoDiffs) {
    return mp_ConversionParameters[_ui_diff];
  }
  else {
    return TConversionParameters();
  }
}


////////////////////////////////////////////////////////////////////////////////


TConversion::TConversion(char* _pc_QA) :
	mpc_QA(_pc_QA),
	mui_Type(TYPE_NEARESTINT),
	mb_Rounding(false),
	mb_Invert(false)
{
}

void TConversion::SetType(unsigned int _ui_Type, unsigned int _ui_Precision)
{
	if(_ui_Type <= TYPE_PRECISION) {
		mui_Type = _ui_Type;
	}
	else {
		mui_Type = TYPE_NEARESTINT;
	}
	mui_Precision = _ui_Precision;
}

void TConversion::SetInverseConversion(bool _b_Invert)
{
  mb_Invert = _b_Invert;
}

void TConversion::SetFromRounding(bool _b_Rounding)
{
	mb_Rounding = _b_Rounding;
}

void TConversion::GetQuestionString(	const char* _pc_Base,
																			double _d_Conversion,
																			int _i_Maximum, int _i_Minimum)
{
	char pc_QAbase[EXLARGE_PATH];

	double d_From, d_To;
	int i_Temp;
	if(_i_Maximum > _i_Minimum) {
		TNumeric::RandomInt(_i_Maximum-_i_Minimum, &i_Temp);
	}
	else {
		TNumeric::RandomInt(_i_Maximum, &i_Temp);
	}
	i_Temp += _i_Minimum;

	if(mb_Rounding) {
		if(i_Temp>10) {
			if(i_Temp < 1000) {
				d_From = (i_Temp/10)*10;
			}
			else {
				d_From = (i_Temp/100)*100;
			}
		}
    else {
      d_From = i_Temp;
    }
	}
	else {
    d_From = i_Temp;
  }

	if(!mb_Invert) {
		d_To = d_From*_d_Conversion;
	}
	else {
    d_To = d_From*(1.0/_d_Conversion);
  }

	sprintf(pc_QAbase, _pc_Base, d_From, _d_Conversion);
	if(mui_Type == TYPE_PRECISION) {
		TAnswerStringHelper::CreateAnswerStringRoundedDouble(mpc_QA, pc_QAbase, d_To, mui_Precision);
	}
	else if(mui_Type == TYPE_NEARESTHALF) {
		TAnswerStringHelper::CreateAnswerStringDoubleToNearestHalf(mpc_QA, pc_QAbase, d_To);
	}
	else {
		TAnswerStringHelper::CreateAnswerStringDoubleToNearestInt(mpc_QA, pc_QAbase, d_To);
	}
}
