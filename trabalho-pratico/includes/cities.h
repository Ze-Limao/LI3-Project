#include "../includes/rides.h"
#include "../includes/drivers.h"
#include "../includes/query1.h"


typedef struct catalog_cities Catalog_Cities;
typedef struct avaliacao_media_driver Avaliacao_media_driver;
typedef struct city City;

Catalog_Cities * cities_catalog ();
void fill_cities_catalog (Catalog_Cities * catalog_cities, Catalog_Rides* catalog_rides, Catalog_Drivers* catalog_drivers);
void free_cities_catalog (Catalog_Cities * catalog_cities);
unsigned int get_num_rides_city (Catalog_Cities * catalog_cities, char * city);
double get_total_gasto_city (Catalog_Cities* catalog_cities, char * city);
bool is_in_hash_cities (Catalog_Cities * catalog_cities, char* city);
void fill_array_rides (Catalog_Cities * catalog_cities, unsigned short int total_dist, char * city);
double get_average_distance (Catalog_Cities* catalog_cities, Catalog_Rides* catalog_rides,char * city, unsigned short int dateInf, unsigned short int dateSup);


