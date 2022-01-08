namespace injector {        

//char *Bytes;
        int ByteLength;
        unsigned int MALLOC = 0;//just an open sppot    0x10026000
		unsigned int currentlyLoadedGSCAddressToPatch = 0;
		unsigned int currentlyLoadedGSCAddressFix = 0;
        unsigned int InjectTolocation(char *location)
        {
			char returnData[20];
			opd_s jjj_t = {0x18ac04,TOC};
			int(*jjj)(unsigned int arg1, int arg2, char *arg3, int arg4, int arg5) = (int(*)(unsigned int, int, char *, int, int))&jjj_t;
			jjj((unsigned int)&returnData/*0x10040000*/, 0x33, location, 1, -1);
			return *(unsigned int*)((unsigned int)&returnData)/*0x10040000*/;
            //RPC.Call(0x18ac04, new object[] { 0x10040000, 0x33, location, 1, -1 });
            //return PS3.Extensions.ReadUInt32(0x10040000);
        }
 
        unsigned int SpacetoInject()
        {
			if (MALLOC == 0) {
				MALLOC = (unsigned int)SWindow::WUtils::malloc(300000);
				printf("\n\nGSC Locations: 0x%X to 0x%X\n\n\n",MALLOC,MALLOC+300000);
			}
            return MALLOC;//(MALLOC = (MALLOC + ByteLength) + 100);
        }
		void unloadCurrentGSC() {
			if (currentlyLoadedGSCAddressToPatch != 0)
				*(unsigned int*)(currentlyLoadedGSCAddressToPatch) = currentlyLoadedGSCAddressFix;
			currentlyLoadedGSCAddressToPatch = 0;
		}
		char dialoginfo[0xFF];
        void injectFile(char *file,char *overrite/* = "maps/mp/gametypes/_clientids.gsc" *//*"maps/mp/gametypes/_rank.gsc" for some*/ )//inject a .gsc file
        {
			unloadCurrentGSC();
			printf("Injecting %s\n",file);
			ByteLength = getFileSize(file);
			if (ByteLength != -1) {
				printf("ByteLength: 0x%X\n",ByteLength);
				unsigned int WriteOffset = SpacetoInject();
				printf("WriteOffset: 0x%X\n",WriteOffset);
				unsigned int offset = InjectTolocation(overrite);//for zombies use  "maps/mp/gametypes_zm/_clientids.gsc"
				printf("offset: 0x%X\n",offset);
				//char zero[] = {0};
				//memfill((void*)WriteOffset,zero,sizeof(zero),ByteLength+8);//8 just cuz it might not be exactly 4 aligned idk who cares
				//printf("Prepared area of memory\n");
				readFile(file,(char*)WriteOffset,ByteLength);
				printf("File read to address 0x%X\n",WriteOffset);
				currentlyLoadedGSCAddressToPatch = offset + 8;
				currentlyLoadedGSCAddressFix = *(unsigned int*)(offset + 8);
				*(unsigned int*)(offset + 8) = WriteOffset;
				printf("WriteOffset written to 0x%X\n\n",offset + 8);
				//*(int*)0x140C2D0 = WriteOffset;
				//printf("Inject %s!\n",file);
				//cellMsgDialogOpen(1,fprintf("Injected %s!",file),my_dialog2,(void*) 0x0000aaab, NULL);
				strcpy(dialoginfo,fprintf("Injected %s!",file));
				dialog(dialoginfo);
			} else {
				//cellMsgDialogOpen(1,fprintf("Failed to inject %s!",file),my_dialog2,(void*) 0x0000aaab, NULL);
				strcpy(dialoginfo,fprintf("Failed to inject %s!",file));
				dialog(dialoginfo);//has to save it cuz it doesn't instantly call it in the dialog function, it takes a second to send
			}
        }
 
}

//BossamBemass is the creator of bossam
//OfficialCoolJay is the creator of zombieland



/*
downloadFile("dl/bossam.gsc","gopro_2027/bossam.gsc",279068);
	downloadFile("dl/zombieland.gsc","gopro_2027/zombieland.gsc",188538);
	downloadFile("dl/batman.gsc","gopro_2027/batman.gsc",275688);
*/

void injectGSC(char *filename, char *overrite, int fileSize = 0) {
	static char text[128];
	strcpy(text,"Loading GSC");
	dialog(text);
	if (!doesFileExist(filename)) {
		if (fileSize != 0) {//can only download if file size is specified
			strcpy(text,"Downloading...");
			makeFolder("/dev_hdd0/tmp/gopro_2027/");
			makeFolder("/dev_hdd0/tmp/gopro_2027/GSC/");
			char buf1[128];
			char buf2[128];
			strcpy(buf1,fprintf("dl/GSC/%s",filename));
			strcpy(buf2,fprintf("gopro_2027/GSC/%s",filename));
			downloadFile(buf1,buf2,fileSize);
		} else {
			strcpy(text,"Could not download!");
			dialog(text);
			return;
		}
	}
	strcpy(text,"Injecting...");
	dialog(text);
	strcpy(text,fprintf("/dev_hdd0/tmp/gopro_2027/GSC/%s",filename));
	injector::injectFile(text,overrite);
	strcpy(text,"Injected!");
	dialog(text);
}

void injectBossam() {
	//injector::injectFile("/dev_hdd0/tmp/gopro_2027/bossam.gsc","maps/mp/gametypes/_clientids.gsc");
	if (!DvarGetBool("cl_ingame"))
	injectGSC("bossam.gsc","maps/mp/gametypes/_clientids.gsc",279068);//300000
}
void injectZombieland() {
	//injector::injectFile("/dev_hdd0/tmp/gopro_2027/zombieland.gsc","maps/mp/gametypes/_rank.gsc");
	if (!DvarGetBool("cl_ingame"))
	injectGSC("zombieland.gsc","maps/mp/gametypes/_rank.gsc",188538);
}
//void injectBatman() {
	//injector::injectFile("/dev_hdd0/tmp/gopro_2027/batman.gsc","maps/mp/gametypes/_development_dvars.gsc");
//}

void injectElegance() {
	if (!DvarGetBool("cl_ingame"))
	injectGSC("Elegance.gsc","maps/mp/_development_dvars.gsc",211416);
}
void injectLOZAZZA() {
	if (!DvarGetBool("cl_ingame"))
	injectGSC("LozSnip.gsc","maps/mp/gametypes/_clientids.gsc",121624);
}
void injectAvalanche() {
	if (!DvarGetBool("cl_ingame"))
	injectGSC("28.gsc","maps/mp/gametypes/_clientids.gsc",29688);
}
void injectTrickshot() {
	if (!DvarGetBool("cl_ingame"))
	injectGSC("azza.gsc","maps/mp/gametypes/_clientids.gsc",59580);
}
void injectHunger() {
	if (!DvarGetBool("cl_ingame"))
	injectGSC("hunger.gsc","maps/mp/gametypes/_clientids.gsc",100272);
}
void injectCrusher() {
	if (!DvarGetBool("cl_ingame"))
	injectGSC("crusher.gsc","maps/mp/gametypes/_clientids.gsc",18908);
}
void injectInspire() {
	if (!DvarGetBool("cl_ingame"))
	injectGSC("sagi.gsc","maps/mp/_development_dvars.gsc",183652);
}
void injectMike() {
	if (!DvarGetBool("cl_ingame"))
	injectGSC("mike.gsc","maps/mp/gametypes/_clientids.gsc",49516);
}
void injectSupermanTrickshot() {
	if (!DvarGetBool("cl_ingame"))
	injectGSC("lmz1.gsc","maps/mp/gametypes/_clientids.gsc",76812);
}
void injectDeathRun() {
	if (!DvarGetBool("cl_ingame"))
	injectGSC("stur.gsc","maps/mp/gametypes/_clientids.gsc",34556);
}
void injectZombielandShark() {
	if (!DvarGetBool("cl_ingame"))
	injectGSC("zombieland2.gsc","maps/mp/gametypes/_clientids.gsc",122000);
}


/*
bossam
zombieland
Elegance v5 lite - mod menu - maps/mp/_development_dvars.gsc - Elegance.gsc
LOZ AZZA MENU V2 - trickshotting menu - maps/mp/gametypes/_clientids.gsc - LozSnip.gsc
AVALANCHE GAMEMODE - cargo only TDM - maps/mp/gametypes/_clientids.gsc - 28.gsc
Trickshot Menu V4 - trickshots - maps/mp/gametypes/_clientids.gsc - azza.gsc
The Hunger Games V3.5 - DRONE,YEMEN,CARGO,STANDOFF ONLY FFA - maps/mp/gametypes/_clientids.gsc - hunger.gsc
The Crusher Game - FFA ANY MAP - maps/mp/gametypes/_clientids.gsc - crusher.gsc
Insipre v1 - mod menu - maps/mp/_development_dvars.gsc - sagi.gsc
Mike Myers - nuketown only - maps/mp/gametypes/_clientids.gsc - mike.gsc
Lucky Modz Superman mod menu - Trickshotting on carrier - maps/mp/gametypes/_clientids.gsc - lmz1.gsc
Death Run - Cargo Only - maps/mp/gametypes/_clientids.gsc - stur.gsc
*/




namespace injector2 {        


        unsigned int InjectTolocation(char *location)
        {
			char returnData[20];
			opd_s jjj_t = {0x18ac04,TOC};
			int(*jjj)(unsigned int arg1, int arg2, char *arg3, int arg4, int arg5) = (int(*)(unsigned int, int, char *, int, int))&jjj_t;
			jjj((unsigned int)&returnData/*0x10040000*/, 0x33, location, 1, -1);
			return *(unsigned int*)((unsigned int)&returnData)/*0x10040000*/;
        }
 
        
        void dumpFile(char *file,char *overrite/* = "maps/mp/gametypes/_clientids.gsc" *//*"maps/mp/gametypes/_rank.gsc" for some*/ )//inject a .gsc file
        {
				unsigned int offset = InjectTolocation(overrite);//for zombies use  "maps/mp/gametypes_zm/_clientids.gsc"
				printf("Dumping %s\n",overrite);
				printf("Offset: 0x%X\n",offset);
				return;
				if (offset > 0x10000) {
				
					char *data = (char*)(*(unsigned int*)(offset + 8));
					printf("Data: 0x%X\n",(unsigned int)data);
					if ((unsigned int)data > 0x10000) {
						//300000 is size

						writeToFile(file,data,100000);
						printf("Dumped!\n");
						return;
					}
				}
				printf("failed to dump\n");
        }

		void dumpThem() {
			//"maps/mp/gametypes/_clientids.gsc"
			//"maps/mp/gametypes/_rank.gsc"
			//"maps/mp/gametypes/_development_dvars.gsc"
			dumpFile("/dev_hdd0/tmp/_clientids.gsc","maps/mp/gametypes/_clientids.gsc");
			dumpFile("/dev_hdd0/tmp/_rank.gsc","maps/mp/gametypes/_rank.gsc");
			dumpFile("/dev_hdd0/tmp/_development_dvars.gsc","maps/mp/gametypes/_development_dvars.gsc");
		}
 
}