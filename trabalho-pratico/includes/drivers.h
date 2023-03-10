#ifndef DRIVERS_H
#define DRIVERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../includes/parser.h"
#include "../includes/dates.h"
#include "../includes/rides.h"
#include <glib.h>
#include <stdbool.h>
#include <math.h>



typedef struct driver Driver;
typedef struct catalog_drivers Catalog_Drivers;
typedef struct driver_aval_date Driver_Aval_Date;


Catalog_Drivers * drivers_catalog(char * pathfiles);
void init_array_drivers(Catalog_Drivers * catalog_drivers);
void update_avaliacao_media_driver(Catalog_Drivers * catalog_drivers);
void free_drivers_catalog (Catalog_Drivers * catalog_drivers);


char * get_driver_id (Catalog_Drivers * catalog_drivers,  int index);
bool   get_driver_acc_Status(Catalog_Drivers * catalog_drivers,  int index);
double get_driver_avalMedia (Catalog_Drivers * catalog_drivers,  int index);
double get_driver_date (Catalog_Drivers * catalog_drivers,  int index);
char * get_driver_name (Catalog_Drivers * catalog_drivers,  int index);
char   get_driver_gender (Catalog_Drivers * catalog_drivers,  int index);
short int get_driver_age (Catalog_Drivers * catalog_drivers,  int index);
double get_driver_total_auferido (Catalog_Drivers * catalog_drivers,  int index);
char get_driver_carclass (Catalog_Drivers * catalog_drivers,  int index);
uint get_array_drivers_size (Catalog_Drivers* catalog_drivers);
int get_driver_Nviagens (Catalog_Drivers * catalog_drivers,  int index);
unsigned short int get_data_creation_days_driver (Catalog_Drivers* catalog_drivers, int index);


int get_array_top_N_drivers_length (Catalog_Drivers* catalog_drivers);
void top_N_drivers (Catalog_Drivers * catalog_drivers);
char * get_name_driver_top_N (Catalog_Drivers * catalog_drivers,int n);
int get_id_driver_top_N (Catalog_Drivers * catalog_drivers, int n);
double get_aval_med_top_N (Catalog_Drivers * catalog_drivers, int n);

void free_top_N_drivers (Catalog_Drivers* catalog_drivers, int size);

void fill_drivers_array (Catalog_Drivers* catalog_drivers, Catalog_Rides* catalog_rides);

#endif