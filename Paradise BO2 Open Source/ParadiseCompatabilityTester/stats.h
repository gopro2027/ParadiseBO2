/*enum ClientNum_t
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
};*/
 
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
 
//r3 is 0, r5 is 0
//r4 is
//D014FF9C  00003E20 FFFFFFFF 307341E4 30732958 00000000 00000000 00000000 ..> ....0sA.0s)X............
//D014FFB8  00000000 02146D48 00000007 00000000 00000000 00000940 00000000 ......mH...............@....
//D014FFD4  00000000 00000000 00000000 00000000 D0150060 00000000 00000940 ...................`.......@
//D014FFF0  00000000 0026AFF4 00000000 00000000 000005F2 FFFFFFFF 3076F7F8
opd_s SetStatFromState_t = { 0x344810/*0x22D7BC*//*0x22D744*/, TOC };
void(*SetStatFromState)(int clientNum, ddlState_t *searchState, int value) = (void(*)(int, ddlState_t *, int))&SetStatFromState_t;
 
opd_s LiveStats_MoveToPlayerStatPath_t = { 0x5432A4, TOC };// RANKXP StatValue
int(*LiveStats_MoveToPlayerStatPath)(ddlState_t *resultState, char *statName, char *statType) = (int(*)(ddlState_t *, char *, char *))&LiveStats_MoveToPlayerStatPath_t;

void SetPlayerStatValue(int clientNum, char *statName, float value)
{
  ddlState_t statsState;
  statsState.absoluteOffset = 0x01780F28;
 
  if ( LiveStats_MoveToPlayerStatPath(&statsState, statName, "StatValue") )
    SetStatFromState(clientNum, &statsState, value);
  else
    printf("SetPlayerStat: path not found.\n");
}

void setClientRank(int client, int rank) {
	SetPlayerStatValue(client,"PRANK",rank);
}

void setClientPrestige(int client, int prestige) {
	SetPlayerStatValue(client,"PLEVEL",prestige);
}