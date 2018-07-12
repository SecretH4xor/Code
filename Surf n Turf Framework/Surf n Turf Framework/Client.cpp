#include "Main.h"
#include <string.h>

void Fonts(){
	WaterMarkfont = pSurface->FontCreate();
	pSurface->SetFontGlyphSet(WaterMarkfont,/*Microsoft Sans Serif*/XorStr<0x64,21,0x49F7A41B>("\x29\x0C\x05\x15\x07\x1A\x05\x0D\x18\x4D\x3D\x0E\x1E\x02\x52\x20\x11\x07\x1F\x11"+0x49F7A41B).s,15,200,0,0,FONTFLAG_OUTLINE);

	MenuTitleFont = pSurface->FontCreate();
	pSurface->SetFontGlyphSet(MenuTitleFont,/*Microsoft Sans Serif*/XorStr<0x64,21,0x49F7A41B>("\x29\x0C\x05\x15\x07\x1A\x05\x0D\x18\x4D\x3D\x0E\x1E\x02\x52\x20\x11\x07\x1F\x11"+0x49F7A41B).s,15,200,0,0,FONTFLAG_OUTLINE);

	MenuCheckboxFont = pSurface->FontCreate();
	pSurface->SetFontGlyphSet(MenuCheckboxFont,/*Microsoft Sans Serif*/XorStr<0x64,21,0x49F7A41B>("\x29\x0C\x05\x15\x07\x1A\x05\x0D\x18\x4D\x3D\x0E\x1E\x02\x52\x20\x11\x07\x1F\x11"+0x49F7A41B).s,15,800,0,0,FONTFLAG_NONE);

	MenuButtonFont = pSurface->FontCreate();
	pSurface->SetFontGlyphSet(MenuButtonFont,/*Microsoft Sans Serif*/XorStr<0x64,21,0x49F7A41B>("\x29\x0C\x05\x15\x07\x1A\x05\x0D\x18\x4D\x3D\x0E\x1E\x02\x52\x20\x11\x07\x1F\x11"+0x49F7A41B).s,15,800,0,0,FONTFLAG_NONE);

	MenuButtonToggledFont = pSurface->FontCreate();
	pSurface->SetFontGlyphSet(MenuButtonToggledFont,/*Microsoft Sans Serif*/XorStr<0x64,21,0x49F7A41B>("\x29\x0C\x05\x15\x07\x1A\x05\x0D\x18\x4D\x3D\x0E\x1E\x02\x52\x20\x11\x07\x1F\x11"+0x49F7A41B).s,17,800,0,0,FONTFLAG_NONE);

	MenuTabFont = pSurface->FontCreate();
	pSurface->SetFontGlyphSet(MenuTabFont,/*Microsoft Sans Serif*/XorStr<0x64,21,0x49F7A41B>("\x29\x0C\x05\x15\x07\x1A\x05\x0D\x18\x4D\x3D\x0E\x1E\x02\x52\x20\x11\x07\x1F\x11"+0x49F7A41B).s,15,200,0,0,FONTFLAG_OUTLINE);

	MenuTabselectedFont = pSurface->FontCreate();
	pSurface->SetFontGlyphSet(MenuTabselectedFont,/*Microsoft Sans Serif*/XorStr<0x64,21,0x49F7A41B>("\x29\x0C\x05\x15\x07\x1A\x05\x0D\x18\x4D\x3D\x0E\x1E\x02\x52\x20\x11\x07\x1F\x11"+0x49F7A41B).s,17,200,0,0,FONTFLAG_OUTLINE);

	PlusMinusArrowfont = pSurface->FontCreate();
	pSurface->SetFontGlyphSet(PlusMinusArrowfont,/*Microsoft Sans Serif*/XorStr<0x64,21,0x49F7A41B>("\x29\x0C\x05\x15\x07\x1A\x05\x0D\x18\x4D\x3D\x0E\x1E\x02\x52\x20\x11\x07\x1F\x11"+0x49F7A41B).s,13,700,0,0,FONTFLAG_NONE);

	PlusMinusfont = pSurface->FontCreate();
	pSurface->SetFontGlyphSet(PlusMinusfont,/*Microsoft Sans Serif*/XorStr<0x64,21,0x49F7A41B>("\x29\x0C\x05\x15\x07\x1A\x05\x0D\x18\x4D\x3D\x0E\x1E\x02\x52\x20\x11\x07\x1F\x11"+0x49F7A41B).s,15,800,0,0,FONTFLAG_NONE);

	EspFont = pSurface->FontCreate();
	pSurface->SetFontGlyphSet(EspFont,/*Consolas*/XorStr<0x52,9,0x15A0F176>("\x11\x3C\x3A\x26\x39\x3B\x39\x2A"+0x15A0F176).s,12,0,0,0,FONTFLAG_OUTLINE);

	RadarEspFont = pSurface->FontCreate();
	pSurface->SetFontGlyphSet(RadarEspFont,/*Consolas*/XorStr<0x52,9,0x15A0F176>("\x11\x3C\x3A\x26\x39\x3B\x39\x2A"+0x15A0F176).s,10,0,0,0,FONTFLAG_OUTLINE);

}

void DrawMenu(){
	if(GetAsyncKeyState(VK_INSERT) &1)
	{
		pEngine->cmd("cl_mouseenable 1");
		bMenu=!bMenu;
	}
	if(!bMenu)
	{
		pMenu.BuildMenu(pCvars.Menu_PosX,pCvars.Menu_PosY,510,350,/*SnT Framework*/XorStr<0xC5,14,0xF060BD66>("\x96\xA8\x93\xE8\x8F\xB8\xAA\xA1\xA8\xB9\xA0\xA2\xBA"+0xF060BD66).s);

		aMouse.UpdatePos();
		aMouse.ClickHandler();
		pEngine->cmd("cl_mouseenable 0");
	}
}

void WaterMark(){
	int iScreenSize[2];
	pEngine->GetScreenSize(iScreenSize[0], iScreenSize[1]);
	int iScreenCenter[2] = {iScreenSize[0] * 0.5, iScreenSize[1] * 0.5 };
	cDraw.DrawString(WaterMarkfont,true,iScreenSize[0] / 2, 15,Color(255,255,255,255),/*ProClub Surf n Turf Framework v1.0 Beta : Counter Strike: Global Offensive*/XorStr<0x8F,75,0x45FD1CD9>("\xDF\xE2\xFE\xD1\xFF\xE1\xF7\xB6\xC4\xED\xEB\xFC\xBB\xF2\xBD\xCA\xEA\xD2\xC7\x82\xE5\xD6\xC4\xCB\xC2\xDF\xC6\xD8\xC0\x8C\xDB\x9F\x81\x80\x91\xF0\xD6\xC0\xD4\x96\x8D\x98\xFA\xD5\xCE\xD2\xC9\xDB\xCD\xE0\x92\xB6\xB1\xAD\xAE\xA3\xFD\xE8\x8E\xA6\xA4\xAE\xAC\xA2\xEF\x9F\xB7\xB4\xB6\xBA\xA6\xBF\xA1\xBD"+0x45FD1CD9).s);
	cDraw.DrawString(WaterMarkfont,true,iScreenSize[0] / 2, 30,Color(255,255,255,255)," Build Info:  " __DATE__ " | At: " __TIME__ );
}

void EspWhen(C_BaseEntity* pLocalplayer){

	if(pCvars.ESP_When == 1)
	{
		if(pLocalplayer->GetLifeState() == LIFE_ALIVE)
			pCvars.ESPActive = 0;	
		else
			pCvars.ESPActive = 1;
	}

	if(pCvars.ESP_When == 2)
	{
		if(!GetAsyncKeyState(VK_SHIFT))
			pCvars.ESPActive = 0;	
		else
			pCvars.ESPActive = 1;
	}

	if(pCvars.ESP_When == 3)
	{
		if(bMenu)
			pCvars.ESPActive = 0;	
		else
			pCvars.ESPActive = 1;
	}
}

void DrawESP(C_BaseEntity* pLocalplayer,C_BaseEntity* pBaseEnt,Color TeamColors,int iIndex,player_info_t pInfo){

	Vector vWorldPos,vScreen;
	vWorldPos = pBaseEnt->GetAbsOrigin();

	if(cDraw.WorldToScreen(vWorldPos,vScreen)){
		if(pCvars.ESPActive){
			if(pCvars.BoxESP)
				if(pCvars.BoxStyle == 0)
					ESP.BoxESP(pBaseEnt,TeamColors,iIndex);
				else if(pCvars.BoxStyle == 1)
					ESP.BoundingBox(pLocalplayer,pBaseEnt);

			if(pCvars.NameESP)
				ESP.NameESP(pBaseEnt,iIndex,pInfo);

			if(pCvars.HealthESP && pCvars.BoxStyle == 0)
				ESP.HealthBarESP(pBaseEnt,iIndex,pBaseEnt->GetHealth());

			if(pCvars.ArmorESP && pCvars.BoxStyle == 0)
				ESP.ArmorBarESP(pBaseEnt,iIndex,pBaseEnt->GetArmor());
		}
	}
}

void __fastcall Hook_PaintTraverse(void* thisptr,int edx,unsigned int vguiPanel, bool forceRepaint, bool allowForce){

	typedef void (__thiscall *original)(void* thisptr,unsigned int vguiPanel, bool forceRepaint, bool allowForce);
	g_pPanelHook->GetMethod<original>(VMThook::HOOKS::HK_PAINTTRAVERSE)(thisptr,vguiPanel,forceRepaint,allowForce);
	C_BaseEntity* pLocalplayer;

	static bool bOnce = false;
	if(!bOnce)
	{
		Fonts();
		bOnce = true;
	}

	WaterMark();

	PCHAR szPanelName = (PCHAR)pPanel->GetName(vguiPanel);
	if (strstr(szPanelName, "FocusOverlayPanel"))
	{	
		pLocalplayer = (C_BaseEntity*)pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());

		for(int iIndex = 1;iIndex <= pClientEntList->GetHighestEntityIndex( ); iIndex++ )
		{
			C_BaseEntity* pBaseEnt = (C_BaseEntity*)pClientEntList->GetClientEntity(iIndex);

			IClientEntity* pEnt = (IClientEntity*)pClientEntList->GetClientEntity(iIndex);

			if(pBaseEnt == NULL)
				continue;

			player_info_t pInfo;

			C_BaseEntity* pLocalplayer = (C_BaseEntity*)pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());

//			Radar.DrawRadar(pCvars.Radar_PosX ,pCvars.Radar_PosY,pCvars.Radar_PosW,pCvars.Radar_PosH,/*Radar*/XorStr<0xC5,6,0xE62B5146>("\x97\xA7\xA3\xA9\xBB"+0xE62B5146).s);

			if(iIndex == pEngine->GetLocalPlayer())
				continue;
			if(!pEngine->GetPlayerInfo(iIndex,&pInfo))
				continue;
			if(!pBaseEnt->GetLifeState() == LIFE_ALIVE)
				continue;
			if(pBaseEnt->IsDormant())
				continue;
			if(pCvars.EnemyOnly && pBaseEnt->TeamNum() == pLocalplayer->TeamNum())
				continue;

			Color TeamColors = Color(255,255,255,255);

			switch( pBaseEnt->TeamNum() )
			{
			case 2:
				TeamColors = Color(200,60,60,255);
				break;
			case 3:
				TeamColors = Color(84,167,255,255);
				break;
			}
			ESP.Crosshair(pLocalplayer,Color(255,0,0,255));

//			Radar.DrawPoint(pBaseEnt->GetAbsOrigin(),pLocalplayer->GetAbsOrigin(),pLocalplayer->GetAbsAngles(),TeamColors,pInfo,pBaseEnt->GetHealth());

			EspWhen(pLocalplayer);

			DrawESP(pLocalplayer,pBaseEnt,TeamColors,iIndex,pInfo);


		}
		DrawMenu();
	}

}

void Bunnyhop(CUserCmd* pCmd,C_BaseEntity* pLocalplayer)
{
	static bool bLastJumped = false;
	static bool bShouldFake = false;

	if( !bLastJumped && bShouldFake ) 
	{
		bShouldFake = false;
		pCmd->buttons |= IN_JUMP;
	}
	else if( pCmd->buttons & IN_JUMP ) 
	{
		if( pLocalplayer->GetFlags() & FL_ONGROUND ) 
		{
			bLastJumped = true;
			bShouldFake = true;
		}
		else 
		{
			pCmd->buttons &= ~IN_JUMP;
			bLastJumped = false;
		}
	}
	else 
	{
		bLastJumped = false;
		bShouldFake = false;
	}
}

void AutoStrafe(C_BaseEntity* pLocalplayer,CUserCmd* pCmd)
{
	if( pLocalplayer->GetFlags() & FL_ONGROUND )
		return;

	if( pCmd->mousedx > 1 || pCmd->mousedx < -1 ) {
		pCmd->sidemove = pCmd->mousedx < 0.f ? -400.f : 400.f;
	}
}
void __fastcall Hook_CreateMove(void* thisptr,int edx,int sequence_number, float input_sample_frametime, bool active){

	typedef void (__thiscall *original)(void*, int,float,bool);
	g_pClientHook->GetMethod<original>(21)(thisptr,sequence_number,input_sample_frametime,active);

	if ( !pEngine->IsInGame() || !pInput )
		return;	

	CVerifiedUserCmd *g_pVerifiedCommands = *(CVerifiedUserCmd**)( (DWORD)pInput + 0xF0 );
	if ( !g_pVerifiedCommands )
		return;

		DWORD _ebp = 0;
	_asm mov _ebp, ebp

	bool bSendPacket = ( bool* )( *( char** )_ebp - 0x1 );

	CVerifiedUserCmd *pVerified = &g_pVerifiedCommands[ sequence_number % MULTIPLAYER_BACKUP ];

	CUserCmd* pCmd = pInput->GetUserCmd(NULL, sequence_number );
	if ( !pCmd || !pVerified )
		return;

	C_BaseEntity* pLocalplayer = (C_BaseEntity*)pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());

	if(pCvars.BunnyHop)
		Bunnyhop(pCmd,pLocalplayer);

	if(pCvars.AutoStrafe)
		AutoStrafe(pLocalplayer,pCmd);

	//AntiAim.RunAntiAim( pLocalplayer, pCmd, bSendPacket );

	//pCmd->viewangles.Normalize();

	pVerified->m_cmd = *pCmd;
	pVerified->m_crc = pCmd->GetChecksum();
}


