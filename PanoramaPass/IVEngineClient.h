#pragma once

class INetChannel;
class IVEngineClient
{
public:
	INetChannel* get_net_channel()
	{
		typedef INetChannel*(__thiscall* original_fn)(void*);
		return call_vfunc<original_fn>(this, 78)(this);
	}
};
IVEngineClient* g_engine = nullptr;