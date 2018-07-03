#pragma once

template <typename T>
T call_vfunc( void *vTable, int iIndex ) {
	return (*(T**)vTable)[iIndex];
}

typedef void* (*create_interface_fn)( const char* name, int* return_code );
template <typename T>
T* capture_interface( const char* module_name, const char* interface_name )
{
	static create_interface_fn create_interface = nullptr;
	while ( !create_interface )
		create_interface = (create_interface_fn)GetProcAddress( GetModuleHandleA( module_name ), "CreateInterface" );

	return (T*)create_interface( interface_name, nullptr );
}