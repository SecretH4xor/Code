#include "Main.h"

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
CreateInterfaceFn CaptureFactory(char *pszFactoryModule);

void *CaptureInterface(CreateInterfaceFn fn, char *pszInterfaceName);

extern ULONG PatternSearch(std::string ModuleName, PBYTE Pattern, std::string Mask,ULONG uCodeBase, ULONG uSizeOfCode);

namespace base
{
	namespace Debug
	{
		extern bool AttachDebugConsole( void );
		extern void LOG(const char* output);		
	}
}