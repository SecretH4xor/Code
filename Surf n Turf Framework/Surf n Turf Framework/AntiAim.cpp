#include "Main.h"
C_AntiAim AntiAim;

static float RunAimPlayerBehindWall(CUserCmd* Cmd, C_BaseEntity* LocalPlayer)
{
	for (int i = pGlobals->maxclients; i >= 1; --i)
	{
		if (i == LocalPlayer->GetIndex())
		{
			continue;
		}

		C_BaseEntity* targetEntity = (C_BaseEntity*)pClientEntList->GetClientEntity(i);

		if (!targetEntity
			|| targetEntity->IsDormant()
			|| !targetEntity->GetLifeState() == LIFE_ALIVE
			|| (targetEntity->TeamNum() == LocalPlayer->TeamNum()))
		{
			continue;
		}

		int health = targetEntity->GetHealth();

		if (!(health > 0)
			|| (targetEntity->GetHealth() >= 500))
		{
			continue;
		}

		float fldist = FLT_MAX;
		Vector dir = (targetEntity->GetAbsOrigin() - LocalPlayer->GetAbsOrigin());
		Vector Dis;
		float distance = Dis.flNormalizeVector(dir);
		if (distance < fldist)
		{
			fldist = distance;
			Dis.NormalizeVector(dir);
			Dis.VectorToAngles(dir, Cmd->viewangles);
		}

		return Cmd->viewangles.y;
	}
}

Vector AlternativeCheck(C_BaseEntity* pLocalPlayer, CUserCmd* pCmd)
{
	Vector AbsVelocity = pLocalPlayer->GetEstimatedAbsVelocity();

	float angle = RunAimPlayerBehindWall(pCmd, pLocalPlayer);

	bool Check;
	if (pLocalPlayer->TeamNum() == 3)
	{
		Check = !((angle >= 0.0f) && (angle <= 180.0f));
	}
	else
	{
		Check = (angle > 0.0f) && (angle < 180.0f);
	}

	if (Check)
	{
		AbsVelocity.x = -AbsVelocity.x;
	}

	return AbsVelocity;
}

void C_AntiAim::SetupPitch( CUserCmd *cmd )
{

	if ( pCvars.AntiAimPitch == 1 )//´safe down
	{
		cmd->viewangles.x = 88.9f;
	}

	if (  pCvars.AntiAimPitch == 2 )//FakeDown
	{
		cmd->viewangles.x = -271;
	}

	if (  pCvars.AntiAimPitch == 3 )//Emotion
	{
		cmd->viewangles.x = 70;
	}

	if (  pCvars.AntiAimPitch == 4 )//MM Down
	{
		cmd->viewangles.x = 177.99f;
	}
	if ( pCvars.AntiAimPitch == 5 ) // test 
	{
		cmd->viewangles.x = 261.f || 180.f;
	}
	if ( pCvars.AntiAimPitch == 6 ) // zero
	{
		cmd->viewangles.x = 0.0f;
	}
	if ( pCvars.AntiAimPitch == 7 ) //up
	{
		cmd->viewangles.x = -89;
	}

}

void C_AntiAim::Sideways(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets)
{
	static bool first;
	if (pCvars.AntiAimMode == 0)
	{
		if (first)
		{
			first = false;
			if (localPlayer->TeamNum() == 2)
			{
				cmd->viewangles.y = 360.f;
			}
			else
			{
				cmd->viewangles.y = 90.0f;
			}
			bSendPackets = true;
		}
		else
		{
			first = true;
			if (localPlayer->TeamNum() == 2)
			{
				cmd->viewangles.y = 180.f;
			}
			else
			{
				cmd->viewangles.y = 270.0f;
			}
			bSendPackets = false;
		}
	}
	else
	{
		if (first)
		{
			first = false;
			if (localPlayer->TeamNum() == 2)
			{
				cmd->viewangles.y -= 155.f;
			}
			else
			{
				cmd->viewangles.y -= 300.f;
			}
			bSendPackets = true;
		}
		else
		{
			first = true;
			if (localPlayer->TeamNum() == 2)
			{
				cmd->viewangles.y -= 10.0f;
			}
			else
			{
				cmd->viewangles.y -= 271.0f;
			}
			bSendPackets = false;
		}
	}
}

void C_AntiAim::Backwards(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets)
{
	static bool first;

	if (pCvars.AntiAimMode == 0)
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y = 180.0f;
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y = 360.0f;
			bSendPackets = false;
		}
	}
	else
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y -= 180.0f;
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y -= 360.0f;
			bSendPackets = false;
		}
	}
}

void C_AntiAim::AlternativeAngles(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets, Vector pVecAbs)
{
	static bool first;
	if (pCvars.AntiAimMode == 0)
	{
		if (first)
		{
			first = false;
			if (pVecAbs.x >= 0.0f)
			{
				if (localPlayer->TeamNum() == 2)
					cmd->viewangles.y = 90.0f;
				else
					cmd->viewangles.y = 270.0f;
			}
			else
			{
				if (localPlayer->TeamNum() == 2)
					cmd->viewangles.y = 270.0f;
				else
					cmd->viewangles.y = 90.0f;
			}
			bSendPackets = true;
		}
		else
		{
			first = true;
			if (pVecAbs.x >= 0.0f)
			{
				if (localPlayer->TeamNum() == 2)
					cmd->viewangles.y = 270.0f;
				else
					cmd->viewangles.y = 90.0f;
			}
			else
			{
				if (localPlayer->TeamNum() == 2)
					cmd->viewangles.y = 90.0f;
				else
					cmd->viewangles.y = 270.0f;
			}
			bSendPackets = false;
		}
	}
	else
	{
		if (first)
		{
			first = false;
			if (pVecAbs.x >= 0.0f)
			{
				if (localPlayer->TeamNum() == 2)
					cmd->viewangles.y -= 90.0f;
				else
					cmd->viewangles.y -= 270.0f;
			}
			else
			{
				if (localPlayer->TeamNum() == 2)
					cmd->viewangles.y -= 270.0f;
				else
					cmd->viewangles.y -= 90.0f;
			}
			bSendPackets = true;
		}
		else
		{
			first = true; 
			if (pVecAbs.x >= 0.0f)
			{
				if (localPlayer->TeamNum() == 2)
					cmd->viewangles.y -= 270.0f;
				else
					cmd->viewangles.y -= 90.0f;
			}
			else
			{
				if (localPlayer->TeamNum() == 2)
					cmd->viewangles.y -= 90.0f;
				else
					cmd->viewangles.y -= 270.0f;
			}
			bSendPackets = false;
		}
	}
}

void C_AntiAim::Crownt(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets)
{
	static bool first;

	if (pCvars.AntiAimMode == 0)
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y += 155.0f;
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y -= 115.0f;
			bSendPackets = false;
		}
	}
	else
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y -= 155.0f;
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y += 115.0f;
			bSendPackets = false;
		}
	}
}

void C_AntiAim::Spinbot(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets)
{
	static bool first;

	if (pCvars.AntiAimMode == 0)
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y = (GetTickCount() / 0.001f * 360.0);
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y = (GetTickCount() / 0.001f * -360.0f);
			bSendPackets = false;
		}
	}
	else
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y -= (GetTickCount() / 0.001f * 360.0);
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y += (GetTickCount() / 0.001f * -360.0f);
			bSendPackets = false;
		}
	}
}

void C_AntiAim::RunFakelags(C_BaseEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets)
{

	//Alternative Check 
	Vector vTemp = AlternativeCheck(localPlayer, cmd);


	//==================================================

	//Setup Pitch

	SetupPitch(cmd);

	//=================================================
	
	

	float ***GetLowerBodyYawTarget;

	GetLowerBodyYawTarget[ 0x39F8 ][ 0xE6996CCF ] [ 0xE6996CCF ];



	//Setup Yaw
	static bool jitterswitch = false;
	if (pCvars.AntiAimType == 0) //Sideways
	{
		cmd->viewangles.y = ( localPlayer && 180, bSendPackets = false);

	}

	if (pCvars.AntiAimType == 1) //Backwards
	{
		Backwards( localPlayer, cmd, bSendPackets );
	}
	
	if (pCvars.AntiAimType == 2) //Test
	{
		cmd->viewangles.y = 180.f;
	}
	else
	{
		cmd->viewangles.y = 270;
		bSendPackets = false;
	}

	if ( pCvars.AntiAimType == 3 ) //test
	{
		if ( jitterswitch = false )
		{
			cmd->viewangles.y = 360 || 90;
		}
		else
		{
			cmd->viewangles.y = 270 || 180;
			bSendPackets = false;
			jitterswitch = true;
		}

	}

	if (pCvars.AntiAimType == 4) //Backwards Jitter
	{
		if (jitterswitch)
		{
			cmd->viewangles.y -= (180.0f - pCvars.JitterAngle);
			jitterswitch = false;
		}
		else
		{
			cmd->viewangles.y -= (180.0f + pCvars.JitterAngle);
			jitterswitch = true;
		}
	}
	if (pCvars.AntiAimType == 5) //Sideways Jitter
	{
		if (jitterswitch)
		{
			cmd->viewangles.y -= (90.0f - pCvars.JitterAngle);
			jitterswitch = false;
		}
		else
		{
			cmd->viewangles.y -= (90.0f + pCvars.JitterAngle);
			jitterswitch = true;
		}
	}
	if (pCvars.AntiAimType == 6) //Backwards Jitter 2
	{
		static bool sendpackets = false;

		if (sendpackets)
		{
			bSendPackets = true;
			if (jitterswitch)
			{
				cmd->viewangles.y -= 145.0f;
				jitterswitch = false;
			}
			else
			{
				cmd->viewangles.y -= 215.0f;
				jitterswitch = true;
			}
			sendpackets = false;
		}
		else
		{
			bSendPackets = false;
			cmd->viewangles.y -= 360.0f;
			sendpackets = true;
		}
	}


	if ( pCvars.AntiAimType == 7 )//FAKE FORWARD
	{
		if ( cmd->command_number % 3 )
		{
			
			cmd->viewangles.y += 180.0f;
		}
		else
		{
			bSendPackets = false;
			cmd->viewangles.y -= 180.0f;
		}

	}
	
	if ( pCvars.AntiAimType == 8 ) //Jitter Synced
	{
	{
			//Jitter Synced
			if ( cmd->command_number % 3 )
			cmd->viewangles.y = cmd->viewangles.y + 100.0;
			bSendPackets = false;
		}
	}
	
	if ( pCvars.AntiAimType == 9 )
	{
		//Sideways
		{
			Spinbot( localPlayer, cmd, bSendPackets );
		}
	}

	if ( pCvars.AntiAimType == 10 )
	{
		static bool spin;
		if (spin) 
		{
			spin = true;
			cmd->viewangles.y += 360.f;
		}
		else
		{
			spin = false;
			cmd->viewangles.y = 69.02738273f;
			bSendPackets = false;
		}

	}
	//=================================================

	//Following AntiAim

	if (pCvars.AntiAimMode == 3 && pCvars.AntiAimType != 4)
	{
		RunAimPlayerBehindWall(cmd,localPlayer);
	}

	//=================================================

	//Setup FakeLags

	if (pCvars.FakeLaggMode == 1)//Constant
	{
		static int Ticks =  13;
		if (Ticks <= 0)
		{
			bSendPackets = true;

			Vector vel = localPlayer->GetVelocity();
			vel.z = 0.0f;

			int f = ( int ) ( ceilf( ( 64.0f / 0.0078125f ) / vel.Length() ) );

			if ( f < 1 )
				f = 1;

			if ( f > 13 )
				f = 13;

			static bool diff = false;
			diff = !diff;

			Ticks = f - (diff ? 1 : 0);
		}
		else
		{
			bSendPackets = false;
			Ticks--;
		}
	}

	if ( pCvars.FakeLaggMode == 2 )//SQCH FAKELAG
	{
		static int iTick;
		if ( iTick < pCvars.Constant_Force && !( cmd->buttons & IN_ATTACK ) ) 
		{
			bSendPackets = false;
			iTick++;
		}
		else 
		{
			bSendPackets = true;
			iTick = 0;
		}
	}

	if (pCvars.FakeLaggMode == 3)//Constant + Disable IN_ATTACK
	{
		if (cmd->buttons & IN_ATTACK)
		{
			bSendPackets = true;
		}
		static int Ticks = pCvars.Constant_Force;
		if (Ticks <= 0)
		{
			bSendPackets = true;
			Ticks = pCvars.Constant_Force;
		}
		else
		{
			bSendPackets = false;
			Ticks--;
		}
	}

	if (pCvars.FakeLaggMode == 4) // Alternative
	{
		static int Ticks = 0;
		static bool Packet_Drop = false;
		bool Reset_Counter = false;
		if (Packet_Drop)
			bSendPackets = false;
		if (Packet_Drop&&Ticks > pCvars.TicksBlocked) // 5 or 7 //4 !
		{
			Reset_Counter = true;
			Packet_Drop = false;
		}
		else if (!Packet_Drop&&Ticks > pCvars.TicksSent) //2 or 4 //2 !
		{
			Reset_Counter = true;
			Packet_Drop = true;
		}
		Ticks++;
		if (Reset_Counter)
			Ticks = 0;
	}

	if (pCvars.FakeLaggMode == 5) // Alternative + Custom IN_ATTACK
	{
		if (cmd->buttons & IN_ATTACK)
		{
			static int Ticks = pCvars.InAttackForce;
			if (Ticks <= 0)
			{
				bSendPackets = true;
				Ticks = pCvars.InAttackForce;
			}
			else
			{
				bSendPackets = false;
				Ticks--;
			}
		}
		else
		{
			static int Ticks = 0;
			static bool Packet_Drop = false;
			bool Reset_Counter = false;
			if (Packet_Drop)
				bSendPackets = false;
			if (Packet_Drop&&Ticks > pCvars.TicksBlocked) // 5 or 7 //4 !
			{
				Reset_Counter = true;
				Packet_Drop = false;
			}
			else if (!Packet_Drop&&Ticks > pCvars.TicksSent) //2 or 4 //2 !
			{
				Reset_Counter = true;
				Packet_Drop = true;
			}
			Ticks++;
			if (Reset_Counter)
				Ticks = 0;
		}
	}

	if (pCvars.FakeLaggMode == 6) // Alternative + Off IN_ATTACK
	{
		if (cmd->buttons & IN_ATTACK)
		{
			bSendPackets = true;
		}
		else
		{
			static int Ticks = 0;
			static bool Packet_Drop = false;
			bool Reset_Counter = false;
			if (Packet_Drop)
				bSendPackets = false;
			if (Packet_Drop&&Ticks > pCvars.TicksBlocked) // 5 or 7 //4 !
			{
				Reset_Counter = true;
				Packet_Drop = false;
			}
			else if (!Packet_Drop&&Ticks > pCvars.TicksSent) //2 or 4 //2 !
			{
				Reset_Counter = true;
				Packet_Drop = true;
			}
			Ticks++;
			if (Reset_Counter)
				Ticks = 0;
		}
	}
}

void C_AntiAim::RunAntiAim(C_BaseEntity* LocalPlayer, CUserCmd* Cmd, bool &bSendPackets)
{
	RunFakelags(LocalPlayer, Cmd, bSendPackets);
}