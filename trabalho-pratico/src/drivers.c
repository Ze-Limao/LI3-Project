#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>

#include "../includes/drivers.h"

struct catalog_drivers {
  GHashTable * hash_drivers;
};

struct drivers {
  char * id;
  char * name;
  char * birth_day;
  char gender;
  char * car_class;
  char * license_plate;
  unsigned short int date;
  char * city;
  char * account_creation;
  bool account_status;
  double total_auferido;
  int avaliacao_total_driver; // short int nao chegou 
  int numero_viagens_driver;
  double avaliacao_media_driver;
};

Catalog_Drivers * drivers_catalog(char * pathfiles) {
  char * line = NULL;
  size_t len;

  GHashTable * hash_drivers = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free); // FAZER DESTROY NO FIM 
  char driverfile[256];
  strcpy(driverfile, pathfiles);
  char * filename = strcat(driverfile, "/drivers.csv");
  FILE * file = fopen(filename, "r");
  int i = 0;
  do {
    while (getline( & line, & len, file) != -1) {
      Drivers * d = malloc(sizeof(struct drivers));
      char * token;
      int i = 0;
      while ((token = strsep( & line, ";\n"))) {
        switch (i) {
        case 0:
          d -> id = strdup(token);
          break;
        case 1:
          d -> name = strdup(token);
          break;
        case 2:
          d -> birth_day = strdup(token);
          break;
        case 3:
          d -> gender = * (token);
          break;
        case 4:
          d -> car_class = strdup(token);
          break;
        case 5:
          d -> license_plate = strdup(token);
          break;
        case 6:
          d -> city = strdup(token);
          break;
        case 7:
          d -> account_creation = strdup(token);
          break;
        case 8:
          if (strcmp(token, "active")) {
            d -> account_status = true;
          } else {
            d -> account_status = false;
          }
        }
        i++;
      }
      g_hash_table_insert(hash_drivers, d -> id, d);

    }
    i++;
  } while (!feof(file));
  fclose(file);
  
  Catalog_Drivers * catalog_drivers = malloc (sizeof (struct catalog_drivers));
  catalog_drivers -> hash_drivers = hash_drivers;

return catalog_drivers;
}

void initHash_drivers(Catalog_Drivers * hash_drivers) { ///// COLOCAR A initHash NUM SÍTIO + APROPRIADO
  uint size = g_hash_table_size(hash_drivers->hash_drivers);
  Drivers * d;
gpointer * keys = g_hash_table_get_keys_as_array(hash_drivers->hash_drivers, & size);
  for (uint i = 0; i < size; i++) {
    d = g_hash_table_lookup(hash_drivers->hash_drivers, keys[i]);
    d -> avaliacao_media_driver = 0;
    d -> avaliacao_total_driver = 0;
    d -> numero_viagens_driver = 0;
    d->date = 0;
  }
}


//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************



char * getIdDriver(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  return strdup (d -> id);
}


bool getAccountStatus(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  return d -> account_status;
}


double getAvaliacaoMediaDriver(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  return d -> avaliacao_media_driver;
}


double getDateDriver(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  return d -> date;
}


char * getNameaDriver(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  return strdup(d -> name);
}


int getAvaliacaoTotalDriver(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  return d->avaliacao_total_driver;
}


int getNviagensDriver(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  return d -> numero_viagens_driver;
}


void avaliacaoMediaDriver(Catalog_Drivers * drivers_hash, char * key, double r){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  d -> avaliacao_media_driver = r;
}


char  getGenderDriver(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  return d -> gender;
}


char* getBirthDayDriver(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  return strdup (d -> birth_day);
}


double getTotalAuferidoDriver(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  return d -> total_auferido;
}


char * getCarClassDriver(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  return strdup (d -> car_class);
}

uint get_hash_drivers_size (Catalog_Drivers * hash_drivers) {
  uint size = g_hash_table_size (hash_drivers->hash_drivers);
  return size;
}

gpointer * get_keys_as_array_drivers (Catalog_Drivers * hash_drivers, uint size) {
  gpointer * aux = g_hash_table_get_keys_as_array (hash_drivers->hash_drivers, &size);
  return aux;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void totalAuferidoDriver(Catalog_Drivers * drivers_hash, char * key, double ta){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  d -> total_auferido += ta;
}


void avaliacaoTotalDriver(Catalog_Drivers * drivers_hash, char * key, short int r){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  d -> avaliacao_total_driver += r;
}


void numeroViagensDriver(Catalog_Drivers * drivers_hash, char * key){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  d -> numero_viagens_driver += 1;
}


void dateDriver(Catalog_Drivers * drivers_hash,char * key, unsigned short int r){
  Drivers * d;
  d = g_hash_table_lookup(drivers_hash->hash_drivers, key);
  if (r > d -> date)  d -> date = r;
}