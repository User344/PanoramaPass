#include <Windows.h>
#include <cstdio>
#include "misc.h"
#include "vfunc_hook.h"
#include "IVEngineClient.h"
#include "IGameEventManager.h"
#include "INetMessage.h"
#include "hooked_sendnetmsg.h"
#include "hooked_fireeventclientside.h"

void alloc_console()
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	SetConsoleTitleA("PanoramaPass by @User344");

	printf("[V] PanoramaPass started!\n");
}

void free_console()
{
	FreeConsole();
}

void patch_version()
{
	const auto engine_dll = GetModuleHandleA("engine.dll");
	auto& client_version = *(int*)(*(DWORD*)((DWORD)engine_dll + 0x1B2FA9));
	if (client_version != 13639)
	{
		printf("[X] Version mismatch found! Is CS:GO was updated?\n");
		printf("[X] Offset can be wrong, so you should wait for update\n");
		return;
	}
	client_version = 13638;

	printf("[V] Version changed!\n");
}

void capture_interfaces()
{
	g_engine = capture_interface<IVEngineClient>( "engine.dll", "VEngineClient014" );
	g_events = capture_interface<IGameEventManager2>( "engine.dll", "GAMEEVENTSMANAGER002" );

	printf("[V] Interface captured!\n");
}

vfunc_hook hk_events;
void hook_vtables()
{
	const auto index = 9;
	hk_events.setup( g_events );
	hk_events.hook_index(index, hooked_fireeventclientside);
	original_fireeventclientside = hk_events.get_original<fireeventclientside_fn>(index);

	printf("[V] Hooked successfully!\n");
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if ( fdwReason == DLL_PROCESS_ATTACH )
	{
		alloc_console();
		capture_interfaces();
		patch_version();
		hook_vtables();

		return true;
	}
	else if ( fdwReason == DLL_PROCESS_DETACH )
	{
		hk_events.unhook_all();
		hk_netchannel.unhook_all();
		free_console();

		return true;
	}

	return false;
}