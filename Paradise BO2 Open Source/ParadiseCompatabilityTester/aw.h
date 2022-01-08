namespace autowall {



typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec5_t[5];
typedef int DWORD;
typedef short WORD;
typedef char BYTE;
typedef vec_t *pvec3_t;
float Get3DDistance(vec_t *v1, vec_t *v2) {
	float a = v1[0]-v2[0];
	float b = v1[1]-v2[1];
	float c = v1[2]-v2[2];
	return sqrt(a*a+b*b+c*c);
}
/*void VectorCopy(vec_t *original, vec_t *save) {
	save[0] = original[0];
	save[1] = original[1];
	save[2] = original[2];
}

void VectorSubtract(vec_t *end, vec_t *start, vec_t *dir) {
	dir[0] = end[0] - start[0];
	dir[1] = end[1] - start[1];
	dir[2] = end[2] - start[2];
}
*/
void VectorNormalize(vec_t *v){
	float length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if(length != 0){
        v[0] = v[0]/length;
        v[1] = v[1]/length;
        v[2] = v[2]/length;
    }
}
#define DotProduct(a,b)			((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])

#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define CrossProduct(a,b,c)		((c)[0]=(a)[1]*(b)[2]-(a)[2]*(b)[1],(c)[1]=(a)[2]*(b)[0]-(a)[0]*(b)[2],(c)[2]=(a)[0]*(b)[1]-(a)[1]*(b)[0])

float min(float x, float y) {
	return x > y ? y : x;
}
enum TraceHitType
{
    TRACE_HITTYPE_NONE = 0,
    TRACE_HITTYPE_ENTITY = 1,
    TRACE_HITTYPE_DYNENT_MODEL = 2,
    TRACE_HITTYPE_DYNENT_BRUSH = 3,
    TRACE_HITTYPE_DYNENT_UNKNOWN = 4
};
struct trace_t
{
    vec3_t normal;//0x0
    float fraction;//0xC
    short sflags;
	short cflags;
    TraceHitType hitType;
    short hitId;//0x20
    short modelIndex;
    short partName;
    short partGroup;
    char unk4[0x10];
}; // 0x38

//opd_s Trace_GetEntityHitID_t = {0x306CC0,TOC};
//int(*Trace_GetEntityHitID_a)(int trace) = (int(*)(int))&Trace_GetEntityHitID_t;
int Trace_GetEntityHitID(unsigned int trace) {
	/*__asm("clrldi %r3, %r3, 32");*/
	//Trace_GetEntityHitID_a(trace);


	int r4 = *(int*)(trace+0x1C);
	bool cr0 = r4 == 2;
	int cr1 = r4 == 1;
	int cr6 = r4 == 4;
	int cr7 = r4 == 3;
	if (cr0 == true) {
		return 0x3FE;
	}
	if (cr7 == false) {
		if (cr6 == false) {
			if (cr1 == false) {
				return 0x3FF;
			} else {
				return *(short*)(trace+0x20);
			}
		} else {
			return 0x3FE;
		}
	} else {
		return 0x3FE;
	}
}

 
struct BulletFireParams//I believe this is proper
{
    int worldEntNum;//proper
	int skipNum;//equals 0
    float damageMultiplier;
    int methodOfDeath;//bulletType
    vec3_t origStart;
    vec3_t start;
    vec3_t end;
    vec3_t dir;
}; // 0x40
/*
D014B6C0  00000000 000003FE 3F800000 00000001 C4DB7115 43602935 C07A1800 ........?.........q.C`)5.z..
D014B6DC  C48081D4 44127B19 C034233F 45AE6B1F 45720B20 40E3B8DC 3F6538BE ....D.{..4#?E.k.Er. @...?e8.
D014B6F8  3EE3F9FB 3AB05729 00000000 00000000 00000000 00000000 00000000
struct from memoru
*/
 
struct BulletTraceResults
{
    /*trace_t trace;//THIS NEED TO BE FIXED. THE STRUCTURE.
    int* hitEnt; // gentity_s*
    float hitPos[3];0x2F0-0x8-0xc
    int ignoreHitEnt;0x2F0-0x8
    int hitSurfaceType;*/ //0x2F0
	//hirSurfaceType is at 0x2F0   or 0xF4 or 0x54
	char data[0x2F4];
}; // 0x2F4
struct weaponWeirdData {
	int unknwn1;
	int unknown2;
	int weaponDefPtr;
};
weaponWeirdData wtfisthislolweaponshit;
//opd_s BulletTrace_t = {0x001CF4B8,TOC};
//bool (*BulletTraceO)(int localClientNum, BulletFireParams *bp, int weapDefptr, int centityattacker, BulletTraceResults *br, int lastSurfaceType, bool simulated) = (bool(*)(int, BulletFireParams *, int, int, BulletTraceResults *, int, bool))&BulletTrace_t;
opd_s BulletTrace_t = {0xE9FBC/*0x001CF4B8 Bullet_Trace*/,TOC};//5 args.
/*
r3=00000000D014B6C0  BulletFireParams //proven
r4=000000000135B948  WEAPON DEF POINTER  //proven    return value from sub_606EE0
r5=00000000016B9F20  probably BulletTraceResults
r6=00000000D014B360  CENTITY  //proven
r7=0000000000000000  surface type I think
*/
//int localClientNum, BulletFireParams *bp, int weapDef, int centityattacker, BulletTraceResults *br, int lastSurfaceType, bool simulated
//I want BulletTrace not Bullet_Trace
bool (*BulletTraceO)(int localClientNum, BulletFireParams *bp, unsigned int weapDef, unsigned int centityattacker, BulletTraceResults *br, unsigned int lastSurfaceType, bool simulated) = (bool(*)(int,BulletFireParams *, unsigned int,unsigned int, BulletTraceResults *,unsigned int, bool))&BulletTrace_t;
bool BulletTrace(BulletFireParams* bulletFireParams, BulletTraceResults* bulletTraceResults, unsigned int localClientNum, unsigned int centity, unsigned int surfaceType)
{
	int wepid = *(int*)(Centity(Get_cgs()->localIndex)+0x2B4);
	//0x606EE0
	//opd_s unkfunk_t = {0x606EE0,TOC};//weapon def variant
	//int (*unkfunk)(int wepid) = (int(*)(int))&unkfunk_t;
	int weaponDefPtr = GetWeaponDef(wepid);
	//printf("WeaponDefPtr: %x, *(int*)(weaponDefPtr+0x8): %x\n",weaponDefPtr,*(int*)(weaponDefPtr+0x8));
	//wtfisthislolweaponshit.weaponDefPtr = weaponDefPtr;
	//if (weaponDefPtr < 0x10000)
		//return false;
	return BulletTraceO(localClientNum,bulletFireParams,weaponDefPtr,centity,bulletTraceResults,surfaceType,false);
	//return BulletTraceO(bulletFireParams,/*0x0135B948*//*(int)&wtfisthislolweaponshit*/weaponDefPtr,bulletTraceResults,centity,surfaceType);
    /*bool hit = 0;
    __declspec(align(16)) char save[512];
    _fxsave(save);
    __asm
    {
        push surfaceType
        push entity
        push localClientNum
        mov esi,bulletTraceResults
        mov edi,bulletFireParams
        call _BulletTrace
        mov hit,al
        add esp,0Ch
    }
    _fxrstor(save);
    return hit;*/
}
 
 //0x005EFFC0
opd_s BG_GetSurfacePenetrationDepth_t = {0x005EFFC0,TOC};
float (*BG_GetSurfacePenetrationDepth)(unsigned int weaponDefPtr, unsigned int surfaceType) = (float(*)(unsigned int,unsigned int))&BG_GetSurfacePenetrationDepth_t;
 
opd_s BG_AdvanceTrace_t = {0x005EFE18,TOC};
bool (*BG_AdvanceTrace)(BulletFireParams* bulletFireParams, BulletTraceResults* bulletTraceResults, float amount) = (bool(*)(BulletFireParams*,BulletTraceResults*,float))&BG_AdvanceTrace_t;
 


opd_s FireBulletPenetrate_t = {0x000EAC28,TOC};
void (*FireBulletPenetrate)(int localClientNum, BulletFireParams* bulletFireParams, int weaponIndex, unsigned int centityAttacker, unsigned int pointerToViewPoint, bool unknwon, bool unknwon2, BulletTraceResults *btr) = (void(*)(int,BulletFireParams*,int,unsigned int, unsigned int, bool, bool, BulletTraceResults *))&FireBulletPenetrate_t;

char blr[4] = { 0x4E, 0x80, 0x00, 0x20 };
char nop[4] = { 0x60, 0x00, 0x00, 0x00 };
char patch0[4] = { 0xF8, 0x21, 0xFE, 0xC1 };
char patch1[4] = { 0xF8, 0x21, 0xFE, 0xE1 };
//int tmpdsgfhasedfrh = 0;
bool isTargetHitable(pvec3_t start, pvec3_t end/*,int targetClient*//*int localClient, int targetClient, char* tagName*/, int targetClientNum) {
	//if (!cEntityz(localClient)->Alive)return false;

	//write_process(0xB5EA8, blr, 4);
	//write_process(0x14A6D8, blr, 4);
	//write_process(0xBC854, nop, 4);

	/*Vector3 PlayerOrigin;
	if(!GetTagPos(targetClient, tagName, PlayerOrigin)) return;

	BulletFireParams bp;
	bp.MaxEntNum = 2046;
	bp.ignoreEntIndex = localClient;
	bp.damageMultiplier = 1.0f;
	bp.methodOfDeath = 2;

	Memcpy(&bp.origStart, &refdef->ViewOrigin);
	Memcpy(&bp.start, &refdef->ViewOrigin, 12);
	Memcpy(&bp.end, &PlayerOrigin, 12);
	*/
	BulletTraceResults bulletTraceResults;
	BulletFireParams bulletFireParams;
    memset(&bulletFireParams, 0x00, sizeof(BulletFireParams));
 
    bulletFireParams.worldEntNum = 1022;//0x3FE
    bulletFireParams.skipNum = 0;//Centity(Get_cgs()->localIndex);//*(DWORD*)((DWORD)&cg_entitiesArray[cgArray->clientNum] + 488);
    bulletFireParams.damageMultiplier = 1.0f;
    bulletFireParams.methodOfDeath = 1;//(*(BYTE*)(weaponDefPtr + 1357) != 0) + 1;   like I care what this deos right now
    VectorCopy(start, bulletFireParams.origStart);
    VectorCopy(start, bulletFireParams.start);
    VectorCopy(end, bulletFireParams.end);

	/*Vector3 angles; VectoAngles(&SubstractVector(PlayerOrigin, refdef->ViewOrigin), &angles);
	bp.dir = AnglesToForward_0(angles);*/
	vec3_t dir;
    VectorSubtract(end, start, dir);
    VectorNormalize(dir);
    VectorCopy(dir, bulletFireParams.dir);
	//hi:
	int wepid = *(int*)(Centity(Get_cgs()->localIndex)+0x2B4);
	//printf("Centity: 0x%x\n",Centity(Get_cgs()->localIndex));
	//if (tmpdsgfhasedfrh == 0)
	write_process((void*)addresses.CG_BulletHitEvent_Patch/*0x000E9BE8*/,blr,4);//CG_BulletHitEvent
	write_process((void*)addresses.Tracer_Spawn_Patch/*0x0045C038*/,blr,4);//Tracer_Spawn
		FireBulletPenetrate(0, &bulletFireParams, wepid, Centity(Get_cgs()->localIndex), (unsigned int)&(Get_cgs()->refdef.viewOrigin), 1,1,&bulletTraceResults);
	write_process((void*)addresses.CG_BulletHitEvent_Patch/*0x000E9BE8*/,patch0,4);//CG_BulletHitEvent
	write_process((void*)addresses.Tracer_Spawn_Patch/*0x0045C038*/,patch1,4);//Tracer_Spawn
	//0x000EB188 maybe this to disable sound? nah
	//tmpdsgfhasedfrh++;
	//if (tmpdsgfhasedfrh > 100)
		//tmpdsgfhasedfrh = 0;
	//write_process(0xB5EA8, patch0, 4);
	//write_process(0x14A6D8, patch1, 4);
	//printf("Damage: %x\n",*(unsigned int*)&bulletFireParams.damageMultiplier);
	unsigned int traceResultTrace = (unsigned int)&bulletTraceResults;
	/*if (bulletFireParams.damageMultiplier > 0.0f) {
		return true;
		//BG_AdvanceTrace(&bulletFireParams,&bulletTraceResults,1.13500000536441803f);
		//goto hi;
	}*/
	return (bulletFireParams.skipNum == targetClientNum);
	if (/*Trace_GetEntityHitID(traceResultTrace) != 1022*/bulletFireParams.skipNum == targetClientNum/* && bulletFireParams.damageMultiplier > 0.0f && bulletFireParams.damageMultiplier < 1.0f*/)//returns here
        return true;
	/*if (bulletFireParams.damageMultiplier >= 1.0f)
		return false;
	if (bulletFireParams.damageMultiplier > 0.0f)//can be changed
		return true;*/
	return false;
	//return bulletFireParams.damageMultiplier;
	//return (bulletFireParams.unknwon/*ignoreEntIndex*/ == targetClient); //8----->
}





float GetAutoWallDamageMultiplier(pvec3_t start, pvec3_t end)
{
	if (autowallEnabled == false)
		return 0.0;
	if (allowAutowall == false)
		return 0.0;
    // get our weapon
	int wepid = *(int*)(Centity(Get_cgs()->localIndex)+0x2B4);
	int weaponDefPtr = GetWeaponDef(wepid);
	//printf("Got wep id %i %i %i\n",weaponDefPtr,(int)*(char*)(weaponDefPtr+0x2b),(int)*(char*)(weaponDefPtr+0x2f));
 
    // set up our BulletFireParams struct
    BulletFireParams bulletFireParams;
    memset(&bulletFireParams, 0x00, sizeof(BulletFireParams));
 
    bulletFireParams.worldEntNum = 1022;
    //bulletFireParams.ignoreEntIndex = Centity(Get_cgs()->localIndex);//*(DWORD*)((DWORD)&cg_entitiesArray[cgArray->clientNum] + 488);
    bulletFireParams.damageMultiplier = 1.0f;
    bulletFireParams.methodOfDeath = 1;//(*(BYTE*)(weaponDefPtr + 1357) != 0) + 1;   like I care what this deos right now
    VectorCopy(start, bulletFireParams.origStart);
    VectorCopy(start, bulletFireParams.start);
    VectorCopy(end, bulletFireParams.end);
 
    vec3_t dir;
    VectorSubtract(end, start, dir);
    VectorNormalize(dir);
    VectorCopy(dir, bulletFireParams.dir);
	//printf("Initialized shit\n");
 
    // call BulletTrace for the first time and get our BulletTraceResults struct
    BulletTraceResults bulletTraceResults;
    int hit = BulletTrace(&bulletFireParams, &bulletTraceResults, 0, Centity(Get_cgs()->localIndex)/*&cg_entitiesArray[cgArray->clientNum]*/, 0);
	//printf("did the first BulletTrace %i %i\n",*(int*)(&bulletFireParams.damageMultiplier),hit);
    // if the result of the bullet trace was TRACE_HITTYPE_NONE, we return the full damage multiplier
    if (hit == false)//means it hit the entity
        return bulletFireParams.damageMultiplier;
//#ifdef appleslololol
	//printf("There was not a hit\n");
    // return if the hit type was TRACE_HITTYPE_ENTITY
	unsigned int traceResultTrace = (unsigned int)&bulletTraceResults;
    if (Trace_GetEntityHitID(traceResultTrace) != 1022)//returns here
        return 1.0f;
	//printf("Yayy! It's a proper hit!: %x hit:%i\n",*(unsigned int*)(&bulletFireParams.damageMultiplier),hit);
	//float pen = BG_GetSurfacePenetrationDepth(*(DWORD*)(weaponDefPtr + 36)/*weaponDefPtr*/, *(unsigned int*)(&bulletTraceResults+0x54));//0x24
	//return pen > 0.0f ? pen: 0.0f;




//#ifdef appleslololol


	//printf("Got entity hit id\n");
    //if (*(WORD*)((DWORD)&bulletTraceResults.trace + 40) == 2)
        //return 0.0f;
	//printf("Not sure what is here but it worked\n");
    // return if our weapon doesn't penetrate, some weird var from bulletTraceResults.trace is true or some weird weapon shit i dont know
    /*if (!*(DWORD*)(weaponDefPtr + 36) // if (weaponDefPtr->penetrateType == PENETRATE_TYPE_NONE)
        || *(BYTE*)((DWORD)bulletTraceResults.data + 43)
        || *(BYTE*)(weaponDefPtr + 1581)
        )
        return 0.0f;*/
	//printf("btrdata: %i %i\n",*(BYTE*)((DWORD)bulletTraceResults.data + 43), *(BYTE*)((DWORD)bulletTraceResults.data + 47));
	//return 0;
	if (*(DWORD*)(weaponDefPtr + 36) == 0 // if (weaponDefPtr->penetrateType == PENETRATE_TYPE_NONE)
        /*|| *(BYTE*)((DWORD)bulletTraceResults.data + 43)//not sure if this
		|| *(BYTE*)((DWORD)bulletTraceResults.data + 47)//or this
        || *(BYTE*)(weaponDefPtr + 1585) == 0*/
        )
        return 0.0f;
	//printf("yea...\n");
    // we can penetrate a maximum of 5 walls, we loop each wall
    int penetrationCount = 0;
    float perk_bulletPenetrationMultiplier = 2.0f;
    float penetrationDepth;
    BulletFireParams bulletFireParams_2;
    BulletTraceResults bulletTraceResults_2;
    vec3_t hitPosBackup;
    bool hit_2;
    bool v26;
	int loopcount = 0;
    while (true)
    {
		//printf("In loop %i\n",loopcount);
		loopcount++;
        // get the penetration depth of the hit surface, and apply the perk_bulletPenetrationMultiplier perk if we have it
        // need to test if perk detection works
		//printf("Bullet Trace Results addr: %i surface: %i %i\n",(unsigned int)&bulletTraceResults,*(unsigned int*)(bulletTraceResults.data+0xF4),*(unsigned int*)(bulletTraceResults.data+0x54));
        penetrationDepth = BG_GetSurfacePenetrationDepth(*(DWORD*)(weaponDefPtr + 36)/*weaponDefPtr*/,*(unsigned int*)(bulletTraceResults.data+0x54));
        //if (*(WORD*)((DWORD)&cg_entitiesArray[cgArray->clientNum] + 678) == 1 && (*(DWORD*)((DWORD)&clientinfo[cgArray->clientNum] + 389756) & 32))
            //penetrationDepth *= perk_bulletPenetrationMultiplier;
		//printf("heya %i\n",*(unsigned int*)&penetrationDepth);
        // we return if our penetration depth is zero or negative
        if (penetrationDepth <= 0.0f)
            return 0.0f;
		//else
			//return 1.0f;
		//printf("ohoh\n");

		/*VectorCopy(*(vec3_t*)(&bulletTraceResults+0x40),bulletFireParams.start);
		VectorCopy(*(vec3_t*)(&bulletTraceResults+0x40),bulletFireParams.origStart);
		VectorCopy(end,bulletFireParams.end);*/
		BG_AdvanceTrace(&bulletFireParams, &bulletTraceResults, 1.13500000536441803f);
		//VectorCopy(bulletFireParams.end, bulletFireParams.start);
		//VectorMA(bulletFireParams.start, 2, bulletFireParams.dir, *(vec3_t*)(&bulletTraceResults+/*0x2dc*/0x54-0x14));
		hit = BulletTrace(&bulletFireParams, &bulletTraceResults, 0, Centity(Get_cgs()->localIndex), *(unsigned int*)(bulletTraceResults.data+0x54)/*bulletTraceResults.hitSurfaceType*/);
		
		unsigned int traceResultTrace = (unsigned int)&bulletTraceResults;
		//return Trace_GetEntityHitID(traceResultTrace) != 1022?1.0:0.0;

		bulletFireParams.damageMultiplier -= 1.13500000536441803f / penetrationDepth;
		//printf("Damage Multiplier: %x\n",*(unsigned int*)&bulletFireParams.damageMultiplier);
		if (Trace_GetEntityHitID(traceResultTrace) != 1022)//returns here
			return bulletFireParams.damageMultiplier;
		else
			return 0.0f;















        // backup our latest hit position and advance the trace (return if we can't advance the trace)
        VectorCopy(*(vec3_t*)(&bulletTraceResults+/*0x2dc*/0x54-0x14), hitPosBackup);
        if (!BG_AdvanceTrace(&bulletFireParams, &bulletTraceResults, 0.13500000536441803f))
            return 0.0f;
		//printf("Did some advance trace\n");
        // get the wall depth by hitting the face of the surface, then the back of the surface, and saving those hit positions
        hit = BulletTrace(&bulletFireParams, &bulletTraceResults, 0, Centity(Get_cgs()->localIndex), *(unsigned int*)(bulletTraceResults.data+0x54)/*bulletTraceResults.hitSurfaceType*/);
		
		//printf("did some bullet trace\n");
        memcpy(&bulletFireParams_2, &bulletFireParams, sizeof(BulletFireParams));
 
        VectorScale(bulletFireParams.dir, -1.0f, bulletFireParams_2.dir); // inverse the direction when at the back of the wall
        VectorCopy(bulletFireParams.end, bulletFireParams_2.start);
        VectorMA(hitPosBackup, 0.009999999776482582f, bulletFireParams_2.dir, bulletFireParams_2.end);
 
        memcpy(&bulletTraceResults_2, &bulletTraceResults, sizeof(BulletTraceResults));
 
        VectorScale(*(vec3_t*)&bulletTraceResults_2, -1.0f, *(vec3_t*)&bulletTraceResults_2);
		//printf("scaled a vector\n");
        if (hit)
            BG_AdvanceTrace(&bulletFireParams_2, &bulletTraceResults_2, 0.009999999776482582f);
		//printf("more shit\n");
        hit_2 = BulletTrace(&bulletFireParams_2, &bulletTraceResults_2, 0, Centity(Get_cgs()->localIndex), *(unsigned int*)(bulletTraceResults_2.data+0x54)/*bulletTraceResults_2.hitSurfaceType*/);
		
		//printf("even more shit\n");
        v26 = (hit_2 != 0) && *(BYTE*)((DWORD)&bulletTraceResults_2/*.trace*/ + 42) || *(BYTE*)((DWORD)&bulletTraceResults/*.trace*/ + 43) && *(BYTE*)((DWORD)&bulletTraceResults_2/*.trace*/ + 43);
		//printf("am I loco shit\n");
        if (hit_2 || v26)
            break;
        if (!hit)
        {
            return bulletFireParams.damageMultiplier;
        }
        goto continueLoop;
 
continueLoop:
        if (hit)
        {
            penetrationCount++;
            if (penetrationCount < 5) // max number of surfaces penetrated is 5 (from penetrationCount dvar)
                continue;
        }
 
        //return 0.0f;
    }
 
    // calculate the surface depth
    float surfaceDepth = 0.0f;
	//printf("About to calc 3d\n");
    if (v26)
        surfaceDepth = Get3DDistance(bulletFireParams_2.start, bulletFireParams_2.end);
    else
        surfaceDepth = Get3DDistance(*(vec3_t*)(&bulletTraceResults_2+/*0x2dc*/0x54-0x14), hitPosBackup);
    //printf("calculated some 3d\n");
    // minimum surface depth is 1.0f
    if (surfaceDepth < 1.0f)
        surfaceDepth = 1.0f;
    
    // if we hit the back side of the wall, set the minimum penetration depth of both surfaces hit as our final penetration depth
    if (hit_2)
    {
        float penetrationDepth_2 = BG_GetSurfacePenetrationDepth(*(DWORD*)(weaponDefPtr + 36)/*weaponDefPtr*/, *(unsigned int*)(bulletTraceResults_2.data+0x54)/*bulletTraceResults_2.hitSurfaceType*/);
		//printf("kekekekekekek\n");
        //if (*(WORD*)((DWORD)&cg_entitiesArray[cgArray->clientNum] + 678) == 1 && (*(DWORD*)((DWORD)&clientinfo[cgArray->clientNum] + 389756) & 32))
            //penetrationDepth_2 *= perk_bulletPenetrationMultiplier;
        //printf("calced da min: %i %i\n",*(int*)(&penetrationDepth),*(int*)(&penetrationDepth_2));
        penetrationDepth = min(penetrationDepth, penetrationDepth_2);
        
        // we return if our penetration depth is zero or negative
        if (penetrationDepth <= 0.0f)
            return 0.0f;
    }
 bulletFireParams.damageMultiplier -= surfaceDepth / penetrationDepth;
   /* if (*(WORD*)((DWORD)&cg_entitiesArray[cgArray->clientNum] + 678) == 1)
    {
        if (*(DWORD*)((DWORD)&clientinfo[cgArray->clientNum] + 389756) & 32)
        {
LABEL_84:*/
            /*if (bulletFireParams.damageMultiplier <= 0.0f)
                return 0.0f;
 
            goto continueLoop;*/
        //}
    
    // decrease our damage multiplier (the fraction)
    //bulletFireParams.damageMultiplier -= surfaceDepth / penetrationDepth;
    //goto LABEL_84;
 
    // impossibru, this return can't be executed (who cares)
	//printf("came to end\n");
    return bulletFireParams.damageMultiplier;
//#endif
}






}