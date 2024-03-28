#include "pch.h"
#include "Framework.h"


int main()
{
	srand(time(NULL));
	FRAMEWORK.Init(1920,1080,"Cuphead");
	FRAMEWORK.Do();
	FRAMEWORK.Release();

	return 0;
}