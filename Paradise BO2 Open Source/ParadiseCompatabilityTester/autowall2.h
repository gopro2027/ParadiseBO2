//WHAT I NEED TO FIND void CG_SimulateBulletFire_Internal(BulletFireParams *bp, centity_t *attacker)
struct BulletFireParams
{
    int weaponEntIndex;
    int ignoreEntIndex;
    float damageMultiplier;
    int methodOfDeath;
    Vector3 origStart;
    Vector3 start;
    Vector3 end;
    Vector3 dir;
};
opd_s CG_SimulateBulletFire_Internal_t = {0x000EA224,TOC};
void(*CG_SimulateBulletFire_Internal)(BulletFireParams *bp, int centityAttacker) = (void(*)(BulletFireParams,int))&CG_SimulateBulletFire_Internal_t;

/*
class bulletTrace_t  //I think this is actually BulletFireParams based on this post https://www.unknowncheats.me/forum/call-duty-black-ops/99400-perfect-autowall.html
{  //used in CG_SimulateBulletFire_Internal on bo2
public:
    __int32 worldEntNum; //0x0000
    __int32 skipNum; //0x0004
    float power; //0x0008
    __int32 bulletType; //0x000C
    Vector3 vieworg; //0x0010
    Vector3 start; //0x001C
    Vector3 end; //0x0028
    Vector3 viewDirection; //0x0034
};//Size=0x0040
*/
void SetupBulletTrace( BulletFireParams* btr, Vector3 start, Vector3 end, int skipNum )
{
    btr->weaponEntIndex = 2047;
    btr->ignoreEntIndex = skipNum;
    btr->damageMultiplier = 1.0f;
    btr->methodOfDeath = 1;

	//copy view angles
	btr->origStart.x = Get_cgs()->refdefViewAngles[0];
	btr->origStart.y = Get_cgs()->refdefViewAngles[1];
	btr->origStart.z = Get_cgs()->refdefViewAngles[2];
    
	//copy start pos
	btr->start.x = start.x;
	btr->start.y = start.y;
	btr->start.z = start.z;

	//copy end pos
	btr->end.x = end.x;
	btr->end.y = end.y;
	btr->end.z = end.z;
 
    Vector3 delta = end - start;
    //VectorSubtract( end, start, delta );
 
    Vector3 angles;
    VectorAngles( delta, angles );
    AngleVectors( angles, btr->viewDirection, NULL, NULL );
}

/*
typedef void ( __cdecl* oFireBulletPenetrate ) (int localClientNum, bulletTrace_t* btr, int weaponID, centity_t *ent, int minus_1_param, float *tracerStart, bool drawTracer);
oFireBulletPenetrate FireBulletPenetrate = ( oFireBulletPenetrate)0x5A5370;
bool R_BulletPenetrationCheck( bulletTrace_t * pBulletTrace )
{
    DWORD dwAddr = 0x5A2FB0;
    static bool returnC;
    __asm   mov     eax, pBulletTrace
    __asm   call    dwAddr
    __asm   mov    returnC, al
 
    return returnC;
 
}*/
 
bool GetRemainingPower( vec3_t vieworg, centity_t* cent, vec3_t origin, float* remainingPower )
{
    bulletTrace_t bulletTrace;
    SetupBulletTrace( &bulletTrace, vieworg, origin, 0 );
    if(R_BulletPenetrationCheck(&bulletTrace))
    {
    //BYTE Patch3[1]        = {0xC3};
    //BYTE Patch4[1]        = {0x8B};
    //WriteProcessMemory(GetCurrentProcess(), (void*)0x5A5210, &Patch3, 1, 0);
    FireBulletPenetrate(cg->clientNum,&bulletTrace,cg_entities[cg->clientNum].WeaponID,&cg_entities[cg->clientNum],-1,refdef->viewOrg,false);
    //WriteProcessMemory(GetCurrentProcess(), (void*)0x5A5210, &Patch4, 1, 0);
 
    if ( bulletTrace.skipNum == cent->clientNUm)
    {
        *remainingPower = bulletTrace.power;
 
        return true;
    }
    else
    {
        *remainingPower = -0.0f;
 
        return false;
    }
    }
    else
    {
    return false;
    }