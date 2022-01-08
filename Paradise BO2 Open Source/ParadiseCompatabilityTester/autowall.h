enum TraceHitType
{
    TRACE_HITTYPE_NONE = 0,
    TRACE_HITTYPE_ENTITY = 1,
    TRACE_HITTYPE_DYNENT_MODEL = 2,
    TRACE_HITTYPE_DYNENT_BRUSH = 3,
    TRACE_HITTYPE_DYNENT_UNKNOWN = 4
};
 
#pragma pack(push, 1)
 
struct trace_t
{
    vec3_t normal;
    char unk1[0x04];
    float fraction;
    char unk2[0x08];
    TraceHitType hitType;
    short hitId;
    short modelIndex;
    short partName;
    short partGroup;
    char unk4[0x10];
}; // 0x38
 
#pragma pack(pop)
 
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
}; // 0x40
 
struct BulletTraceResults
{
    trace_t trace;
    int* hitEnt; // gentity_s*
    float hitPos[3];
    int ignoreHitEnt;
    int hitSurfaceType;
}; // 0x50
 
int _BulletTrace = 0xblahblah;
 
float (__cdecl* _BG_GetSurfacePenetrationDepth)(int weaponDefPtr, int surfaceType) = (float(__cdecl*)(int,int))0xfakfak;
 
bool (__cdecl* _BG_AdvanceTrace)(BulletFireParams* bulletFireParams, BulletTraceResults* bulletTraceResults, float amount) = (bool(_cdecl*)(BulletFireParams*,BulletTraceResults*,float))0xmehmeh;
 
bool BulletTrace(BulletFireParams* bulletFireParams, BulletTraceResults* bulletTraceResults, int localClientNum, centity_s* entity, int surfaceType)
{
    bool hit = 0;
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
    return hit;
}
 
float BG_GetSurfacePenetrationDepth(int weaponDefPtr, int surfaceType)
{
    return _BG_GetSurfacePenetrationDepth(weaponDefPtr, surfaceType);
}
 
bool BG_AdvanceTrace(BulletFireParams* bulletFireParams, BulletTraceResults* bulletTraceResults, float amount)
{
    return _BG_AdvanceTrace(bulletFireParams, bulletTraceResults, amount);
}
 
float GetAutoWallDamageMultiplier(Vector3 *start, Vector3 *end)
{
    // get our weapon
    int wepid = *(int*)(Centity(Get_cgs()->localIndex)+addresses.wepidcentityoffset/*0x2B4*/);
	int weaponDefPtr = GetWeaponDef(wepid);
    // set up our BulletFireParams struct
    BulletFireParams bulletFireParams;
    memset(&bulletFireParams, 0x00, sizeof(BulletFireParams));
 
    bulletFireParams.weaponEntIndex = 1022;
    bulletFireParams.ignoreEntIndex = *(int*)((int)&cg_entitiesArray[cgArray->clientNum] + 0x1E8);
    bulletFireParams.damageMultiplier = 1.0f;
    bulletFireParams.methodOfDeath = (*(char*)(weaponDefPtr + 0x54D) != 0) + 1;
    VectorCopy(start, &bulletFireParams.origStart);
    VectorCopy(start, &bulletFireParams.start);
    VectorCopy(end, &bulletFireParams.end);
 
    vec3_t dir;
    VectorSubtract(end, start, dir);
    VectorNormalize(dir);
    VectorCopy(dir, bulletFireParams.dir);
 
    // call BulletTrace for the first time and get our BulletTraceResults struct
    BulletTraceResults bulletTraceResults;
    bool hit = BulletTrace(&bulletFireParams, &bulletTraceResults, 0, &cg_entitiesArray[cgArray->clientNum], 0);
 
    // if the result of the bullet trace was TRACE_HITTYPE_NONE, we return the full damage multiplier
    if (!hit)
        return bulletFireParams.damageMultiplier;
 
    // return if the hit type was TRACE_HITTYPE_ENTITY
    if (Trace_GetEntityHitId(&bulletTraceResults.trace) != 1022)
        return 0.0f;
 
    if (*(WORD*)((DWORD)&bulletTraceResults.trace + 40) == 2)
        return 0.0f;
 
    // return if our weapon doesn't penetrate, some weird var from bulletTraceResults.trace is true or some weird weapon shit i dont know
    if (!*(DWORD*)(weaponDefPtr + 36) // if (weaponDefPtr->penetrateType == PENETRATE_TYPE_NONE)
        || *(BYTE*)((DWORD)&bulletTraceResults.trace + 43)
        || *(BYTE*)(weaponDefPtr + 1581)
        )
        return 0.0f;
 
    // we can penetrate a maximum of 5 walls, we loop each wall
    int penetrationCount = 0;
    float perk_bulletPenetrationMultiplier = 2.0f;
    float penetrationDepth;
    BulletFireParams bulletFireParams_2;
    BulletTraceResults bulletTraceResults_2;
    vec3_t hitPosBackup;
    bool hit_2;
    bool v26;
    while (true)
    {
        // get the penetration depth of the hit surface, and apply the perk_bulletPenetrationMultiplier perk if we have it
        // need to test if perk detection works
        penetrationDepth = BG_GetSurfacePenetrationDepth(weaponDefPtr, bulletTraceResults.hitSurfaceType);
        if (*(WORD*)((DWORD)&cg_entitiesArray[cgArray->clientNum] + 678) == 1 && (*(DWORD*)((DWORD)&clientinfo[cgArray->clientNum] + 389756) & 32))
            penetrationDepth *= perk_bulletPenetrationMultiplier;
 
        // we return if our penetration depth is zero or negative
        if (penetrationDepth <= 0.0f)
            return 0.0f;
 
        // backup our latest hit position and advance the trace (return if we can't advance the trace)
        VectorCopy(bulletTraceResults.hitPos, hitPosBackup);
        if (!BG_AdvanceTrace(&bulletFireParams, &bulletTraceResults, 0.13500000536441803f))
            return 0.0f;
 
        // get the wall depth by hitting the face of the surface, then the back of the surface, and saving those hit positions
        hit = BulletTrace(&bulletFireParams, &bulletTraceResults, 0, &cg_entitiesArray[cgArray->clientNum], bulletTraceResults.hitSurfaceType);
 
        memcpy(&bulletFireParams_2, &bulletFireParams, sizeof(BulletFireParams));
 
        VectorScale(bulletFireParams.dir, -1.0f, bulletFireParams_2.dir); // inverse the direction when at the back of the wall
        VectorCopy(bulletFireParams.end, bulletFireParams_2.start);
        VectorMA(hitPosBackup, 0.009999999776482582f, bulletFireParams_2.dir, bulletFireParams_2.end);
 
        memcpy(&bulletTraceResults_2, &bulletTraceResults, sizeof(BulletTraceResults));
 
        VectorScale(bulletTraceResults_2.trace.normal, -1.0f, bulletTraceResults_2.trace.normal);
 
        if (hit)
            BG_AdvanceTrace(&bulletFireParams_2, &bulletTraceResults_2, 0.009999999776482582f);
 
        hit_2 = BulletTrace(&bulletFireParams_2, &bulletTraceResults_2, 0, &cg_entitiesArray[cgArray->clientNum], bulletTraceResults_2.hitSurfaceType);
 
        v26 = (hit_2 != 0) && *(BYTE*)((DWORD)&bulletTraceResults_2.trace + 42) || *(BYTE*)((DWORD)&bulletTraceResults.trace + 43) && *(BYTE*)((DWORD)&bulletTraceResults_2.trace + 43);
 
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
 
        return 0.0f;
    }
 
    // calculate the surface depth
    float surfaceDepth = 0.0f;
    if (v26)
        surfaceDepth = Get3DDistance(bulletFireParams_2.start, bulletFireParams_2.end);
    else
        surfaceDepth = Get3DDistance(bulletTraceResults_2.hitPos, hitPosBackup);
    
    // minimum surface depth is 1.0f
    if (surfaceDepth < 1.0f)
        surfaceDepth = 1.0f;
    
    // if we hit the back side of the wall, set the minimum penetration depth of both surfaces hit as our final penetration depth
    if (hit_2)
    {
        float penetrationDepth_2 = BG_GetSurfacePenetrationDepth(weaponDefPtr, bulletTraceResults_2.hitSurfaceType);
        if (*(WORD*)((DWORD)&cg_entitiesArray[cgArray->clientNum] + 678) == 1 && (*(DWORD*)((DWORD)&clientinfo[cgArray->clientNum] + 389756) & 32))
            penetrationDepth_2 *= perk_bulletPenetrationMultiplier;
        
        penetrationDepth = min(penetrationDepth, penetrationDepth_2);
        
        // we return if our penetration depth is zero or negative
        if (penetrationDepth <= 0.0f)
            return 0.0f;
    }
 
    if (*(WORD*)((DWORD)&cg_entitiesArray[cgArray->clientNum] + 678) == 1)
    {
        if (*(DWORD*)((DWORD)&clientinfo[cgArray->clientNum] + 389756) & 32)
        {
LABEL_84:
            if (bulletFireParams.damageMultiplier <= 0.0f)
                return 0.0f;
 
            goto continueLoop;
        }
    }
    
    // decrease our damage multiplier (the fraction)
    bulletFireParams.damageMultiplier -= surfaceDepth / penetrationDepth;
    goto LABEL_84;
 
    // impossibru, this return can't be executed (who cares)
    return 0.0f;
}