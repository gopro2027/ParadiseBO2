namespace submenuOpensFuncs {
	void self() {
		windowUtils::closeAllWindows();
		windowUtils::openWindow(MENUS::Self);
		windowUtils::openWindow(MENUS::PrivateLobby);
	}
	void aimbot() {
		windowUtils::closeAllWindows();
		windowUtils::openWindow(MENUS::Aimbot);
		windowUtils::openWindow(MENUS::AimbotPresets);
	}
	void ipaddresses(){
		windowUtils::closeAllWindows();
		windowUtils::openWindow(MENUS::IPs);
		windowUtils::openWindow(MENUS::IP2s);
	}
	void lobbyinfo(){
		windowUtils::closeAllWindows();
		windowUtils::openWindow(MENUS::LobbyInfo);
	}
	void hostmenu(){
		windowUtils::closeAllWindows();
		windowUtils::openWindow(MENUS::Host);
		windowUtils::openWindow(MENUS::Infection);
	}
	void credits(){
		windowUtils::closeAllWindows();
		windowUtils::openWindow(MENUS::Credits);
	}
	void pregame() {
		windowUtils::closeAllWindows();
		windowUtils::openWindow(MENUS::Prelobby);
		windowUtils::openWindow(MENUS::Injector);
		windowUtils::openWindow(MENUS::Name);
	}
};
namespace menuVars {
	char dvarName[50];
	char dvarValue[50];
	OptionValue aimbotToggle;
	OptionValue ESPToggle;
	OptionValue testInt;
	OptionValue testFloat;
	OptionValue selectedPlayer;
	OptionValue zero;
	OptionValue silentaimbot;
	OptionValue requireaiming;
	OptionValue autoshoot;
	OptionValue nospread;
	OptionValue safeaimbot;
	OptionValue checkvisibility;
	OptionValue autowall;
	OptionValue vsat;
	OptionValue norecoil;
	OptionValue snaplines;
	OptionValue entities;
	OptionValue wallhack;
	OptionValue laser;
	OptionValue lag;
	OptionValue dof;
	OptionValue drawgun;
	OptionValue drawfps;
	OptionValue minicrosshair;
	OptionValue forcehost;
	OptionValue dvarname;
	OptionValue dvarvalue;
	OptionValue playerNameInt;
	OptionValue playerPrestigeLevelInt;
	OptionValue playerLevelInt;
	void doMenuVars() {
		//force the windows to show up
		if (main.selectedWindow == MENUS::Main) {
			Window *menu = &main.windows[MENUS::Main];
			menu->options[menu->selectedOption].callback();
		}
		aimbotToggle.b = AimbotStarted;
		ESPToggle.b = ESP;
		zero.i = 0;
		silentaimbot.b = silentAimbot;
		requireaiming.b = Required;
		autoshoot.b = autoShoot;
		nospread.b = NoSpreadToggle;
		safeaimbot.b = safeAimbot;
		checkvisibility.b = Stealth;
		autowall.b = autowallEnabled;//even though it's an int, has to be a bool for the menu to pick up on it properly
		forcehost.b = !(bool)(*(char*)0x1CD6018);
		dvarname.str = dvarName;
		dvarvalue.str = dvarValue;
		
		//begin set player name option
		char *name = (char*)(0x00F9E690+0x148*playerNameInt.i+0x8);
		static char playerName[50];
		snprintf(playerName,sizeof(playerName),"Player: %s",name);
		windowUtils::setMenuOptionName(MENUS::Host,1,playerName);
		//end set player name option



	}
};
namespace optionCallbacks {
	using namespace menuVars;
	void aimbotToggleCallback() {
		AimbotStarted = !AimbotStarted;
	}
	void silentaimbot() {
		silentAimbot = !silentAimbot;
	}
	void requireaiming() {
		Required = !Required;
	}
	void autoshoot() {
		autoShoot = !autoShoot;
	}
	void nospread() {
		NoSpreadToggle = !NoSpreadToggle;
	}
	void safeaimbot() {
		safeAimbot = !safeAimbot;
		print("Recommended to enable. Fix for a bug dealing with out of bounds view angles.");
	}
	void checkvisibility() {
		Stealth = !Stealth;
	}
	void autowall() {
		autowallEnabled = !autowallEnabled;
	}
	void ESPCallback() {
		ESP = !ESP;
	}
	void endgame() {
		endGame();
	}
	void crashServer() {
		Cbuf_AddText(0, "cmd sl");
	}
	void vsatCallback() {
		menuVars::vsat.b = !menuVars::vsat.b;
				if (menuVars::vsat.b) {
					char nop[] = { 0x60, 0x00, 0x00, 0x00 };
					write_process((void*)0x00033C60, &nop, sizeof(nop));//vsat
				} else {
					char rec[] = { 0x40, 0x81, 0x00, 0x44 };
					write_process((void*)0x00033C60, &rec, sizeof(rec));
				}
	}
	void norecoilCallback() {
		norecoil.b = !norecoil.b;
				if (norecoil.b) {
					char nop[] = { 0x60, 0x00, 0x00, 0x00 };
					write_process((void*)0x000F9E54, &nop, sizeof(nop));//no recoil
				} else {
					char rec[] = { 0x48, 0x50, 0x6D, 0x65 };
					write_process((void*)0x000F9E54, &rec, sizeof(rec));
				}
	}
	void snaplinesCallback() {
		SNAPLINES = !SNAPLINES;
		snaplines.b = SNAPLINES;
	}
	void entitiesCallback() {
		entities.b = !entities.b;
				char invisiblebodieson[] = {0x1};
				char invisiblebodiesoff[] = {0x0};
				if (entities.b)
					write_process((void*)0x0076F25B,invisiblebodieson,1);
				else
					write_process((void*)0x0076F25B,invisiblebodiesoff,1);
				
	}
	void wallhackCallback() {
		wallhack.b = !wallhack.b;
				char wallhackon[] = { 0x38, 0xC0, 0xFF, 0xFF};
				char wallhackoff[] = {0x63, 0x26, 0x00, 0x00};
				if (wallhack.b)
					write_process((void*)0x834D0,wallhackon,4);
				else
					write_process((void*)0x834D0,wallhackoff,4);
	}
	void laserCallback() {
		laser.b = !laser.b;
				char laseron[] = {0x2C, 0x03, 0x00, 0x01};
				char laseroff[] = {0x2C, 0x03, 0x00, 0x00};
				if (laser.b)
					write_process((void*)0xEF68C,laseron,4);
				else
					write_process((void*)0xEF68C,laseroff,4);
	}
	void lagCallback() {
		*(char*)(0x1CC56E0 + 0x18) = !*(char*)(0x1CC56E0 + 0x18);
		lag.b = *(char*)(0x1CC56E0 + 0x18);
	}
	void dofCallback() {
		*(char*)(0x1CBFE00 + 0x18) = !*(char*)(0x1CBFE00 + 0x18);
		dof.b = *(char*)(0x1CBFE00 + 0x18);
	}
	void drawgunCallback() {
		*(char*)(0x1CC5020 + 0x18) = !*(char*)(0x1CC5020 + 0x18);
		drawgun.b = *(char*)(0x1CC5020 + 0x18);
	}
	void drawfpsCallback() {
		*(int*)(0x1CC5680 + 0x18) = !*(int*)(0x1CC5680 + 0x18);
		drawfps.b = *(int*)(0x1CC5680 + 0x18);
	}
	void minicrosshairCallback() {
		crosshair = !crosshair;
		minicrosshair.b = crosshair;
	}
	void forcehostCallback() {
		*(char*)0x1CD6018 = (char)(!(bool)(*(char*)0x1CD6018));//party_connectToOthers = 0x1CD6000 + 0x18;
		   //Form1.PS31.SetMemory(30236696u, new byte[1]);//0x1CD6000 + 0x18  party_connectToOthers
                //Form1.PS31.SetMemory(30235163u, new byte[]{1});//party_minplayers = 0x1CD5A00 + 0x18;
                //Form1.PS31.SetMemory(30237851u, new byte[]{1});//party_minLobbyTime = 0x1CD6480 + 0x18;
                //Form1.PS31.SetMemory(30235451u, new byte[]{1});//party_gameStartTimerLength = 0x1CD5B20 + 0x18;
	}
	void switchtoaxis() {
		print("Switched to axis");
		for (int i = 0; i < 0x20; i++)
				runServer("axis",i);
	}
	void switchtoallies() {
		print("Switched to allies");
				for (int i = 0; i < 0x20; i++)
				runServer("allies",i);
	}
	void switchtocodcaster() {
		print("Switched to spectator");
				for (int i = 0; i < 0x20; i++)
				runServer("spectator",i);
	}

	SWindow::OptionValue speedInfectionValue;
	void speedInfection() {
		setDvarAll("g_speed",ItoS(speedInfectionValue.i));
	}
	void presetNoAimbot() {
		setAimbotPreset(aimbotPresets::NoAimbot);
		print("Aimbot is now disabled");
	}
	void presetSANS() {
		setAimbotPreset(aimbotPresets::SilentAimNoSpread);
		print("Great choice");
	}
	void presetHVH() {
		setAimbotPreset(aimbotPresets::SilentAimNoSpreadSuperAutowall);
		print("Utilizes the super autowall function");
	}
	void presetSSTREAK() {
		setAimbotPreset(aimbotPresets::Scorestreak);
		print("Works best in loadstar and dragonfire. Does not work in all scorestreaks.");
	}
	void presetTrickshot() {
		setAimbotPreset(aimbotPresets::Trickshot);
		print("Tap L1/Aim quickly to shoot");
	}
	void changeNameCallback(char *str) {
		//CharlesBabbage
		strcpy((char*)0x026C0658,str);
		strcpy((char*)0x026c067f,str);
	}
	void changeName() {
		keyboard::openKeyboard(changeNameCallback,20);
	}

	void sayInChatCallback(char *str) {
		char buf[300];
		snprintf(buf,sizeof(buf),"cmd say %s\n",str);
		Cbuf_AddText(0,buf);
	}
	void sayInChat() {
		//cmd vsay %s\n
		keyboard::openKeyboard(sayInChatCallback);
	}

	void runCMDCallback(char *str) {
		Cbuf_AddText(0,str);
	}
	void runCMD() {
		keyboard::openKeyboard(runCMDCallback);
	}

	void updateIPList() {
		static char strings[18][200];
		for (int i = 0; i < 18; i++) {
			//0x00F9E690+0x148*0 xuid
			int ip = *(int*)(0x00F9E690+0x148*i+0x96);
			//if (ip != 0 && i != Get_cgs()->localIndex) {
				char *name = (char*)(0x00F9E690+0x148*i+0x8);
				int p1 = (ip&0xff000000)>>24;
				int p2 = (ip&0x00ff0000)>>16;
				int p3 = (ip&0x0000ff00)>>8;
				int p4 = (ip&0x000000ff)>>0;
				if (i != Get_cgs()->localIndex)
					snprintf(strings[i],sizeof(strings[i]),"%s [^1%i.%i.%i.%i^7]",name,p1,p2,p3,p4);
				else
					snprintf(strings[i],sizeof(strings[i]),"%s [^1You!^7]",name);
				addOption(strings[i]);
			//}
		}

		for (int i = 0; i <= 17; i++) {
			windowUtils::setMenuOptionName(MENUS::IP2s,i,strings[i]);
		}
	}

	
	/*
#define min(x,y) (x>y?y:x)
#define max(x,y) (x>y?x:y)
	void setDvarNameCallback(char *str) {
		strncpy(dvarName,str,min(50,strlen(str)));
		windowUtils::setMenuOptionName(MENUS::Infection,0,dvarName);
	}
	void setDvarValueCallback(char *str) {
		strncpy(dvarValue,str,min(50,strlen(str)));
		windowUtils::setMenuOptionName(MENUS::Infection,0,dvarValue);
	}
	void setDvarName() {
		keyboard::openKeyboard(setDvarNameCallback,50);
	}
	void setDvarValue() {
		keyboard::openKeyboard(setDvarValueCallback,50);
	}*/
	void doInfection() {
		if (strlen(dvarName) < 1) {
			print("Dvar name not set! Press Square to edit values");
			return;
		}
		if (strlen(dvarValue) < 1) {
			print("Dvar value not set! Press Square to edit values");
			return;
		}
		setDvarAll(dvarName,dvarValue);
		print("Infection set!");
	}


	void runInfectionString(char *str) {
		int index;
		for (index = 0; index < strlen(str); index++) {
			if (str[index] == ' ')
				break;
		}
		//index is now the position of the first space
		str[index] = 0;
		setDvarAll(str,str+index+1);
		printf("Setting dvar %s with value %s\n",(char*)str,(char*)(str+index+1));
		str[index] = ' ';
	}

	void loadInfections() {
		if (doesFileExist("/dev_hdd0/tmp/gopro_2027/bo2infection.txt")) {
			char *buf = (char*)0x10070000;
			unsigned int fileSize = getFileSize("/dev_hdd0/tmp/gopro_2027/bo2infection.txt");
			readFile("/dev_hdd0/tmp/gopro_2027/bo2infection.txt",buf,fileSize);
			char *currentString = buf;
			for (int i = 0; i < fileSize; i++) {
				if (buf[i] == '\n') {
					buf[i] = 0;
					runInfectionString(currentString);
					buf[i] = '\n';//sets back to normal. Not necessary but whatever
					currentString = (char*)(buf+i+1);
				}
			}
			dialog("Infections set!");
		} else {
			dialog("Please create the file '/dev_hdd0/tmp/gopro_2027/bo2infection.txt' and put your infection code in there.\nThis is an image of the file format for the infections:\nhttp://i.imgur.com/D06p9wj.png\nHave fun and be nice!");
		}
	}

	
	void setPrestigeCallback() {
		//playerPrestigeLevelInt
		//playerNameInt
		setPrestige(playerNameInt.i,playerPrestigeLevelInt.i);
	}
	void setLevelCallback() {
		//playerPrestigeLevelInt
		//playerNameInt
		setLevel(playerNameInt.i,playerLevelInt.i);
	}
#include "bo2dvars.h"
	void dumpDvars() {
		//first dvar 0xD9B540
		dvar_t *dvar = (dvar_t *)(0xD9B540);
		while ((unsigned int)(dvar->hashNext) >= 0x10000) {

			dvar = dvar->hashNext;
			char text[200];
			//unsigned int value = *(unsigned int*)(allBo2Dvars[i]);
			//unsigned int addr = allBo2Dvars[i];
			//unsigned int addrminus18 = allBo2Dvars[i]-0x18;
			//unsigned int flags = *(unsigned int*)(addrminus18+0xc);
			//if (flags & 0x500) {
				snprintf(text,sizeof(text),"%s 0x%X 0x%X\n",dvar->name,(unsigned int)dvar,dvar->flags&0x500);
				appendToFile("/dev_hdd0/tmp/bo2dvarsdump.txt",text,strlen(text));
			//}
		}
	}

	void loadSPRX() {
		loader_sprx("/dev_hdd0/tmp/webm.sprx");
	}

};













char SV_ReceiveStatsSaveData[4*4];
void SV_ReceiveStatsDetour(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6);
void SV_ReceiveStatsDetour(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6) {
	printf("Started writing data to file\n");
	appendToFile("/dev_hdd0/tmp/gopro_2027/BO2StatsDump.txt",(char*)(0x19CE8BC+8),strlen((char*)(0x19CE8BC+8)));
	appendToFile("/dev_hdd0/tmp/gopro_2027/BO2StatsDump.txt","\n",1);
	printf("Done writing data to file\n");
	opd_s SV_ReceiveStats_t = {0x344148,TOC};
	void(*SV_ReceiveStats)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6) = (void(*)(unsigned int, unsigned int, unsigned int, unsigned int))&SV_ReceiveStats_t;
	memcpy((void*)0x344148,(void*)SV_ReceiveStatsSaveData,4*4);//fix original function
	printf("Calling receive stats\n");
	SV_ReceiveStats(r3,r4,r5,r6);//run original code
	printf("Done calling receive stats\n");
	PatchInJump(0x344148,(int)SV_ReceiveStatsDetour,false);//patch back again
}

void SV_ReceiveStatsDetourStart() {
	//0x19CE8BC+10*10*4 is the read address + size
	memcpy((void*)SV_ReceiveStatsSaveData,(void*)0x344148,4*4);
	PatchInJump(0x344148,(int)SV_ReceiveStatsDetour,false);
}




void setupMenu() {

	//all client ip list (maybe leave out)
	//more infections
	//more names to change to
	//credits
	//lobby info

	//SV_ReceiveStatsDetourStart();


	//setup bool values that are changed on the start:
	menuVars::vsat.b = true;
	menuVars::norecoil.b = true;
	menuVars::drawgun.b = true;

	printf("Doign menu setup\n");
	sleep(10000);
	//allocate space for the windows
	main.createWindowPool(MENUS::Submenus_Count);
	printf("Kek\n");
#pragma region main menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::Main];
		menu->setup(5,"Paradise BO2",300,100);
		menu->isOpened = true;
		//setup options
		WindowOption *options = menu->options;
		options[0].setup("Non-Host",submenuOpensFuncs::self);
		options[1].setup("Aimbot",submenuOpensFuncs::aimbot);
		options[2].setup("IP Addresses",submenuOpensFuncs::ipaddresses);
		//options[3].setup("Lobby Info",submenuOpensFuncs::lobbyinfo);
		options[3].setup("Host Menu",submenuOpensFuncs::hostmenu);
		options[4].setup("Pre-Game Only",submenuOpensFuncs::pregame);
		//options[5].setup("Credits",submenuOpensFuncs::credits);      //TODO
	}
#pragma endregion

#pragma region self menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::Self];
		menu->setup(16,"Public Lobby",500,100);
		//setup options
		WindowOption *options = menu->options;
		options[0].setup("Vsat",optionCallbacks::vsatCallback,Option_Bool,&menuVars::vsat,"");
		options[1].setup("No Recoil",optionCallbacks::norecoilCallback,Option_Bool,&menuVars::norecoil,"");
		options[2].setup("Simple Snaplines",optionCallbacks::snaplinesCallback,Option_Bool,&menuVars::snaplines,"");
		options[3].setup("Simple ESP",optionCallbacks::ESPCallback,Option_Bool,&menuVars::ESPToggle,"Toggle ESP");
		options[4].setup("Invisible Entities",optionCallbacks::entitiesCallback,Option_Bool,&menuVars::entities,"");
		options[5].setup("Wall Hack",optionCallbacks::wallhackCallback,Option_Bool,&menuVars::wallhack,"");
		options[6].setup("Laser",optionCallbacks::laserCallback,Option_Bool,&menuVars::laser,"");
		options[7].setup("Lagometer",optionCallbacks::lagCallback,Option_Bool,&menuVars::lag,"");
		options[8].setup("DOF Debug",optionCallbacks::dofCallback,Option_Bool,&menuVars::dof,"");
		options[9].setup("Draw Gun",optionCallbacks::drawgunCallback,Option_Bool,&menuVars::drawgun,"");
		options[10].setup("Draw FPS",optionCallbacks::drawfpsCallback,Option_Bool,&menuVars::drawfps,"");
		options[11].setup("Mini Crosshair",optionCallbacks::minicrosshairCallback,Option_Bool,&menuVars::minicrosshair,"");
		options[12].setup("End Game",optionCallbacks::endgame);
		options[13].setup("Crash Server",optionCallbacks::crashServer);
		options[14].setup("Say in Chat",optionCallbacks::sayInChat);
		options[15].setup("Run CMD",optionCallbacks::runCMD);
		//options[14].setup("",optionCallbacks::ESPCallback,Option_Bool,&menuVars:,"");
	}
#pragma endregion

#pragma region private lobby menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::PrivateLobby];
		menu->setup(4,"Private Lobby Only",700,100);
		//setup options
		WindowOption *options = menu->options;
		options[0].setup("Switch To Axis",optionCallbacks::switchtoaxis);
		options[1].setup("Switch To Allies",optionCallbacks::switchtoallies);
		options[2].setup("Switch To Spectator",optionCallbacks::switchtocodcaster);
		options[3].setup("Dump dvars",optionCallbacks::dumpDvars);
	}
#pragma endregion

	/*
#pragma region menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::PrivateLobby];
		menu->setup(1,"",500,100);
		//setup options
		WindowOption *options = menu->options;
		//options[0].setup("",optionCallbacks::,Option_Bool,&menuVars:,"");
	}
#pragma endregion
	*/

#pragma region menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::AimbotPresets];
		menu->setup(6,"Presets",700,100);
		//setup options
		WindowOption *options = menu->options;
		options[0].setup("No Aimbot",optionCallbacks::presetNoAimbot);
		options[1].setup("Silent No Spread Autowall",optionCallbacks::presetSANS);
		options[2].setup("HvH Mode",optionCallbacks::presetHVH);
		options[3].setup("Scorestreak Aimbot",optionCallbacks::presetSSTREAK);
		options[4].setup("Non Host Trickshot Aimbot",optionCallbacks::presetTrickshot);
		options[5].setup("Load webm.sprx",optionCallbacks::loadSPRX);
	}
#pragma endregion

#pragma region menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::Injector];
		menu->setup(14,"Inject GSC",700,100);
		//setup options
		WindowOption *options = menu->options;
		options[0].setup("Bossam",injectBossam);
		options[1].setup("Zombieland 1",injectZombieland);
		options[2].setup("Elegance",injectElegance);
		options[3].setup("LOZAZZA",injectLOZAZZA);
		options[4].setup("Avalanche Gamemode",injectAvalanche);
		options[5].setup("Trickshot",injectTrickshot);
		options[6].setup("Hunger Games",injectHunger);
		options[7].setup("Crusher Gamemode",injectCrusher);
		options[8].setup("Inspire",injectInspire);
		options[9].setup("Mike Myers",injectMike);
		options[10].setup("Superman Trickshot",injectSupermanTrickshot);
		options[11].setup("Death Run",injectDeathRun);
		options[12].setup("Zombieland 2",injectZombielandShark);
		options[13].setup("Unload GSC",injector::unloadCurrentGSC);
	}
#pragma endregion

#pragma region menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::Name];
		menu->setup(1,"Name Changer",900,100);
		//setup options
		WindowOption *options = menu->options;
		options[0].setup("Custom Name",optionCallbacks::changeName);
	}
#pragma endregion

#pragma region menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::IPs];
		menu->setup(2,"IP Utils",500,100);
		//setup options
		WindowOption *options = menu->options;
		options[0].setup("Dump IP's To File",ipGrabber);
		options[1].setup("Update IP List",optionCallbacks::updateIPList);
	}
#pragma endregion

#pragma region menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::IP2s];
		menu->setup(18,"IP Addresses",700,100);
		//setup options
		WindowOption *options = menu->options;
		menu->maxOptionsPerPage = 18;
		for (int i = 0; i <= 17; i++) {
			options[i].setup("");
		}
	}
#pragma endregion

#pragma region menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::Host];
		menu->setup(4,"Host Utilities",500,100);
		//setup options
		WindowOption *options = menu->options;
		options[0].setup("Anti-Non Host End Game",antiEndGame);
		options[1].setup("Player",nullfunc,Option_Int,&optionCallbacks::playerNameInt);
		options[2].setup("Set Prestige",optionCallbacks::setPrestigeCallback,Option_Int,&optionCallbacks::playerPrestigeLevelInt);
		options[2].setupMinMax(0,15);
		options[3].setup("Set Level",optionCallbacks::setLevelCallback,Option_Int,&optionCallbacks::playerLevelInt);
		options[3].setupMinMax(0,55);
	}
#pragma endregion

#pragma region menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::Infection];
		menu->setup(4,"Infections",700,100);
		//setup options
		WindowOption *options = menu->options;
		//options[0].setup("Speed",optionCallbacks::speedInfection,SWindow::Option_Int,&optionCallbacks::speedInfectionValue);
		options[0].setup("Dvar Name",nullfunc,Option_String,&optionCallbacks::dvarname);
		options[1].setup("Dvar Value",nullfunc,Option_String,&optionCallbacks::dvarvalue);
		options[2].setup("Set Dvar/Infection",optionCallbacks::doInfection);
		options[3].setup("Load Infections From File",optionCallbacks::loadInfections);
	}
#pragma endregion

#pragma region aimbot menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::Aimbot];
		menu->setup(8,"Aimbot Options",500,100);
		//setup options
		WindowOption *options = menu->options;
		options[0].setup("Aimbot",optionCallbacks::aimbotToggleCallback,Option_Bool,&menuVars::aimbotToggle,"Toggle Aimbot");
		options[1].setup("Silent Aimbot",optionCallbacks::silentaimbot,Option_Bool,&menuVars::silentaimbot,"Like you're not looking at them");
		options[2].setup("Require Aiming",optionCallbacks::requireaiming,Option_Bool,&menuVars::requireaiming,"Must aim to trigger aimbot");
		options[3].setup("Auto Shoot",optionCallbacks::autoshoot,Option_Bool,&menuVars::autoshoot,"Shoots automatically");
		options[4].setup("No Spread",optionCallbacks::nospread,Option_Bool,&menuVars::nospread,"Don't have to aim at all");
		options[5].setup("Check Visibility",optionCallbacks::checkvisibility,Option_Bool,&menuVars::checkvisibility,"Player has to be in sight");
		options[6].setup("Autowall",optionCallbacks::autowall,Option_Bool,&menuVars::autowall,"Players has to be damageable");
		options[7].setup("Safe Aimbot",optionCallbacks::safeaimbot,Option_Bool,&menuVars::safeaimbot,"Helps prevent problems with silent aimbot");
		//options[0].setup("",optionCallbacks:,Option_Bool,&menuVars:,"Info");
	}
#pragma endregion



#pragma region pre lobby menu
	{
		//setup window
		Window *menu = &main.windows[MENUS::Prelobby];
		menu->setup(2,"Pre-Game",500,100);
		//setup options
		WindowOption *options = menu->options;
		options[0].setup("Force Host",optionCallbacks::forcehostCallback,Option_Bool,&menuVars::forcehost,"");
		options[1].setup("Spoof IP",spoofIP);
	}
#pragma endregion


	printf("Finished Menu Setup\n");
}


