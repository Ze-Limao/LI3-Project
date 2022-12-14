#ifndef DRIVERS_H
#define DRIVERS_H

#include <glib.h>

typedef struct drivers Drivers;
typedef struct catalog_drivers Catalog_Drivers;
typedef struct query2 Query2;

void top_N_drivers (Catalog_Drivers * catalog_drivers);
Catalog_Drivers * drivers_catalog(char * pathfiles);
void insert_top_N_drivers (Catalog_Drivers * catalog_drivers , Query2 ** top_N_drivers);
void initHash_drivers(Catalog_Drivers * catalog_drivers);
void free_hash_drivers (Catalog_Drivers * catalog_drivers);
void totalAuferidoDriver(Catalog_Drivers * catalog_drivers, char * key, double ta);
void avaliacaoTotalDriver(Catalog_Drivers * catalog_drivers, char * key, short int r);
void numeroViagensDriver(Catalog_Drivers * catalog_drivers, char * key);
void dateDriver(Catalog_Drivers * catalog_drivers, char * key, unsigned short int r);
char * getIdDriver(Catalog_Drivers * catalog_drivers, char * key);
bool   getAccountStatus(Catalog_Drivers * catalog_drivers, char * key);
double getAvaliacaoMediaDriver(Catalog_Drivers * catalog_drivers, char * key);
double getDateDriver(Catalog_Drivers * catalog_drivers, char * key);
char * getNameDriver(Catalog_Drivers * catalog_drivers, char * key);
char   getGenderDriver(Catalog_Drivers * catalog_drivers, char * key);
char* getBirthDayDriver(Catalog_Drivers * catalog_drivers, char * key);
double getTotalAuferidoDriver(Catalog_Drivers * catalog_drivers, char * key);
char * getCarClassDriver(Catalog_Drivers * catalog_drivers, char * key);
int getAvaliacaoTotalDriver(Catalog_Drivers * catalog_drivers, char * key);
int getNviagensDriver(Catalog_Drivers * catalog_drivers, char * key);
void avaliacaoMediaDriver(Catalog_Drivers * catalog_drivers, char * key, double r);
char * get_name_driver_top_N (Catalog_Drivers * catalog_drivers,int n);
char * get_id_driver_top_N (Catalog_Drivers * catalog_drivers, int n);
double get_aval_med_top_N (Catalog_Drivers * catalog_drivers, int n);
uint get_hash_drivers_size (Catalog_Drivers * catalog_drivers);
gpointer * get_hash_keys_as_array_drivers (Catalog_Drivers * catalog_drivers, uint size);


#endif