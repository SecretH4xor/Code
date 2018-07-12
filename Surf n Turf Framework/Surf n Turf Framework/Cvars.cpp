#include "Main.h"
cCvars pCvars;


cCvars::cCvars(){

	pCvars.Menu_PosX = 250;
	pCvars.Menu_PosY = 250;

	pCvars.ESPActive = 1;
	pCvars.BoxESP = 1;
	pCvars.BoxOutlineESP = 1;
	pCvars.NameESP = 1;

	pCvars.FOV = 360.0f;
	pCvars.AimPoint = 6;

	pCvars.HealthOption = 2;
	pCvars.HealthBarPos = 2;

	pCvars.ArmorOption = 2;
	pCvars.ArmorBarPos = 2;

	pCvars.NamePos = 2;

	pCvars.HealthOption = 1;
	pCvars.ArmorOption = 1;
	pCvars.NamePos = 1;

	pCvars.ArmorBarPos = 2;
	pCvars.HealthBarPos = 2;
}