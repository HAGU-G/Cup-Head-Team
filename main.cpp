#include "pch.h"
#include "Framework.h"


int main()
{
	srand(time(NULL));
	FRAMEWORK.Init(1600,900,"Cuphead");
	FRAMEWORK.Do();
	FRAMEWORK.Release();

	return 0;
}