#include "pch.h"
#include "Framework.h"


int main()
{
	FRAMEWORK.Init(1280,720,"Cuphead");
	FRAMEWORK.Do();
	FRAMEWORK.Release();

	return 0;
}