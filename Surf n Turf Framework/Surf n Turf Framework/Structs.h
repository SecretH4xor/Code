#pragma once

#ifndef __GAME_CLASSES_H__
#define __GAME_CLASSES_H__



class IBaseClientDLL;
class IVEngineClient;
class IPanel;
class ISurface;
class IVModelInfo;
class CGlobalVarsBase;
class IEngineTrace;
class CInput;
class RecvTable;
class IHandleEntity;
class IClientNetworkable;
class IClientEntity;
class IClientThinkable;
class IClientUnknown;
class IClientNetworkable;

#define	LIFE_ALIVE				0

template< typename Function > Function call_vfunc( PVOID Base, DWORD Index )
{
	PDWORD* VTablePointer = ( PDWORD* )Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[ Index ];
	return ( Function )( dwAddress );
}

enum FontDrawType_t
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC			= 0x001,
	FONTFLAG_UNDERLINE		= 0x002,
	FONTFLAG_STRIKEOUT		= 0x004,
	FONTFLAG_SYMBOL			= 0x008,
	FONTFLAG_ANTIALIAS		= 0x010,
	FONTFLAG_GAUSSIANBLUR	= 0x020,
	FONTFLAG_ROTARY			= 0x040,
	FONTFLAG_DROPSHADOW		= 0x080,
	FONTFLAG_ADDITIVE		= 0x100,
	FONTFLAG_OUTLINE		= 0x200,
	FONTFLAG_CUSTOM			= 0x400,
	FONTFLAG_BITMAP			= 0x800,
};

class Color
{
public:
	Color()
	{
		*((int *)this) = 0;
	}
	Color(int r,int g,int b)
	{
		SetColor(r, g, b, 0);
	}
	Color(int r,int g,int b,int a)
	{
		SetColor(r, g, b, a);
	}
	void SetColor(int r, int g, int b, int a = 0)
	{
		_color[0] = (unsigned char)r;
		_color[1] = (unsigned char)g;
		_color[2] = (unsigned char)b;
		_color[3] = (unsigned char)a;
	}

	void GetColor(int &r, int &g, int &b, int &a) const
	{
		r = _color[0];
		g = _color[1];
		b = _color[2];
		a = _color[3];
	}

	void SetRawColor( int color32 )
	{
		*((int *)this) = color32;
	}

	int GetRawColor() const
	{
		return *((int *)this);
	}

	inline int r() const	{ return _color[0]; }
	inline int g() const	{ return _color[1]; }
	inline int b() const	{ return _color[2]; }
	inline int a() const	{ return _color[3]; }

	unsigned char &operator[](int index)
	{
		return _color[index];
	}

	const unsigned char &operator[](int index) const
	{
		return _color[index];
	}

	bool operator == (const Color &rhs) const
	{
		return ( *((int *)this) == *((int *)&rhs) );
	}

	bool operator != (const Color &rhs) const
	{
		return !(operator==(rhs));
	}

	Color &operator=( const Color &rhs )
	{
		SetRawColor( rhs.GetRawColor() );
		return *this;
	}

	Color FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
				);
		}
		else if (h < 2)
		{
			return Color(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
				);
		}
		else if (h < 3)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
				);
		}
		else if (h < 4)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
				);
		}
		else if (h < 5)
		{
			return Color(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
				);
		}
		else
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255)
				);
		}
	}

private:
	unsigned char _color[4];
};

struct matrix3x4
{
	matrix3x4() {}
	matrix3x4( 
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23 )
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}
	void Init( const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin )
	{
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	matrix3x4( const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin )
	{
		Init( xAxis, yAxis, zAxis, vecOrigin );
	}
	float *operator[]( int i )				
	{ 
		return m_flMatVal[i]; 
	}
	const float *operator[]( int i ) const	
	{ 
		return m_flMatVal[i]; 
	}
	float *Base()							
	{ 
		return &m_flMatVal[0][0]; 
	}
	const float *Base() const				
	{ 
		return &m_flMatVal[0][0]; 
	}

	float m_flMatVal[3][4];
};

class player_info_t
{
public:
	char unknown0[0x10];
	char name[32];
	char unknown2[0x200];
};

class ConVar
{
public:
	ConVar* FindVar(const char *var_name)
	{
		typedef ConVar*(__thiscall* OriginalFn)(void*, const char*);
		return call_vfunc<OriginalFn>(this, 15)(this, var_name);
	}

	void SetValue(int value)
	{
		typedef void(__thiscall* OriginalFn)(void*, int);
		return call_vfunc<OriginalFn>(this, 16)(this, value);
	}
	void SetValue(const char* value)
	{
		typedef void(__thiscall* OriginalFn)(void*, const char*);
		return call_vfunc<OriginalFn>(this, 14)(this, value);
	}
};

class CGlobalVarsBase
{
public:
	float	realtime;
	int		framecount;
	float	absoluteframetime;
	float	absoluteframestarttimestddev;
	float	curtime;
	float	frametime;
	int		maxclients;
	int		tickcount;
	float	interval_per_tick;
	float	interpolation_amount;
	int		simTicksThisFrame;
	int		network_protocol;
	char	pad00[14];
};

class IPlayerInfoManager
{
public:
	CGlobalVarsBase* GetGlobalVars()
	{
		typedef CGlobalVarsBase*(__thiscall* GetGlobalVarsFn)(void*);
		return call_vfunc<GetGlobalVarsFn>(this, 1)(this);
	}
};

class IBaseClientDLL
{
public:
	void CreateMove( int sequence_number, float frametime, bool active )
	{
		typedef void ( __thiscall* oMove )( PVOID,int,float,bool );
		return call_vfunc< oMove >( this, 21 )( this, sequence_number, frametime, active );
	}
};

class IVEngineClient
{
public:
	void GetScreenSize( int& width, int& height )
	{
		typedef void ( __thiscall* oGetScreenSize )( PVOID, int&, int& );
		return call_vfunc< oGetScreenSize >( this, 5 )( this, width, height );
	}
	bool GetPlayerInfo(int ent_num, player_info_t *pinfo)
	{
		typedef bool ( __thiscall* oGetPlayerInfo )( PVOID, int, player_info_t* );
		return call_vfunc< oGetPlayerInfo >( this, 8 )( this, ent_num, pinfo );
	}
	int GetLocalPlayer(  )
	{
		typedef int ( __thiscall* oLocal )( PVOID );
		return call_vfunc< oLocal >( this, 12 )( this );
	}
	float Time(  )
	{
		typedef float ( __thiscall* oTime )( PVOID );
		return call_vfunc< oTime >( this, 14 )( this );
	}
	void SetViewAngles(Vector& vAngles)
	{
		typedef void ( __thiscall* oSetViewAngles )( PVOID, Vector& );
		return call_vfunc< oSetViewAngles >( this, 19 )( this, vAngles );
	}
	int GetMaxClients( )
	{
		typedef bool ( __thiscall* oGetMaxClients )( PVOID );
		return call_vfunc< oGetMaxClients >( this, 20 )( this );
	}
	bool IsConnected(  )
	{
		typedef bool ( __thiscall* oGetScreenSize )( PVOID );
		return call_vfunc< oGetScreenSize >( this, 27 )( this );
	}
	bool IsInGame(  )
	{
		typedef bool ( __thiscall* oLocal )( PVOID );
		return call_vfunc< oLocal >( this, 26 )( this );
	}

	void cmd(const char* cmdstr )
	{
		typedef void(__thiscall* oCmd)(PVOID,const char*);
		return call_vfunc< oCmd >(this, 7)( this, cmdstr);
	}

	void GetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, Vector&);
		return call_vfunc< OriginalFn >(this, 19)(this, vAngles);
	}

#define idx_engine_worldtoscreenmatrix 37

	const matrix3x4& WorldToScreenMatrix(void)
	{
		typedef const matrix3x4& (__thiscall* OriginalFn)(PVOID);
		return call_vfunc<OriginalFn>(this, idx_engine_worldtoscreenmatrix)(this);
	}

};

class ISurface
{
public:
	void DrawSetColor(Color col)
	{
		typedef void ( __thiscall* oDrawSetColor )( PVOID, Color );
		return call_vfunc< oDrawSetColor >( this, 14 )( this, col );
	}
	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void ( __thiscall* oDrawSetColor )( PVOID, int , int , int , int  );
		return call_vfunc< oDrawSetColor >( this, 16 )( this, x0,  y0,  x1,  y1 );
	}
	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void ( __thiscall* oDrawOutlinedRect )( PVOID, int , int , int , int  );
		return call_vfunc< oDrawOutlinedRect >( this, 18 )( this, x0,  y0,  x1,  y1 );
	}
	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void ( __thiscall* oDrawLine )( PVOID, int , int , int , int  );
		return call_vfunc< oDrawLine >( this, 19 )( this, x0,  y0,  x1,  y1 );
	}
	void DrawSetTextFont(unsigned long hFont)
	{
		typedef void ( __thiscall* oDrawSetTextFont )( PVOID, unsigned long  );
		return call_vfunc< oDrawSetTextFont >( this, 23 )( this, hFont );
	}
	void DrawSetTextColor(Color col)
	{
		typedef void ( __thiscall* oDrawSetTextColor )( PVOID, Color  );
		return call_vfunc< oDrawSetTextColor >( this, 24 )( this, col );
	}
	void DrawSetTextPos(int x,int y)
	{
		typedef void ( __thiscall* oDrawSetTextPos )( PVOID, int ,int  );
		return call_vfunc< oDrawSetTextPos >( this, 26 )( this,  x, y );
	}
	void DrawPrintText(wchar_t *text, int textLen, FontDrawType_t drawType = FONT_DRAW_DEFAULT)
	{
		typedef void ( __thiscall* oDrawPrintText )( PVOID, wchar_t*, int, FontDrawType_t  );
		return call_vfunc< oDrawPrintText >( this, 28 )( this,  text, textLen, drawType );
	}
	unsigned long FontCreate()
	{
		typedef unsigned long ( __thiscall* oCreateFont )( PVOID );
		return call_vfunc< oCreateFont >( this, 71 )( this );
	}
	bool SetFontGlyphSet(unsigned long font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0)
	{
		typedef bool( __thiscall* oCreateFont )( PVOID, unsigned long , const char *, int , int , int , int , int, int, int );
		return call_vfunc< oCreateFont >( this, 72 )( this, font, windowsFontName,  tall,  weight,  blur,  scanlines, flags, nRangeMin, nRangeMax );
	}
	bool GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall )
	{
		typedef bool( __thiscall* oGetTextSize )( PVOID, unsigned long, const wchar_t*, int&, int& );
		return call_vfunc< oGetTextSize >( this, 79 )( this, font, text, wide, tall );
	}
	bool GetTextSize2(unsigned long font, const char *text, int &wide, int &tall )
	{
		typedef bool( __thiscall* oGetTextSize )( PVOID, unsigned long, const char*, int&, int& );
		return call_vfunc< oGetTextSize >( this, 79 )( this, font, text, wide, tall );
	}
	void Fadenz( int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool bHorizontal)
	{
		typedef void(__thiscall* oDrawFilledRectFade)(PVOID,int,int,int,int,unsigned int, unsigned int, bool);
		return call_vfunc<oDrawFilledRectFade>(this,123)(this,x0,y0,x1,y1,alpha0,alpha1,bHorizontal);
	}

#define idx_surface_drawoutlinedcircle 103

	void DrawOutlinedCircle(int x, int y, int radius, int segments)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		call_vfunc<OriginalFn>(this,idx_surface_drawoutlinedcircle)(this, x, y, radius, segments);
	}

};//Size=0x0004(4)


struct model_t;

class IVModelInfo
{
public:
	const char* GetModelName(const model_t* pModel)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, const model_t*);
		return call_vfunc<OriginalFn>(this, 3)(this, pModel);
	}
};

class IClientRenderable
{
public:
	virtual void*					GetIClientUnknown() = 0;
	virtual Vector const&			GetRenderOrigin( void ) = 0;
	virtual Vector const&			GetRenderAngles( void ) = 0;
	virtual bool					ShouldDraw( void ) = 0;
	virtual bool					IsTransparent( void ) = 0;
	virtual bool					UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool					UsesFullFrameBufferTexture() = 0;
	virtual void					GetShadowHandle() const = 0;
	virtual void*					RenderHandle() = 0;
	virtual void	                GetRenderBounds( Vector& mins, Vector& maxs ) = 0;
	virtual const model_t*  GetModel( ) const = 0;
	virtual int						DrawModel( int flags ) = 0;
	virtual int						GetBody() = 0;
	virtual void					ComputeFxBlend( ) = 0;
};

class IClientNetworkable
{
public:
	virtual IClientUnknown*	GetIClientUnknown() = 0;	
	virtual void			Release() = 0;	
	virtual void*			GetClientClass() = 0;// FOR NETVARS FIND YOURSELF ClientClass* stuffs
	virtual void			NotifyShouldTransmit( /* ShouldTransmitState_t state*/ ) = 0;
	virtual void			OnPreDataChanged( /*DataUpdateType_t updateType*/ ) = 0;
	virtual void			OnDataChanged( /*DataUpdateType_t updateType*/ ) = 0;
	virtual void			PreDataUpdate( /*DataUpdateType_t updateType*/ ) = 0;
	virtual void			PostDataUpdate( /*DataUpdateType_t updateType*/ ) = 0;	
	virtual void			unknown();
	virtual bool			IsDormant( void ) = 0;
	virtual int				Index( void ) const = 0;	
	virtual void			ReceiveMessage( int classID /*, bf_read &msg*/ ) = 0;	
	virtual void*			GetDataTableBasePtr() = 0;
	virtual void			SetDestroyedOnRecreateEntities( void ) = 0;
};

class IClientUnknown
{
public:
	virtual void*		GetCollideable() = 0;
	virtual IClientNetworkable*	GetClientNetworkable() = 0;
	virtual IClientRenderable*	GetClientRenderable() = 0;
	virtual IClientEntity*		GetIClientEntity() = 0;
	virtual IClientEntity*		GetBaseEntity() = 0;
	virtual IClientThinkable*	GetClientThinkable() = 0;
};

class IClientThinkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual void*				GetThinkHandle() = 0;
	virtual void				SetThinkHandle( void* hThink ) = 0;
	virtual void				Release() = 0;
};

class __declspec ( novtable )IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
public:
	virtual void			Release( void ) = 0;
	virtual void			blahblahpad( void ) = 0;
	virtual Vector&	GetAbsOrigin( void ) const = 0;//in broken place use GetOrigin Below
	virtual const Vector&	GetAbsAngles( void ) const = 0;

	Vector GetOrigin()	
	{ 
		return *reinterpret_cast< Vector* >( ( DWORD)this + ( DWORD )0x134 );
	}
	int GetTeamNum( )		
	{ 
		return *reinterpret_cast< int* >( ( DWORD)this + ( DWORD )0xF0 );
	}
	int GetFlags()		
	{ 
		return *reinterpret_cast< int* >( ( DWORD)this + ( DWORD )0x100 );
	}
};


class IClientEntityList
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual IClientEntity *		GetClientEntity( int entnum );
	virtual IClientEntity*	GetClientEntityFromHandle( DWORD hHandle ) = 0;
	virtual int					NumberOfEntities( bool bIncludeNonNetworkable ) = 0;
	virtual int					GetHighestEntityIndex( void );
	virtual void				SetMaxEntities( int maxents );
	virtual int					GetMaxEntities( );

};

class ClientClass
{
public:
	int				m_ClassID;
	char			*m_pNetworkName;

	const char* GetName( void )
	{
		return *(char**)(this+0x8);
	}
	RecvTable* GetTable( )
	{
		return *(RecvTable**)(this+0xC);
	}
	ClientClass* NextClass( )
	{
		return *(ClientClass**)(this+0x10);
	}
	int GetClassID( void )
	{
		return *(int*)(this+0x14);
	}

	ClientClass* GetAllClasses(VOID)
	{
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
		return call_vfunc<OriginalFn>(this, 8)(this);
	}
};

class CBaseCombatWeapon
{
public:
	char			__pad[0x64];
	int				index;
	float&			GetNextPrimaryAttack();
	float&			GetAccuracyPenalty();
	int&			GetXUIDLow();
	int&			GetXUIDHigh();
	int&			GetEntityQuality();
	int&			GetAccountID();
	int&			GetItemIDHigh();
	int&			GetItemDefinitionIndex();
	int&			GetFallbackPaintKit();
	int&			GetFallbackStatTrak();
	float&			GetFallbackWear();
	bool			IsGun();
	std::string		GetWeaponName();
};

class C_BaseEntity {

public:

	int GetIndex(void)
{
	typedef int(__thiscall *GetIndex_t)(void *thisptr);
	return ((GetIndex_t)(*(DWORD*)(GetNetworkable()), 0x28))(GetNetworkable());
}

	char GetLifeState()
	{
		return *(char*)((DWORD)this + 0x25B);
	}

	void* GetNetworkable( )
	{
		typedef void*( __thiscall* oOriginal)( PVOID);
		return call_vfunc< oOriginal >( this, 4 )( this );
	}

	bool IsDormant()
	{
		typedef bool( __thiscall* oOriginal)( PVOID);
		return call_vfunc< oOriginal >( GetNetworkable(), 9 )( GetNetworkable() );
	}

	Vector GetAbsOrigin()
	{
		typedef Vector&( __thiscall* oOriginal)( PVOID);
		return call_vfunc< oOriginal >( this, 10 )( this );
	}

	Vector m_vecOrigin()
	{
		return *( Vector* )( ( DWORD )this + 0x134 );
	}

	Vector GetVelocity()
	{
		return *( Vector*)(( DWORD)this + 0x0034 + 0xC);
	}

	Vector m_vecViewOffset()
	{
		return *( Vector* )( ( DWORD )this + 0x0104 );
	}

	Vector GetEyePosition()
	{
		return *(Vector*)( ( DWORD )this + 0x104) + m_vecOrigin();
	}

	int TeamNum()
	{
		return *(int*)((DWORD)this + 0xF0);
	}

	int GetHealth()
	{
		return *(int*)((DWORD)this + 0xFC);
	}

	int GetArmor()
	{
		return *(int*)((DWORD)this + 0xAA04);
	}

	int GetFlags()//m_fFlags
	{
		return *(int*)((DWORD)this + 0x100);
	}

	int GetAccount()
	{
		return *(int*)((DWORD)this + 0x2FA8);
	}

	bool IsDefusing()
	{
		return *(bool*)((DWORD)this + 0x3894 );
	}

	bool IsTakingHostage()
	{
		return *(bool*)((DWORD)this + 0x3895 );
	}

	Vector EyeAngles()
	{
		return *(Vector*)((DWORD)this + 0xA8FC );
	}

	Vector m_aimPunchAngle()
	{
		return *(Vector*)((DWORD)this + 0x301C );
	}

	Vector m_viewPunchAngle()
	{
		return *(Vector*)((DWORD)this + 0x3010);
	}

	Vector GetEyeAngles()
	{
		return *( Vector* )( ( DWORD )this + 0xA9EC );
	}

	int m_hOwnerEntity()
	{
		return *( int* )( ( DWORD )this + 0x0148  );
	}

	int GetShotsFired()
	{
		return *(int*)((DWORD)this + 0xA2C0);
	}

	int& GetMoveType()
	{
		return(*(int*)((DWORD_PTR)this + 0x258));
	}

	bool IsPlayer()
	{
		typedef bool ( __thiscall *IsPlayer_t )(PVOID);
		return ((IsPlayer_t)(*(PDWORD)(*(PDWORD)( this ) + 0x200 )))(this);
	}
	Vector GetAbsAngles()
	{
		__asm
		{
			MOV ECX, this;
			MOV EAX, DWORD PTR DS : [ECX];
			CALL DWORD PTR DS : [EAX + 0x2C]
		}
	}

Vector C_BaseEntity::GetEstimatedAbsVelocity(void)
{

	typedef void(__thiscall *EstimateAbsVelocity_t)(void *thisptr,Vector &velocity);
	Vector velocity;
	((EstimateAbsVelocity_t)((*(DWORD*)(this), 0x234)))(this, velocity);

	return velocity;
}

};

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<2)	// player jumping out of water
#define FL_ONTRAIN				(1<<3) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<4)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<5) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<6) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<7)	// Is a player
#define FL_FAKECLIENT			(1<<8)	// Fake client, simulated server side; don't send network messages to them


#define DEFAULT_TICK_INTERVAL	(0.015)				// 15 msec is the default

#define MULTIPLAYER_BACKUP			150

class IPanel
{
public:
	const char *GetName(unsigned int vguiPanel)
	{
		typedef const char *( __thiscall* oGetName )( PVOID, unsigned int );
		return call_vfunc< oGetName >( this, 36 )( this, vguiPanel );
	}

	void PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce = true)
	{
		typedef void( __thiscall* oPaintTraverse )( PVOID, unsigned int, bool, bool );
		return call_vfunc< oPaintTraverse >( this, 41 )( this, vguiPanel, forceRepaint, allowForce );
	}
};

class CUserCmd
{
public:	
	virtual ~CUserCmd();//0x00
	int		command_number;//0x04
	int		tick_count;//0x08
	Vector viewangles;//0x0C
	Vector	aimdirection; 
	float	forwardmove; 
	float	sidemove;    
	float	upmove; 
	int		buttons; //0x30
	BYTE    impulse; //0x35
	int		weaponselect;//0x36	
	int		weaponsubtype;//0x3A
	int		random_seed; //0x3E
	short	mousedx;//0x42		
	short	mousedy;//0x43		
	bool	hasbeenpredicted; 
	Vector headangles;
	Vector	headoffset;	



	CRC32_t GetChecksum(void) const
	{
		CRC32_t crc;

		CRC32_Init(&crc);
		CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
		CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
		CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
		CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection));
		CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
		CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
		CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
		CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
		CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
		CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
		CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
		CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
		CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
		CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));      
		CRC32_Final(&crc);

		return crc;
	}


};
enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17), // OBSOLETE
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19), // OBSOLETE
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23), // OBSOLETE
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25), // OBSOLETE
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
	MATERIAL_VAR_VERTEXFOG = (1 << 31),
};

typedef unsigned short MaterialHandle_t;

class IMaterial
{
public:
	const char*     GetName()
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID);
		return call_vfunc<OriginalFn>(this, 0)(this);
	}
	const char*     GetTextureGroupName()
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID);
		return call_vfunc<OriginalFn>(this, 1)(this);
	}

	void IncrementReferenceCount()
	{
		typedef void(__thiscall* IncrementReferenceCountFn)(void*);
		call_vfunc<IncrementReferenceCountFn>(this, 14)(this);
	}

	void AlphaModulate(float alpha)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, float);
		call_vfunc<OriginalFn>(this, 27)(this, alpha);
	}
	void ColorModulate(float r, float g, float b)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, float, float, float);
		call_vfunc<OriginalFn>(this, 28)(this, r, g, b);
	}
	void SetMaterialVarFlag(MaterialVarFlags_t flag, bool on)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, MaterialVarFlags_t, bool);
		call_vfunc<OriginalFn>(this, 29)(this, flag, on);
	}
};
enum MoveType_t
{
	MOVETYPE_NONE		= 0,	// never moves
	MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,				// Player only - moving on the ground
	MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,				// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
	MOVETYPE_PUSH,				// no clip to world, push and crush
	MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,			// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

	// should always be defined as the last item in the list
	MOVETYPE_LAST		= MOVETYPE_CUSTOM,

	MOVETYPE_MAX_BITS	= 4
};

class CVerifiedUserCmd
{
public:
	CUserCmd        m_cmd;
	CRC32_t         m_crc;

};

class CInput
{
public:	
	virtual		void		Init_All( void );
	virtual		void		Shutdown_All( void );
	virtual		int			GetButtonBits( int );
	virtual		void		CreateMove ( int sequence_number, float input_sample_frametime, bool active );
	virtual		void		ExtraMouseSample( float frametime, bool active );
	virtual		bool		WriteUsercmdDeltaToBuffer( /*bf_write*/int *buf, int from, int to, bool isnewcommand );
	virtual		void		EncodeUserCmdToBuffer( /*bf_write&*/ int buf, int slot );
	virtual		void		DecodeUserCmdFromBuffer( /*bf_read&*/int buf, int slot );	
	virtual		CUserCmd	*GetUserCmd( int nSlot, int sequence_number );

	CUserCmd         *m_pCommands;
	CVerifiedUserCmd *m_pVerifiedCommands;
};

struct surfacephysicsparams_t
{
	// vphysics physical properties
	float			friction;
	float			elasticity;				// collision elasticity - used to compute coefficient of restitution
	float			density;				// physical density (in kg / m^3)
	float			thickness;				// material thickness if not solid (sheet materials) in inches
	float			dampening;
};

struct surfaceaudioparams_t
{
	// sounds / audio data
	float			reflectivity;		// like elasticity, but how much sound should be reflected by this surface
	float			hardnessFactor;	// like elasticity, but only affects impact sound choices
	float			roughnessFactor;	// like friction, but only affects scrape sound choices

	// audio thresholds
	float			roughThreshold;	// surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
	float			hardThreshold;	// surface hardness > this causes "hard" impacts, < this causes "soft" impacts
	float			hardVelocityThreshold;	// collision velocity > this causes "hard" impacts, < this causes "soft" impacts
	// NOTE: Hard impacts must meet both hardnessFactor AND velocity thresholds
};

struct surfacesoundnames_t
{
	unsigned short	stepleft;
	unsigned short	stepright;

	unsigned short	impactSoft;
	unsigned short	impactHard;

	unsigned short	scrapeSmooth;
	unsigned short	scrapeRough;

	unsigned short	bulletImpact;
	unsigned short	rolling;

	unsigned short	breakSound;
	unsigned short	strainSound;
};

struct surfacesoundhandles_t
{
	short	stepleft;
	short	stepright;

	short	impactSoft;
	short	impactHard;

	short	scrapeSmooth;
	short	scrapeRough;

	short	bulletImpact;
	short	rolling;

	short	breakSound;
	short	strainSound;
};

struct surfacegameprops_t
{
	// game movement data
	float			maxSpeedFactor;			// Modulates player max speed when walking on this surface
	float			jumpFactor;				// Indicates how much higher the player should jump when on the surface
	// Game-specific data
	unsigned short	material;

	// Indicates whether or not the player is on a ladder.
	unsigned char	climbable;
	unsigned char	pad;
};
struct surfacedata_t
{
	surfacephysicsparams_t	physics;	// physics parameters
	surfaceaudioparams_t	audio;		// audio parameters
	surfacesoundnames_t		sounds;		// names of linked sounds
	surfacegameprops_t		game;		// Game data / properties

	surfacesoundhandles_t		soundhandles;
};

class IPhysicsSurfaceProps
{
public:
	surfacedata_t *GetSurfaceData(int surfaceDataIndex)
	{
		typedef surfacedata_t*(__thiscall* OriginalFn)(PVOID, int);
		return call_vfunc<OriginalFn>(this, 5)(this, surfaceDataIndex);
	}
};

struct Ray_t
{
	VectorAligned   m_Start;
	VectorAligned   m_Delta;
	VectorAligned   m_StartOffset;
	VectorAligned   m_Extents;

	const   matrix3x4* m_pWorldAxisTransform;

	bool    m_IsRay;
	bool    m_IsSwept;

	Ray_t( ) : m_pWorldAxisTransform( NULL ) { }
};

struct cplane_t
{
	Vector  normal;
	float   dist;
	BYTE    type;
	BYTE    signbits;
	BYTE    pad[2];
};

class CBaseTrace
{
public:
	Vector                  startpos;
	Vector                  endpos;
	cplane_t                plane;
	float                   fraction;
	int                             contents;
	unsigned short  dispFlags;
	bool                    allsolid;
	bool                    startsolid;
};

struct csurface_t
{
	const char*             name;
	short                   surfaceProps;
	unsigned short  flags;
};

class CGameTrace : public CBaseTrace
{
public:
	bool                    DidHitWorld( ) const;
	bool                    DidHitNonWorldEntity( ) const;
	int                             GetEntityIndex( ) const;
	bool                    DidHit( ) const;
public:
	float                   fractionleftsolid;
	csurface_t              surface;
	int                             hitgroup;
	short                   physicsbone;
	unsigned short  worldSurfaceIndex;
	C_BaseEntity*               m_pEnt;
	int                             hitbox;
};

inline bool CGameTrace::DidHit( ) const
{
	return fraction < 1.0f || allsolid || startsolid;
}

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

typedef CGameTrace trace_t;

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(C_BaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}
	virtual TraceType_t	GetTraceType()
	{
		return TRACE_EVERYTHING;
	}
	void* pSkip;
};

class CTraceFilter : public ITraceFilter
{
public:
	virtual bool ShouldHitEntity(C_BaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
	void* pSkip;
};
class CSimpleTraceFilter : public ITraceFilter
{
public:
	CSimpleTraceFilter(PVOID pEnt)
	{
		m_pPassEnt = pEnt;
	}

	virtual bool ShouldHitEntity( IHandleEntity *pHandleEntity, int contentsMask )
	{
		return pHandleEntity != m_pPassEnt;
	}

	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	PVOID m_pPassEnt;
};
class CTraceFilterNoPlayer : public CTraceFilter
{
public:
	CTraceFilterNoPlayer() {}

	virtual bool ShouldHitEntity( IHandleEntity *pServerEntity, int contentsMask )
	{
		IClientUnknown *pUnk = (IClientUnknown*)pServerEntity;
		C_BaseEntity *pEnt = (C_BaseEntity *)pUnk->GetBaseEntity();
		return !pEnt->IsPlayer();
	}
};
class IEngineTrace
{
public:
	void TraceRay( const Ray_t& ray, unsigned int flMask, ITraceFilter* pTraceFilter, trace_t* pTrace )
	{
		typedef void ( __thiscall* TraceRayFn )( PVOID, const Ray_t&, unsigned int, ITraceFilter*, trace_t* );
		call_vfunc<TraceRayFn>( this, 5 )( this, ray, flMask, pTraceFilter, pTrace );
	}

	int GetPointContents( const Vector &vecAbsPosition, IHandleEntity** ppEntity = NULL )
	{
		typedef int(__thiscall* OriginalFn)(PVOID, const Vector &, IHandleEntity**);
		return call_vfunc<OriginalFn>(this, 0)(this, vecAbsPosition, ppEntity);
	}
};

typedef ITraceFilter gtrace;


class IVDebugOverlay
{
public:

	virtual void AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b,bool noDepthTest, float duration) = 0;
	virtual void AddSweptBoxOverlay(const Vector& start, const Vector& end, const Vector& mins, const Vector& max, const Vector & angles, int r, int g, int b, int a, float flDuration) = 0;

};

enum ShaderStencilOp_t
{
#if !defined( _X360 )
    SHADER_STENCILOP_KEEP = 1,
    SHADER_STENCILOP_ZERO = 2,
    SHADER_STENCILOP_SET_TO_REFERENCE = 3,
    SHADER_STENCILOP_INCREMENT_CLAMP = 4,
    SHADER_STENCILOP_DECREMENT_CLAMP = 5,
    SHADER_STENCILOP_INVERT = 6,
    SHADER_STENCILOP_INCREMENT_WRAP = 7,
    SHADER_STENCILOP_DECREMENT_WRAP = 8,
#else
    SHADER_STENCILOP_KEEP = D3DSTENCILOP_KEEP,
    SHADER_STENCILOP_ZERO = D3DSTENCILOP_ZERO,
    SHADER_STENCILOP_SET_TO_REFERENCE = D3DSTENCILOP_REPLACE,
    SHADER_STENCILOP_INCREMENT_CLAMP = D3DSTENCILOP_INCRSAT,
    SHADER_STENCILOP_DECREMENT_CLAMP = D3DSTENCILOP_DECRSAT,
    SHADER_STENCILOP_INVERT = D3DSTENCILOP_INVERT,
    SHADER_STENCILOP_INCREMENT_WRAP = D3DSTENCILOP_INCR,
    SHADER_STENCILOP_DECREMENT_WRAP = D3DSTENCILOP_DECR,
#endif
    SHADER_STENCILOP_FORCE_DWORD = 0x7fffffff
};

enum ShaderStencilFunc_t
{
#if !defined( _X360 )
    SHADER_STENCILFUNC_NEVER = 1,
    SHADER_STENCILFUNC_LESS = 2,
    SHADER_STENCILFUNC_EQUAL = 3,
    SHADER_STENCILFUNC_LEQUAL = 4,
    SHADER_STENCILFUNC_GREATER = 5,
    SHADER_STENCILFUNC_NOTEQUAL = 6,
    SHADER_STENCILFUNC_GEQUAL = 7,
    SHADER_STENCILFUNC_ALWAYS = 8,
#else
    SHADER_STENCILFUNC_NEVER = D3DCMP_NEVER,
    SHADER_STENCILFUNC_LESS = D3DCMP_LESS,
    SHADER_STENCILFUNC_EQUAL = D3DCMP_EQUAL,
    SHADER_STENCILFUNC_LEQUAL = D3DCMP_LESSEQUAL,
    SHADER_STENCILFUNC_GREATER = D3DCMP_GREATER,
    SHADER_STENCILFUNC_NOTEQUAL = D3DCMP_NOTEQUAL,
    SHADER_STENCILFUNC_GEQUAL = D3DCMP_GREATEREQUAL,
    SHADER_STENCILFUNC_ALWAYS = D3DCMP_ALWAYS,
#endif

    SHADER_STENCILFUNC_FORCE_DWORD = 0x7fffffff
};

#if defined( _X360 )
enum ShaderHiStencilFunc_t
{
    SHADER_HI_STENCILFUNC_EQUAL = D3DHSCMP_EQUAL,
    SHADER_HI_STENCILFUNC_NOTEQUAL = D3DHSCMP_NOTEQUAL,

    SHADER_HI_STENCILFUNC_FORCE_DWORD = 0x7fffffff
};
#endif
struct ShaderStencilState_t
{
    bool m_bEnable;
    ShaderStencilOp_t m_FailOp;
    ShaderStencilOp_t m_ZFailOp;
    ShaderStencilOp_t m_PassOp;
    ShaderStencilFunc_t m_CompareFunc;
    int m_nReferenceValue;
    uint32_t m_nTestMask;
    uint32_t m_nWriteMask;

#if defined( _X360 )
    bool m_bHiStencilEnable;
    bool m_bHiStencilWriteEnable;
    ShaderHiStencilFunc_t m_HiStencilCompareFunc;
    int m_nHiStencilReferenceValue;
#endif

    ShaderStencilState_t()
    {
        m_bEnable = false;
        m_PassOp = m_FailOp = m_ZFailOp = SHADER_STENCILOP_KEEP;
        m_CompareFunc = SHADER_STENCILFUNC_ALWAYS;
        m_nReferenceValue = 0;
        m_nTestMask = m_nWriteMask = 0xFFFFFFFF;

#if defined( _X360 )
        m_bHiStencilEnable = false;
        m_bHiStencilWriteEnable = false;
        m_HiStencilCompareFunc = SHADER_HI_STENCILFUNC_EQUAL;
        m_nHiStencilReferenceValue = 0;
#endif
    }
};
#define VirtualFn( cast )typedef cast( __thiscall* OriginalFn )

class CMaterialSystem
{
public:
	IMaterial* CreateMaterial(const char* pMaterialName)
	{
		VirtualFn(IMaterial*)(PVOID, const char*);
		return call_vfunc< OriginalFn >(this, 83)(this, pMaterialName);
	}
	IMaterial* FindMaterial(const char* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = 0)
	{
		VirtualFn(IMaterial*)(PVOID, const char*, const char*, bool, const char*);
		return call_vfunc< OriginalFn >(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}
	MaterialHandle_t FirstMaterial()
	{
		VirtualFn(MaterialHandle_t)(PVOID);
		return call_vfunc< OriginalFn >(this, 86)(this);
	}
	MaterialHandle_t NextMaterial(MaterialHandle_t h)
	{
		VirtualFn(MaterialHandle_t)(PVOID, MaterialHandle_t);
		return call_vfunc< OriginalFn >(this, 87)(this, h);
	}
	MaterialHandle_t InvalidMaterial()
	{
		VirtualFn(MaterialHandle_t)(PVOID);
		return call_vfunc< OriginalFn >(this, 88)(this);
	}
	IMaterial* GetMaterial(MaterialHandle_t h)
	{
		VirtualFn(IMaterial*)(PVOID, MaterialHandle_t);
		return call_vfunc< OriginalFn >(this, 89)(this, h);
	}
	int	GetNumMaterials()
	{
		VirtualFn(int)(PVOID);
		return call_vfunc< OriginalFn >(this, 90)(this);
	}
    void SetStencilState(const ShaderStencilState_t &state)
    {
        typedef void(__thiscall* OriginalFn)(void*, const ShaderStencilState_t&);
        call_vfunc<OriginalFn>(this, 127)(this, state);
    }
};

extern IBaseClientDLL*			pClient				;
extern IVEngineClient*			pEngine				;
extern IPanel*					pPanel				;
extern IClientEntityList*		pClientEntList		;
extern ISurface*				pSurface			;
extern CGlobalVarsBase*		    pGlobals			;
extern IEngineTrace*			pEngineTrace		;
extern CInput*                  pInput              ;
extern IVModelInfo*             pModelInfo          ;
extern IClientNetworkable*      pClientNetworkable  ;
extern IVDebugOverlay*          pDebugOverlay       ;
extern CBaseCombatWeapon*       pCombatWeapon       ;
extern IPhysicsSurfaceProps*	pPhysics			;
extern ConVar*                  gCvars              ;
extern CMaterialSystem*			pMaterialSystem		;
extern ClientClass*				pClass;


extern unsigned long			WaterMarkfont		;
extern unsigned long			MenuTitleFont		;
extern unsigned long			MenuCheckboxFont	;
extern unsigned long			MenuButtonFont		;
extern unsigned long			MenuButtonToggledFont ;
extern unsigned long			MenuTabFont			;
extern unsigned long			MenuTabselectedFont ;
extern unsigned long			PlusMinusArrowfont  ;
extern unsigned long			PlusMinusfont		;
extern unsigned long            EspFont             ;
extern unsigned long			RadarEspFont		;
#endif