#include "Main.h"

Hook_t *g_pClientHook;
Hook_t *g_pPanelHook;

DWORD WINAPI HookThread(LPVOID lpArgs){

	while(!GetModuleHandleA("client.dll"))
		Sleep(100);

	CreateInterfaceFn EngineFactory = CaptureFactory( "engine.dll" );
	CreateInterfaceFn ClientFactory = CaptureFactory( "client.dll" );
	CreateInterfaceFn SurfaceFactory	= CaptureFactory("vguimatsurface.dll");
	CreateInterfaceFn GUIFactory	= CaptureFactory( "vgui2.dll" );
	CreateInterfaceFn PhysicFactory	= CaptureFactory( "vphysics.dll" );
	CreateInterfaceFn MaterialFactory = CaptureFactory( "materialsystem.dll" );

	pClient         = reinterpret_cast<IBaseClientDLL*>(CaptureInterface(ClientFactory, "VClient018"));
	pEngine         = reinterpret_cast<IVEngineClient*>(CaptureInterface(EngineFactory, "VEngineClient014"));
	pPanel			= (IPanel*)GUIFactory("VGUI_Panel009", NULL);
	pClientEntList  = reinterpret_cast<IClientEntityList*>(CaptureInterface(ClientFactory,"VClientEntityList003"));
	pSurface		= reinterpret_cast<ISurface*>(CaptureInterface(SurfaceFactory, "VGUI_Surface031"));
	pEngineTrace    = reinterpret_cast<IEngineTrace*>(CaptureInterface(EngineFactory,"EngineTraceClient004"));
	pMaterialSystem = reinterpret_cast<CMaterialSystem*>(CaptureInterface(MaterialFactory,"VMaterialSystem080"));
	pModelInfo      = reinterpret_cast<IVModelInfo*>(CaptureInterface(EngineFactory,"VModelInfoClient004"));
	pPhysics        = reinterpret_cast<IPhysicsSurfaceProps*>(CaptureInterface(PhysicFactory,"VPhysicsSurfaceProps001"));

	PDWORD Client_int  = NULL;
	memcpy(&Client_int,(void *)(pClient),4);

	pInput = (CInput*)*(PDWORD)(Client_int[21] + 0x62);

	if(pInput)
		pLog.Log("CInput Found");
	else
		pLog.Log("CInput not Found");

	pGlobals = (CGlobalVarsBase*)*(PDWORD)*(PDWORD)(PatternSearch("client.dll", (PBYTE)"\xA1\x00\x00\x00\x00\x8B\x40\x10\x89\x41\x04", "x????xxxxxx", NULL, NULL) + 0x1);

	if(!pGlobals)
		pLog.Log("CGlobalVarsBase not Found");

	g_pPanelHook = new Hook_t(pPanel);
	if(g_pPanelHook){
		g_pPanelHook->HookMethod(&Hook_PaintTraverse,41);
	}

	g_pClientHook = new Hook_t(pClient);
	if(g_pClientHook){
		g_pClientHook->HookMethod(&Hook_CreateMove,21);
	}

	NetVars::Init();

	while(true){

		if (GetAsyncKeyState(VK_DELETE)){
			g_pPanelHook->Unhook();
			g_pClientHook->Unhook();
		}
	}
	return 0x0;
}

BOOL WINAPI hkGetCursorPos(LPPOINT lpPoint)
{
	if (!bMenu)
	{
		lpPoint->x = aMouse.myPos.x;
		lpPoint->y = aMouse.myPos.y;
	}
 
	return GetCursorPos(lpPoint);
}

DWORD WINAPI Unload(HMODULE hModule) {
    FreeLibraryAndExitThread(hModule, 0);
	FreeConsole();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved){
	if(dwReason == DLL_PROCESS_ATTACH){

		//base::Debug::AttachDebugConsole();
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)HookThread,0,0,0);

		return TRUE;
	}
	return FALSE;
}
