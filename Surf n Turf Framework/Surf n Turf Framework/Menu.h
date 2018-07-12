#pragma once

class cMenu
{


public:

	bool			m_bSelected;
	bool			m_bArmorCombo;
	bool			m_bHealthCombo;
	bool			m_bBoxStyleCombo;
	bool			m_bAntiaimCombo;
	bool			m_bAntiAimPitch;
	bool			m_bAntiAimType;
	bool			m_bFakeLaggMode;
	std::vector< std::string >	m_strEspOnlyWhen;
	std::vector< std::string >	m_strHealthOption;
	std::vector< std::string >	m_strArmorOption;
	std::vector< std::string >	m_strAntiAimOption;
	std::vector< std::string >  m_strAntiAimPitch;
	std::vector< std::string >  m_strAntiAimType;
	std::vector< std::string >	m_strFakeLaggMode;
	std::vector< std::string >	m_strBoxStyle;

	cMenu();
	void DrawWindow(int x,int y,int w,int h,const char* title);
	void DrawButton(int x,int y,int w,int h,const char* text,float *status);
	void PlusandMinus(float & cvar,float max,float min,int x,int y,int w,int h,const char* name);
	void DrawCheckBox(int x,int y,float *status,const char* text);
	void iSlider(float x, float y, float len, float min,float max,float *cvar,char *name,Color c);
	void DrawPlayerList(int x,int y,int w,int h,const char* title);
	void BuildMenu(int x,int y,int w,int h,const char* title);
	void ExtraWindow(int x,int y,int w,int h,const char* title);
	void RadarOptions(int x,int y,int w,int h,const char* title);
	void ComboBox(int x, int y, int w, int h, std::vector< std::string > strNotes, int &cvar, bool& bState );
	
};

extern cMenu pMenu;