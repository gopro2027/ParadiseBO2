bool WorldPosToScreenPos_r(Vector3 pos, float* x, float* y);
int selectedMenu = 0;
int selectedOption = 0;
int currentOptionCount = 0;
int lastMenus[20];
int lastMenuCount = 0;
namespace MENUS {
enum MENUS {
	Closed,
	Name,
	LobbyInfo,
	Main,
	Prelobby,
	Self,
	PrivateLobby,
	Aimbot,
	AimbotPresets,
	Host,
	Infection,
	Injector,
	IPs,
	IP2s,
	Credits,
	Invalid,

	Submenus_Count
};
}

#define KEYBOARD_MAX_LENGTH 256
namespace SWindow {class WindowOption;};
namespace keyboardSWindow {void openKeyboard(SWindow::WindowOption *callback, int maxLength = KEYBOARD_MAX_LENGTH, char *title = "Enter Value", char *presetMessage = "");}
#include "Window.h"

namespace keyboard {
	wchar_t Title[KEYBOARD_MAX_LENGTH];
	wchar_t Preset[KEYBOARD_MAX_LENGTH];
	void GetWC(char *c, wchar_t *save) {
		int len = strlen(c);
		for (int i = 0; i < len; i++)
			save[i] = (wchar_t)c[i];
		save[len+1] = (wchar_t)'\0';
	}
	void (*callbackFunction)(char *) = 0;
	char str[KEYBOARD_MAX_LENGTH+1];
	void keyboardCallback(int LocalClientNum, const wchar_t * wString, int Length) {
		for (int i = 0; i < Length; i++) {
			str[i] = wString[i];
		}
		str[Length] = '\0';
		callbackFunction(str);
	}
	void OnScreenKeyboard(int LocalClientNum, wchar_t *Title, wchar_t *PresetMessage, int Length, void(*CompleteFunction)(int LocalClientNum, const wchar_t * wString, int Length), int PanelMode) {
		*(char*)0xD82144 = 1;
		opd_s AdNig = { 0x46710C, TOC };
		((void(*)(int, wchar_t *, wchar_t *, int, void(*)(int, const wchar_t*, int), int))&AdNig)(LocalClientNum, Title, PresetMessage, Length, CompleteFunction, PanelMode);
	}
	void openKeyboard(void (*callbackFunc)(char *), int maxLength = KEYBOARD_MAX_LENGTH, char *title = "Enter Value", char *presetMessage = "") {
		callbackFunction = callbackFunc;
		GetWC(title,Title);
		GetWC(presetMessage,Preset);
		OnScreenKeyboard(0, Title, Preset, KEYBOARD_MAX_LENGTH, keyboardCallback, 1);
	}
}


namespace keyboardSWindow {
	wchar_t Title[KEYBOARD_MAX_LENGTH];
	wchar_t Preset[KEYBOARD_MAX_LENGTH];
	void GetWC(char *c, wchar_t *save) {
	    //mbstowcs (save, c, strlen(c)+1);
		int len = strlen(c);
		for (int i = 0; i < len; i++)
			save[i] = (wchar_t)c[i];
		save[len+1] = (wchar_t)'\0';
	}
	//void (SWindow::WindowOption::*callbackFunction)(char *) = 0;
	SWindow::WindowOption *saveOption;
	char str[KEYBOARD_MAX_LENGTH+1];
	void keyboardCallback(int LocalClientNum, const wchar_t * wString, int Length) {
		for (int i = 0; i < Length; i++) {
			str[i] = wString[i];
		}
		str[Length] = '\0';
		saveOption->keyboardCallback(str);
	}
	void OnScreenKeyboard(int LocalClientNum, wchar_t *Title, wchar_t *PresetMessage, int Length, void(*CompleteFunction)(int LocalClientNum, const wchar_t * wString, int Length), int PanelMode) {
		*(char*)0xD82144 = 1;
		opd_s AdNig = { 0x46710C, TOC };
		((void(*)(int, wchar_t *, wchar_t *, int, void(*)(int, const wchar_t*, int), int))&AdNig)(LocalClientNum, Title, PresetMessage, Length, CompleteFunction, PanelMode);
	}
	void openKeyboard(SWindow::WindowOption *callback, int maxLength, char *title, char *presetMessage) {
		saveOption = callback;
		GetWC(title,Title);
		GetWC(presetMessage,Preset);
		OnScreenKeyboard(0, Title, Preset, KEYBOARD_MAX_LENGTH, keyboardCallback, 1);
	}
}


struct dvar_s {};

opd_s Dvar_SetFromStringByName_t = {0x3DE7D8,TOC};
void (*Dvar_SetFromStringByName)(char *dvarName, char *dvarValue) = (void(*)(char*,char*))&Dvar_SetFromStringByName_t;
//example: Dvar_SetFromStringByName("g_speed","999");

opd_s getDvarByName_t = {0x3DA628,TOC};
dvar_s *(*getDvarByName)(char *dvarString) = (dvar_s *(*)(char *))&getDvarByName_t;
//example: unsigned int dvar = getDvarByName("g_speed");

opd_s Dvar_AddFlags_t = {0x3DEA7C,TOC};
void (*Dvar_AddFlags)(dvar_s *dvar, unsigned int flag) = (void(*)(dvar_s *,unsigned int))&Dvar_AddFlags_t;
//example: Dvar_AddFlags(getDvarByName("g_speed"),0x500);

void setDvar(char *dvar, char *value) {
	Dvar_SetFromStringByName(dvar,value);
}

void setDvarAll(char *dvar, char *value) {
	Dvar_SetFromStringByName(dvar,value);
	Dvar_AddFlags(getDvarByName(dvar),0x500);//sets it to go to all players aka infection
}





/*
 private void freezeHostPreGame()
{
        PS3.SetMemory(40633944u, new byte[]{94,73,250,250,250});
        PS3.SetMemory(40633944u, new byte[]{94,73,250,250,250});
        PS3.SetMemory(40633944u, new byte[]{94,73,250,250,250});
        PS3.SetMemory(40633944u, new byte[]{94,73,250,250,250});
        PS3.SetMemory(40633944u, new byte[]{94,73,250,250,250});
        PS3.SetMemory(40633944u, new byte[]{94,73,250,250,250});
        PS3.SetMemory(40633944u, new byte[]{32,32,32,32,32,94,73,130,130,247});
        PS3.SetMemory(40633944u, new byte[]{32,32,32,32,32,94,73,130,130,247});
        PS3.SetMemory(40633944u, new byte[]{32,32,32,32,32,94,73,130,130,247});
        PS3.SetMemory(40633944u, new byte[]{32,32,32,32,32,94,73,130,130,247});
        PS3.SetMemory(40633944u, new byte[]{32,32,32,32,32,94,73,130,130,247});
        PS3.SetMemory(40633944u, new byte[]{32,32,32,32,32,94,73,130,130,247});
        PS3.SetMemory(40633944u, new byte[]{32,32,32,32,32,94,73,130,130,247});
        PS3.SetMemory(40633944u, new byte[]{94,73,153,153,245});
        PS3.SetMemory(40633944u, new byte[]{94,73,153,153,245});
        PS3.SetMemory(40633944u, new byte[]{94,73,153,153,247});
        PS3.SetMemory(40927800u, new byte[6]);
        PS3.Extension.WriteString(40633983u, !!!!!!! PUT PLAYER NAME HERE !!!!!!!);
} 
this is the code to freeze the host in the pre game lobby
*/


int printTimer = 0;
char *printText;
void print(char *text, int time = 100) {
	printTimer = time;
	printText = text;
}
void loopPrint() {
	if (printTimer > 0) {
		printTimer--;//text: r:0 g:217 b:0 bg: r:0 g:32 b:0
		DrawText(printText,"fonts/720/normalfont"/*"fonts/720/normalfont"*/,menux+5,25+menuy-50,0.85/*0.75*/,colors::White);//title
	}
}


void openMenu() {
	lastMenuCount = 0;
	selectedMenu = MENUS::Main;
	selectedOption = 0;
}
void closeMenu() {
	lastMenuCount = 0;
	selectedMenu = MENUS::Closed;
	selectedOption = 0;
}
void openSubmenu(int menu) {
	lastMenus[lastMenuCount] = selectedMenu;
	lastMenuCount++;
	selectedOption = 0;
	selectedMenu = menu;
}
void goBack() {
	if (lastMenuCount == 0) {
		closeMenu();
	} else {
		lastMenuCount--;
		selectedMenu = lastMenus[lastMenuCount];
		selectedOption = 0;
	}
}
void resetOptions() {
	/*int len = strlen((char*)0x10070200);
	for (int i = 0; i < len+1; i++) {
		*(char*)(0x10070200+i) = 0;
	}*/
	currentOptionCount = 0;
}
namespace Style
{
	/* Engine Colours */
	float Red[4] = { 1, 0, 0, 1 };
	float Blue[4] = { 0, 0, 1, 1 };
	float Green[4] = {23.0/255.0f,63.0/255.0f,105.0/255.0f,1};//{ 52.0/255.0,152.0/255.0,219.0/255.0 ,1 };
	float Yellow[4] = { 1, 1, 0, 1 };
	float White[4] = { 1, 1, 1, 1 };
	float Black[4] = { 0, 0, 0, .4 };
	float Black1[4] = { 0, 0, 0, .6 };
	float Black2[4] = { 0, 0, 0, 1 };
}
float sizescale = 2.0f;
float sizescalefont = 3;
void drawBackground() {
	DrawShader(menux + 54*sizescale, 36*sizescale, 126*sizescale, 13*sizescale+/*193*/(currentOptionCount+1.2f)*20*sizescale, Style::Black,"white"); // bg
 //DrawShader(menux + 55*sizescale, 70*sizescale, 125*sizescale, 155*sizescale, Style::Black,"white");
 DrawShader(menux + 54*sizescale, 53*sizescale, 126*sizescale, 17*sizescale, Style::Black1,"compass_emp"); // subtitle bar
 DrawShader(menux + 54*sizescale, 36*sizescale, 126*sizescale, 17*sizescale, Style::Green,"white"); // top
 DrawShader(menux + 180*sizescale, 36*sizescale, 2*sizescale, 13*sizescale+/*193*/(currentOptionCount+1.2f)*20*sizescale, Style::Green,"white"); // right
 DrawShader(menux + 54*sizescale, 36*sizescale, 2*sizescale, 13*sizescale+/*193*/(currentOptionCount+1.2f)*20*sizescale, Style::Green,"white"); // left
 //DrawShader(menux + 54*sizescale, (225-193)*(currentOptionCount+1.2f)+(currentOptionCount+1.2f)*20*sizescale, 126*sizescale, 4*sizescale, Style::Green,"white"); // bottom
 DrawText("         Paradise", "fonts/720/normalfont", menux + 76*sizescale, 51*sizescale, 0.35f*sizescalefont, Style::Black2);
 DrawText("v1.1", "fonts/720/normalfont", menux + 62*sizescale, 68*sizescale, 0.26f*sizescalefont, Style::White);
 DrawText("By gopro_2027", "fonts/720/normalfont", menux + 124*sizescale, 67*sizescale, 0.26f*sizescalefont, Style::White);
}
void addOption(char *text) {
	//*(unsigned int*)0x0729440 = 0x10070200;
	//*(char*)0x00253AC8 = 0x40;
	//strcpy((char*)(0x10070200+strlen((char*)0x10070200)),text);

	if (currentOptionCount == selectedOption && selectedMenu != MENUS::IPs && selectedMenu != MENUS::Credits && selectedMenu != MENUS::LobbyInfo) {
		//DrawShader(menux,2*25-(25*0.75)  +menuy+5+  25*0.75*currentOptionCount  ,menusizex,25*0.75,colors::hackerGreenText2/*LightBlue*/,"white");
		//DrawText(">","fonts/720/consolefont",menux+5,25+menuy+5+25+25*0.75*currentOptionCount,1/*0.75*/,colors::hackerGreenText/*White*/);
		//DrawText(text,"fonts/720/consolefont",menux+15,25+menuy+5+25+25*0.75*currentOptionCount,1/*0.75*/,colors::hackerGreenText/*White*/);
		DrawText(text, "fonts/720/normalfont", menux + 60*sizescale, (90+currentOptionCount*20)*sizescale, 0.30f*sizescalefont, Style::Green);
	} else {
		//DrawText(text,"fonts/720/consolefont",menux+5,25+menuy+5+25+25*0.75*currentOptionCount,1/*0.75*/,colors::hackerGreenText/*White*/);
		DrawText(text, "fonts/720/normalfont", menux + 60*sizescale, (90+currentOptionCount*20)*sizescale, 0.30f*sizescalefont, Style::White);
	}
	currentOptionCount++;
}

void addBoolOption(char *text, bool data) {
	char textt[200];
	snprintf(textt,200,"%s^7 ^8[%s]",text,data?"^2On^8":"^1Off^8");
	addOption(textt);
	//currentOptionCount--;
	//if (data)
		//DrawText("O","fonts/720/consolefont",menux+(menusizex-25*0.75),25+menuy+5+25+25*0.75*currentOptionCount,1/*0.75*/,colors::hackerGreenText/*White*/);
		//DrawShader(menux+(menusizex-25*0.75),2*25-(25*0.75)  +menuy+5+  25*0.75*currentOptionCount  ,25*0.75,25*0.75,colors::green,"white");
	//else
		//DrawText("X","fonts/720/consolefont",menux+(menusizex-25*0.75),25+menuy+5+25+25*0.75*currentOptionCount,1/*0.75*/,colors::hackerRedText/*White*/);
		//DrawShader(menux+(menusizex-25*0.75),2*25-(25*0.75)  +menuy+5+  25*0.75*currentOptionCount  ,25*0.75,25*0.75,colors::red,"white");
	//currentOptionCount++;
}
void addStringOption(char *text, char *data) {
	char textt[200];
	snprintf(textt,200,"%s^8 [^1%s^8]",text,data);
	addOption(textt);
}

int pressedButtons = 0;
bool isButtonJustPressed(int button) {
	if ((pressedButtons & button) == false) {
		//button hasn't been previously pressed
		if (isButtonDown(button)) {
			pressedButtons |= button;
			return true;
		}
	} else {
		//button was previously pressed
		if (!isButtonDown(button))
			pressedButtons &= ~button;//toggle off cuz it isn't being pressed anymore
	}
	return false;
}

void addArrayOption(char *text, int *index, int min, int max, char **strings) {
	char buf[200];
	snprintf(buf,sizeof(buf),"%s^8 <^1%s^8>",text,strings[*index]);
	if (currentOptionCount == selectedOption) {
		print("R1 and L1 to change selection.",1);
		if (isButtonJustPressed(B_R1)) {
			*index = *index + 1;
			if (*index > max)
				*index = min;
		}
		if (isButtonJustPressed(B_L1)) {
			*index = *index - 1;
			if (*index < min)
				*index = max;
		}
	}
	addOption(buf);
}

void addIntOption(char *text, int *var, int min, int max) {
	char buf[200];
	snprintf(buf,sizeof(buf),"%s^8 <^1%i^8>",text,*var);
	if (currentOptionCount == selectedOption) {
		print("R1 and L1 to change selection.",1);
		if (isButtonJustPressed(B_R1)) {
			*var = *var + 1;
			if (*var > max)
				*var = min;
		}
		if (isButtonJustPressed(B_L1)) {
			*var = *var - 1;
			if (*var < min)
				*var = max;
		}
	}
	addOption(buf);
}




int getOption() {
	if (DvarGetBool("cl_ingame")) {
		if (isButtonJustPressed(B_X))
			return selectedOption;
		else
			return -1;
	} else {
		if (isButtonJustPressed(B_DpadRight))
			return selectedOption;
		else
			return -1;
	}
	return -1;
}

void doButtons() {
	if (selectedMenu != MENUS::Closed) {
		//printf("Menu Opened\n");
		//menu is opened
		if (isButtonJustPressed(B_DpadUp)) {
			selectedOption--;
		}
		if (isButtonJustPressed(B_DpadDown)) {
			selectedOption++;
		}
		if (selectedOption >= currentOptionCount)
			selectedOption = 0;
		if (selectedOption < 0)
			selectedOption = currentOptionCount-1;
		if (DvarGetBool("cl_ingame")) {
			if (isButtonJustPressed(B_Circle))
				goBack();
		} else {
			if (isButtonJustPressed(B_DpadLeft))
				goBack();
		}
		
	} else {
		//printf("Menu Not Opened\n");
		//menu is not opened
		if (isButtonDown(B_DpadUp) && isButtonDown(B_L1)) {
			isButtonJustPressed(B_DpadUp);//cancel out for button presses
			isButtonJustPressed(B_L1);//cancel out for button presses
			openMenu();
		}
	}
}

void endGame() {
	char buffer[50];
	snprintf(buffer, sizeof(buffer), "cmd mr %i %i %s", *(int*)(0xF109E8 + 0x13B4), 3, "endround");
	Cbuf_AddText(0, buffer);
}

/*void killServer() {
	char buffer[50];
	snprintf(buffer, sizeof(buffer), "cmd mr %i %i %s", *(int*)(0xF109E8 + 0x13B4), 3, "killserverpc");
	Cbuf_AddText(0, buffer);
}*/


enum uiMenuCommand_t
{
    UIMENU_NONE = 0x0,
    UIMENU_MAIN = 0x1,
    UIMENU_MAINLOBBY = 0x2,
    UIMENU_INGAME = 0x3,
    UIMENU_PREGAME = 0x4,
    UIMENU_POSTGAME = 0x5,
    UIMENU_WM_QUICKMESSAGE = 0x6,
    UIMENU_SCRIPT_POPUP = 0x7,
    UIMENU_SCOREBOARD = 0x8,
    UIMENU_GAMERCARD = 0x9,
    UIMENU_MUTEERROR = 0xA,
    UIMENU_SPLITSCREENGAMESETUP = 0xB,
    UIMENU_SYSTEMLINKJOINGAME = 0xC,
    UIMENU_PARTY = 0xD,
    UIMENU_WAGER_PARTY = 0xE,
    UIMENU_LEAGUE_PARTY = 0xF,
    UIMENU_GAMELOBBY = 0x10,
    UIMENU_WAGERLOBBY = 0x11,
    UIMENU_PRIVATELOBBY = 0x12,
    UIMENU_LEAGUELOBBY = 0x13,
    UIMENU_THEATERLOBBY = 0x14,
    UIMENU_MIGRATION = 0x15,
    UIMENU_CONTROLLERREMOVED = 0x16,
    UIMENU_ENDOFGAME = 0x17,
    UIMENU_INGAME_NOUNPAUSE = 0x18,
};
void runServer(char *command, int menuid) {
	char buffer[250];
	snprintf(buffer, sizeof(buffer), "cmd mr %i %i %s;", *(int*)(0xF109E8 + 0x13B4), menuid, command);
	Cbuf_AddText(0, buffer);
}

void spoofIP() {
	/*char bytes[] = { 0x23, 0x07, 0x49, 0x22, 0x33, 0x01 };
	for (int client = 0; client < 18; client++) {
		memcpy((void*)(0x00f9e726 + ((unsigned int)client * 328)), bytes , sizeof(bytes));
	}*/

	unsigned int ip = *(unsigned int*)0x0FA9A2E;
	for (unsigned int i = 0; i < 0x200000; i++) {
		if (*(unsigned int*)(0x1A274E4+i) == ip) {
			*(unsigned int*)(0x1A274E4+i) = 0xFF00FF00;
		}
	}

	/*SpoofIPAddr = Search(PS3.Extension.ReadBytes(0x0FA9A2E, 4), 0x1A274E4, 0x200000, 4);
            if (SpoofIPAddr != 0x0)
            {
               //do a sleep maybe 2 be sure?
                PS3.SetMemory(Convert.ToUInt32(SpoofIPAddr), GrabIP("0.0.0.0"));
            }*/
            
}

void threadLoop() {
	char nop[] = { 0x60, 0x00, 0x00, 0x00 };
	char rb[] = { 0x38, 0x60, 0x00, 0x001 };
	char j = 0x40;
	char blr[] = {0x4E, 0x80, 0x00, 0x20 };
	write_process((void*)0x000F9E54, &nop, sizeof(nop));//no recoil
	//write_process((void*)0x000783E0, &rb, sizeof(rb));//redboxes
	//write_process((void*)0x00078604, &nop, sizeof(nop));//redboxes
	write_process((void*)0x00033C60, &nop, sizeof(nop));//vsat
	//write_process((void*)0x52FC6C, &j, 1);//probation bypass THIS CAUSES THE GAME TO FREEZE 0x40
	//*(char*)0x52FC6C = 0x40;//probation bypass   LMAO
	*(char*)(0x53FC6C+0x1) = 0x82;



	/*
	                    byte[] Bypass = new byte[] { 0x41, 0x80 };
                    PS3.SetMemory(0x53FC6C, Bypass);
ON
                    byte[] Bypass = new byte[] { 0x41, 0x82 };
                    PS3.SetMemory(0x53FC6C, Bypass);
OFF
	*/



	//*(int*)0x52FFF8 = 0x60000000;//disable the part that branches to the function when doing an invite
	//*(int*)(0x52FC74) = 0x60000000;
	//write_process((void*)0x52FAA0,&blr,sizeof(blr));

	/*write_process((void*)0x35E96C,&nop,sizeof(nop));
	write_process((void*)0x35E9A0,&nop,sizeof(nop));
	write_process((void*)0x35EA64,&nop,sizeof(nop));
	write_process((void*)0x381154,&nop,sizeof(nop));protected chars bypass
	write_process((void*)0x35E9E4,&nop,sizeof(nop));
	write_process((void*)0x351B74,&nop,sizeof(nop));
	write_process((void*)0x351B4C,&nop,sizeof(nop));*/

	//write_process((void*)0x,&nop,sizeof(nop));
	//write_process((void*)0x00463008,&blr,4);//remember to take this out before release :)
	//sleep(20000);
	//printf("\n\n\nUNPATCHING THAT SHIT\n\n\n");
	//*(char*)0x52FC6C = 0x38;
	//23,63,105
	//53F430 set that to blr for probation bypass
	*(int*)0x13FD48 = 0x38600000;//party_minLobbyTime fix return 0
	*(int*)0x13918C = 0x38600000;//party_minLobbyTime fix return 0
	*(int*)0x138880 = 0x38600000;//party_minLobbyTime fix return 0  THIS ONE IS FOR WHEN YOU FIRST JOIN, ONE OF THE OTHERS IS FOR POST-GAME
	for (;;) {
		*(int*)(0x1CD89A0 + 0x18) = 0;//probation probation_public_probationTime
		//force host needs to set values a lot
		*(int*)(0x1CD5A00 + 0x18) = 1;//party_minplayers
		//*(int*)(0x1CD6960 + 0x18) = 1;//party_dedicatedMergeMinPlayers
		*(int*)(0x1CD5B20 + 0x18) = 0;//party_gameStartTimerLength (10 seconds one)
		//*(int*)(0x1CD6480 + 0x18) = 0;//party_minLobbyTime (45 second one) patched with code above
		sleep(200);
	}
}
namespace aimbotPresets {
enum aimbotPresets {
	Scorestreak,
	SilentAim,
	SilentAimNoSpread,
	SilentAimNoSpreadAutowall,
	SilentAimNoSpreadSuperAutowall,
	RegularAimbot,
	RegularAimbotNoSpread,
	Trickshot,
	NoAimbot
};
}
void setAimbotPreset(int preset) {
	switch(preset) {
	case aimbotPresets::Scorestreak:
		AimbotStarted = true;
		silentAimbot = false;
		Required = false;
		autoShoot = true;
		NoSpreadToggle = true;
		Stealth = true;
		fakeLag = false;
		autowallEnabled = false;
		//superAutowallEnabled = false;
		break;
	case aimbotPresets::SilentAim:
		AimbotStarted = true;
		silentAimbot = true;
		Required = true;
		autoShoot = true;
		NoSpreadToggle = false;
		Stealth = true;
		fakeLag = false;
		autowallEnabled = false;
		//superAutowallEnabled = false;
		break;
	case aimbotPresets::SilentAimNoSpread:
		AimbotStarted = true;
		silentAimbot = true;
		Required = false;
		autoShoot = true;
		NoSpreadToggle = true;
		Stealth = true;
		fakeLag = false;
		autowallEnabled = true;
		//superAutowallEnabled = false;
		break;
	case aimbotPresets::SilentAimNoSpreadAutowall:
		AimbotStarted = true;
		silentAimbot = true;
		Required = false;
		autoShoot = true;
		NoSpreadToggle = true;
		Stealth = true;
		fakeLag = false;
		autowallEnabled = true;
		//superAutowallEnabled = false;
		break;
	case aimbotPresets::RegularAimbot:
		AimbotStarted = true;
		silentAimbot = false;
		Required = true;
		autoShoot = true;
		NoSpreadToggle = false;
		Stealth = true;
		fakeLag = false;
		autowallEnabled = false;
		//superAutowallEnabled = false;
		break;
	case aimbotPresets::RegularAimbotNoSpread:
		AimbotStarted = true;
		silentAimbot = false;
		Required = false;
		autoShoot = true;
		NoSpreadToggle = true;
		Stealth = true;
		fakeLag = false;
		autowallEnabled = false;
		//superAutowallEnabled = false;
		break;
	case aimbotPresets::NoAimbot:
		AimbotStarted = false;
		silentAimbot = false;
		Required = false;
		autoShoot = false;
		NoSpreadToggle = false;
		Stealth = false;
		fakeLag = false;
		autowallEnabled = false;
		//superAutowallEnabled = false;
		break;
	case aimbotPresets::Trickshot:
		AimbotStarted = true;
		silentAimbot = true;
		Required = true;
		autoShoot = true;
		NoSpreadToggle = true;
		Stealth = true;
		fakeLag = false;
		autowallEnabled = false;
		//superAutowallEnabled = false;
		break;
	case aimbotPresets::SilentAimNoSpreadSuperAutowall:
		AimbotStarted = true;
		silentAimbot = true;
		Required = false;
		autoShoot = true;
		NoSpreadToggle = true;
		Stealth = true;
		fakeLag = false;
		autowallEnabled = 3;
		//superAutowallEnabled = true;
		break;
	}
}
void ipGrabber() {
	for (int i = 0; i < 18; i++) {
				//0x00F9E690+0x148*0 xuid
				int ip = *(int*)(0x00F9E690+0x148*i+0x96);
				if (ip != 0 && i != Get_cgs()->localIndex) {
					char *name = (char*)(0x00F9E690+0x148*i+0x8);
					int p1 = (ip&0xff000000)>>24;
					int p2 = (ip&0x00ff0000)>>16;
					int p3 = (ip&0x0000ff00)>>8;
					int p4 = (ip&0x000000ff)>>0;
					char buf[100];
					snprintf(buf,sizeof(buf),"%s - %i.%i.%i.%i\n",name,p1,p2,p3,p4);
					//strcpy((char*)(0x10070400+strlen((char*)0x10070400)),buf);
					appendToFile("/dev_hdd0/tmp/gopro_2027/BO2IPS.txt",buf,strlen(buf));
				}
			}
	print("IP's dumped to /dev_hdd0/tmp/gopro_2027/BO2IPS.txt");
	//appendToFile("/dev_hdd0/tmp/gopro_2027/BO2IPS.txt",(char*)0x10070400,strlen((char*)0x10070400));
}
#include "Injector.h"
bool menuOpened = false;
#include "WindowSetup.h"
void doMenu() {
	if (true/*DvarGetBool("cl_ingame")*/) {
		//1280x720 or 880x720
		//
		DrawShader(900, 50-25*0.75, 250, 25*0.75, colors::DarkOpaque, "white");
		DrawText("Paradise SPRX By gopro_2027 L1+UP","fonts/720/consolefont",904,50,0.9/*0.74*/,colors::LightBlue);

		//DrawLine(menux,menuy,menux+menusizex,menuy+menusizey,colors::Black,1.0,5);
		loopPrint();

		if(DvarGetBool("cl_ingame"))
			backgroundColor.a = 70;
		else
			backgroundColor.a = 255;

		//0x3529C8
		//0x3E51B8

		if (isButtonDown(B_DpadUp) && isButtonJustPressed(B_L1)) {
			menuOpened = true;
			//*(unsigned int*)0x00126898 = 0x38600000;//fix for freeze when joining some lobbies li r3, 0
			//selectedWindow = MENUS::Main;
			//*(char*)0x008E2AD0 = 1;
			//setDvar("ui_hideminimap","1");
			//setDvar("compasssize","0");
		}

		if (menuOpened) {
			main.run();
			menuVars::doMenuVars();
			if (isButtonJustPressed(B_R3)) {//BUTTON O WAS PRESSED
				menuOpened = false;
				//*(char*)0x008E2AD0 = 0;
				//setDvar("ui_hideminimap","0");
				
			}
		}







#ifdef oldcodeforbase
		//printf("endpos: %i %i %i    dir*100: %i %i %i\n",(int)espdrawpos.x,(int)espdrawpos.y,(int)espdrawpos.z,(int)(abviewangles.x*100),(int)(abviewangles.y*100),(int)(abviewangles.z*100));
		//float Red[4] = { 1, 0, 0, 1 };
		//if (WorldPosToScreenPos_r(espdrawpos, &espx, &espy))
			//DrawText(".", "fonts/720/normalfont", espx, espy, 0.5, Red);
		if (selectedMenu != MENUS::Closed) {
			drawBackground();
			/*
			//render shit (before resetting menu data)
			//DrawShader(menux-5, menuy-5, menusizex+10, menusizey+10, colors::Black/*LightBlueOpaque*, "black");//background black
			DrawShader(menux, menuy, menusizex, menusizey, colors::hackerGreenBackground/*LightBlueOpaque*, "white");//background green
			DrawShader(menux, menuy, menusizex, menusizey, colors::hackerGreenBackground/*LightBlueOpaque*, "compass_emp"/*"compass_scrambler_large"*//*"white"*);//background scrambler
			//DrawShader(menux, menuy, menusizex, menusizey, colors::DarkOpaque, "white");//background
			DrawText("Paradise BO2","fonts/720/consolefont",menux+5,25+menuy+5,2.0,colors::hackerGreenText);//title
			*/
		}
		resetOptions();
		switch (selectedMenu) {
		case MENUS::Closed:
			//do nothing
			break;
		case MENUS::Main:
			if(DvarGetBool("cl_ingame")) {
				addOption("Public Lobby Mods");
				addOption("Private Lobby Mods");
				addOption("Aimbot Menu");
				addOption("Aimbot Presets");
				addOption("IP Addresses");
				addOption("Lobby Info");
				addOption("Host Menu");
				addOption("Infections");
				addOption("Credits");
				switch(getOption()) {
				case 0:
					openSubmenu(MENUS::Self);
					break;
				case 1:
					openSubmenu(MENUS::PrivateLobby);
					break;
				case 2:
					openSubmenu(MENUS::Aimbot);
					break;
				case 3:
					openSubmenu(MENUS::AimbotPresets);
					break;
				case 4:
					ipGrabber();
					print("IP's dumped to /dev_hdd0/tmp/gopro_2027/BO2IPS.txt");
					openSubmenu(MENUS::IPs);
					break;
				case 5:
					openSubmenu(MENUS::LobbyInfo);
					break;
				case 6:
					openSubmenu(MENUS::Host);
					break;
				case 7:
					openSubmenu(MENUS::Infection);
					break;
				case 8:
					openSubmenu(MENUS::Credits);
					break;
				}
			} else {
				//addOption("GSC Injector");
				addOption("Pre-Lobby");
				addOption("Name Changer");
				addOption("IP Addresses");
				//addOption("Change Team");
				addOption("GSC Injector");
				switch(getOption()) {
				case 0:
					//openSubmenu(MENUS::Injector);
					openSubmenu(MENUS::Prelobby);
					break;
				case 1:
					openSubmenu(MENUS::Name);
					break;
				case 2:
					ipGrabber();
					print("IP's dumped to /dev_hdd0/tmp/gopro_2027/BO2IPS.txt");
					openSubmenu(MENUS::IPs);
					break;
				//case 3:
					//openSubmenu(MENUS::PrivateLobby);
					//break;
				case 3:
					openSubmenu(MENUS::Injector);
					break;
				}
			}
			break;
		case MENUS::Prelobby:
			addBoolOption("Force Host",!(bool)(*(char*)0x1CD6018));
			addOption("Spoof IP Address");
			switch(getOption()) {
			case 0:
				/*
				            if (forceHostOn == true)
            {
                byte[] numArray = new byte[1];
                PS3.SetMemory(30236696U, numArray);
                
            }
            else
            {
                byte[] numArray = new byte[1] { (byte)1 };
                PS3.SetMemory(30236696U, numArray);
                
            }
				*/
				//*(char*)0x01CCF4D8 = (char)(!(bool)(*(char*)0x01CCF4D8));
				*(char*)0x1CD6018 = (char)(!(bool)(*(char*)0x1CD6018));
				break;
			case 1:
				spoofIP();
				break;
			}
			break;
		case MENUS::LobbyInfo:
			addStringOption("Host",getHost());
			addStringOption("Map",getMapLong());
			addStringOption("Gamemode",getGameMode());
			break;
		case MENUS::Name:
			{
			char *name1 = "^5Paradise^1SPRX";
			char *name2 = "AverageJoe2012";
			char *name3 = "CharlesBabbage";
			char *name4 = "^12^2SPOOK^34^5U";
			char *name5 = "paradisesprx.com";
			char *name6 = "[{%}][{%}][{%}]";
			char buf[128];
			addOption(fprintf("> %s",name1));
			addOption(fprintf("> %s",name2));
			addOption(fprintf("> %s",name3));
			addOption(fprintf("> %s",name4));
			addOption(fprintf("> %s",name5));
			addOption(fprintf("> %s",name6));
			switch(getOption()) {
			case 0:
				strcpy((char*)0x026C0658,name1);
				strcpy((char*)0x026c067f,name1);
				break;
			case 1:
				strcpy((char*)0x026C0658,name2);
				strcpy((char*)0x026c067f,name2);
				break;
			case 2:
				strcpy((char*)0x026C0658,name3);
				strcpy((char*)0x026c067f,name3);
				break;
			case 3:
				strcpy((char*)0x026C0658,name4);
				strcpy((char*)0x026c067f,name4);
				break;
			case 4:
				strcpy((char*)0x026C0658,name5);
				strcpy((char*)0x026c067f,name5);
				break;
			case 5:
				strcpy((char*)0x026C0658,name6);
				strcpy((char*)0x026c067f,name6);
				break;
			}
			}//30151740 = 111,80,0,0,47,80,0,0   green bodies     PS3.SetMemory(537808u, new byte[]{56,192,255,255});
			break;
		case MENUS::Aimbot:
			addBoolOption("Aimbot",AimbotStarted);
			addBoolOption("Silent Aimbot",silentAimbot);
			addBoolOption("Require Aiming",Required);
			addBoolOption("Auto Shoot",autoShoot);
			addBoolOption("No Spread",NoSpreadToggle);
			addBoolOption("Check Visibility",Stealth);
			char *autowallnames[4] = {"Disabled","Stable","Experimental","HvH Mode"};
			addArrayOption("Autowall",&autowallEnabled,0,3,autowallnames);
			addBoolOption("Safe Aimbot",safeAimbot);
			addArrayOption("Tag",&currentTag,0,3,selectableTags);
			switch(getOption()) {
			case 0:
				AimbotStarted = !AimbotStarted;
				break;
			case 1:
				silentAimbot = !silentAimbot;
				break;
			case 2:
				Required = !Required;
				break;
			case 3:
				autoShoot = !autoShoot;
				break;
			case 4:
				NoSpreadToggle = !NoSpreadToggle;
				break;
			case 5:
				Stealth = !Stealth;
				break;
			case 6:
				//autowallEnabled = !autowallEnabled;
				break;
			/*case 7:
				superAutowallEnabled = !superAutowallEnabled;
				if (superAutowallEnabled) {
					print("Will cause extra lag.");
					autowallEnabled = true;
				}
				break;*/
			/*case 7:
				fakeLag = !fakeLag;
				print("Does not work with no spread. Buggy.");
				break;*/
			case 7:
				safeAimbot = !safeAimbot;
				print("Recommended to enable. Temporary fix for a bug dealing with out of bounds view angles.");
				break;
			/*case 8:
				nextTag();
				break;*/
			}
			break;
		case MENUS::Self:
			addBoolOption("Vsat",vsat);
			addBoolOption("No Recoil",noRecoil);
			addBoolOption("Simple Snaplines",SNAPLINES);
			addBoolOption("Simple ESP",ESP);
			addBoolOption("Force Host",(bool)(*(char*)0x01CCF4D8));
			addBoolOption("Invisible Entities",invisibleBodies);
			addBoolOption("Wall Hack",wallHackEnabled);
			addBoolOption("Laser",laserEnabled);
			addBoolOption("Lagometer",*(char*)(0x1CC56E0 + 0x18));
			addBoolOption("DOF Debug",*(char*)(0x1CBFE00 + 0x18));
			addBoolOption("Draw Gun",*(char*)(0x1CC5020 + 0x18));
			addBoolOption("Draw FPS",*(int*)(0x1CC5680 + 0x18));
			addBoolOption("Mini Crosshair",crosshair);
			//addBoolOption("Floating Bodies",blinkingBodiesEnabled);
			//addBoolOption("Big Names",bigNamesEnabled);
			addOption("End Game");
			//addOption("Kill Server");
			//addOption("marines");
			//addOption("opfour");
			switch(getOption()) {
			case 0:
				vsat = !vsat;
				if (vsat) {
					char nop[] = { 0x60, 0x00, 0x00, 0x00 };
					write_process((void*)0x00033C60, &nop, sizeof(nop));//vsat
				} else {
					char rec[] = { 0x40, 0x81, 0x00, 0x44 };
					write_process((void*)0x00033C60, &rec, sizeof(rec));
				}
				break;
			case 1:
				noRecoil = !noRecoil;
				if (noRecoil) {
					char nop[] = { 0x60, 0x00, 0x00, 0x00 };
					write_process((void*)0x000F9E54, &nop, sizeof(nop));//no recoil
				} else {
					char rec[] = { 0x48, 0x50, 0x6D, 0x65 };
					write_process((void*)0x000F9E54, &rec, sizeof(rec));
				}
				break;
			case 2:
				/*redBoxes = !redBoxes;
				if (redBoxes) {
					char nop[] = { 0x60, 0x00, 0x00, 0x00 };
					char rb[] = { 0x38, 0x60, 0x00, 0x001 };
					write_process((void*)0x000783E0, rb, sizeof(rb));//redboxes
					write_process((void*)0x00078604, nop, sizeof(nop));//redboxes
				} else {
					char rec1[] = { 0x38, 0x60, 0x00, 0x00 };
					char rec[] = { 0x41, 0x81, 0x01, 0x0C };
					write_process((void*)0x00078604, rec, sizeof(rec));
					write_process((void*)0x000783E0, rec1, sizeof(rec1));
				}*/
				SNAPLINES = !SNAPLINES;
				break;
			case 3:
				ESP = !ESP;
				break;
			case 4:
				*(char*)0x01CCF4D8 = (char)(!(bool)(*(char*)0x01CCF4D8));
				break;
			case 5:
				invisibleBodies = !invisibleBodies;
				char invisiblebodieson[] = {0x1};
				char invisiblebodiesoff[] = {0x0};
				if (invisibleBodies)
					write_process((void*)0x0076F25B,invisiblebodieson,1);
				else
					write_process((void*)0x0076F25B,invisiblebodiesoff,1);
				break;
			case 6:
				wallHackEnabled = !wallHackEnabled;
				char wallhackon[] = { 0x38, 0xC0, 0xFF, 0xFF};
				char wallhackoff[] = {0x63, 0x26, 0x00, 0x00};
				if (wallHackEnabled)
					write_process((void*)0x834D0,wallhackon,4);
				else
					write_process((void*)0x834D0,wallhackoff,4);
				break;
			case 7:
				laserEnabled = !laserEnabled;
				char laseron[] = {0x2C, 0x03, 0x00, 0x01};
				char laseroff[] = {0x2C, 0x03, 0x00, 0x00};
				if (laserEnabled)
					write_process((void*)0xEF68C,laseron,4);
				else
					write_process((void*)0xEF68C,laseroff,4);
				break;
			case 8:
				*(char*)(0x1CC56E0 + 0x18) = !*(char*)(0x1CC56E0 + 0x18);
				break;
			case 9:
				*(char*)(0x1CBFE00 + 0x18) = !*(char*)(0x1CBFE00 + 0x18);
				break;
			case 10:
				*(char*)(0x1CC5020 + 0x18) = !*(char*)(0x1CC5020 + 0x18);
				break;
			case 11:
				*(int*)(0x1CC5680 + 0x18) = !*(int*)(0x1CC5680 + 0x18);
				break;
			case 12:
				crosshair = !crosshair;
				break;
			/*case 8:
				blinkingBodiesEnabled = !blinkingBodiesEnabled;
				char blinkingbodieson[] = {0x43, 0x48};
				char blinkingbodiesoff[] = {0xC4, 0x48};
				if (blinkingBodiesEnabled)
					write_process((void*)0x1CE03D8,blinkingbodieson,2);
				else
					write_process((void*)0x1CE03D8,blinkingbodiesoff,2);
				break;
			case 9:
				bigNamesEnabled = !bigNamesEnabled;
				char bneon[] = {0x3F, 0xFF, 0xFF, 0x00};
				char bneoff[] = { 0x3F, 0x26, 0x66, 0x66};
				if (bigNamesEnabled)
					write_process((void*)0x1CD6E98,bneon,4);
				else
					write_process((void*)0x1CD6E98,bneoff,4);
				break;*/
			//ADD MORE STUFF NOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			case 13:
				endGame();
				break;
			case 14:
				//killServer();
				Cbuf_AddText(0, "cmd sl");
				break;
			/*case 15:
				runServer("changeclass_marines_splitscreen",3);
				break;
			case 16:
				runServer("changeclass_opfor_splitscreen",3);
				break;*/
			}
			break;
		case MENUS::PrivateLobby:
			static int lobbythingy = 0;
			addOption("Switch To Axis");
			addOption("Switch To Allies");
			addOption("Switch To Cod-Caster");
			//addIntOption("Mode",&lobbythingy,0,0x19);
			switch(getOption()) {
			case 0:
				print("Switched to axis");
				for (int i = 0; i < 0x20; i++)
				runServer("axis",i);
				break;
			case 1:
				print("Switched to allies");
				for (int i = 0; i < 0x20; i++)
				runServer("allies",i);
				break;
			case 2:
				print("Switched to spectator");
				for (int i = 0; i < 0x20; i++)
				runServer("spectator",i);
				break;
			}
			break;
		case MENUS::AimbotPresets:
			addOption("No Aimbot");
			//addOption("Regular Aimbot");
			//addOption("Regular Aimbot No Spread");
			//addOption("Silent Aimbot");
			addOption("Silent No Spread Autowall");
			addOption("HvH Mode");
			//addOption("Silent Aimbot No Spread Autowall");
			addOption("Scorestreak Aimbot");
			addOption("Non Host Trickshot Aimbot");
			switch(getOption()) {
			case 0:
				setAimbotPreset(aimbotPresets::NoAimbot);
				print("Aimbot is now disabled");
				break;
			/*case 1:
				setAimbotPreset(aimbotPresets::RegularAimbot);
				print("This requires aiming");
				break;
			case 2:
				setAimbotPreset(aimbotPresets::RegularAimbotNoSpread);
				print("This does not require aiming");
				break;
			case 3:
				setAimbotPreset(aimbotPresets::SilentAim);
				print("This requires aiming");
				break;*/
			case 1:
				setAimbotPreset(aimbotPresets::SilentAimNoSpread);
				print("Enable autowall for even more hax");
				break;
			/*case 2:
				setAimbotPreset(aimbotPresets::SilentAimNoSpreadAutowall);
				print("This is the best aimbot for lmg's");
				break;*/
			case 2:
				setAimbotPreset(aimbotPresets::SilentAimNoSpreadSuperAutowall);
				print("Utilizes the super autowall function");
				break;
			case 3:
				setAimbotPreset(aimbotPresets::Scorestreak);
				print("Works best in loadstar and dragonfire. Does not work in all scorestreaks.");
				break;
			case 4:
				setAimbotPreset(aimbotPresets::Trickshot);
				print("Tap L1/Aim quickly to shoot");
				break;
			}
			break;
		case MENUS::IPs:
			for (int i = 0; i < 18; i++) {
				//0x00F9E690+0x148*0 xuid
				int ip = *(int*)(0x00F9E690+0x148*i+0x96);
				if (ip != 0 && i != Get_cgs()->localIndex) {
					char *name = (char*)(0x00F9E690+0x148*i+0x8);
					int p1 = (ip&0xff000000)>>24;
					int p2 = (ip&0x00ff0000)>>16;
					int p3 = (ip&0x0000ff00)>>8;
					int p4 = (ip&0x000000ff)>>0;
					char buf[100];
					snprintf(buf,sizeof(buf),"%s [^1%i.%i.%i.%i^7]",name,p1,p2,p3,p4);
					addOption(buf);
				}
			}
			break;
		case MENUS::Credits:
			//printf("client %i %i\n",Get_cgs()->localIndex,*(int*)(cg_t(0)));
			addOption("gopro_2027 [^1Aimbot & Menu^7]");
			addOption("SemjasesDev [^1IP Info^7]");
			addOption("Sabotage [^1YAE Source^7]");
			addOption("Viiperz [^1Design Help^7]");
			addOption("Sony [^1PS3 & SEN^7]");
			addOption("Linus Torvalds [^1Linux^7]");
			addOption("Bjarne Stroustrup [^1C++^7]");
			addOption("Dennis Ritchie [^1C^7]");
			addOption("IBM [^1Computer Software^7]");
			addOption("IBM [^1Computer Hardware^7]");
			addOption("Konrad Zuse [^1Programming^7]");
			addOption("Charles Babbage [^1Computer^7]");
			break;
		case MENUS::Injector:
			{
			//const char *errorLink = "File didn't download properly!";//"Download at\nhttp://goo.gl/1z7PJN\nSorry for the inconvenience!\nThis may be automated in a future update.";
			static int index = 0;
			static char *options[13] = {"Bossam - Mod Menu","Zombieland - Gamemode","Elegance - Mod Menu","LOZ AZZA MENU V2 - Trickshot menu","AVALANCHE - Gamemode - Cargo Only TDM","Trickshot Menu - Mod Menu","The Hunger Games - DRONE,YEMEN,CARGO,STANDOFF ONLY FFA","The Crusher Game - FFA ANY MAP","Inspire - Mod Menu","Mike Myers - Gamemode - Nuketown Only","Lucky Modz Superman - Mod Menu - Carrier Trickshotting","Death Run - Cargo Only","Zombieland (Shark's Version) - All Maps Custom & Wonder Weapons"};
			addArrayOption("Load ",&index,0,12,options);
			addOption("Unload Current GSC");
			addOption("Inject /dev_hdd0/tmp/gopro_2027/GSC/Custom.gsc to _clientids.gsc");
			addOption("Inject /dev_hdd0/tmp/gopro_2027/GSC/Custom.gsc to _rank.gsc");
			addOption("Inject /dev_hdd0/tmp/gopro_2027/GSC/Custom.gsc to _development_dvars.gsc");
			//addOption("Load /dev_hdd0/tmp/OtherMenu.gsc");
			//static int index = 0;
			//static char *options[2] = {"maps/mp/gametypes/_clientids.gsc","maps/mp/gametypes/_rank.gsc"};
			//addArrayOption("Load At",&index,0,1,options);
			switch (getOption()) {
			case 0:
				//load
				switch (index) {
				case 0:
					injectBossam();
					break;
				case 1:
					injectZombieland();
					break;
				case 2:
					injectElegance();
					break;
				case 3:
					injectLOZAZZA();
					break;
				case 4:
					injectAvalanche();
					break;
				case 5:
					injectTrickshot();
					break;
				case 6:
					injectHunger();
					break;
				case 7:
					injectCrusher();
					break;
				case 8:
					injectInspire();
					break;
				case 9:
					injectMike();
					break;
				case 10:
					injectSupermanTrickshot();
					break;
				case 11:
					injectDeathRun();
					break;
				case 12:
					injectZombielandShark();
					break;
				}
				
				break;
			case 1:
				//unload
				injector::unloadCurrentGSC();
				break;

			
			case 2:
				if (doesFileExist("/dev_hdd0/tmp/gopro_2027/GSC/Custom.gsc")) {
					injector::injectFile("/dev_hdd0/tmp/gopro_2027/GSC/Custom.gsc","maps/mp/gametypes/_clientids.gsc");
					dialog("injected");
				}
				else
					dialog("file does not exist");
				break;
			case 3:
				if (doesFileExist("/dev_hdd0/tmp/gopro_2027/GSC/Custom.gsc")) {
					injector::injectFile("/dev_hdd0/tmp/gopro_2027/GSC/Custom.gsc","maps/mp/gametypes/_rank.gsc");
					dialog("injected");
				}
				else
					dialog("file does not exist");
				break;
			case 4:
				if (doesFileExist("/dev_hdd0/tmp/gopro_2027/GSC/Custom.gsc")) {
					injector::injectFile("/dev_hdd0/tmp/gopro_2027/GSC/Custom.gsc","maps/mp/gametypes/_development_dvars.gsc");
					dialog("injected");
				}
				else
					dialog("file does not exist");
				break;
			}
			break;
			}
		case MENUS::Host:
			addOption("Anti-End Game");
			/*addOption("Rank 55");
			addOption("Prestige 15");
			addOption("Rank 0");
			addOption("Prestige 0");*/
			switch(getOption()) {
			case 0:
				antiEndGame();
				break;
			/*case 0:
				setClientRank(*(int*)(cg_t(0)),55);
				break;
			case 1:
				setClientPrestige(*(int*)(cg_t(0)),9);
				break;
			case 2:
				setClientRank(*(int*)(cg_t(0)),0);
				break;
			case 3:
				setClientPrestige(*(int*)(cg_t(0)),0);
				break;*/
			}
			break;
		case MENUS::Infection:
			addOption("Slow Speed");
			addOption("Normal Speed");
			addOption("Super Speed");

			switch(getOption()) {
			case 0:
				setDvarAll("g_speed","1");
				break;
			case 1:
				setDvarAll("g_speed","190");
				break;
			case 2:
				setDvarAll("g_speed","999");
				break;
			}
			break;
		default:
			//close menu or something
			closeMenu();
			break;
		}









#endif




		doButtons();//must go after the text was rendered
	}
}


void Aimbot(uint64_t)
{
	for (;;)
	{
		if (DvarGetBool("cl_ingame"))
		{
			if(safeAimbot)
				if (!*(bool*)ClientInfo(LocalPlayer, 0x8F))
					if (*(int*)ClientInfo(LocalPlayer, 0x0C) > 0)
						if (silentAimbot)
							*(float*)(*(int*)0x00D689D8+0x2C94) = 0;//fix for look up or down
			if (DoAngles && AimbotStarted)
			{
				if (!*(bool*)ClientInfo(LocalPlayer, 0x8F))
				{
					if (*(int*)ClientInfo(LocalPlayer, 0x0C) > 0)
					{
						allowAutowall = true;
						vec = vectoangles(Angles);
						float FinalAngles[2] = { vec.x - *(float*)(ClientActive(0x108)), vec.y - *(float*)(ClientActive(0x10C)) };
						AimAngles.x = FinalAngles[0];
						AimAngles.y = FinalAngles[1];
						AimAngles.z = 0;
						aimbothit = true;
						if (!silentAimbot) {
							CL_SetViewAngles(0, FinalAngles);
							//if (autoShoot) {
								//*(char*)0xee4dc0 = 1;//shoot
							//}
						}
					} else {
						allowAutowall = false;
						aimbothit = false;
					}
				} else {
					allowAutowall = false;
					aimbothit = false;
				}
				DoAngles = false;
			}
			sleep(2);
		} else {
			allowAutowall = false;
			aimbothit = false;
		}
		sleep(4);
	}
}
void drawCrosshair(float size1, float size2) {
	float x = getScreenPercentX(0.5f);
	float y = getScreenPercentY(0.5f);
	DrawShader(x-size1/2,y-size2/2,size1,size2,colors::red,"white");
	DrawShader(x-size2/2,y-size1/2,size2,size1,colors::red,"white");
	*(char*)(0x1CC5AA0 + 0x18) = false;//crosshair
}

void renderHook() {
	*(char*)(0x1CC5AA0 + 0x18) = true;//crosshair
	doMenu();
	if (DvarGetBool("cl_ingame"))
		if (crosshair)
			drawCrosshair(100,1);
}
bool isAimingAllTheWay() {
	float aimRatio_a = *(float*)0x03780EC08;//0 is not aiming. 1.0 is aimed all the way
	return (aimRatio_a == 1.0f);
}
void hook() {
	if (DvarGetBool("cl_ingame")) {
	LocalPlayer = *(int*)(cg_t(0));
	if(ESP || SNAPLINES) {
		renderESP(LocalPlayer);
	}
	if (AimbotStarted)
		{
			//*(int*)(0x1EF77B0) & (1<<8)
			if (Required && /*isButtonDown(B_L1)*//**(int*)(0x1EF77B0) & (1<<8)*/isAimingAllTheWay()/*this is the dvar*(char*)0x00EE4D00*//**(char*)(0x1EF77B2) == 0x01 || *(char*)(0x1EF77B2) == 0x03*/)
			{
				//LocalPlayer = *(int*)(cg_t(0));
				if (!*(bool*)ClientInfo(LocalPlayer, 0x8F))
				{
					if (*(int*)ClientInfo(LocalPlayer, 0x0C) > 0)
					{
						NearstPlayer = GetNearestPlayer(LocalPlayer);
						if (NearstPlayer == -1) {
							aimbothit = false;
							//if(AimbotStarted && autoShoot && !silentAimbot)
								//*(char*)0xee4dc0 = 0;//unshoot
						}
						else
						if (ClientReady)
						{
							ClientReady = false;
							Position = GetTagPos(NearstPlayer, TagOrigin);
							Angles = Difference(Position, Get_cgs()->refdef.viewOrigin/*GetTagPos(LocalPlayer, TagOrigin)*/);
							DoAngles = true;
						}
					}
				}
			}
			else if (!Required)
			{
				LocalPlayer = *(int*)(cg_t(0));
				if (!*(bool*)ClientInfo(LocalPlayer, 0x8F))
				{
					if (*(int*)ClientInfo(LocalPlayer, 0x0C) > 0)
					{
						NearstPlayer = GetNearestPlayer(LocalPlayer);
						if (NearstPlayer == -1) {
							aimbothit = false;
							//if(AimbotStarted && autoShoot && !silentAimbot)
								//*(char*)0xee4dc0 = 0;//unshoot
						}
						else
						if (ClientReady)
						{
							ClientReady = false;
							Position = GetTagPos(NearstPlayer, TagOrigin);
							Angles = Difference(Position, Get_cgs()->refdef.viewOrigin/*GetTagPos(LocalPlayer, TagOrigin)*/);
							DoAngles = true;
						}
					}
				}
			} 
			else {
				aimbothit = false;
			}
		}
	}
}

//0x00F9E690+0x148*i steal host. set your long int to the host's long int
/*

C14F5771 A433BCCF

F56BE9B29275E8D4 my current xuid

My xuid is also at 0x00D86760 (probably main)
Also my xuid at 0x00ED6D40   this one gets overwrritten at 0x000008BDC4
then in mem is the player xuid array I look at
then xuid at 0x00FA7B08
then another xuid array at 0x00FA7FEB
then another that is similar to the one I always use at 0x00FA9998

0x0377C7E98+0x69E18 aka 0x37831CB0 is my real xuid?

0x0377C7E98+0x69E18+0x808*-3

xuid's: 0x377C6680+0x808*i+0x69E18 but THIS one gets reset too

*/