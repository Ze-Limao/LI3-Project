#ifndef RIDES_H
#define RIDES_H

#include <stdbool.h>
#include <glib.h>
#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/query4.h"


typedef struct ride Ride;
typedef struct catalog_rides Catalog_Rides;

Catalog_Rides* rides_catalog(Catalog_Users * catalog_users, Catalog_Drivers * catalog_drivers, Catalog_Cities * catalog_cities, char * pathfiles);
unsigned short int get_ride_date (Catalog_Rides * catalog_rides, char * id);
int get_ride_distance (Catalog_Rides * catalog_rides, char * id);
uint get_hash_rides_size (Catalog_Rides * catalog_rides);
gpointer * get_hash_keys_as_array_rides (Catalog_Rides * catalog_rides, uint size);
char * get_ride_driver (Catalog_Rides * catalog_rides, char* id);
void free_hash_rides (Catalog_Rides * catalog_rides);

#endif