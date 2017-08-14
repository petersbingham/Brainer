//---------------------------------------------------------------------------

#ifndef SmartCritH
#define SmartCritH

class TSmartCrit
{
  private:
    CRITICAL_SECTION* mp_CritSection;    

	public:
    TSmartCrit(CRITICAL_SECTION* _p_CritSection) 
    : mp_CritSection(_p_CritSection) {
      EnterCriticalSection(mp_CritSection);  
    };
    ~TSmartCrit() {
      LeaveCriticalSection(mp_CritSection);  
    }
};

//---------------------------------------------------------------------------
#endif
