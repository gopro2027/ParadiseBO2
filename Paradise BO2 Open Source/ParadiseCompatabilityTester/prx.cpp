#define COBRA 0
#define DEX 1






#include "stdafx.h"

#include <cellstatus.h>
#include <sys/prx.h>

#include <sys/types.h>
#include <netdb.h> 
#include <sys/types.h>
#include <cell/cell_fs.h>
#include <sys/stat.h>
#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <string.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/process.h>
#include <ppu_intrinsics.h>
#include <stdarg.h>
#include <stdio.h>
#include <sysutil\sysutil_msgdialog.h>
#include <sysutil\sysutil_oskdialog.h>
#include <sysutil\sysutil_oskdialog_ext.h>
#include <cstdlib>
#include <math.h>


void loader_sprx(const char* PATH_PRX)
{
  sys_prx_id_t prx_id ;
  printf ("Loading original prx... \n");
  prx_id = sys_prx_load_module(PATH_PRX, 0, NULL);
  if (prx_id <= CELL_OK) 
  {
    printf ("Failed!\n");
    return;
  } 
  else
    printf ("Done!\n\nStarting module... \n");

  int modres;
  if(sys_prx_start_module( prx_id, 0, NULL, &modres, 0, NULL) != CELL_OK)
    printf ("Failed!\n");
}


/*
0x01F4A179 search for endround
0x01F7D404
*/
bool DvarGetBool(const char *dvarName)
{
	//only used for cl_ingame so yea...
	return *(char*)(0x1CB68C0 + 0x18);
	/*
	if (Dvar_GetBool_f(Dvar_FindMalleableVar(dvarName)))
		return true;
	else
		return false;*/
}

void antiEndGame() {
	if (DvarGetBool("cl_ingame")) {
	//endround
	static unsigned int endroundAddress = 0;

	if (endroundAddress != 0) {
		if (*(char*)endroundAddress == 'j') {
			return;//it's still patched
		}
		else {
			endroundAddress = 0;
			antiEndGame();
		}
	} else {
		unsigned int addr = 0x01F4A179;
		while (!strstr((const char*)addr,(const char*)"endround")) {
			addr++;
			if (endroundAddress > 0x01F4A179+0x100000) {
				return;
			}
		}
		addr++;
		endroundAddress = addr;
		*(char*)addr = 'j';
	}
	}
}

#include <sys/types.h>
#include <sys/types.h>
#include <cell/cell_fs.h>
#include <sys/stat.h>
#include "networking.h"
void my_dialog2(int button, void *userdata)
{
    switch(button) {
        case CELL_MSGDIALOG_BUTTON_OK:

        case CELL_MSGDIALOG_BUTTON_NONE:

		case CELL_MSGDIALOG_BUTTON_ESCAPE:
            //dialog_action = 1;
            break;
        default:
		    break;
    }
}
#define dialog(text) cellMsgDialogClose(0);sleep(200);cellMsgDialogOpen(1,text,my_dialog2,(void*) 0x0000aaab, NULL);

char *fprintf(const char *fmt, ...)
{
	//duplicate name fprintf but don't care
	//128 is from the printf max size
	static char strBuf[128];
	int l_iLen;

	va_list args;
	va_start(args, fmt);
	
	
	vsnprintf(strBuf, 128, fmt, args);	
	
	va_end(args);
	return strBuf;
	//return 0;
}

/*char *sfprintf(char *strBuf, const char *fmt, ...)
{
	//duplicate name fprintf but don't care
	//128 is from the printf max size
	int l_iLen;

	va_list args;
	va_start(args, fmt);
	
	
	vsnprintf(strBuf, 128, fmt, args);	
	
	va_end(args);
	return strBuf;
	//return 0;
}*/



int doesFolderExist(const char *Path)
{
	int i, err;	CellFsStat status;
	for (i = 0; i < 15; i++) 
	{
		err = cellFsStat(Path, &status);
		if (err == CELL_FS_SUCCEEDED) 
		{
			return 1;
		}
	}
	return 0;
}

#define doesFileExist(file) doesFolderExist(file)

//checks if it exists already and if not then it creates it
void makeFolder(char *path) {
	if (!doesFolderExist(path))
		cellFsMkdir(path, S_IRWXO | S_IRWXU | S_IRWXG | S_IFDIR | CELL_FS_S_IFDIR | 0777);
}

int getFileSize(char *file) {
	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret) {
		CellFsStat sb;
		ret = cellFsFstat(fd,&sb);
		if (!ret) {
			return sb.st_size;
		}
	}
	return -1;
}
/*bool doesFileExist(char *file) {
	if (getFileSize(file) == -1)
		return false;
	return true;
}*/
void readFile(char *file, char buf[], int size) {
	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, buf, size, &nread);
		if (!ret)
		{
			cellFsClose(fd);
		}
	}
}
void readFiles(char *folder) {
	int fd;
	int ret;
	uint64_t data_count;
	CellFsDirent entries[512];
	//ret = cellFsOpen(folder, 0, &fd, NULL, 0);
	ret = cellFsOpendir(folder,&fd);
	//CellFsDirectoryEntry entries[0xf];
	if (!ret)
	{
		//ret = cellFsGetDirectoryEntries(fd,entries,0xf,&data_count);
		ret = cellFsReaddir(fd,entries,&data_count);
		if (!ret) {
			printf("count %i, entries:\n",(int)data_count);
			for (int i = 0; i < data_count; i++) {
				printf("Entry: %s, type: ",entries[i].d_name);
				switch(entries[i].d_type) {
				case CELL_FS_TYPE_UNKNOWN:
					printf("Unknown");
					break;
				case CELL_FS_TYPE_DIRECTORY:
					printf("Directory");
					break;
				case CELL_FS_TYPE_REGULAR:
					printf("Regular");
					break;
				case CELL_FS_TYPE_SYMLINK:
					printf("Symlink");
					break;
				default:
					printf("ERROR");
					break;
				}
				printf("\n");
				/*
				 CellFsDirent.d_type 
				#define CELL_FS_TYPE_UNKNOWN   0
				#define CELL_FS_TYPE_DIRECTORY 1
				#define CELL_FS_TYPE_REGULAR   2
				#define CELL_FS_TYPE_SYMLINK   3
				*/
			}
		} else {
			printf("Could not get entries\n");
		}
	} else {
		printf("error opening directory\n");
	}
}
void writeToFile(char *file, char buf[] = NULL, int size = 0) {
	int err;
 int fd;
 uint64_t nrw;
 int ret;
 /* Open file */
 err = cellFsOpen(file,CELL_FS_O_RDWR|CELL_FS_O_CREAT, &fd, NULL, 0);
 /* Clear file */
 cellFsTruncate(file,0);
 /* Write to file */
 if (size != 0)
 err = cellFsWrite(fd, (const void *)buf, (uint64_t)size, &nrw);
 /* Close file */
 err = cellFsClose(fd);
}
void appendToFile(char *file, char buf[] = NULL, int size = 0) {
	//int ogsize = getFileSize(file);
	int err;
 int fd;
 uint64_t nrw;
 int ret;
 /* Open file */
 err = cellFsOpen(file,CELL_FS_O_RDWR|CELL_FS_O_APPEND|CELL_FS_O_CREAT, &fd, NULL, 0);
 /* Clear file */
 //cellFsTruncate(file,0);
 /* Write to file */
 if (size != 0)
 err = cellFsWrite(fd, (const void *)buf, (uint64_t)size, &nrw);
 /* Close file */
 err = cellFsClose(fd);
}


//0xE22F1c network part

struct Addresses {
	int GLOBAL_CGAME_PTR_ADD;//0x2C - 0xE22F18
	int unk5;//0x34 - 0x9897824
	int GLOBAL_CLIENT_PTR_ADD;//0x20 - 0xD689D8
	int hookp0;//0x00 - 0x3D600000
	int unk4;//0x24 - 0x856234
	int hookp3;//0x14 - 0x4E800420
	int CG_BulletHitEvent_Patch;//0x000E9BE8
	int unk1;//0x08 - 0x9089
	int hookp1;//0x04 - 0x396B0000
	int CG_BulletEndposition;//0x30 - 0x000EBB48
	int unk2;//0x0C - 0x98632C
	int wepidcentityoffset;//0x28 - 0x2B4
	int Tracer_Spawn_Patch;//0x0045C038
	int BG_seedRandWithGameTime;//0x38 - 0x005D6C54
	int hookp2;//0x10 - 0x7D6903A6
	int unk3;//0x18 - 0x6723558
	int playerstate;//0x1C - 0x03780EA28
};

Addresses addresses;

sys_ppu_thread_t ThreadModuleID;
sys_ppu_thread_t AimbotThread;









int write_process(void* destination, const void* source, size_t size)
{
#if COBRA == 1
	memcpy(destination,source,size);
	return 0;
#endif
#if DEX == 1
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);//dex only
	return_to_user_prog(int);
#endif
}
bool isNumericChar(char x) {
	return (x >= '0' && x <= '9') ? true : false;
}
int StoI2( const char *c ) {
	int value = 0;
    int sign = 1;
    if( *c == '+' || *c == '-' ) {
       if( *c == '-' ) sign = -1;
       c++;
    }
    while ( isNumericChar( *c ) ) {
        value *= 10;
        value += (int) (*c-'0');
        c++;
    }
    return value * sign;
}


void memfill(void *address, void *data, size_t dataSize, int length) {
	for (int i = 0; i < length; i+= dataSize) {
		for (int s = 0; i < dataSize; i++) {
			*(char*)(i+s) = ((char*)data)[s];
		}
	}
}


void reverse(char arr[], int count)
{
   char temp;
   for (int i = 0; i < count/2; ++i)
   {
      temp = arr[i];
      arr[i] = arr[count-i-1];
      arr[count-i-1] = temp;
   }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}
char *ItoS(int num)
{
	char buf[30];
	return itoa(num,buf,10);
}
void sleep(usecond_t time)  //1 second = 1000
{
	sys_timer_usleep(time * 1000);
}
int StoI( const char *c ) {
    int value = 0;
    int sign = 1;
    if( *c == '+' || *c == '-' ) {
       if( *c == '-' ) sign = -1;
       c++;
    }
    while ( isNumericChar( *c ) ) {
        value *= 10;
        value += (int) (*c-'0');
        c++;
    }
    return value * sign;
}


void PatchInJump(int Address, int Destination, bool Linked) {

	// use this data to copy over the address
	int FuncBytes[4];

	// Get the actual destination address
	Destination = *(int *)Destination;

	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF); // lis     %r11, dest>>16
	if (Destination & 0x8000) // If bit 16 is 1
		FuncBytes[0] += 1;

	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF); // addi    %r11, %r11, dest&0xFFFF
	FuncBytes[2] = 0x7D6903A6; // mtctr    %r11

	FuncBytes[3] = 0x4E800420; // bctr

	if (Linked)
		FuncBytes[3] += 1; // bctrl

	write_process((void*)Address, FuncBytes, 4 * 4);
}
void outputTestHook() {
	static int i = 0;
	printf("Called %i\n",i++);
}

#include "Vectors.h"
#include "Structs.h"
#include "Aimbot.h"
//#include "stats2.h"
//#include "stats.h"
#include "stats3.h"

#include "Base.h"
bool sessionOpened = false;
void init() {
	//sleep(20000);
	//printf("Patches made\n");
	//injectGSC("","/maps/mp/gametypes/_persistence.gsc");

	//destiny changes


//*(unsigned int*)0x1EB030 = 0x4800001C;//something to do with spread fix
//*(unsigned int*)0x1FAEF4 = 0x60000000;//cmd sl patch, confirmed working
//*(unsigned int*)0x1FAF68 = 0x60000000;//cmd sl patch, confirmed working
*(char*)0x90B104 = 0;

//*(unsigned int*)0x467474 = 0x3C800000;//might be the code that makes it auto restart ps3 on exit, also used in keyboard function

//*(unsigned int*)0x49FB54 = 0x60000000;//causes freeze
//*(unsigned int*)0x49FB58 = 0x60000000;//causes freeze

//*(unsigned int*)0x49FC9C = 0x60000000;//code that makes debugger break?
//*(unsigned int*)0x49FCA0 = 0x60000000;//code that makes debugger break?

//*(unsigned int*)0x50B854 = 0x3C600000;//turns a bl into an lis r3 0, this is mainly what I am testing next, antic cheat maybe?

//*(unsigned int*)0x532B5C = 0x38600001;//makes r3 be 1
//*(unsigned int*)0x532B60 = 0x4E800020;//makes a function return at start

//probation (not destiny)
//*(unsigned int*)0x53FBB8 = 0x38600000;//li r3 0
//*(unsigned int*)(0x53FBB8+0x4) = 0x4E800020;//blr

//*(unsigned int*)0x5463A8 = 0x48000018;//something to do with stats


/*
these are all data
*(unsigned int*)0x907E70 = 0x0;
*(unsigned int*)0x907F48 = 0x0;
*(unsigned int*)0x90E184 = 0x0;
*(unsigned int*)0x9ABA48 = 0xC0000000;
*(unsigned int*)0xA62760 = 0x498;
*(unsigned int*)0xA62774 = 0x1A4;
*(unsigned int*)0xA7F6D8 = 0x1D8;*/


	//end destiny changes







	//printf("\n");
	//readFiles("/dev_hdd0/tmp/JiggyMenuV4.5/");//reading directory contents HAS TO HAVE THE / AT THE BEGINNING
	//printf("\n");
	addresses.GLOBAL_CGAME_PTR_ADD= 0xE22F18;
	addresses.GLOBAL_CLIENT_PTR_ADD= 0xD689D8;
	addresses.CG_BulletHitEvent_Patch=0x000E9BE8;
	addresses.CG_BulletEndposition= 0x000EBB48;
	addresses.wepidcentityoffset= 0x2B4;
	addresses.Tracer_Spawn_Patch=0x0045C038;
	addresses.BG_seedRandWithGameTime= 0x005D6C54;
	addresses.playerstate= 0x03780EA28;

	//memcpy((void*)&addresses,(void*)data,sizeof(Addresses));
	PatchInJump(0x42FC8, (int)hook, false);
	PatchInJump(0x3971A0/*0x42FC8 I used this for a long time*/, (int)renderHook, false);
	PatchInJump(0x98A60,(int)outputTestHook,false);
	sys_ppu_thread_create(&AimbotThread, Aimbot, 0, 10, 0x0A, 0, "Aimbot");
	//PatchInJump(0x00105244,(int)hkCL,false);//silent aim hook client command
	PatchInJump(0x00116524,(int)hkCL,false);//silent aim hook write packet
	setupMenu();
	threadLoop();//stops the whole process
	//for(;;) {//temporary
		//sleep(200);
	//}
}

void start() {
			//cellMsgDialogOpen(1,"Welcome to Paradise!\nMade by gopro_2027",my_dialog2,(void*) 0x0000aaab, NULL);
	dialog("Welcome to Paradise!\nMade by gopro_2027");
			init();
}
void Thread(uint64_t nothing) {
	sleep(10000);
	start();
	sys_ppu_thread_exit(nothing);
}


SYS_MODULE_INFO("Paradise SPRX", 0, 1, 1);
SYS_MODULE_START( _ParadiseCompatabilityTester_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _ParadiseCompatabilityTester_export_function, LIBNAME );

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _ParadiseCompatabilityTester_export_function(void)
{
    return CELL_OK;
}


extern "C" int _ParadiseCompatabilityTester_prx_entry(void)
{
	//unpatch the load dealio:
	//this is for the ParadiseGTA.sprx string thing
	//0xAF2565 is the address
	char data[] = {0x47, 0x43, 0x43, 0x3A, 0x20, 0x28, 0x47, 0x4E, 0x55, 0x29, 0x20, 0x34, 0x2E, 0x31, 0x2E, 0x31, 0x20, 0x28, 0x53, 0x44, 0x4B, 0x34, 0x30, 0x30, 0x2C, 0x20, 0x24, 0x52, 0x65, 0x76, 0x3A};
	for (int i = 0; i < sizeof(data); i++)
		*(char*)(0xAF2564+i) = data[i];
	//yeyuh


	char nop[] = { 0x60, 0x00, 0x00, 0x00 };
	write_process((void*)0x00462C24,&nop,4);//hang detect thread disable
	sys_ppu_thread_create(&ThreadModuleID, Thread, 0, 0x4AA, 0x7000, 0, "Paradise SPRX");
    return SYS_PRX_RESIDENT;
}





/*
obfoscate a number in memory:
#include <iostream>
#include <stdio.h>
#include <cstdlib>

//the address we are wanting to hide
#define address (0xaabbccdd)
//the amount of other values to mess with it
#define spoofersCount (100)

int main()
{
  srand (time(NULL));
  unsigned int nums[spoofersCount];
  unsigned int addr = address;
  for (int i = 0; i < spoofersCount; i++) {
    nums[i] = rand();
    addr^=nums[i];
  }
  
  int placePosition = rand()%spoofersCount;
  int numsPosition = 0;
  for (int i = 0; i < spoofersCount+1; i++) {
      if (i == placePosition) {
          printf("unsigned int n%i = 0x%X;\n",i,addr);
      } else {
          printf("unsigned int n%i = 0x%X;\n",i,nums[numsPosition]);
          numsPosition++;
      }
  }
  printf("unsigned int addr = ");
  for (int i = 0; i < spoofersCount+1; i++) {
      if (i == spoofersCount) {
          printf("n%i;\n",i);
      } else {
          printf("n%i ^ ",i);
      }
  }
  printf("//printf(\"0x%%X\",addr);\n");
}




*/