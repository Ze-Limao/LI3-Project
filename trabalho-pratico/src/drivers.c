#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>
#include "../includes/parser.h"
#include "../includes/query1.h"
#include "../includes/dates.h"
#include "../includes/drivers_services.h"
#include "../includes/drivers.h"

struct catalog_drivers {
  Driver ** array_drivers;
  uint array_length;
  Driver_Aval_Date * top_N_drivers;
};

struct driver {
  //char * id;
  char * name;
  short int age;
  char gender;
  char * car_class;
  char * license_plate;
  unsigned short int date;
  char * city;
  unsigned short int account_creation;
  bool account_status;
  double total_auferido;
  int avaliacao_total_driver;
  int numero_viagens_driver;
  double avaliacao_media_driver;
};

  Driver* create_driver(char** tokens, void* catalog) {
    Driver* driver = malloc(sizeof(Driver));
    //driver->id = strdup(tokens[0]);
    driver->name = strdup(tokens[1]);
    driver->age = calcula_idade (tokens[2]);
    driver->gender = *tokens[3];
    driver->car_class = strdup(tokens[4]);
    driver->license_plate = strdup(tokens[5]);
    driver->city = strdup(tokens[6]);
    driver->account_creation = convert_to_day(tokens[7]);
    driver->account_status = (tokens[8][0] == 'a' || tokens[8][0] == 'A') == 1;
    
    Catalog_Drivers* catalog_drivers = (Catalog_Drivers*)catalog;

  // Fetch das informações do catálogo
  uint num_drivers = catalog_drivers->array_length;
  Driver** array_drivers = catalog_drivers->array_drivers;

  // Adiciona a ride ao catálogo
  array_drivers[num_drivers] = driver;
  catalog_drivers->array_length++;
  num_drivers++; 
  if (num_drivers % 100 == 0) catalog_drivers->array_drivers = realloc(array_drivers, sizeof(Driver*) * (num_drivers + 100));

  return driver; 
  }



Catalog_Drivers * drivers_catalog(char * pathfiles) {
  Driver** array_drivers = malloc (100 * sizeof (Driver*));  

  Catalog_Drivers* catalog_drivers = malloc (sizeof (Catalog_Drivers));
  catalog_drivers -> array_drivers = array_drivers;
  catalog_drivers -> array_length = 0;

  char driverfile[256];
  strcpy(driverfile, pathfiles);
  char * filename = strcat(driverfile, "/drivers.csv");

  // Call parse_csv with the create and insert functions
  parse_csv(filename, (create_fn)create_driver, catalog_drivers);
  return catalog_drivers;
}


//---------------------------------------Estrutura auxiliar dos drivers (query2) ---------------------------------------------//
void set_top_N_drivers(Catalog_Drivers* catalog_drivers, void* top_N_drivers) {
    catalog_drivers->top_N_drivers = (Driver_Aval_Date*) top_N_drivers;
}
void* get_top_N_drivers(Catalog_Drivers* catalog_drivers) {
    return (void*) catalog_drivers->top_N_drivers;
}


//----------------------------------------------------------------------------------------------------------------------

void initHash_drivers(Catalog_Drivers * catalog_drivers) { 
  uint size = catalog_drivers->array_length;
  Driver * d;
  for (uint i = 0; i < size; i++) {
    d = catalog_drivers->array_drivers[i];
    d -> avaliacao_media_driver = 0;
    d -> avaliacao_total_driver = 0;
    d -> numero_viagens_driver = 0;
    d ->total_auferido = 0;
    d-> date = 0;
  }
}

void update_avaliacao_media_driver (Catalog_Drivers * catalog_drivers) {
  uint size = catalog_drivers->array_length;
  double r = 0;
  for (uint i = 0; i < size; i++) {
    r = (float) get_driver_avalMedia(catalog_drivers, i) / (float) get_driver_Nviagens(catalog_drivers, i);
    avaliacaoMediaDriver(catalog_drivers,i, r);
  }
}



//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************
 
//***************************************************** Funções de encapsulamento de drivers *********************************************************

unsigned short int get_data_creation_days_driver (Catalog_Drivers* catalog_drivers, int index) {
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d->account_creation;
}

/*
char * get_driver_id (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return strdup (d -> id);
}
*/

uint get_array_drivers_size (Catalog_Drivers* catalog_drivers) {
  return catalog_drivers->array_length;
}

bool get_driver_acc_Status (Catalog_Drivers * catalog_drivers, int index){
  if ((uint)index > catalog_drivers->array_length) return false;
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d -> account_status;
}


double get_driver_avalMedia (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d -> avaliacao_media_driver;
}


double get_driver_date (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index];
  return d -> date;
}


char * get_driver_name (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return strdup(d -> name);
}

int get_driver_Nviagens (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d -> numero_viagens_driver;
}


void avaliacaoMediaDriver(Catalog_Drivers * catalog_drivers, int index, double r){
  Driver * d = catalog_drivers->array_drivers[index]; 
  d -> avaliacao_media_driver = r;
}


char  get_driver_gender (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d -> gender;
}


short int get_driver_age (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return (d -> age);
}


double get_driver_total_auferido (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return d -> total_auferido;
}


char * get_driver_carclass (Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers[index]; 
  return strdup (d -> car_class);
}

/*
uint get_hash_drivers_size (Catalog_Drivers * catalog_drivers) {
  uint size = g_hash_table_size (catalog_drivers->hash_drivers);
  return size;
}
*/

/*
gpointer * get_hash_keys_as_array_drivers (Catalog_Drivers * catalog_drivers, uint size) {
  gpointer * aux = g_hash_table_get_keys_as_array (catalog_drivers->hash_drivers, &size);
  return aux;
}
*/

//-----------------------Funções que interagem com o catálogo dos drivers---------------------------------------------------------------------------------------------------------------------------------


void totalAuferidoDriver(Catalog_Drivers * catalog_drivers, int index, double ta){
  Driver * d = catalog_drivers->array_drivers [index]; 
  d -> total_auferido += ta;
}


void inc_avaliacao_media_driver(Catalog_Drivers * catalog_drivers, int index, short int r){
  Driver * d = catalog_drivers->array_drivers [index]; 
  d -> avaliacao_media_driver += r;
}


void numeroViagensDriver(Catalog_Drivers * catalog_drivers, int index){
  Driver * d = catalog_drivers->array_drivers [index]; 
  d -> numero_viagens_driver += 1;
}


void dateDriver(Catalog_Drivers * catalog_drivers,int index, unsigned short int r){
  Driver * d = catalog_drivers->array_drivers [index]; 
  if (r > d -> date)  d -> date = r;
}

//--------------------------------------------Função free---------------------------------------------------------//

void free_driver_data(gpointer key, gpointer value, gpointer user_data) {
  Driver *d = (Driver *)value;
  //free (d->id);
  free (d->name);
  //free (d->birth_day);
  free (d->car_class);
  free (d->license_plate);
  free (d->city);
  //free (d->account_creation);
  free (d);
  (void)key;/*unused*/
  (void)user_data;/*unused*/
}


void free_drivers_catalog (Catalog_Drivers * catalog_drivers) {
  uint size = catalog_drivers->array_length;
  
  for (uint i = 0; i < size; i++) {
  Driver *d = catalog_drivers->array_drivers[i];
  free (d->name);
  //free (d->birth_day);
  free (d->car_class);
  free (d->license_plate);
  free (d->city);
  //free (d->account_creation);
  free (d);
  }

  //g_hash_table_foreach(catalog_drivers->hash_drivers, (GHFunc)free_driver_data, NULL);
  //g_hash_table_destroy (catalog_drivers->hash_drivers);
  free_drivers_services (catalog_drivers, size);
  free (catalog_drivers->top_N_drivers);
  free (catalog_drivers);
}