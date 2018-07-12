//#include "Radar.h"
//
//cRadar Radar;
//
//
//void DrawGrid(int x,int y,int w,int h,int size,Color color,Color color2){
//	int s	= size;
//	int s1	= s+1;
//	int s2	= s-1;
//	for(int v=x;v<=x+w-s2;v+=s1){
//		cDraw.FillRGBA(  v, y, s, h,color);
//		cDraw.FillRGBA(v+s, y, s, h,color2);
//	}
//	for(int v=y;v<=y+h-s2;v+=s1){
//		cDraw.FillRGBA(x,  v, w, s,color);
//		cDraw.FillRGBA(x,v+s, w, s,color2);
//	}
//}
//
////float Radarx = pCvars.Radar_PosX+pCvars.Radar_PosW /2, Radary = pCvars.Radar_PosY+pCvars.Radar_PosH /2;
//
//void cRadar::DrawPoint(Vector vOriginx,Vector vOriginy,Vector vAngle,Color iTeam,player_info_t pInfo,int health){
//
//	if(!pCvars.Radar)
//		return;
//
//	float vOrx = vOriginx.x- vOriginy.x;
//	float vOry = vOriginx.y- vOriginy.y;
//
//	float flAngle = vAngle.y;
//
//	float yaw = (flAngle) * (M_PI/180.0);
//
//	float mainViewAngles_CosYaw = cos(yaw);
//	float mainViewAngles_SinYaw = sin(yaw);
//
//	float x =  vOry*(-mainViewAngles_CosYaw)  + vOrx*mainViewAngles_SinYaw;
//	float y =  vOrx*(-mainViewAngles_CosYaw)  - vOry*mainViewAngles_SinYaw;
//
//	float range = 30 * 30;
//
//	if(fabs(x)>range || fabs(y)>range)
//	{ 
//		if(y>x)
//		{
//			if(y>-x) {
//				x = range*x/y;
//				y = range;
//			}  else  {
//				y = -range*y/x; 
//				x = -range; 
//			}
//		} else {
//			if(y>-x) {
//				y = range*y/x; 
//				x = range; 
//			}  else  {
//				x = -range*x/y;
//				y = -range;
//			}
//		}
//	}
//	int ScreenX = Radarx + int( x/range*float(90));
//	int ScreenY = Radary + int( y/range*float(90));
//	cDraw.FillRGBA( ScreenX-1, ScreenY-1,6,6, iTeam);
//	cDraw.OutlinedRect(ScreenX-1, ScreenY-1,6,6, Color(0,0,0,255));
//
//	if(pCvars.Radar_Name)
//		cDraw.DrawString(RadarEspFont,true,ScreenX,ScreenY+10,Color(255,255,255,255),pInfo.name);
//
//	if(pCvars.Radar_Health)
//		cDraw.NormalTextCent(true,RadarEspFont,ScreenX,ScreenY+20,Color(255,255,255,255),"%i",health);
//}
//
//void cRadar::DrawRadar(int x,int y,int w,int h,char* title){
//
//	if(!pCvars.Radar)
//		return;
//
//	pMenu.ExtraWindow(x,y,w,h,title);
//	cDraw.DrawLine(x+5,y+5,x+w/2,y+h/2,Color(0,0,0,255));//FOV Lines
//	cDraw.DrawLine(x+w-5,y+5,x+w/2,y+h/2,Color(0,0,0,255)); // FOV Lines
//
//	cDraw.FillRGBA(x+w/2-3,y+h/2-3,6,6,Color(0,255,0,255)); //Player Square
//	cDraw.OutlinedRect(x+w/2-3,y+h/2-3,6,6, Color(0,0,0,255));//Player Square Outline
//
//	if(aMouse.LeftClick(x+w-23,y-25,23,23))
//		pCvars.RadarOptions=!pCvars.RadarOptions;
//}
//
