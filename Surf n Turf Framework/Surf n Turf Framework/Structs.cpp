#include "Main.h"

MoveType_t GetMoveType();

IBaseClientDLL*			pClient				= NULL;//
IVEngineClient*			pEngine				= NULL;//
IPanel*					pPanel				= NULL;//
IClientEntityList*		pClientEntList		= NULL;//
ISurface*				pSurface			= NULL;//
CGlobalVarsBase*		pGlobals			= NULL;//
IEngineTrace*			pEngineTrace		= NULL;//
CInput*                 pInput              = NULL;//
IVModelInfo*            pModelInfo          = NULL;//
IClientNetworkable*     pClientNetworkable  = NULL;
IVDebugOverlay*         pDebugOverlay       = NULL;
CBaseCombatWeapon*      pCombatWeapon       = NULL;
IPhysicsSurfaceProps*	pPhysics			= NULL;//
CMaterialSystem*		pMaterialSystem		= NULL;//

ConVar*                 gCvars              = NULL;
unsigned long			WaterMarkfont		= NULL;
unsigned long			MenuTitleFont		= NULL;
unsigned long			MenuCheckboxFont	= NULL;
unsigned long			MenuButtonFont		= NULL;
unsigned long			MenuButtonToggledFont = NULL;
unsigned long			MenuTabFont			= NULL;
unsigned long			MenuTabselectedFont	= NULL;
unsigned long			PlusMinusArrowfont  = NULL;
unsigned long			PlusMinusfont		= NULL;
unsigned long           EspFont             = NULL;
unsigned long           RadarEspFont        = NULL;
