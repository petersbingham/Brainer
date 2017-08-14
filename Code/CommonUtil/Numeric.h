//---------------------------------------------------------------------------

#ifndef NumericH
#define NumericH

#include <stdlib.h>
#include <time.h>
#include <string>

class TNumeric
{
	public:
	template <typename T> static void RandomInt(int _i_Max, T* _p_RandNo);
	template <typename T> static void RandomIntOverIncRange(int _i_Min, int _i_Max, T* _p_RandNo);
	template <typename T> static void RandomIntMultipleFive(int _i_Max, T* _p_RandNo);
	template <typename T> static void OrderArray(T* _p_Start, unsigned int _ui_length);
	template <typename T> static void Swap(T& First, T& Second);
	static void RoundToNearestInt(double _d_double, int* _pi_int);
	static void RoundPrecision(double _d_double, double* _pd_double, unsigned int _ui_Precision);
	template <typename T> static void ArrayShuffle(T *array, size_t n);
	static inline double convertToDouble(std::string const& s);
};

template <typename T> void TNumeric::RandomIntMultipleFive(int _i_Max, T* _p_RandNo)
{
  RandomInt(_i_Max, _p_RandNo);
  *_p_RandNo = (*_p_RandNo/5) * 5;
}

template <typename T> void TNumeric::OrderArray(T* _p_Start, unsigned int _ui_length)
{
	for (int i = 0; i < _ui_length; i++) {
		if (i<_ui_length-1) {
			if (_p_Start[i] > _p_Start[i+1]) {
				Swap(_p_Start[i], _p_Start[i+1]);
				i = -1;
			}
		}
    }
}

template <typename T> void TNumeric::RandomInt(int _i_Max, T* _p_RandNo)
{
  static bool b_seeded = false;
  if(!b_seeded) {
    srand((unsigned int)time(0));
    b_seeded = true;
  }
  int i_rand = rand();
  *_p_RandNo = i_rand % _i_Max;
}

template <typename T> void TNumeric::RandomIntOverIncRange(int _i_Min, int _i_Max, T* _p_RandNo)
{
  if(_i_Min>_i_Max) {
    Swap(_i_Min,_i_Max);
  }
	RandomInt(_i_Max-_i_Min+1, _p_RandNo);
	*_p_RandNo += _i_Min;
}

template <typename T> void TNumeric::Swap(T& First, T& Second)
{
  T Temp = First;
  First = Second;
  Second = Temp;
}

template <typename T> void TNumeric::ArrayShuffle(T *array, size_t n)
{
	if (n > 1)
	{
		size_t i;
		for (i = 0; i < n - 1; i++)
		{
		  size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
		  T t = array[j];
		  array[j] = array[i];
		  array[i] = t;
		}
	}
}

//---------------------------------------------------------------------------
#endif
