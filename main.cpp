#include "pch.h"
#include "Framework.h"


int main()
{
	FRAMEWORK.Init(1920,1080,"Cup Head");
	FRAMEWORK.Do();
	FRAMEWORK.Release();

	return 0;
}