typedef int (__stdcall *INTPROCUINTCHARPTR)(unsigned int, char*);
typedef int (__stdcall *INTPROCUINTINTPTR)(unsigned int, int*);
typedef int (__stdcall *INTPROCUINT)(unsigned int);
typedef int (__stdcall *INTPROCUINTINT)(unsigned int, int);
typedef unsigned int (__stdcall *UINTPROCVOID)(void);
typedef unsigned int (__stdcall *UINTPROCUINT)(unsigned int);

class TGamedllLoader;

class TGamedllWrapper {
  public:
    TGamedllWrapper(const char* _pc_DllPath, const char* _pc_DllName);
   ~TGamedllWrapper();

   bool getDllLoaded(){return mb_functionsOK;};
   bool getDeviceOpened(){return mb_DeviceOpened;};

   UINTPROCVOID fnptrGetNumberOfGames;
   UINTPROCUINT fnGetNumberOfQuestions;
   INTPROCUINTCHARPTR fnptrGetGameName;
   INTPROCUINTINTPTR fnptrGetGameType;
   INTPROCUINTCHARPTR fnptrGetQA;
   INTPROCUINTINT fnptrSetDiff;
   INTPROCUINTINTPTR fnptrGetTimeLimit;
   INTPROCUINT fnptrReset;

  private:
   bool mb_DeviceOpened;
   bool mb_functionsOK;
   bool loadFunctionPointers();
   TGamedllLoader *mp_GamedllLoader;
};