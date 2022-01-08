#define TOC 0xD67E98

/* dvar->flags */
#define DVAR_ARCHIVE		(1 << 0)	// 0x0001
#define DVAR_USERINFO		(1 << 1)	// 0x0002
#define DVAR_SERVERINFO		(1 << 2)	// 0x0004
#define DVAR_SYSTEMINFO		(1 << 3)	// 0x0008
#define DVAR_INIT		(1 << 4)	// 0x0010
#define DVAR_LATCH		(1 << 5)	// 0x0020
#define DVAR_ROM		(1 << 6)	// 0x0040
#define DVAR_CHEAT		(1 << 7)	// 0x0080
#define DVAR_DEVELOPER		(1 << 8)	// 0x0100
#define DVAR_SAVED		(1 << 9)	// 0x0200
#define DVAR_NORESTART		(1 << 10)	// 0x0400
#define DVAR_CHANGEABLE_RESET	(1 << 12)	// 0x1000
#define DVAR_EXTERNAL		(1 << 14)	// 0x4000
#define DVAR_AUTOEXEC		(1 << 15)	// 0x8000

enum dvarType_t
{
	DVAR_TYPE_INVALID = 0x0,
	DVAR_TYPE_BOOL = 0x1,
	DVAR_TYPE_FLOAT = 0x2,
	DVAR_TYPE_FLOAT_2 = 0x3,
	DVAR_TYPE_FLOAT_3 = 0x4,
	DVAR_TYPE_FLOAT_4 = 0x5,
	DVAR_TYPE_INT = 0x6,
	DVAR_TYPE_ENUM = 0x7,
	DVAR_TYPE_STRING = 0x8,
	DVAR_TYPE_COLOR = 0x9,
	DVAR_TYPE_INT64 = 0xA,
	DVAR_TYPE_LINEAR_COLOR_RGB = 0xB,
	DVAR_TYPE_COLOR_XYZ = 0xC,
	DVAR_TYPE_COUNT = 0xD,
};

union DvarLimits
{
	struct {
		int stringCount;
		const char **strings;
	} enumeration;

	struct {
		int min;
		int max;
	} integer;

	struct {
		float min;
		float max;
	} value, vector;

	struct {
		int64_t min;
		int64_t max;
	} integer64;
};

union DvarValue
{
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	int64_t integer64;
	 int64_t unsignedInt64;
	float value;
	float vectorv[4];
	const char *string;
	char color[4];
};

#pragma pack(push, 4)
struct dvar_t
{
	const char *name;
	const char *description;
	int hash;
	unsigned int flags;
	dvarType_t type;
	bool modified;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarLimits domain;
	dvar_t *hashNext;
	int unknown3;
};
#pragma pack(pop)


struct GfxCmdHeader
{
	unsigned short byteCount;
	char id;
	char ui3d;
};

union GfxColor
{
	unsigned int packed;
	char array[4];
};

struct GfxCmdDrawText2D
{
	GfxCmdHeader header;
	int type;
	float x;
	float y;
	float w;
	float h;
	float rotation;
	void *font;
	float xScale;
	float yScale;
	GfxColor color;
	signed int maxChars;
	int renderFlags;
	int cursorPos;
	char cursorLetter;
	GfxColor glowForceColor;
	int fxBirthTime;
	int fxLetterTime;
	int fxDecayStartTime;
	int fxDecayDuration;
	int fxRedactDecayStartTime;
	int fxRedactDecayDuration;
	void *fxMaterial;
	void *fxMaterialGlow;
	float padding;
	char text[3];
};

struct GfxCmdStretchPic
{
	GfxCmdHeader header;
	void *material;
	float x;
	float y;
	float w0;
	float w;
	float h;
	float s0;
	float t0;
	float s1;
	float t1;
	GfxColor color;
};

//#define GLOBAL_CGAME_PTR_ADDR		0xE22F18
//#define GLOBAL_CLIENT_PTR_ADDR	0xD689D8

typedef struct
{
	int x;						// 0x0
	int y;						// 0x4
	int width;					// 0x8
	int height;					// 0xC
	char padding000[0x14];		// 0x10
	float fovx;					// 0x24
	float fovy;					// 0x28
	float fovz;					// 0x2C
	char padding001[0x4];		// 0x30
	float fov;					// 0x34
	Vector3 viewOrigin;			// 0x38
	char padding002[0x4];		// 0x44
	Vector3 axis[3];			// 0x48
	// 0x6C
} RefDef;

typedef struct
{
	char padding000[0x2B4];		// 0x0
	int identifierThing;		// 0x2B4
	// 0x2B8
} WeaponInfoThing;

typedef struct
{
	char padding000[0xC];		// 0x0
	char name[0x20];			// 0xC
	int team;					// 0x2C
	char padding001[0x7D8];		// 0x30
	// 0x808
} ClientInfor;


typedef struct
{
	int localIndex;				// 0x0
	char padding000[0x244];		// 0x4
	int weaponData;				// 0x248
	char padding001[0x24];		// 0x24C
	float zoomAmount;			// 0x270
	char padding002[0x4832C];	// 0x274
	float refdefViewAngles[3];	// 0x485A0
	char padding003[0x2810];	// 0x485AC
	WeaponInfoThing weaponThing;// 0x4ADBC
	char padding004[0x2B1C];	// 0x4B074
	RefDef refdef;				// 0x4DB90
	char padding005[0x1C1A4];	// 0x4DBFC
	ClientInfor clientInfosZ[16];	// 0x69DA0
	char padding006[0xF070];	// 0x71E20
	float spreadMult;			// 0x80E90
} cgs;
//*(int*)0xE22F18+0x4DB90+0x38 = view origin

enum CommandMask
{
	CMD_MASK_FIRE = (1 << 31),
};
struct vec3i {
	int x,y,z;
};
/*typedef struct
{
	int time;					// 0x0
	int buttons;				// 0x4
	char padding000[0x4];		// 0x8
	vec3i viewAngles;		    // 0xC
	char padding001[0x24];		// 0x18
	// 0x3C
} CCommand;*/
typedef struct
{
	int time;					// 0x0
	int buttons;				// 0x4
	char padding000[0x4];		// 0x8
	vec3i viewAngles;		    // 0xC
	char padding002[0xC];       // 0x18
	char forwardmove;           // 0x24
	char sidemove;             // 0x25
	char upmove;                // 0x26
	char padding003[0x1];       // 0x27
	char padding001[0x14];		// 0x28
	// 0x3C
} CCommand;

typedef struct
{
	CCommand commands[128];		// 0x0
	int currentIdx;				// 0x1E00
} CInput;

typedef struct
{
	char padding000[0x98];		// 0x0
	Vector3 origin;				// 0x98
	char padding001[0x64];		// 0xA4
	float refViewAngle[2];		// 0x108
	char padding002[0x2B84];	// 0x110
	float viewAngle[2];			// 0x2C94
	char padding003[0x40014];	// 0x2C9C
	CInput input;				// 0x42CB0
} Client;

struct ScreenPlacement
{
    int64_t scaleVirtualToReal;
    int64_t scaleVirtualToFull;
    int64_t scaleRealToVirtual;
    int64_t virtualViewableMin;
    int64_t virtualViewableMax;
    int64_t virtualTweakableMin;
    int64_t virtualTweakableMax;
    int64_t realViewportBase;
    int64_t realViewportSize;
    int64_t realViewportMid;
    int64_t realViewableMin;
    int32_t realViewableMaxX;
    int32_t realViewableMaxY;
    int64_t realTweakableMin;
    int64_t realTweakableMax;
    int64_t subScreen;
    int hudSplitscreenScale;
};





cgs* Get_cgs()
{
	return *((cgs **)addresses.GLOBAL_CGAME_PTR_ADD);
}


Client* client_get()
{
	return *((Client **)addresses.GLOBAL_CLIENT_PTR_ADD);
}

int getServerTime() {
	return *(int*)(*(int*)addresses.GLOBAL_CLIENT_PTR_ADD/*0xD689D8*/+0x2AAC);
}

char *getHost() {
	return (char*)(*(int*)0xE22F1C+20*4);
}

char *getMapLong() {
	return (char*)(*(int*)0xE22F1C+8+7*12*4);
}

char *getMapShort() {
	return (char*)(*(int*)0xE22F1C+7*15*4-0xc);
}

char *getGameMode() {
	return (char*)(*(int*)0xE22F1C+12*4);
}

void drawLagometer(bool enable) {
	*(char*)(0x1CC56E0 + 0x18) = enable;
}

void drawDofDebug(bool enable) {
	*(char*)(0x1CBFE00 + 0x18) = enable;
}

void drawGun(bool enable) {
	*(char*)(0x1CC5020 + 0x18) = enable;
}
void drawFPS(bool enable) {
	*(int*)(0x1CC5680 + 0x18) = enable;
}
struct opd_s {
	int addr,toc;
};

opd_s AimTarget_isTargetVisible_t = { 0x15988, TOC };
opd_s SL_GetString_t = { 0x48ED68, TOC };
opd_s AimTarget_GetTagPos_t = { 0x015708, TOC };
opd_s CL_SetViewAngles_t = { 0x10B978, TOC };
opd_s Dvar_GetBool_t = { 0x3DA948, TOC };
opd_s Dvar_FindMalleableVar_t = { 0x3DA628, TOC };
opd_s CG_IsEntityFriendlyNotEnemy_t = { 0x049720, TOC };
opd_s R_ConvertColorToBytes_t = { 0x794980, TOC };
opd_s R_GetCommandBuffer_t = { 0x769F6C, TOC };
opd_s SetDrawText2DGlowParms_t = { 0x76A9B8, TOC };
opd_s Material_RegisterHandle_t = { 0x763220, TOC };
opd_s R_RegisterFont_t = { 0x75A2C0, TOC };
opd_s CG_GameMessage_t = { 0x6AD98, TOC };
opd_s Cbuf_AddText_t = { 0x313C18, TOC };
opd_s CG_DrawRotatedPicPhysical_t = { 0x0456F8, TOC };
opd_s R_AddCmdDrawTextInternal_t = { 0x76A910, TOC };
opd_s R_AddCmdDrawStretchPicInternal_t = { 0x076A3E8, TOC };
//opd_s CL_WritePacket_t = {0x00116524,TOC};
opd_s ScrPlace_GetView_t = {0x0015F080,TOC};


void(*R_AddCmdDrawStretchPicInternal)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float * color, void *material) = (void(*)(float, float, float, float, float, float, float, float, float *, void*))&R_AddCmdDrawStretchPicInternal_t;
void(*R_AddCmdDrawTextInternal)(const char* text, int maxChars, void* font, float x, float y, float yScale, float xScale, float rotation, float * colors, int Style) = (void(*)(const char*, int, void*, float, float, float, float, float, float *, int))&R_AddCmdDrawTextInternal_t;
int(*CG_DrawRotatedPicPhysical)(ScreenPlacement* screenPlacement, float X, float Y, float Width, float Height, float Angle, float* Color, void* Material) = (int(*)(ScreenPlacement*, float, float, float, float, float, float*, void*))&CG_DrawRotatedPicPhysical_t;
void(*Cbuf_AddText)(int LocalClient, char* text) = (void(*)(int, char*))&Cbuf_AddText_t;
void(*CL_SetViewAngles)(int LocalClient, const float* Angles) = (void(*)(int, const float*))&CL_SetViewAngles_t;
int(*SL_GetString)(const char *str) = (int(*)(const char*))&SL_GetString_t;
bool(*AimTarget_GetTagPos)(int targ_centity, unsigned tagIndex, float *pos) = (bool(*)(int, unsigned int, float*))&AimTarget_GetTagPos_t;
bool(*AimTarget_GetTagPos_r)(int targ_centity, unsigned tagIndex, float *pos) = (bool(*)(int, unsigned int, float*))&AimTarget_GetTagPos_t;
bool(*AimTarget_isTargetVisible)(int LocalClient, int Centity) = (bool(*)(int, int))&AimTarget_isTargetVisible_t;
bool(*Dvar_GetBool_f)(dvar_t* LocalClient) = (bool(*)(dvar_t*))&Dvar_GetBool_t;
dvar_t*(*Dvar_FindMalleableVar)(const char* LocalClient) = (dvar_t*(*)(const char*))&Dvar_FindMalleableVar_t;
void*(*R_ConvertColorToBytes)(const float* colorFloat, char* colorBytes) = (void*(*)(const float*, char*))&R_ConvertColorToBytes_t;
bool(*CG_IsEntityFriendlyNotEnemy)(int LocalClient, int Centity) = (bool(*)(int, int))&CG_IsEntityFriendlyNotEnemy_t;
GfxCmdHeader*(*R_GetCommandBuffer)(int renderCmd, int bytes) = (GfxCmdHeader*(*)(int, int))&R_GetCommandBuffer_t;
bool(*SetDrawText2DGlowParms)(GfxCmdDrawText2D *cmd, const float *color, const float *glowColor) = (bool(*)(GfxCmdDrawText2D*, const float*, const float*))&SetDrawText2DGlowParms_t;
void*(*Material_RegisterHandle)(const char *name, int imageTrack, bool errorIfMissing, int waitTime) = (void*(*)(const char*, int, bool, int))&Material_RegisterHandle_t;
void*(*R_RegisterFont)(const char * name, int imageTrack) = (void*(*)(const char*, int))&R_RegisterFont_t;
void(*CG_GameMessage)(int LocalClient, const char * msg) = (void(*)(int, const char *))&CG_GameMessage_t;
ScreenPlacement*(*ScrPlace_GetView)(int localClient) = (ScreenPlacement*(*)(int))&ScrPlace_GetView_t;
//void(*CL_WritePacket)(int LocalClient) = (void(*)(int))&CL_WritePacket_t;

void DrawText(const char *text, const char *fontName, float x, float y, float scale, float * color)
{
	R_AddCmdDrawTextInternal(text, 0x7FFFFFFF, R_RegisterFont(fontName, 0), x, y, scale, scale, 0, color, 0);
}

void DrawShader(float x, float y, float width, float height, float * color, const char *material)
{
	R_AddCmdDrawStretchPicInternal(x, y, width, height, 0, 0, 1, 1, color, Material_RegisterHandle(material, 0, 0, 0));
}

float getScreenPercentX(float percent) {
	Get_cgs()->refdef.width*percent;
}
float getScreenPercentY(float percent) {
	Get_cgs()->refdef.height*percent;
}

void DrawLine(float X1, float Y1, float X2, float Y2, float *color/*4 floats array*/, float a, float Width)
{
	//not working yet
	ScreenPlacement* scr = ScrPlace_GetView(0);
	float X, Y, Angle, L1, L2, H1;
	H1 = Y2 - Y1;
	L1 = X2 - X1;
	L2 = myMath::root(L1 * L1 + H1 * H1,2);//this is nor correct somehow
	L2*=myMath::sin(L2);
	X = X1 + ((L1 - L2) / 2);//(dif-length)/2+startx THIS IS CORRECT  this made it move right
	Y = Y1 + (H1 / 2);//correct
	scr->realViewableMaxX = (int32_t)X;
	scr->realViewableMaxY = (int32_t)Y;
	Angle = (float)myMath::atan2(H1,L1) * 180.00 / PI;
	float colorf[4] = { color[0], color[1], color[2],  a};
	CG_DrawRotatedPicPhysical(scr, X, Y, L2, Width, Angle, colorf, Material_RegisterHandle("white", 0, 0, 0));
}

int DrawLine1(int x1, int y1, int x2, int y2, float* color){
	ScreenPlacement* ptr = ScrPlace_GetView(0);

	float x,y,angle,l1,l2,h1;
    h1=y2-y1;
    l1=x2-x1;
    l2=sqrt(l1 * l1 + h1 * h1);
    x=x1+((l1-l2)/2);
    y=y1+(h1/2);
    angle=myMath::atan2(h1,l1)* (180 / 3.14159265358979323846) ;
    return CG_DrawRotatedPicPhysical(ptr,x,y,l2,1.0,angle,color, Material_RegisterHandle("white", 0, 0, 0));
}




bool checkAntiBan()
{
	int nop = 0x60000000;
	if (
		*(int*)0x004FBA74 == nop &&
		*(int*)0x00537DD4 == nop &&
		*(int*)0x00538148 == nop &&
		*(int*)0x005200E8 == nop &&
		*(int*)0x005200F4 == nop 
		) return true; else return false;
}

bool doAntiBan()
{
	char nop[4] = { 0x60, 0x00, 0x00, 0x00 };
	write_process((void*)0x004FBA74, nop, sizeof(nop));
	write_process((void*)0x00537DD4, nop, sizeof(nop));
	write_process((void*)0x00538148, nop, sizeof(nop));
	write_process((void*)0x005200E8, nop, sizeof(nop));
	write_process((void*)0x005200F4, nop, sizeof(nop));
	sleep(1000);
	if (checkAntiBan() == true)
		return true;
	else
		return false;
}


bool AimbotStarted = true;
bool DoAngles;
int LocalPlayer;
int NearstPlayer;
bool silentAimbot = true;
int autowallEnabled = 1;
//int superAutowallEnabled = 0;
bool allowAutowall = false;
bool NoSpreadToggle = true;
bool aimbothit;
bool safeAimbot = false;
Vector3 AimAngles;
Vector3 Position;
Vector3 vec;
Vector3 Angles;
Vector3 veccccc;
bool ClientReady;
bool Required = false;
bool ESP = true;
bool SNAPLINES = false;
bool invisibleBodies = false;
bool wallHackEnabled = false;
bool laserEnabled = false;
bool blinkingBodiesEnabled = false;
bool bigNamesEnabled = false;
bool autoShoot = true;
bool Stealth = true;
bool fakeLag = false;
bool redBoxes = false;
bool noRecoil = true;
bool vsat = true;
bool crosshair = false;
float espx, espy;
Vector3 espdrawpos = Vector3(50,50,50);
Vector3 abviewangles = Vector3(50,50,50);
char* TagOrigin = "j_head";
char *selectableTags[] = {"j_head","j_helmet","j_neck","torso_stabilizer"};
int currentTag = 0;
/*void nextTag() {
	currentTag++;
	if (currentTag > 3)
		currentTag = 0;
	switch(currentTag) {
	case 0:
		TagOrigin = "j_head";
		break;
	case 1:
		TagOrigin = "j_helmet";
		break;
	case 2:
		TagOrigin = "j_neck";
		break;
	case 3:
		TagOrigin = "torso_stabilizer";
		break;
	}
}*/
//char *font = "fonts/distfont";
float menux = 200, menuy = 100;
float menusizex = 220, menusizey = 300;

namespace colors {
float LightBlue[] = {0.0,1.0,1.0,1.0};
float Blue[] = {0.0,0.0,1.0,1.0};
float LightBlueOpaque[] = {0,1.0,1,100.0/255.0};
float DarkOpaque[] = {0,0,0,100.0/255.0};
float White[] = {1,1,1,1};
float Black[] = {0,0,0,1};
float RedOpaque[] = {1.0,0.0,0.0,100.0/255.0};
float green[] = {0,1,0,1};
float red[] = {1,0,0,1};
//text: r:0 g:217 b:0 bg: r:0 g:32 b:0
float hackerGreenText[] = {0,217.0/255.0,0,1.0};
float hackerGreenText2[] = {0,217.0/255.0,0,0.7};
float hackerGreenBackground[] = {0,32.0/255.0,0,1};
float hackerRedText[] = {217.0/255.0,0,0,1.0};
}

enum buttonslol {
	B_X = 0x1000,
	B_Triangle = 0x8000,
	B_Square = 0x4000,
	B_Circle = 0x2000,
	B_DpadUp = 0x0001,
	B_DpadDown = 0x0002,
	B_DpadLeft = 0x0004,
	B_DpadRight = 0x0008,
	B_R1 = 0x0200,
	B_R2 = 0x0800,
	B_R3 = 0x0080,
	B_L1 = 0x0100,
	B_L2 = 0x0400,
	B_L3 = 0x0040,
	B_Start = 0x0010,
	B_Select = 0x0020,
};
bool isButtonDown(int button) {
	return *(short*)0x1EF77B2 & button;
}