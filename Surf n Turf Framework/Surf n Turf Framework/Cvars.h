#include "Main.h"

class cCvars
{
public:
	cCvars();
		/*Triggerbot*/ float Triggerbot;
		/*ESP Features*/ float BoxESP,BoxOutlineESP,NameESP,HealthESP,ArmorESP,WeaponESP,RecoilCrosshair,NightMode;
		/*ESP Options*/	float  ESPActive,EnemyOnly,VisibleOnly,TeamColors,HealthBarPos,ArmorBarPos,NamePos;
		/*ESP Options*/ int BoxStyle;
		/*esp When*/ int ESP_When,HealthOption,ArmorOption;
		/*Useless ESP*/ float  ChickenESP;
	   /*Misc Features*/ float Radar,RadarOptions,AutoPistol,BunnyHop,AutoStrafe,RCS;
	   /*Vars*/ float Cheats,thirdperson;
	   /*AntiAim*/ int AntiAimMode,AntiAimPitch,AntiAimType,FakeLaggMode;
	   /*Anti Aim*/ float Constant_Force,InAttackForce, TicksBlocked, TicksSent, JitterAngle, Spinspeed;

	   /*Radar Options*/ float Radar_Health,Radar_Name;

	   /*Misc Options*/ float RCSAmount;
	   /*Glow ESP*/ float GlowActive,Glow_weapons,Glow_C4,Glow_decoy;

	   /*Aimbot*/ float Aimbot_Active, AimPoint,FOV,Silentaim;

	   /*Open Windows*/ float OpenESPOptions;


		/*Menu Pages*/ int Menu_Page,ESP_Page;
		/*Player List*/ float PlayerList;
		/*Positions*/ float Menu_PosX,Menu_PosY;
};
extern cCvars pCvars;