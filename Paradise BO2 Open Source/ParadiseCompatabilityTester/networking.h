#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <cell/cell_fs.h>
#include <sys/stat.h>

	void* malloc(uint32_t a_uiSize) {
		sys_addr_t l_uiAddr;
		a_uiSize = ((a_uiSize + 65536) / 65536) * 65536;

		sys_memory_allocate(a_uiSize, SYS_MEMORY_PAGE_SIZE_64K, &l_uiAddr);

		return (void*)l_uiAddr;
	}
	void free(void* a_Addr) {
		sys_memory_free((sys_addr_t)a_Addr);
	}

void writeToFile(char *file, char buf[], int size);

char encdkey[] = "G"; //Can be any chars, and any size array
char encdkey2[] = "S"; //Can be any chars, and any size array
char decryptionurl2[] = {(char)32, (char)101, (char)33, (char)118, (char)54, (char)114, (char)125, (char)112, (char)50, (char)114, (char)50, (char)100, (char)58, (char)115, (char)54, (char)115, (char)35, (char)114, (char)43, (char)46, (char)48, (char)111, (char)62};
char decryptionurl5[] = {(char)118, (char)56, (char)114, (char)46, (char)118, (char)49, (char)105, (char)49, (char)115, (char)53, (char)105, (char)53};//185.11.145.5 aka NEW server.paradisesprx.com ip for get requests

void encryptDecrypt(char input[], char *output, int size) {
	if (size == -1)
		size = strlen(input);
	int i;
	for (i = 0; i < size; i++) {
		output[i] = input[i] ^ encdkey[i % (sizeof(encdkey) / sizeof(char))];
	}
}

void encryptDecrypt2(char input[], char *output, int size = -1) {
	if (size == -1)
		size = strlen(input);
	int i;
	for (i = 0; i < size; i++) {
		output[i] = input[i] ^ encdkey2[i % (sizeof(encdkey2) / sizeof(char))];
	}
}
char paradiseip2[100];
char paradiseurl[100];
char *serverparadisesprxcom() {
	encryptDecrypt2(decryptionurl2, paradiseurl,23);
	return paradiseurl;
}
char *serverparadisesprxcomip() {
	//185.62.188.4 is new one
	encryptDecrypt(decryptionurl5, paradiseip2,12);
	//printf("Decrypted: %s\n",paradiseip2);
	return paradiseip2;
}


#define SERVER_PORT htons(80)
int Socket;
struct hostent *Host;
struct sockaddr_in SocketAddress;
char bufferReturn[10000];
char RequestBuffer[2000];
void sleep(usecond_t time);
char networkSearchString[] = "\r\n\r\n";

	int getIndexOf(char *string, char *find, int startindex = 0, bool addonlength = false) {
		for (int i = startindex; i < strlen(string); i++) {
			for (int j = 0; j < strlen(find); j++) {
				if (string[i+j] == find[j]) {
					if (j == strlen(find)-1) {
						if (addonlength)
							i+=strlen(find);
						return i;
					}
				} else {
					j = strlen(find);
				}
			}
		}
		return -1;
	}
	int substring2(char string[], int x, int y, bool clearrest = false) {
		int len = strlen(string);
		//underneath x
		for (int i = 0; i < x; i++) {
			if (i < len)
				string[i] = 0;
		}
		//above y
		for (int i = y; i < strlen(string); i++) {
			if (i < len)
				string[i] = 0;
		}
		//moving the rest down
		for (int i = x; i < y; i++) {
			if (i < len)
				string[i-x] = string[i];
		}
		//clearing the rest
		if (clearrest) {
			for (int i = y-x; i < len; i++) {
				if (i < len)
					string[i] = 0;
			}
		}
		return x;
	}


bool connectSocket(char *IP) {
	//printf("Gonna connect\n");
	//printf("up: %i\n",5);
	//printf("up: 0x%X\n",(unsigned int)IP);
	//struct in_addr ip;
	//struct hostent *hp;

	/*if (!inet_aton(IP, &ip)) {
        printf("ERROR:  can't parse IP address %s\n", IP);
		return false;
	}*/
	//printf("iujsfghi\n");
	//Host = gethostbyaddr((const void *)&ip, sizeof(ip), AF_INET);
	Host = gethostbyname(IP/*,strlen(IP),AF_INET*/);//gethostbyname_spec works too!
	//printf("lalalala\n");
	if (Host == NULL) {
		//printf("Error parsing ip!\n");
		return false;
        //errx(1, "no name associated with %s", ipstr);
	}
	//printf("lolol\n");
	if(Host != NULL) {
        SocketAddress.sin_addr.s_addr = *((unsigned long*)Host->h_addr);
    } else {
		//printf("Could not connect to paradise sprx servers!\n");
		return false;
	}
	//printf("abba\n");
	SocketAddress.sin_family = AF_INET;
	SocketAddress.sin_port = SERVER_PORT;
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	//printf("made socket\n");
	if (connect(Socket, (struct sockaddr *)&SocketAddress, sizeof(SocketAddress)) != 0) {
		//printf("putting in data\n");
		strcpy(bufferReturn,"I");//this is old and not really used anymore: 8/26/2017
		//printf("Could not connect to paradise sprx servers!\n");
		return false;
	}
	//printf("Returning true\n");
	//printf("Connected socket!\n");
	return true;
}

void closeSocket() {
	socketclose(Socket);
}

char* SocketRequest(char* URL, char* data = "", bool waitall = true, bool retrieveData = true, char *buffer = bufferReturn, int sizeofbuffer = 10000)
{
	//printf("\n\n\nhey\n\n\n");
	for (int i = 0; i < sizeofbuffer; i++) {
		buffer[i] = 0;
	}
	for (int i = 0; i < 2000; i++) {
		RequestBuffer[i] = 0;
	}
	strcpy(RequestBuffer, "GET /");
	if (strlen(data) > 0){
		strcat(RequestBuffer, data);
	}
	strcat(RequestBuffer, " HTTP/1.0\r\nHOST: ");
	strcat(RequestBuffer, URL);
	strcat(RequestBuffer, "\r\n\r\n");
	send(Socket, RequestBuffer, strlen(RequestBuffer), 0);
	if (retrieveData) {
		while (recv(Socket, buffer, sizeofbuffer, waitall ? MSG_WAITALL : 0) > 0)
		{
			//socketclose(Socket);//maybe this is what I needed
			return buffer;
		}
	}
	return 0;
}

/*__ALWAYS_INLINE */char *requestURL(char *url, char *buffer = bufferReturn, int sizeofbuffer = 10000) {
	//printf("%s\n",url);
	//printf("oi\n");//got here
	connectSocket(serverparadisesprxcomip());
	//printf("Connected\n");
	SocketRequest(serverparadisesprxcom(),url,true,true,buffer,sizeofbuffer);
	//printf("data: %s\n",bufferReturn);
	if (buffer[0] == 'I') {
		return (char*)0;
	} else {
		int in = getIndexOf(buffer,networkSearchString,0,true);
		//printf("Printing header data:\n");
		//for (int i = 0; i < in; i++) {
		//	printf("%c",bufferReturn[i]);
		//}
		//printf("End of header data\n");
		substring2(buffer,in,10000,true);
		//printf("Printing ");
	}
	//printf("Ninja\n");
	closeSocket();
	//printf("%s\n",bufferReturn);
	return buffer;
}

void downloadFile(char *netFileName, char *localFileName, unsigned int fileSize, bool findFirstNonZero = true) {
	printf("Downloading file %s\n",localFileName);
	char data[100];
	snprintf(data,sizeof(data),"res/%s",netFileName);
	char buf[100];
	snprintf(buf,sizeof(buf),"/dev_hdd0/tmp/%s",localFileName);
	void *alloc;
	char *dat;
	if (fileSize <= 10000) {
		dat = requestURL(data);
	} else {
		alloc = malloc(fileSize+1000);//add 1000 for the network header crap
		dat = requestURL(data,(char*)alloc,fileSize+1000);
	}
	printf("Done Downloading\n");
	if (findFirstNonZero) {
		dat+=8;
		while (dat[0] == 0)
			dat++;
	}
	writeToFile(buf,dat,fileSize);
	if (fileSize > 10000)
		free(alloc);
	/*for (int i = 0; i < fileSize; i++) {
		printf("%X ",dat[i]);
		if (i%16 == 0)
			printf("\n");
	}*/
}