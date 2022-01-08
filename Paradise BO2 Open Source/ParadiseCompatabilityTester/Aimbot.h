bool canUseAutowall() {
	if (autowallEnabled == false)
		return false;
	//if (allowAutowall == false)
		//return false;
	return true;
}

int Centity(int ClientIndex)
{
	return *(int*)(0xE22F20) + (ClientIndex * 0x374);
}

opd_s GetWeaponDef_t = {0x00606F08,TOC};
int(*GetWeaponDef)(int weapon) = (int(*)(int))&GetWeaponDef_t;

opd_s GetSpreadForWeapon_t = {0x005F09C8,TOC};
void(*GetSpreadForWeapon)(int playerstate,int weaponid,float *min, float *max) = (void(*)(int,int,float*,float*))&GetSpreadForWeapon_t;
#include "aw.h"

int cg_t(int Mod)
{
	return *(int*)(addresses.GLOBAL_CGAME_PTR_ADD/*0xE22F18*/) + Mod;
}
typedef float vec3_t[3];
Vector3 GetTagPos(int targEnt, const char *tagName)
{
	float out[3];
	AimTarget_GetTagPos(Centity(targEnt), SL_GetString(tagName), out);
	return Vector3(out[0], out[1], out[2]);
}
float outTMPTAGPOS[3];
float *GetTagPosFloat(int targEnt, const char *tagName)
{
	AimTarget_GetTagPos(Centity(targEnt), SL_GetString(tagName), outTMPTAGPOS);
	return outTMPTAGPOS;
}

int ClientActive(int Mod)
{
	return Mod + *(int*)addresses.GLOBAL_CLIENT_PTR_ADD/*0xD689D8*/;
}

Vector3 GetPlayerOrigin(int index)
{
	return *(Vector3*)(Centity(index) + 0x168);
}
float *GetPlayerOriginFloat(int index)
{
	return (float*)(Centity(index) + 0x168);
}

float *getMyRefDef() {
	return (float*)&(Get_cgs()->refdef.viewOrigin);
}

int ClientInfo(int Index, int Mod)
{
	return (cg_t(0)) + 0x69DA0 + (Index * 0x808) + Mod;
}

char *tagList[] = {"j_head",
"j_neck",
"j_spine4",
"back_mid",
"back_low",
"torso_stabilizer",
"pelvis",
"j_mainroot",
"j_wrist_ri",
"j_wrist_le",
"j_elbow_ri",
"j_elbow_le",
"j_shoulder_ri",
"j_shoulder_le",
"j_ankle_ri",
"j_ankle_le",
"j_knee_ri",
"j_knee_le",
"tag_weapon_right",
"tag_weapon_left"};
int playerTags[18];
void setPlayerTag(int player, int tag) {
	playerTags[player] = tag%20;
}
int getPlayerTag(int player) {
	return playerTags[player];
}
char *getTagInList(int tag) {
	return tagList[tag];
}
int nearestClient;
char *bestTag = "";
int GetNearestPlayer(int Client)
{
	bestTag = TagOrigin;
	nearestClient = -1;
	float nearestDistance = 99999999;
	for (int i = 0; i < 18; ++i)
	{
		if (i != Client)
		{
			if (!CG_IsEntityFriendlyNotEnemy(0, Centity(i)))
			{
				if (!*(bool*)ClientInfo(i, 0x8F))
				{
					if (*(int*)ClientInfo(i, 0x0C) > 0 && *(int*)(Centity(i)+0x2B4) != 0x59/*assault shield*/)
					{
						float Distance = Distance3D(GetPlayerOrigin(Client), GetPlayerOrigin(i));
							if (Distance < nearestDistance)
							{
						if ((AimTarget_isTargetVisible(0, Centity(i)) && Stealth))
						{
							//float Distance = Distance3D(GetPlayerOrigin(Client), GetPlayerOrigin(i));
							//if (Distance < nearestDistance)
							//{
								nearestDistance = Distance;
								nearestClient = i;
								ClientReady = true;
							//}
						}
						else if (!Stealth)
						{
							//float Distance = Distance3D(GetPlayerOrigin(Client), GetPlayerOrigin(i));
							//if (Distance < nearestDistance)
							//{
								nearestDistance = Distance;
								nearestClient = i;
								ClientReady = true;
							//}
						}
						else if (autowallEnabled != 0) {
							int tag = getPlayerTag(i);
							if (autowallEnabled == 2) {//experimental
								//for (int ti = 0; ti < 20; ti++) {
									bestTag = getTagInList(tag);
									if (autowall::isTargetHitable(getMyRefDef(), GetTagPosFloat(i, bestTag),i)/*autowall::GetAutoWallDamageMultiplier(getMyRefDef(), GetTagPosFloat(i, TagOrigin)) > 0.9f*/) {
										//float Distance = Distance3D(GetPlayerOrigin(Client), GetPlayerOrigin(i));
										//if (Distance < nearestDistance)
										//{
										nearestDistance = Distance;
										nearestClient = i;
										ClientReady = true;
										//break;
										//}
									} else {
										setPlayerTag(i,tag+1);
									}
								//}
							}
							else if(autowallEnabled == 3) {//super
								for (int ti = 0; ti < 20; ti++) {
									bestTag = getTagInList(ti);
									if (autowall::isTargetHitable(getMyRefDef(), GetTagPosFloat(i, bestTag),i)/*autowall::GetAutoWallDamageMultiplier(getMyRefDef(), GetTagPosFloat(i, TagOrigin)) > 0.9f*/) {
										nearestDistance = Distance;
										nearestClient = i;
										ClientReady = true;
										break;
									}
								}
							}
							else {//stable aka 1
								if (autowall::isTargetHitable(getMyRefDef(), GetTagPosFloat(i, TagOrigin),i)/*autowall::GetAutoWallDamageMultiplier(getMyRefDef(), GetTagPosFloat(i, TagOrigin)) > 0.9f*/) {
										//float Distance = Distance3D(GetPlayerOrigin(Client), GetPlayerOrigin(i));
										//if (Distance < nearestDistance)
										//{
										nearestDistance = Distance;
										nearestClient = i;
										ClientReady = true;
										//}
									}
							}
						}
							}
					}
				}
			}
		}
	}
	TagOrigin = bestTag;
	return nearestClient;
}

bool WorldPosToScreenPos_r(int Entity, float* x, float* y, char *tag = "j_neck")
{
	//0x10024000 is ok because allocations start at 0x10026000
	*(Vector3*)0x10024000 = GetTagPos(Entity, tag);
	__asm(
	"li %r3, 0;"
		"lis %r4, 0x1002;"
		"ori %r4, %r4, 0x4000;"
		"lis %r5, 0x1002;"
		"ori %r5, %r5, 0x5000;"
		"lis %r11, 0x5;"
		"ori %r11, %r11, 0xA480;"
		"mtctr %r11;"
		"bctrl;"
		"mr %r8, %r3;"
		);
	*x = *(float*)0x10025000;
	*y = *(float*)0x10025004;
	__asm("mr %r3, %r8");

}

bool WorldPosToScreenPos_r(Vector3 pos, float* x, float* y)
{
	*(float*)(0x10024000) = pos.x;
	*(float*)(0x10024004) = pos.y;
	*(float*)(0x10024008) = pos.z;
	__asm(
	"li %r3, 0;"
		"lis %r4, 0x1002;"
		"ori %r4, %r4, 0x4000;"
		"lis %r5, 0x1002;"
		"ori %r5, %r5, 0x5000;"
		"lis %r11, 0x5;"
		"ori %r11, %r11, 0xA480;"
		"mtctr %r11;"
		"bctrl;"
		"mr %r8, %r3;"
		);
	*x = *(float*)0x10025000;
	*y = *(float*)0x10025004;
	__asm("mr %r3, %r8");

}

void renderESP(int Client) {
	float cx = getScreenPercentX(0.5f);
	float cy = getScreenPercentY(0.5f);
	for (int i = 0; i < 18; ++i) {
		if (i != Client) {
			if (!CG_IsEntityFriendlyNotEnemy(0, Centity(i))) {//is enemy
				if (!*(bool*)ClientInfo(i, 0x8F)) {
					if (*(int*)ClientInfo(i, 0x0C) > 0) {
						//float x,y;
						float hx,hy;
						float rx,ry;
						float mcx,mcy;
						//float lx,ly;
						if (WorldPosToScreenPos_r(i,&hx,&hy,"j_helmet") && WorldPosToScreenPos_r(i,&rx,&ry,"j_ankle_ri") && WorldPosToScreenPos_r(i,&mcx,&mcy,"j_mainroot")) {
							int maxy = ry;
							int miny = hy;
							int sizey = myMath::abs(ry-hy);
							int sizex = sizey/2;//cuz why not
							int minx = hx - sizex/2;
							if (AimTarget_isTargetVisible(0, Centity(i))) {
								//color blue
								if(ESP)
									DrawShader(minx,miny,sizex,sizey,colors::LightBlueOpaque,"white");
								if(SNAPLINES)
									DrawLine1(cx,cy,mcx,mcy,colors::LightBlueOpaque);
							} else {
								//color red
								if(ESP)
									DrawShader(minx,miny,sizex,sizey,colors::RedOpaque,"white");
								if(SNAPLINES)
									DrawLine1(cx,cy,mcx,mcy,colors::RedOpaque);
							}
						}
					}
				}
			}
		}
	}
}





//#include "autowall.h"

#define ANGLE2SHORT(x)   ((int)((x)*65536/360) & 65535)
float normalize180(float num) {
	while (num < -180)
		num+=360;
	while (num > 180)
		num-=360;
	return num;
}
float normalize90(float num) {
	while (num < -90)
		num+=180;
	while (num > 90)
		num-=180;
	if (num > 89)
		num = 88;
	if (num < -89)
		num = -88;
	return num;
}

opd_s clcnc = {0x00105244,TOC};
int(*CL_CreateNewCommands)(int localClientNum) = (int(*)(int))&clcnc;
opd_s clwp = {0x00116524,TOC};
int(*CL_WritePacket)(int localClientNum) = (int(*)(int))&clwp;
int hkCL(int r3);
int clcnc_redo(int r3) {//bo2: 0x00105244
	char bytes[16] = {0xF8, 0x21, 0xFF, 0x41, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x01, 0x00, 0xD0, 0x1C, 0x83, 0x04, 0x58};
	write_process((void*)0x00105244,bytes,16);
	int j = CL_CreateNewCommands(r3);
	PatchInJump(0x00105244,(int)hkCL,false);
	return j;
}
int wp_redo(int r3, int howManyTimes = 0) {//bo2: 0x00116524
	char bytes[16] = {0xF8, 0x21, 0xF6, 0xC1, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x01, 0x09, 0x50, 0xFB, 0x41, 0x09, 0x10};
	write_process((void*)0x00116524,bytes,16);
	int j = 0;//CL_WritePacket(r3);
	for (int i = 0; i < howManyTimes; i++)
		j = CL_WritePacket(r3);
	PatchInJump(0x00116524,(int)hkCL,false);
	return j;
}

void AntiAimCmd(CCommand* c)//idk if this works lol
{
    c->buttons &= ~(1<<28);
    c->buttons &= ~(1<<11);
}


/*void BG_seedRandWithGameTime(int *pHoldrand)
{
	*pHoldrand ^= *(char *)pHoldrand << 8;
	*pHoldrand = *pHoldrand ^ ((*(char *)pHoldrand << 8) << 8) ^ ((*(char *)pHoldrand << 8) << 16);
}*/

void SinCos(float num, float *sin, float *cos) {
	*sin = myMath::sin(num);
	*cos = myMath::cos(num);
}
void AngleVectors( Vector3 *angles, Vector3 *forward, Vector3 *right, Vector3 *up )
{
	float sr, sp, sy, cr, cp, cy;
	SinCos(angles->y, &sy, &cy );
	SinCos(angles->x, &sp, &cp );
	SinCos(angles->z, &sr, &cr );
	//printf("sr %i, sp %i, sy %i, cr %i, cp %i, cy %i\n", (int)(sr*100),(int)(sp*100),(int)(sy*100),(int)(cr*100),(int)(cp*100),(int)(cy*100));
	//if (forward)
	//{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	//}
 
	//if (right)
	//{
		right->x = (-1*sr*sp*cy+-1*cr*-sy);
		right->y = (-1*sr*sp*sy+-1*cr*cy);
		right->z = -1*sr*cp;
	//}
 
	//if (up)
	//{
		up->x = (cr*sp*cy+-sr*-sy);
		up->y = (cr*sp*sy+-sr*cy);
		up->z = cr*cp;
	//}
}

void VectorAnglessss(Vector3 *dir, Vector3 *save) {
	float forward;
	float yaw, pitch;
	if (dir->x == 0 && dir->y == 0)
	{
		yaw = 0;
		if (dir->z > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else
	{
		if (dir->x != -1) yaw = (float)(myMath::atan2((double)dir->y, (double)dir->x) * 180.00 / PI);
		else if (dir->y > 0) yaw = 90.00;
		else yaw = 270;
		if (yaw < 0) yaw += 360.00;
		forward = (float)sqrt((double)(dir->x * dir->x + dir->y * dir->y));
		pitch = (float)(myMath::atan2((double)dir->z, (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}
	save->x = -pitch;
	save->y = yaw;
	save->z = 0;
}
#define SHORT2ANGLE(x)  ((x)*(360.0/65536))
void GetMovementFix(unsigned int state, float oForwardMove, float oSideMove, CCommand *cmd)
    {
        //fix movement Q_Q
        switch (state)
        {
        case 0:
        case 1:
            if (cmd->forwardmove == 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->forwardmove = 0;
                    cmd->sidemove = 0;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->forwardmove = 450;
                    cmd->sidemove = -450;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->forwardmove = -450;
                    cmd->sidemove = 450;
                }
            }
            else if (cmd->forwardmove < 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->forwardmove = -450;
                    cmd->sidemove = -450;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->forwardmove = 0;
                    cmd->sidemove = -450;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->forwardmove = -450;
                    cmd->sidemove = 0;
                }
            }
            else if (cmd->forwardmove > 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->forwardmove = 450;
                    cmd->sidemove = 450;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->forwardmove = 450;
                    cmd->sidemove = 0;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->forwardmove = 0;
                    cmd->sidemove = 450;
                }
            }
        case 2:
            cmd->forwardmove = -oSideMove;
            cmd->sidemove = oForwardMove;
        case 3:
            if (cmd->forwardmove == 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->sidemove = 0;
                    cmd->forwardmove = 0;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->sidemove = 450;
                    cmd->forwardmove = 450;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->sidemove = -450;
                    cmd->forwardmove = -450;
                }
            }
            else if (cmd->forwardmove < 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->sidemove = -450;
                    cmd->forwardmove = 450;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->sidemove = 0;
                    cmd->forwardmove = 450;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->sidemove = -450;
                    cmd->forwardmove = 0;
                }
            }
            else if (cmd->forwardmove > 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->sidemove = 450;
                    cmd->forwardmove = -450;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->sidemove = 450;
                    cmd->forwardmove = 0;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->sidemove = 0;
                    cmd->forwardmove = -450;
                }
            }
            break;
        case 4:
            cmd->forwardmove = -oForwardMove;
            cmd->sidemove = -oSideMove;
            break;
        case 5:
            if (cmd->forwardmove == 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->forwardmove = 0;
                    cmd->sidemove = 0;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->forwardmove = -450;
                    cmd->sidemove = 450;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->forwardmove = 450;
                    cmd->sidemove = -450;
                }
            }
            else if (cmd->forwardmove < 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->forwardmove = 450;
                    cmd->sidemove = 450;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->forwardmove = 0;
                    cmd->sidemove = 450;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->forwardmove = 450;
                    cmd->sidemove = 0;
                }
            }
            else if (cmd->forwardmove > 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->forwardmove = -450;
                    cmd->sidemove = -450;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->forwardmove = -450;
                    cmd->sidemove = 0;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->forwardmove = 0;
                    cmd->sidemove = -450;
                }
            }
            break;
        case 6:
            cmd->forwardmove = oSideMove;
            cmd->sidemove = -oForwardMove;
            break;
        case 7://originally 6. Changed to 7
            if (cmd->forwardmove == 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->sidemove = 0;
                    cmd->forwardmove = 0;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->sidemove = -450;
                    cmd->forwardmove = -450;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->sidemove = 450;
                    cmd->forwardmove = 450;
                }
            }
            else if (cmd->forwardmove < 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->sidemove = 450;
                    cmd->forwardmove = -450;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->sidemove = 0;
                    cmd->forwardmove = -450;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->sidemove = 450;
                    cmd->forwardmove = 0;
                }
            }
            else if (cmd->forwardmove > 0)
            {
                if (cmd->sidemove == 0)
                {
                    cmd->sidemove = -450;
                    cmd->forwardmove = 450;
                }
                else if (cmd->sidemove < 0)
                {
                    cmd->sidemove = -450;
                    cmd->forwardmove = 0;
                }
                else if (cmd->sidemove > 0)
                {
                    cmd->sidemove = 0;
                    cmd->forwardmove = 450;
                }
            }
            break;
        }
    }

void doSilentAim() {

	/*if ((!(cmd->buttons & IN_ATTACK) || (cmd->buttons & IN_ATTACK && BaseWeapon->NextPrimaryAttack() > flServerTime &&
    !CBaseWeapon::IsWeaponNonAim(BaseWeapon->GetWeaponID())))
    && !(cmd->buttons & IN_USE))
{
    Vector spinAngles = viewAnglesCopy;
 
    spinAngles.y += 45 * (state % 8);
    cmd->viewangles = Vector::ClampAngle(spinAngles);
 
    g_pMISC->GetMovementFix(state % 8, oForwardMove, oSideMove, cmd);
 
    state++;
}*/
	


	int wepid = *(int*)(Centity(Get_cgs()->localIndex)+0x2B4);
	float spread, minSpread, maxSpread;
	CCommand* cmd = &client_get()->input.commands[client_get()->input.currentIdx&0x7F];
	CCommand* oldcmd = &client_get()->input.commands[(client_get()->input.currentIdx-1)&0x7F];
	int playerstate = addresses.playerstate/*0x03780EA28*/;
	float aimRatio_a = *(float*)0x03780EC08;//0 is not aiming. 1.0 is aimed all the way
	if (aimRatio_a == 1.0f)
		return;
	int weaponDefPtr = GetWeaponDef(wepid);
	spread = Get_cgs()->spreadMult * 0.0039215689;
	GetSpreadForWeapon(playerstate,wepid,&minSpread,&maxSpread);
	spread = minSpread + ((maxSpread - minSpread) * spread);
	int iCurrentTime = *(int*)playerstate;
	opd_s BG_seedRandWithGameTime_t = {addresses.BG_seedRandWithGameTime/*0x005D6C54*/,TOC};
	void(*BG_seedRandWithGameTime)(int *save) = (void(*)(int *))&BG_seedRandWithGameTime_t;
	BG_seedRandWithGameTime(&iCurrentTime);
	Vector3 viewAngles,spreadEndVec;
	float range = 8192.0f;
	Vector3 viewAxis[3];
	vec3_t spreadDirection;
	AngleVectors(&AimAngles, &(viewAxis[0]), &(viewAxis[1]), &(viewAxis[2]));
	opd_s CG_BulletEndposition_t = {addresses.CG_BulletEndposition/*0x000EBB48*/,TOC};
	void(*CG_BulletEndposition)(int *seed,float spread,Vector3 *start,Vector3 *end,vec3_t *dir,Vector3 *forwdir, Vector3 *rightdir, Vector3 *updir, float range) = (void(*)(int*,float,Vector3*,Vector3*,vec3_t *,Vector3*,Vector3*,Vector3*,float))&CG_BulletEndposition_t;
	CG_BulletEndposition(&iCurrentTime, spread, &Get_cgs()->refdef.viewOrigin,&spreadEndVec, &spreadDirection,&viewAxis[0], &viewAxis[1], &viewAxis[2], range);
	Vector3 tmp = Difference(spreadEndVec, Get_cgs()->refdef.viewOrigin);
	VectorAnglessss(&tmp,&viewAngles);
	oldcmd->viewAngles.x += ANGLE2SHORT(/*AimAngles.x+*/(AimAngles.x - viewAngles.x));
	oldcmd->viewAngles.y += ANGLE2SHORT(/*AimAngles.y+*/(AimAngles.y - viewAngles.y));
}

/*
//basic silent aim for reference
void DoSilentAim(bool bAdjust)
{
	CCommand* cmd = &client_get()->input.commands[client_get()->input.currentIdx&0x7F];
	CCommand* oldcmd = &client_get()->input.commands[(client_get()->input.currentIdx-1)&0x7F];

    if (bAdjust) {
		oldcmd->time+=2;// = getServerTime()-1;
		int x = ANGLE2SHORT(normalize90(AimAngles.x));
		int y = ANGLE2SHORT(normalize180(AimAngles.y));

        oldcmd->viewAngles.x = x;
        oldcmd->viewAngles.y = y;

		NoSpread(oldcmd);

		//oldcmd->buttons &= ~(1<<31);//unshoot
		if(autoShoot)
			cmd->buttons |= (1<<31);//shoot    oldcmd does not work
    }
}*/
float AngleNormalize360(float angle) {
	return (360.0 / 65536) * ((int)(angle * (65536 / 360.0)) & 65535);
}
void fixWalking() {
	CCommand* cmd = &client_get()->input.commands[client_get()->input.currentIdx&0x7F];
	CCommand* oldcmd = &client_get()->input.commands[(client_get()->input.currentIdx-1)&0x7F];
	int forwardmove = cmd->forwardmove;
	int rightmove = cmd->sidemove;
					
					if ( forwardmove != 0 || rightmove != 0 )
					{
						float move_angle = AngleNormalize360( myMath::atan2( -rightmove / 127.0, forwardmove / 127.0 ) );
						float delta_angle = 0;//AngleNormalize360( AimAngles.y - ( game_->GetCG( )->predictedPlayerState.viewangles[ 1 ] - SHORT2ANGLE( game_->GetCG( )->predictedPlayerState.delta_angles[ 1 ] ) ) );
						float destination_angle = AngleNormalize360( move_angle - delta_angle );
						float forwardmove_ratio = myMath::cos( destination_angle  );
						float rightmove_ratio = -myMath::sin( destination_angle  );
 
						if ( myMath::abs( forwardmove_ratio ) < myMath::abs( rightmove_ratio ) )
						{
							forwardmove_ratio *= 1.0 / myMath::abs( rightmove_ratio );
							rightmove_ratio = rightmove_ratio > 0.0 ? 1.0 : -1.0;
						}
						else if ( myMath::abs( forwardmove_ratio ) > myMath::abs( rightmove_ratio ) )
						{
							rightmove_ratio *= 1.0 / myMath::abs( forwardmove_ratio );
							forwardmove_ratio = forwardmove_ratio > 0.0 ? 1.0 : -1.0;
						}
						else
						{
							forwardmove_ratio = 1.0;
							rightmove_ratio = 1.0;
						}
 
						forwardmove = forwardmove_ratio * 127;
						rightmove = rightmove_ratio * 127;
 
						oldcmd->forwardmove = forwardmove;
						oldcmd->sidemove = rightmove;
					}
}

int timelag = 0;
int testtype = 0;
bool ySwitch;
int hkCL(int r3)
{
	CCommand* cmd = &client_get()->input.commands[client_get()->input.currentIdx&0x7F];
	CCommand* oldcmd = &client_get()->input.commands[(client_get()->input.currentIdx-1)&0x7F];


	bool changeTime = false;
	bool doWpRedo = true;
	if (aimbothit && silentAimbot && AimbotStarted) {
		oldcmd->viewAngles.x = ANGLE2SHORT(AimAngles.x);
		oldcmd->viewAngles.y = ANGLE2SHORT(AimAngles.y);
		changeTime = true;

		if (fakeLag) {
			timelag++;
			doWpRedo = false;
			if (timelag >= 25) {
				doWpRedo = true;
				timelag = 0;
			}
		}
	}
	if (aimbothit && AimbotStarted && NoSpreadToggle) {
		doSilentAim();
		changeTime = true;
	}
	if(aimbothit && autoShoot && AimbotStarted) {
		//cmd->buttons |= (1<<31);
		oldcmd->buttons &= ~(1<<31);
                cmd->buttons |= (1<<31);
	}
	if (changeTime) {
		oldcmd->time += 1;//I originally had it at 2
		//fixWalking();//doesn't work yet
	}

	//if (ySwitch == true) {
		//cmd->buttons &= ~(1<<31);
	//}

	
	if(!(oldcmd->buttons &= (1<<31))) {
		/*if ( ySwitch )
			oldcmd->viewAngles.y += 323210000;
		else
			oldcmd->viewAngles.y -= 323210000;
		
		ySwitch = !ySwitch;*/

		static int state = 0;
		static vec3i spinAngles;
		spinAngles.y += 45 * (state % 8);
		cmd->viewAngles.x = ANGLE2SHORT(spinAngles.x);
 
		GetMovementFix(state % 8, oldcmd->forwardmove, oldcmd->sidemove, cmd);
		
		state++;
	}

	//printf("x: %i y: %i z: %i\n",(int)((float)SHORT2ANGLE(oldcmd->viewAngles.x)),(int)((float)SHORT2ANGLE(oldcmd->viewAngles.y)),(int)((float)SHORT2ANGLE(oldcmd->viewAngles.z)));
	while ((float)SHORT2ANGLE(oldcmd->viewAngles.x) > 360.0f)
		oldcmd->viewAngles.x = ANGLE2SHORT((float)SHORT2ANGLE(oldcmd->viewAngles.x)-360.0f);
	while ((float)SHORT2ANGLE(oldcmd->viewAngles.x) < 0.0f)
		oldcmd->viewAngles.x = ANGLE2SHORT((float)SHORT2ANGLE(oldcmd->viewAngles.x)+360.0f);

	while ((float)SHORT2ANGLE(oldcmd->viewAngles.y) > 360.0f)
		oldcmd->viewAngles.y = ANGLE2SHORT((float)SHORT2ANGLE(oldcmd->viewAngles.y)-360.0f);
	while ((float)SHORT2ANGLE(oldcmd->viewAngles.y) < 0.0f)
		oldcmd->viewAngles.y = ANGLE2SHORT((float)SHORT2ANGLE(oldcmd->viewAngles.y)+360.0f);
	if (doWpRedo)
		return wp_redo(r3,1);
	return 0;
} 