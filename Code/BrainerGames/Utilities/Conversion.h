//---------------------------------------------------------------------------

#ifndef ConversionH
#define ConversionH

#include <string.h>
#include "CommonHeader.h"

class TConversionParameters
{
  public:
    unsigned int mui_Type;
    int mi_Precision;
    bool mb_Invert;
    bool mb_Rounding;
    char* mpc_Base;
    double md_Conversion;
    int mi_Maximum;
    int mi_Minimum;

    TConversionParameters();

    TConversionParameters ( unsigned int _ui_Type,
                            int _i_Precision,
                            bool _b_Invert,
                            bool _b_Rounding,
                            char* _pc_Base,
                            double _d_Conversion,
                            int _i_Maximum,
                            int _i_Minimum);

    ~TConversionParameters();

    TConversionParameters (const TConversionParameters & copy);
    TConversionParameters & operator=(const TConversionParameters & copy);

  private:
    void commonCopy(const TConversionParameters & copy);
};

class TConversionDiffParameters
{
  private:
    TConversionParameters* mp_ConversionParameters;

  public:
    TConversionDiffParameters();
    TConversionDiffParameters(const TConversionParameters& _p_EasyConversion,
                              const TConversionParameters& _p_MediumConversion,
                              const TConversionParameters& _p_HardConversion);
    ~TConversionDiffParameters();
    TConversionDiffParameters (const TConversionDiffParameters & copy);
    TConversionDiffParameters & operator=(const TConversionDiffParameters & copy);

    TConversionParameters GetConversionParameters(unsigned int _ui_diff);
};

class TConversion
{
	private:
		char* mpc_QA;
		unsigned int mui_Type;
		unsigned int mui_Precision;

		bool mb_Rounding;
		bool mb_Invert;

	public:
		enum {
			TYPE_NEARESTINT,
			TYPE_NEARESTHALF,
			TYPE_PRECISION
		};

		TConversion(char* _pc_QA);
		void SetType(unsigned int _ui_Type, unsigned int _ui_Precision = 1);
		void SetInverseConversion(bool _b_Invert);
		void SetFromRounding(bool _b_Rounding);

		void GetQuestionString(	const char* _pc_Base,
														double _d_Conversion,
														int _i_Maximum, int _i_Minimum);
};

void ConversionHelper(TConversion* _p_Conversion, const TConversionParameters& _ConversionParameters);

//---------------------------------------------------------------------------
#endif
