#pragma once

class cEsp
{

public:
	void BoundingBox(C_BaseEntity* pLocalPlayer,C_BaseEntity* pBaseEnt);
	void BoxESP(C_BaseEntity* pBaseEnt,Color c,int index);
	void NameESP(C_BaseEntity* pBaseEnt,int index,player_info_t pInfo);
	void HealthESP(C_BaseEntity* pBaseEnt,int index,int health);
	void ArmorESP(C_BaseEntity* pBaseEnt,int index,int Armor);
	void DefusingESP(C_BaseEntity* pBaseEnt,int index);
	void Crosshair(C_BaseEntity* pLocalPlayer,Color color);
	void HealthBarESP(C_BaseEntity* pBaseEnt,int index,int health);
	void ArmorBarESP(C_BaseEntity* pBaseEnt,int index,int Armor);
	void NightMode();
};
extern cEsp ESP;