enum ClientNum_t
{
  INVALID_CLIENT_INDEX = 0xFFFFFFFF,
  CLIENT_INDEX_FIRST = 0x0,
  CLIENT_INDEX_0 = 0x0,
  CLIENT_INDEX_1 = 0x1,
  CLIENT_INDEX_2 = 0x2,
  CLIENT_INDEX_3 = 0x3,
  CLIENT_INDEX_4 = 0x4,
  CLIENT_INDEX_5 = 0x5,
  CLIENT_INDEX_6 = 0x6,
  CLIENT_INDEX_7 = 0x7,
  CLIENT_INDEX_8 = 0x8,
  CLIENT_INDEX_9 = 0x9,
  CLIENT_INDEX_10 = 0xA,
  CLIENT_INDEX_11 = 0xB,
  CLIENT_INDEX_12 = 0xC,
  CLIENT_INDEX_13 = 0xD,
  CLIENT_INDEX_14 = 0xE,
  CLIENT_INDEX_15 = 0xF,
  CLIENT_INDEX_16 = 0x10,
  CLIENT_INDEX_17 = 0x11,
  CLIENT_INDEX_18 = 0x12,
  CLIENT_INDEX_19 = 0x13,
  CLIENT_INDEX_20 = 0x14,
  CLIENT_INDEX_21 = 0x15,
  CLIENT_INDEX_22 = 0x16,
  CLIENT_INDEX_23 = 0x17,
  CLIENT_INDEX_24 = 0x18,
  CLIENT_INDEX_25 = 0x19,
  CLIENT_INDEX_26 = 0x1A,
  CLIENT_INDEX_27 = 0x1B,
  CLIENT_INDEX_28 = 0x1C,
  CLIENT_INDEX_29 = 0x1D,
  CLIENT_INDEX_30 = 0x1E,
  CLIENT_INDEX_31 = 0x1F,
  CLIENT_INDEX_COUNT = 0x12,
};
 
enum ddlReturnCodes_e
{
  DDL_RC_SUCCESS = 0x0,
  DDL_RC_ERROR = 0xFFFFFFFF,
  DDL_RC_BUFFER_IO_ERROR = 0xFFFFFFFE,
  DDL_RC_STATE_INVALID = 0xFFFFFFFD,
  DDL_RC_MEMBER_NULL = 0xFFFFFFFC,
  DDL_RC_MEMBER_INVALID = 0xFFFFFFFB,
  DDL_RC_OFFSET_INVALID = 0xFFFFFFFA,
  DDL_RC_TRUNCATED = 0xFFFFFFF9,
};
 
struct ddlMemberDef_t
{
  const char *name;
  int size;
  int offset;
  int type;
  int externalIndex;
  unsigned int rangeLimit;
  unsigned int serverDelta;
  unsigned int clientDelta;
  int arraySize;
  int enumIndex;
  int permission;
};
 
struct ddlHash_t
{
  int hash;
  int index;
};
 
struct ddlEnumDef_t
{
  const char *name;
  int memberCount;
  const char **members;
  ddlHash_t *hashTable;
};
 
struct ddlStructDef_t
{
  const char *name;
  int size;
  int memberCount;
  ddlMemberDef_t *members;
  ddlHash_t *hashTable;
};
 
struct ddlDef_t
{
  int version;
  int size;
  ddlStructDef_t *structList;
  int structCount;
  ddlEnumDef_t *enumList;
  int enumCount;
  ddlDef_t *next;
};
 
struct ddlState_t
{
  int absoluteOffset;
  int arrayIndex;
  ddlMemberDef_t *member;
  ddlDef_t *ddl;
  ddlReturnCodes_e returnCode;
};

/*
opd_s SetStatFromState_t = { 0x344810  0x22D7BC, TOC };
void(*SetStatFromState)(ClientNum_t clientNum, ddlState_t *searchState, unsigned int value) = (void(*)(ClientNum_t, ddlState_t *, unsigned int))&SetStatFromState_t;
 
opd_s LiveStats_MoveToPlayerStatPath_t = { 0x5432A4, TOC };//this is right like 100%
int(*LiveStats_MoveToPlayerStatPath)(ddlState_t *searchState,const char *statName, char *statPart) = (int(*)(ddlState_t *,const char *, char *))&LiveStats_MoveToPlayerStatPath_t;
*/

/*
void SetPlayerStatValue(ClientNum_t clientNum, const char *statName, unsigned int value)
{
  static ddlState_t statsState;
 
  if ( LiveStats_MoveToPlayerStatPath(&statsState, statName, "StatValue") ) {
	  printf("&statsState: 0x%X\n",(unsigned int)(&statsState));
	  SetStatFromState(clientNum, &statsState, value);
  }
  else
    printf("SetPlayerStat: path not found.");
	
}*/
void setDvarAll(char *dvar, char *value);
void SetPlayerStatValue(unsigned int clientNum, char *statName, float value) {
	//setDvarAll("tu4_statsParity","1");
	opd_s SetPlayerStatValue_t = {0x22D744,TOC};//0x22D744
	void (*SetPlayerStatValue)(unsigned int clientNum, char *statName, float value) = (void(*)(unsigned int, char *, float))&SetPlayerStatValue_t;
	SetPlayerStatValue(clientNum,statName,value);
}

void setPrestige(int client, int level) {
	SetPlayerStatValue((ClientNum_t)client,"PLEVEL",level);
}
void setLevel(int client, int level) {
	SetPlayerStatValue((ClientNum_t)client,"LEVEL",level);
}




union ddlValue_t {
float fixedPointValue;//idk what this is
int intValue;
unsigned int uintValue;
int64_t int64Value;
float floatValue;
char *stringPtr;
};

opd_s va_t = { 0x4DB3D8, TOC };
char *(*va)(const char *format, ...) = (char *(*)(const char *, ...))&va_t;

opd_s LiveStats_GetRootDDLState_t = { 0x53C264, TOC };//this is bo2 offset 0x53C264
ddlState_t *(*LiveStats_GetRootDDLState)() = (ddlState_t *(*)())&LiveStats_GetRootDDLState_t;

opd_s DDL_MoveTo_t = { 0x4A7B18, TOC };//bo2 address is 0x4A7B18
int(*DDL_MoveTo)(ddlState_t *searchState, ddlState_t *resultState, int argNum, ...) = (int(*)(ddlState_t *, ddlState_t *, int, ...))&DDL_MoveTo_t;
//344538 SV_SetClientStat  344538 SV_SetClientStat
opd_s SV_SetClientStat_t = {0x344538,TOC};
void(*SV_SetClientStat)(int clientNum, ddlState_t *searchState, ddlValue_t value) = (void(*)(int, ddlState_t *, ddlValue_t))&SV_SetClientStat_t;

opd_s SV_SetClientInt64Stat_t = { 0x3447B4, TOC };//actually SV_SetClientInt64Stat
void(*SV_SetClientInt64Stat)(int clientNum, ddlState_t *searchState, unsigned int value) = (void(*)(int, ddlState_t *, unsigned int))&SV_SetClientInt64Stat_t;

/*void SetClientPerk(int clientNum,int classnum)
{
	ddlState_t searchState;
	if(classnum<6)
	{
	DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 3, "cacLoadouts", va("customclass%i",classnum), "specialty1");
	}
	else
	{
	DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 3, "cacLoadouts", va("prestigeclass%i",(classnum - 5)), "specialty1");
	}
	SV_SetClientDIntStat(clientNum, &searchState,0);
}*/
/*
void setPrestige(int clientNum,int prestige)
{
	ddlState_t searchState;
	DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 3, "PlayerStatsList", "PLEVEL", "StatValue");
	//SV_SetClientInt64Stat(clientNum, &searchState,0);
	ddlValue_t val;
	val.intValue = prestige;
	SV_SetClientStat(clientNum,&searchState,val);
}



*/


