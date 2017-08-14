//---------------------------------------------------------------------------
#include "stdafx.h"
#include "Numeric.h"
#include <math.h>
#include <sstream>

void TNumeric::RoundToNearestInt(double _d_double, int* _pi_int)
{
	*_pi_int = (int)_d_double;
	if(_d_double-(double)(*_pi_int)>=0.5) {
		(*_pi_int)++;
	}
}

void TNumeric::RoundPrecision(double _d_double, double* _pd_double, unsigned int _ui_Precision)
{
	int i_Multiplier;
	RoundToNearestInt(_d_double*pow(10.0,(int)_ui_Precision), &i_Multiplier);
	*_pd_double = (double)i_Multiplier/pow(10.0,(int)_ui_Precision);
}

class BadConversion : public std::runtime_error {
	public:
	BadConversion(std::string const& s)
	 : std::runtime_error(s)
	 { }
};

inline double TNumeric::convertToDouble(std::string const& s)
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
	 throw BadConversion("convertToDouble(\"" + s + "\")");
	return x;
}
