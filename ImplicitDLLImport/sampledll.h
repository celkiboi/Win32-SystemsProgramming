#ifdef DLL_EXPORT
#define DLL _declspec(dllexport) 
#else
#define DLL _declspec(dllimport)
#endif

DLL int Add(int leftSide, int rightSide);

DLL int Subtract(int leftSide, int rightSide);