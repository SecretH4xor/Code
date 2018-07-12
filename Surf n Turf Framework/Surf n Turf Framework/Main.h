#pragma once

#include <Windows.h>
#include <winnt.h>
#include <stdio.h>
#include <WinUser.h>
#include <windef.h>
#include <iostream>
#include <vector>
#include <stdint.h>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <conio.h>
#include <process.h>

#include "Hook.h"
#include "CRC32.h"
#include "SDK.h"
#include "Math.h"
#include "Structs.h"
#include "Utils.h"
#include "Menu.h"
#include "Mouse.h"
#include "xorstring.h"
#include "Cvars.h"
#include "esp.h"
#include "ESPPositions.h"
//#include "Radar.h"
#include "Log.h"
#include "dt_recv.h"
#include "Netvars.h"
#include "AntiAim.h"



static bool bMenu = true;
static bool BuyMenu = true;
static bool done = false;

typedef VMThook::VMTManager Hook_t;
extern Hook_t *g_pClientHook;
extern Hook_t *g_pPanelHook;



void __fastcall Hook_PaintTraverse(void* thisptr,int edx,unsigned int vguiPanel, bool forceRepaint, bool allowForce);
void __fastcall Hook_CreateMove(void* thisptr,int edx,int sequence_number, float input_sample_frametime, bool active);

#define DO_ONCE( arg )				\
	static bool UnIqUe_ONC3 = false;\
	if( UnIqUe_ONC3 == false )\
{									\
	UnIqUe_ONC3 = true;				\
	arg								\
}

#define IN_ATTACK					(1 << 0)
#define IN_JUMP						(1 << 1)
#define IN_DUCK					    (1 << 2)
