opd_s SetPlayerStatValue_t = { 0x22D744, TOC };
void(*SetPlayerStatValue)(int clientNum, char *statName, float value) = (void(*)(int, char *, float))&SetPlayerStatValue_t;

/*opd_s setStat_t = {0x22D744,TOC};
void (*setStat)(int client, char *statName, float value) = (void(*)(int,char*,float))&setStat_t;*/

void setClientRank(int client, float rank) {
	SetPlayerStatValue(client,"RANK",rank);
	printf("RANK set for client %i value 0x%X rounded %i\n",client,*(unsigned int*)(&rank),(int)(rank));
}

void setClientPrestige(int client, float prestige) {
	SetPlayerStatValue(client,"PLEVEL",prestige);
	printf("PLEVEL set for client %i value 0x%X rounded %i\n",client,*(unsigned int*)(&prestige),(int)(prestige));
}

