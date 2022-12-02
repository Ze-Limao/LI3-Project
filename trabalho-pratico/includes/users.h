#ifndef USERS_H
#define USERS_H

#include <glib.h>
#include <stdbool.h>

typedef struct users Users;
typedef struct  catalog_users Catalog_Users;


Catalog_Users * users_catalog(char* pathfiles);
uint get_hash_size_users (Catalog_Users * catalog_users);
gpointer * get_hash_keys_as_array_users (Catalog_Users * catalog_users, uint size);
void initHash_users(Catalog_Users * catalog_users);
void incUserNumeroViagens(Catalog_Users * catalog_users, char * id);
void avaliacaoTotalUser(Catalog_Users * catalog_users, char * id, short int r);
void totalDistanceUser(Catalog_Users * catalog_users, char * id, int r);
void dateUser(Catalog_Users * catalog_users, char * id, unsigned short int r);
void totalGastoUser(Catalog_Users * catalog_users, char * id, double tg);
char * getUsernameUser(Catalog_Users * catalog_users, char * id);
int getDistanceUser(Catalog_Users * catalog_users, char * id);
unsigned short int getDateUser(Catalog_Users * catalog_users, char * id);
char * getNameUser(Catalog_Users * catalog_users, char * id);
bool getAccountStatusUser(Catalog_Users * catalog_users, char * id);
char * getBirthDateUser(Catalog_Users * catalog_users, char* id);
char  getGenderUser(Catalog_Users * catalog_users, char * id);
short int  getAvaliacaoTotalUser(Catalog_Users * catalog_users, char * id);
short int  getNviagensUser(Catalog_Users * catalog_users, char * id);
double getAvaliacaoMediaUser(Catalog_Users * catalog_users, char * id);
double getTotalGastoUser(Catalog_Users * catalog_users, char * id);
void avaliacaoMediaUser(Catalog_Users * catalog_users, char * id, double r);



#endif