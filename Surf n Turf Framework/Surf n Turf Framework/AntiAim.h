#pragma once
#include "Main.h"

class C_AntiAim
{
public :

	void Spinbot(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets);
	void Crownt(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets);
	void AlternativeAngles(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets, Vector pVecAbs);
	void Backwards(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets);
	void Sideways(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets);
	void SetupPitch(CUserCmd *cmd);

	void RunAntiAim(C_BaseEntity* LocalPlayer, CUserCmd* Cmd, bool &bSendPackets);
	void RunFakelags(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets);

	void MovementFix(CUserCmd* pCmd);

};
extern C_AntiAim AntiAim;