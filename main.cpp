#include "pch.h"
#include "Framework.h"


int main()
{
	Framework::Init();
	Framework::MainLoop();
	Framework::Release();

	return 0;
}