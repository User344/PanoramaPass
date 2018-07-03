#pragma once

typedef bool(__thiscall *fireeventclientside_fn)( void*, IGameEvent* pEvent );
fireeventclientside_fn original_fireeventclientside;

vfunc_hook hk_netchannel;
bool __fastcall hooked_fireeventclientside( void* ecx, void* edx, IGameEvent* pEvent )
{
	if ( !pEvent )
		return original_fireeventclientside(ecx, pEvent);

	const auto name = pEvent->GetName();
	if ( !strcmp( name, "server_spawn" ) )
	{
		const auto netchannel = g_engine->get_net_channel();
		if (netchannel)
		{
			const auto index = 40;
			hk_netchannel.setup( netchannel );
			hk_netchannel.hook_index( index, hooked_sendnetmsg );
			original_sendnetmsg = hk_netchannel.get_original<sendnetmsg_fn>(index);

			printf("[V] INetChannel hooked successfully!\n");
		}
		else
		{
			printf("[X] INetChannel is nullptr!\n");
		}
	}

	if ( !strcmp( name, "cs_game_disconnected" ) )
	{
		if ( hk_netchannel.is_hooked() )
		{
			hk_netchannel.unhook_all();
			printf("[V] INetChannel was unhooked!\n");
		}
	}

	return original_fireeventclientside(ecx, pEvent);
}