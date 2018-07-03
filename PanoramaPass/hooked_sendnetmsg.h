#pragma once

class INetMessage;
typedef bool(__thiscall *sendnetmsg_fn)( void*, INetMessage* msg, bool reliable, bool voice );
sendnetmsg_fn original_sendnetmsg;

bool __fastcall hooked_sendnetmsg( void* ecx, void*, INetMessage* msg, bool reliable, bool voice )
{
	if ( !msg )
		return original_sendnetmsg( ecx, msg, reliable, voice );

	const auto name = msg->GetName();
	if ( strcmp( name, "CCLCMsg_FileCRCCheck" ) == 0 )
	{
		//printf("[V] send_table_crc was patched!\n");
		return false;
	}
	if ( strcmp( name, "CCLCMsg_ClientInfo" ) == 0 )
	{
		auto clientinfo_msg = (cclcmsg_clientinfo_t*)msg;
		clientinfo_msg->send_table_crc = 0x6DB42B5;
		printf("[V] send_table_crc was patched!\n");
	}

	return original_sendnetmsg( ecx, msg, reliable, voice );
}
