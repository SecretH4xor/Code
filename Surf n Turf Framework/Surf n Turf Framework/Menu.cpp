#include "Main.h"
#include "Menu.h"
#include <time.h>
cMenu pMenu;

cMenu::cMenu(void){

	m_strEspOnlyWhen.push_back( "Off" );//0
	m_strEspOnlyWhen.push_back( "Dead" );//1
	m_strEspOnlyWhen.push_back( "Walking" );//2
	m_strEspOnlyWhen.push_back( "Menu Open" );//3


	m_strHealthOption.push_back( "Text" );
	m_strHealthOption.push_back( "Bars" );


	m_strArmorOption.push_back( "Text" );
	m_strArmorOption.push_back( "Bars" );

	m_strBoxStyle.push_back( "Corner" );
	m_strBoxStyle.push_back( "Bounding" );

	m_strAntiAimOption.push_back( "Off" );
	m_strAntiAimOption.push_back( "Spinbot" );

	m_strAntiAimPitch.push_back( "Off" );
	m_strAntiAimPitch.push_back( "safe down" );
	m_strAntiAimPitch.push_back( "FakeDown" );
	m_strAntiAimPitch.push_back( "Emotion" );
	m_strAntiAimPitch.push_back( "MM Down" );
	m_strAntiAimPitch.push_back( "test" );
	m_strAntiAimPitch.push_back( "zero" );
	m_strAntiAimPitch.push_back( "up" );


	m_strAntiAimType.push_back( "Sideways" );
	m_strAntiAimType.push_back( "Backwards" );
	m_strAntiAimType.push_back( "Test" );
	m_strAntiAimType.push_back( "test" );
	m_strAntiAimType.push_back( "Backwards Jitter" );
	m_strAntiAimType.push_back( "Sideways Jitter" );
	m_strAntiAimType.push_back( "Backwards Jitter 2" );
	m_strAntiAimType.push_back( "FAKE FORWARD" );
	m_strAntiAimType.push_back( "Spinbot" );
	m_strAntiAimType.push_back( "Spinbot" );


	m_strFakeLaggMode.push_back( "Off" );
	m_strFakeLaggMode.push_back( "Constant" );
	m_strFakeLaggMode.push_back( "SQCH FAKELAG" );
	m_strFakeLaggMode.push_back( "Constant + Disable IN_ATTACK" );
	m_strFakeLaggMode.push_back( "Alternative" );
	m_strFakeLaggMode.push_back( "Alternative + Custom IN_ATTACK" );
	m_strFakeLaggMode.push_back( "Alternative + Off IN_ATTACK" );
}

void cMenu::DrawCheckBox(int x,int y,float *status,const char* text){
	cDraw.OutlinedRect(x,y,15,15,Color(25,25,25,255));
	cDraw.DrawString(MenuCheckboxFont,false,x+20,y,Color(25,25,25,255),text);

	if(aMouse.IsOver(x,y,15,15))
		cDraw.OutlinedRect(x,y,15,15,Color(255,0,0,255));

	if(aMouse.LeftClick(x,y,15,15))
	{

		if(*status == 0)
		{
			*status = 1;	
		}
		else
			*status = 0;
	}

	if(*status == 1)
	{
		cDraw.DrawString(MenuCheckboxFont,true,x+7.5,y+5,Color(46,46,46,255),"x");
	}
}

void cMenu::ComboBox( int x, int y, int w, int h, std::vector< std::string > strNodes, int& cvar, bool& bState ){
	auto iIndex = cvar;
	auto nSize = strNodes.size();

	static float storedcvar = cvar;
	if ( iIndex >= ( int ) nSize )
		iIndex = ( int ) nSize - 1;

	int iFontSize[ 2 ] ={ 0 };
	auto strCurrentString = strNodes[ iIndex ];

	cDraw.FillRGBA( x, y, w, h, Color( 46,46,46,255 ) );
	cDraw.FillRGBA( x + w - h, y, h, h, Color( 75, 75, 75, 255 ) );
	cDraw.OutlinedRect( x, y, w, h, Color( 90, 90, 90, 255 ) );
	cDraw.DrawString( MenuCheckboxFont,false, x + 5, y + ( h / 2 ) - 7, Color( 255, 255, 255, 230 ), strCurrentString.c_str() );

	static bool press = false;

	if ( aMouse.LeftClick( x + w - h, y, h, h ))
	{
			bState = !bState;
			press = true;
	}

	if ( bState )
	{
		auto Y = y + h;
		for ( int i = 0; i < ( int ) nSize; i++ )
		{
			auto bHover = aMouse.IsOver( x, Y + 2 + ( i * 20 ), w, 20 );

			cDraw.FillRGBA( x, Y + 2 + ( i * 20 ), w, 20, bHover ? Color( 150, 20, 20, 255 ) : Color( 50, 50, 50, 255 ) );
			cDraw.OutlinedRect( x, Y + 2 + ( i * 20 ), w, 20, Color( 90, 90, 90, 255 ) );
			cDraw.DrawString( MenuCheckboxFont,false, x + 5, Y + 3 + ( i * 20 ), Color( 255, 255, 255, 255 ), strNodes[ i ].c_str() );

			if ( bHover && ( GetAsyncKeyState( VK_LBUTTON ) ))
			{
				cvar = i;
				bState = false;
			}
		}
		//if( (GetAsyncKeyState(VK_LBUTTON)) && !aMouse.CheckPos( x, Y, w, nSize ) )
		//	bState = false;
		//if(storedcvar != cvar)
		//	bState = false;
	}

	if ( !bState )
	{
		// draw arrow pointing down
		cDraw.FillRGBA( ( x + w - h + 113 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 114 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 115 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 117 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 118 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 119 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
	}
	else
	{
		// draw arrow pointing up
		cDraw.FillRGBA( ( x + w - h + 113 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 114 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 115 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 117 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 118 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
		cDraw.FillRGBA( ( x + w - h + 119 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
	}
}

void cMenu::iSlider(float x, float y, float len, float min,float max,float *cvar,char *name,Color c)
{
	float Scale = max/len;
	{
		cDraw.FillRGBA(x,y,len+10,20,Color(100,100,100,255));
		cDraw.OutlinedRect(x,y,len+10,20,Color(0,0,0,255));
		if ( aMouse.myPos.x >= ( x ) && aMouse.myPos.x <= ( x + len) && aMouse.myPos.y >= ( y - 5 ) && aMouse.myPos.y <= ( y + 20) && GetAsyncKeyState( VK_LBUTTON ) )
			*cvar = min + (aMouse.myPos.x - x) * Scale;

		cDraw.FillRGBA(x+(*cvar/Scale),y,10,20,Color(65,65,65,255));
		cDraw.OutlinedRect(x+(*cvar/Scale),y,10,20,Color(0,0,0,255));

		if(*cvar > max)
			*cvar = max;
		if(*cvar < min)
			*cvar = min; 

		cDraw.FillRGBA(x,y,(*cvar/Scale),20,c);
	}

	cDraw.DrawString(MenuCheckboxFont,true,x+len / 2,y+10,Color(25,25,25,255),name);
	cDraw.NormalText(MenuCheckboxFont,x+len+15,y,Color(25,25,25,255),"%1.0f",*cvar);
}

void cMenu::PlusandMinus(float & cvar,float max,float min,int x,int y,int w,int h,const char* name){
	cDraw.FillRGBA(x,y,w,h,Color(150,150,150,255)); //fill
	cDraw.OutlinedRect(x,y,w,h,Color(25,25,25,255));//border

	cDraw.OutlinedRect(x,y,15,15,Color(25,25,25,255));//left box
	cDraw.OutlinedRect(x+w-15,y,15,15,Color(25,25,25,255));//Right box

	if(aMouse.IsOver(x,y,15,15))
		cDraw.OutlinedRect(x,y,15,15,Color(255,0,0,255));//Highlighted left box

	if(aMouse.IsOver(x+w-15,y,15,15))
		cDraw.OutlinedRect(x+w-15,y,15,15,Color(255,0,0,255));//Highlighted Right box

	cDraw.DrawString(PlusMinusArrowfont,true,x+7.5,y+7.5,Color(25,25,25,255),"<"); // Left Arrow
	cDraw.DrawString(PlusMinusArrowfont,true,x+w-7.5,y+7.5,Color(25,25,25,255),">"); // Right Arrow

	if(aMouse.LeftClick(x,y,15,15)) 
		cvar -= 1; // Decrease Var
	if(aMouse.LeftClick(x+w-15,y,15,15))
		cvar += 1; // Increase Var

	if(cvar > max)
		cvar = max;
	if(cvar < min)
		cvar = min;

	cDraw.String(PlusMinusfont,true,x+w/2,y,Color(25,25,25,255),"%0.1f",cvar); // Printed Var
	cDraw.NormalText(PlusMinusfont,x+w+5,y,Color(25,25,25,255),name);//Name
}

void cMenu::DrawButton(int x, int y, int w, int h, const char* text,float *status){
	//cDraw.FillRGBA(x,y,w,h,Color(150,150,150,255));
	cDraw.OutlinedRect(x,y,w,h,Color(25,25,25,255));

	if(aMouse.IsOver(x,y,w,h))
		cDraw.OutlinedRect(x,y,w,h,Color(255,0,0,255));

	if(aMouse.LeftClick(x,y,w,h))
	{

		if(*status == 0)
			*status = 1;
		else
			*status = 0;
	}

	if(*status == 1)
	{
		cDraw.OutlinedRect(x,y,w,h,Color(255,106,0,255));
		cDraw.DrawString(MenuButtonToggledFont,true,x+w / 2,y+h/2,Color(255,0,0,255),text);
	}
	else
		cDraw.DrawString(MenuButtonFont,true,x+w / 2,y+h/2,Color(25,25,25,255),text);
}

void GroupBox(std::string Text,int w, int h,int x, int y){
	RECT txtSize = cDraw.GetTextSize(MenuTitleFont, Text.c_str());

	cDraw.FillRGBA(x + 2, y + 2, w - 4, h - 4, Color(0, 0, 0, 0));
	cDraw.NormalText(MenuTitleFont,x + 15, y - (txtSize.bottom / 2), Color(255,255,255,255),  Text.c_str());

	cDraw.DrawLine(x, y, x + 12, y, Color(0,0,0,250)); //before text
	cDraw.DrawLine(x + 15 + txtSize.right + 5, y, x + w, y, Color(0,0,0,250)); //after text
	cDraw.DrawLine(x+w,y,x+w,y+h,Color(0,0,0,250));//right down
	cDraw.DrawLine(x,y+h,x+w,y+h,Color(0,0,0,250));//bottom
	cDraw.DrawLine(x,y,x,y+h,Color(0,0,0,250));
}

void DrawTabs(int x,int y,int w,int h)
{	
	if(aMouse.IsOver(x+5,y,125, 30))
		cDraw.OutlinedRect(x+5,y,125, 30,Color(255,0,0,255));
	else
		cDraw.OutlinedRect(x+5,y,125, 30,Color(0,0,0,255));

	if(pCvars.Menu_Page == 1)
		cDraw.DrawString(MenuTabselectedFont,true,x+67.5,y+15,Color(255,0,0,255),"Aimbot");
	else
		cDraw.DrawString(MenuTabFont,true,x+67.5,y+15,Color(255,255,255,255),"Aimbot");

	//if(aMouse.LeftClick(x+5,y,125, 30)&1)
		//pCvars.Menu_Page = 1;
//======================================================================================================//
	if(aMouse.IsOver(x+130,y,125, 30))
		cDraw.OutlinedRect(x+130,y,125, 30,Color(0,255,0,255));
	else
		cDraw.OutlinedRect(x+130,y,125, 30,Color(0,0,0,255));

	if(pCvars.Menu_Page == 2)
		cDraw.DrawString(MenuTabselectedFont,true,x+192.5,y+15,Color(0,255,0,255),"Visuals");
	else
		cDraw.DrawString(MenuTabFont,true,x+192.5,y+15,Color(255,255,255,255),"Visuals");

	if(aMouse.LeftClick(x+130,y,125, 30))
		pCvars.Menu_Page = 2;
//======================================================================================================//
	if(aMouse.IsOver(x+255,y,125, 30))
		cDraw.OutlinedRect(x+255,y,125, 30,Color(255,0,0,255));
	else
		cDraw.OutlinedRect(x+255,y,125, 30,Color(0,0,0,255));

	if(pCvars.Menu_Page == 3)
		cDraw.DrawString(MenuTabselectedFont,true,x+317.5,y+15,Color(0,255,0,255),"Misc");
	else
		cDraw.DrawString(MenuTabFont,true,x+317.5,y+15,Color(255,255,255,255),"Misc");

	//if(aMouse.LeftClick(x+255,y,125, 30))
	//	pCvars.Menu_Page = 3;
//======================================================================================================//
	if(aMouse.IsOver(x+380,y,125, 30))
		cDraw.OutlinedRect(x+380,y,125, 30,Color(255,0,0,255));	
	else
		cDraw.OutlinedRect(x+380,y,125, 30,Color(0,0,0,255));

	if(pCvars.Menu_Page == 4)
		cDraw.DrawString(MenuTabselectedFont,true,x+442.5,y+15,Color(255,0,0,255),"Colors");
	else
		cDraw.DrawString(MenuTabFont,true,x+442.5,y+15,Color(255,255,255,255),"Colors");
	
	//if(aMouse.LeftClick(x+380,y,125, 30))
		//pCvars.Menu_Page = 4;
//======================================================================================================//
}

void DrawPages(int x,int y,int w,int h)
{
	//Top Left x+25,y+45

	//Top Right x + w / 2 + 5,y+45

	if(pCvars.Menu_Page == 1){//Aimbot
		GroupBox("Aimbot",230,h-60,x+15,y+45);
		GroupBox("Trigger Bot",230,h-60,x+260,y+45);
	}

	if(pCvars.Menu_Page == 2){//Visuals
		GroupBox("ESP",230,h-60,x+15,y+45);
		GroupBox("Options",230,175,x+260,y+45);
		GroupBox("ESP Only When",230,100,x+260,y+235);

		pMenu.DrawCheckBox(x+25,y+60,&pCvars.ESPActive,"Enable");
		pMenu.DrawCheckBox(x+25,y+100,&pCvars.BoxESP,"Box");
		pMenu.DrawCheckBox(x+25,y+120,&pCvars.BoxOutlineESP,"Box Outline");
		pMenu.DrawCheckBox(x+25,y+140,&pCvars.NameESP,"Name");
		pMenu.DrawCheckBox(x+25,y+160,&pCvars.HealthESP,"Health");
		pMenu.DrawCheckBox(x+25,y+180,&pCvars.ArmorESP,"Armor");
		pMenu.DrawCheckBox(x+25,y+200,&pCvars.RecoilCrosshair,"Recoil Crosshair");
		pMenu.DrawCheckBox(x+25,y+220,&pCvars.NightMode,"NightMode");


		pMenu.DrawCheckBox(x+270,y+60,&pCvars.EnemyOnly,"Enemy Only");

		pMenu.ComboBox(x+270,y+80,150,20,pMenu.m_strBoxStyle,pCvars.BoxStyle,pMenu.m_bBoxStyleCombo);

		pMenu.ComboBox(x+270,y+250,150,20,pMenu.m_strEspOnlyWhen,pCvars.ESP_When,pMenu.m_bSelected);


	}
	if(pCvars.Menu_Page == 3){//Misc
		//GroupBox("Misc",230,h-60,x+15,y+45);
		//GroupBox("Tweak",230,h-60,x+260,y+45);

		pMenu.DrawCheckBox(x+25,y+60,&pCvars.BunnyHop,"Bunny Hop");
		pMenu.DrawCheckBox(x+25,y+80,&pCvars.AutoStrafe,"Auto Strafe");
		//pMenu.DrawCheckBox(x+25,y+120,&pCvars.BoxOutlineESP,"Box Outline");
		//pMenu.DrawCheckBox(x+25,y+140,&pCvars.NameESP,"Name");
		//pMenu.DrawCheckBox(x+25,y+160,&pCvars.HealthESP,"Health");
		//pMenu.DrawCheckBox(x+25,y+180,&pCvars.ArmorESP,"Armor");
		//pMenu.DrawCheckBox(x+25,y+200,&pCvars.RecoilCrosshair,"Recoil Crosshair");


		//pMenu.iSlider(x+270,y+60,150,1,15,&pCvars.Constant_Force,"FakeLag Value",Color(255,255,255,255));
		//pMenu.iSlider(x+270,y+85,150,1,15,&pCvars.InAttackForce,"IN_ATTACK value",Color(255,255,255,255));
		//pMenu.iSlider(x+270,y+110,150,1,15,&pCvars.TicksBlocked,"Blocked Packets",Color(255,255,255,255));
		//pMenu.iSlider(x+270,y+135,150,1,15,&pCvars.TicksSent,"Sent Packets",Color(255,255,255,255));
		//pMenu.iSlider(x+270,y+160,150,1,20,&pCvars.Spinspeed,"Spin Speed",Color(255,255,255,255));
		//pMenu.iSlider(x+270,y+185,150,1,180,&pCvars.JitterAngle,"Jitter Angle",Color(255,255,255,255));

		//pMenu.ComboBox(x+270,y+210,150,20,pMenu.m_strAntiAimPitch,pCvars.AntiAimPitch,pMenu.m_bAntiAimPitch);
		//pMenu.ComboBox(x+270,y+235,150,20,pMenu.m_strAntiAimType,pCvars.AntiAimType,pMenu.m_bAntiAimType);
		//pMenu.ComboBox(x+270,y+260,150,20,pMenu.m_strFakeLaggMode,pCvars.FakeLaggMode,pMenu.m_bFakeLaggMode);
	}
	if(pCvars.Menu_Page == 4){//color

	}
}

void cMenu::DrawWindow(int x,int y,int w,int h,const char* title){
	cDraw.FillRGBA(x,y-25,w,23,Color(46,46,46,255));//title fill
	cDraw.OutlinedRect(x,y-25,w,23,Color(0,0,0,255));//title outline
	cDraw.DrawString(MenuTitleFont,true,x+w/2,y-15,Color(255,255,255,255),title);// title text

	cDraw.FillRGBA(x,y,w,h,Color(46,46,46,255));//main background
	cDraw.OutlinedRect(x,y,w,h,Color(0,0,0,255));// main border

	cDraw.FillRGBAFade(x+5,y+30,w-10,h-35,Color(201,201,201,255),255,150,false);// main fade
	cDraw.OutlinedRect(x+5,y+30,w-10,h-35,Color(0,0,0,255)); // fade boarder
}

void cMenu::BuildMenu(int x,int y,int w,int h,const char* title){
	DrawWindow(x,y,w,h,title);
	DrawTabs(x,y,w,h);
	DrawPages(x,y,w,h);
}

