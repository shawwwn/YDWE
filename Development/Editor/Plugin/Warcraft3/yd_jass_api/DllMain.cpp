#include <windows.h>


namespace base { namespace warcraft3 { namespace japi {
void InitializeUnitState();
void InitializeAbilityState();
void InitializeEventDamageData();
void InitializeDisplayChat();
void InitializeUtilFuncs();
}}}

void Initialize()
{
	base::warcraft3::japi::InitializeUnitState();
	base::warcraft3::japi::InitializeAbilityState();
	base::warcraft3::japi::InitializeEventDamageData();
	base::warcraft3::japi::InitializeDisplayChat();
	base::warcraft3::japi::InitializeUtilFuncs();
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID /*pReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);
		Initialize();
	}

	return TRUE;
}

const char *PluginName()
{
	return "yd_jass_api";
}

// 6F2978FC
