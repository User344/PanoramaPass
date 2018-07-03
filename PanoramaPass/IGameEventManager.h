#pragma once

class IGameEvent {
public:
	const char* GetName() {
		return call_vfunc<const char*(__thiscall *)(void*)>(this, 1)(this);
	}

	bool GetBool(const char* szKeyName, bool bDefault = false) {
		return call_vfunc<bool(__thiscall *)(void*, const char*, bool)>(this, 5)(this, szKeyName, bDefault);
	}

	int GetInt(const char* szKeyName, int nDefault = 0) {
		return call_vfunc<int(__thiscall *)(void*, const char*, int)>(this, 6)(this, szKeyName, nDefault);
	}

	float GetFloat(const char* szKeyName, float flDefault = 0) {
		return call_vfunc<float(__thiscall *)(void*, const char*, float)>(this, 8)(this, szKeyName, flDefault);
	}

	const char* GetString(const char* szKeyName) {
		return call_vfunc<const char*(__thiscall *)(void*, const char*, int)>(this, 9)(this, szKeyName, 0);
	}

	void SetString(const char* szKeyName, const char* szValue) {
		return call_vfunc<void(__thiscall *)(void*, const char*, const char*)>(this, 16)(this, szKeyName, szValue);
	}
};

class IGameEventManager2
{
public:

};
IGameEventManager2* g_events;