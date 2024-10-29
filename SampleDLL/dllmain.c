#define DLL_EXPORT
#include "sampledll.h"

DLL int Add(int leftSide, int rightSide)
{
	return leftSide + rightSide;
}

DLL int Subtract(int leftSide, int rightSide)
{
	return leftSide - rightSide;
}