#include "Main.h"

cEsp ESP;

void cEsp::Crosshair(C_BaseEntity* pLocalPlayer,Color color)
{
	if(pEngine->IsInGame() && pEngine->IsConnected()){
		if(!pCvars.RecoilCrosshair)
			return;

		Vector punchAngle = pLocalPlayer->m_aimPunchAngle();
		int iScreenSize[2];
		pEngine->GetScreenSize(iScreenSize[0], iScreenSize[1]);

		int x = iScreenSize[0] / 2;
		int y = iScreenSize[1] / 2;
		int dy = iScreenSize[1] / 90;
		int dx = iScreenSize[0] / 90;
		x -= (dx*(punchAngle.y));
		y += (dy*(punchAngle.x));


		if( pCvars.RecoilCrosshair == 1 )
		{
			cDraw.OutlinedRect(x - 5, y, 10, 1,Color(255,0,0,255));
			cDraw.OutlinedRect(x, y - 5, 1, 10,Color(255,0,0,255));
		}
	}
}

void cEsp::BoundingBox(C_BaseEntity* pLocalPlayer,C_BaseEntity* pBaseEnt){
	static Vector duckOffset = Vector(0.f, 0.f, 53.5f); // VEC_DUCK_HULL_MAX
	static Vector standOffset = Vector(0.f, 0.f, 72.f); // VEC_HULL_MAX

	int teamnumenemy = pBaseEnt->TeamNum();
	Color colour = Color(255, 255, 255, 255);

	if (teamnumenemy == 2)
	{
		colour = Color(200,60,60,255);
	}
	if (teamnumenemy == 3)
	{
		colour = Color(84,167,255,255);
	}

	int iWidth, iHeight;

	player_info_t PlayerInfo;

	iWidth *= 0.5f;
	iHeight *= 0.5f;

		Vector origin;
	if (!cDraw.WorldToScreen(pBaseEnt->GetAbsOrigin(), origin))
	{
		return;
	}

	if (!pLocalPlayer)
	{
		return;
	}

	Vector offset = (pBaseEnt->GetFlags() & FL_DUCKING) ? duckOffset : standOffset;
	Vector max = (pBaseEnt->GetAbsOrigin() + offset);

	Vector top;
	if (!cDraw.WorldToScreen(max, top))
	{
		return;
	}

float len = 0.f;
	int fontIndex = 0;

	if (pLocalPlayer)
	{
		//len = ( max - localPlayer->GetEyePosition() ).Length();
		//fontIndex = GetFontIndexByDistance( len );
	}

	float boxHeight = (origin.y - top.y);
	float boxHalfWidth = (boxHeight * 0.225f);

	{
		boxHalfWidth *= 1.345794392523364f;
	}

	Vector box((top.x - boxHalfWidth), top.y, 0.f);

	cDraw.OutlinedRect((box.x - 1), (box.y - 1), ((boxHalfWidth * 2) + 2), (boxHeight + 2), Color(0, 0, 0, 255));
	cDraw.OutlinedRect((box.x + 1), (box.y + 1), ((boxHalfWidth * 2) - 2), (boxHeight - 2), Color(0, 0, 0, 255));
	cDraw.OutlinedRect(box.x, box.y, (boxHalfWidth * 2), boxHeight, colour);

	if(pCvars.HealthESP){
		float health = pBaseEnt->GetHealth();
		if (health > 0)
		{
			int scale = (health * 2.55f);
			Color patch(0, 0, 0, 255);
			if (health > 100)
			{
				patch.SetColor(255, 255, 255, 255);
			}
			cDraw.OutlinedRect(box.x, box.y + boxHeight, (boxHalfWidth * 2)*(health / 100), 4, Color(0, 0, 0, 255));
			cDraw.OutlinedRect(box.x, box.y + boxHeight + 1, (boxHalfWidth * 2)*(health / 100), 2, Color(0, scale, 0, 255));
		}
	}
}

void cEsp::BoxESP(C_BaseEntity* pBaseEnt,Color c,int index){

	Vector mon, nom;

	Color GetColor = Color(255,255,255,255);

	nom = pBaseEnt->GetAbsOrigin();

	if(pBaseEnt->GetFlags() & FL_DUCKING)
		mon = nom + Vector( 0, 0, 50.f );
	else
		mon = nom + Vector( 0, 0, 75.f );

	Vector bottom,top;

	IClientEntity* pBaseEntClient;
	pBaseEntClient = pClientEntList->GetClientEntity(index);

	pBaseEnt = (C_BaseEntity*)pBaseEntClient->GetBaseEntity();

	if(  cDraw.TransformVector( nom, bottom ) &&  cDraw.TransformVector( mon, top ) ){
		float height = (bottom.y - top.y);
		float width = height / 5.f;

		cDraw.DrawCornerBox(top.x,bottom.y,width * 2,height,1,c);
	}
}

void cEsp::NameESP(C_BaseEntity* pBaseEnt,int index,player_info_t pInfo){

	Vector mon, nom;

	Color GetColor = Color(255,255,255,255);

	nom = pBaseEnt->GetAbsOrigin();

	if(pBaseEnt->GetFlags() & FL_DUCKING)
		mon = nom + Vector( 0, 0, 50.f );
	else
		mon = nom + Vector( 0, 0, 75.f );

	Vector bottom,top;

	IClientEntity* pBaseEntClient;
	pBaseEntClient = pClientEntList->GetClientEntity(index);

	pBaseEnt = (C_BaseEntity*)pBaseEntClient->GetBaseEntity();

	if(  cDraw.TransformVector( nom, bottom ) &&  cDraw.TransformVector( mon, top ) ){
		float height = (bottom.y - top.y);
		float width = height / 5.f;
		cDraw.DrawString(EspFont,true,top.x,top.y-3,Color(255,255,255,255),pInfo.name);
	}
}

void cEsp::HealthESP(C_BaseEntity* pBaseEnt,int index,int health){

	Vector mon, nom;

	Color GetColor = Color(255,255,255,255);

	nom = pBaseEnt->GetAbsOrigin();

	if(pBaseEnt->GetFlags() & FL_DUCKING)
		mon = nom + Vector( 0, 0, 50.f );
	else
		mon = nom + Vector( 0, 0, 75.f );

	Vector bottom,top;



	IClientEntity* pBaseEntClient;
	pBaseEntClient = pClientEntList->GetClientEntity(index);

	pBaseEnt = (C_BaseEntity*)pBaseEntClient->GetBaseEntity();

	if(  cDraw.TransformVector( nom, bottom ) &&  cDraw.TransformVector( mon, top ) ){
		float height = (bottom.y - top.y);
		float width = height / 5.f;
		cDraw.NormalText(EspFont,top.x + width + 2,top.y + 10,Color(255,255,255,255),"H: %i",health);
	}
}

void cEsp::ArmorESP(C_BaseEntity* pBaseEnt,int index,int Armor)
{


	Vector mon, nom;

	Color GetColor = Color(255,255,255,255);

	nom = pBaseEnt->GetAbsOrigin();

	if(pBaseEnt->GetFlags() & FL_DUCKING)
		mon = nom + Vector( 0, 0, 50.f );
	else
		mon = nom + Vector( 0, 0, 75.f );

	Vector bottom,top;



	IClientEntity* pBaseEntClient;
	pBaseEntClient = pClientEntList->GetClientEntity(index);

	pBaseEnt = (C_BaseEntity*)pBaseEntClient->GetBaseEntity();

	if(  cDraw.TransformVector( nom, bottom ) &&  cDraw.TransformVector( mon, top ) ){
		float height = (bottom.y - top.y);
		float width = height / 5.f;

		if(pCvars.HealthOption == 0){
			cDraw.NormalText(EspFont,top.x + width + 2,top.y + 20,Color(255,255,255,255),"A: %i",Armor);
		}
		else if(pCvars.HealthOption == 1)
			cDraw.NormalText(EspFont,top.x + width + 2,top.y + 10,Color(255,255,255,255),"A: %i",Armor);
	}
}

void cEsp::DefusingESP(C_BaseEntity* pBaseEnt,int index)
{


	Vector mon, nom;

	Color GetColor = Color(255,255,255,255);

	nom = pBaseEnt->GetAbsOrigin();

	if(pBaseEnt->GetFlags() & FL_DUCKING)
		mon = nom + Vector( 0, 0, 50.f );
	else
		mon = nom + Vector( 0, 0, 75.f );

	Vector bottom,top;

	IClientEntity* pBaseEntClient;
	pBaseEntClient = pClientEntList->GetClientEntity(index);

	pBaseEnt = (C_BaseEntity*)pBaseEntClient->GetBaseEntity();

	if(  cDraw.TransformVector( nom, bottom ) &&  cDraw.TransformVector( mon, top ) ){
		float height = (bottom.y - top.y);
		float width = height / 5.f;

		cDraw.NormalText(EspFont,top.x + width + 2,top.y + 30,Color(255,255,255,255),/*Defusing*/XorStr<0x29,9,0xF2237A10>("\x6D\x4F\x4D\x59\x5E\x47\x41\x57"+0xF2237A10).s);
	}
}

void cEsp::HealthBarESP(C_BaseEntity* pBaseEnt,int index,int health){

	Vector mon, nom;

	Color GetColor = Color(255,255,255,255);

	nom = pBaseEnt->GetAbsOrigin();

	if(pBaseEnt->GetFlags() & FL_DUCKING)
		mon = nom + Vector( 0, 0, 50.f );
	else
		mon = nom + Vector( 0, 0, 75.f );

	Vector bottom,top;

	IClientEntity* pBaseEntClient;
	pBaseEntClient = pClientEntList->GetClientEntity(index);

	pBaseEnt = (C_BaseEntity*)pBaseEntClient->GetBaseEntity();

	if(  cDraw.TransformVector( nom, bottom ) &&  cDraw.TransformVector( mon, top ) ){
		float height = (bottom.y - top.y);
		float width = height / 5.f;

		int barhealthheight = (health * (height/10) / 10);
		int barhealthwidth = (health * (width*2/10) / 10);
		int g = health * 2.55, r = 255 - g;

		cDraw.FillRGBA(top.x - width - 5,top.y,4,barhealthheight+2,Color(r,g,0,255));
		cDraw.OutlinedRect(top.x - width - 5, top.y,4,height+2,Color(0,0,0,255));
	}
}

void cEsp::ArmorBarESP(C_BaseEntity* pBaseEnt,int index,int Armor){

	Vector mon, nom;

	Color GetColor = Color(255,255,255,255);

	nom = pBaseEnt->GetAbsOrigin();

	if(pBaseEnt->GetFlags() & FL_DUCKING)
		mon = nom + Vector( 0, 0, 50.f );
	else
		mon = nom + Vector( 0, 0, 75.f );

	Vector bottom,top;

	IClientEntity* pBaseEntClient;
	pBaseEntClient = pClientEntList->GetClientEntity(index);

	pBaseEnt = (C_BaseEntity*)pBaseEntClient->GetBaseEntity();

	if(  cDraw.TransformVector( nom, bottom ) &&  cDraw.TransformVector( mon, top ) ){
		float height = (bottom.y - top.y);
		float width = height / 5.f;

		int barArmorheight = (Armor * (height/10) / 10);
		int barArmorwidth = (Armor * (width*2/10) / 10);

		cDraw.FillRGBA(top.x + width + 2,top.y,4,barArmorheight+2,Color(127,127,127,255));
		cDraw.OutlinedRect(top.x + width + 2,top.y,4,height + 2,Color(0,0,0,255));
	}
}

void cEsp::NightMode(){
	{
		if (!done)
		{
			static auto sv_skyname = gCvars->FindVar("sv_skyname");
			static auto r_DrawSpecificStaticProp = gCvars->FindVar("r_DrawSpecificStaticProp");
			r_DrawSpecificStaticProp->SetValue(1);
			sv_skyname->SetValue("sky_csgo_night02");

			for (MaterialHandle_t i = pMaterialSystem->FirstMaterial(); i != pMaterialSystem->InvalidMaterial(); i = pMaterialSystem->NextMaterial(i))
			{
				IMaterial *pMaterial = pMaterialSystem->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{
					pMaterial->ColorModulate(0.10, 0.10, 0.10);
				}
				if (strstr(group, "StaticProp"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}

				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				done = true;
			}

		}
		else
		{
			if (done)
			{
				for (MaterialHandle_t i = pMaterialSystem->FirstMaterial(); i != pMaterialSystem->InvalidMaterial(); i = pMaterialSystem->NextMaterial(i))
				{
					IMaterial *pMaterial = pMaterialSystem->GetMaterial(i);

					if (!pMaterial)
						continue;

					const char* group = pMaterial->GetTextureGroupName();
					const char* name = pMaterial->GetName();

					if (strstr(group, "World textures"))
					{

						pMaterial->ColorModulate(1, 1, 1);
					}
					if (strstr(group, "StaticProp"))
					{

						pMaterial->ColorModulate(1, 1, 1);
					}
					if (strstr(name, "models/props/de_dust/palace_bigdome"))
					{
						pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
					}
					if (strstr(name, "models/props/de_dust/palace_pillars"))
					{

						pMaterial->ColorModulate(1, 1, 1);
					}
					if (strstr(group, "Particle textures"))
					{
						pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
					}
				}
				done = false;
			}
		}
	}
}