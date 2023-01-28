#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>
#include "../includes/cities.h"

/**
 * @brief Catálogo das cidades, que contém a referência para a hashtable das cidades
 * 
 */
struct catalog_cities {
        /**
     * @brief Hashtable das cidades
     * 
     */
    GHashTable * cities_hash;
};

/**
 * @brief Struct que constitui o array a ser ordenado por avaliações médias e ids 
 */
struct avaliacao_media_driver{
    /**
     * @brief id do driver
     * 
     */
    uint id_driver;
    /**
     * @brief avaliação (total) do driver naquela cidade
     * 
     */
    unsigned short int score_driver;
    /**
     * @brief número de rides efetuadas por aquele driver naquela cidade
     * 
     */
    unsigned short int num_rides;
};


/**
 * @brief Struct que corresponde ao valor para cada chave da hashtable (cidade)
 * 
 */
struct city {
    /**
     * @brief total gasto na cidade
     * 
     */
    double total_gasto;
    /**
     * @brief número de rides feitas na cidade
     * 
     */
    unsigned int num_rides;
    /**
     * @brief array que contém os ids das rides feitas nessa cidade
     * 
     */
    unsigned int* array_rides_city;
    /**
     * @brief tamanho do array dos ids das rides por cidade
     * 
     */
    unsigned int array_rides_city_length;
    /**
     * @brief array de structs Aval_média ordenado por avaliação média e id
     * 
     */
    Avaliacao_media_driver * array_avaliacao;
    /**
     * @brief tamanho do array de Aval_média
     * 
     */
    unsigned int array_avaliacao_length;
};


/**
 * @brief Inicializa o catálogo das cidades
 * 
 * @return apontador para o catálogo
 */

Catalog_Cities * cities_catalog () {
    GHashTable * cities_hash = g_hash_table_new (g_str_hash, g_str_equal);
    Catalog_Cities * catalog_cities = malloc  (sizeof (struct catalog_cities));
    catalog_cities->cities_hash = cities_hash;
    return catalog_cities;
}

/**
 * @brief Insere para cada ride válida e que insere a struct city (já preenchida) na sua hashtable
 * 
 * @param catalog_cities Catálogo das cidades, que contém a referência para a hashtable das cidades
 * @param city_to_check Cidade na qual queremos preencher (key)
 * @param total_gasto_por_ride Total gasto na ride
 * @param size_drivers Tamanho do array dos drivers
 * @param driver_id Id do driver que efetuou a ride
 * @param score_driver Avaliação do driver para aquela ride
 * @param index_array_rides índice na qual se pode encontrar a ride no array das rides
 */

void fill_cities_catalog (Catalog_Cities * catalog_cities, Catalog_Rides* catalog_rides, Catalog_Drivers* catalog_drivers) {

    int ride_id;
    char* city_to_check;
    char car_class;
    double total_gasto_por_ride = 0;
    double total_gasto_sem_tips = 0;
    double ride_tip = 0;
    int driver_id;
    unsigned short int ride_distance = 0;
    float ride_score_driver;
     
    // índice onde está o driver cujo id é "driver_id" no array dos drivers
    int array_driver_index;

    unsigned int array_rides_length = get_array_rides_length (catalog_rides);
    uint array_drives_length = get_array_drivers_size (catalog_drivers);

    for (uint i = 0; i < array_rides_length; i++) {
        
        ride_id = get_ride_id (catalog_rides,i);
        if (ride_id != -1) {
            
            driver_id = get_ride_driver (catalog_rides,i);
            array_driver_index = driver_id - 1;

            ride_distance = get_ride_distance (catalog_rides,i);
            car_class = get_driver_carclass(catalog_drivers, array_driver_index);
            city_to_check = get_ride_city (catalog_rides, i);
            ride_tip = get_ride_tip (catalog_rides,i);
            total_gasto_por_ride = calcula_total_gasto (car_class,ride_distance,ride_tip);
            total_gasto_sem_tips = total_gasto_por_ride - ride_tip;
            ride_score_driver = get_score_driver_ride (catalog_rides,i);  

                if (g_hash_table_lookup (catalog_cities->cities_hash,city_to_check) == NULL) {

                // Copia-se o valor da chave (string cidade) e inicializam-se os valores total_gasto e num_rides;
                char* key =  strdup (city_to_check);
                City* city = malloc (sizeof (City));
                city->total_gasto = 0;
                city->total_gasto += total_gasto_sem_tips;
                city->num_rides = 1;
                
                //inicializa o array de avaliações para esta nova cidade
                city->array_avaliacao = malloc (array_drives_length * sizeof(Avaliacao_media_driver));
                for (uint i = 0; i < array_drives_length; i++) {
                    city->array_avaliacao[i].num_rides = 0;
                    city->array_avaliacao[i].score_driver = 0;
                    city->array_avaliacao[i].id_driver = 0;

                }
                //Preenche o campo do 1º user desta cidade
                city->array_avaliacao[array_driver_index].id_driver = driver_id;
                city->array_avaliacao[array_driver_index].score_driver = ride_score_driver;
                city->array_avaliacao[array_driver_index].num_rides = 1;
                city->array_avaliacao_length = array_drives_length;

                // inicializa o array de rides para a nova cidade e preenche com o 1º id
                city->array_rides_city_length = 0;
                city->array_rides_city = malloc (100 *sizeof(uint));
                city->array_rides_city[city->array_rides_city_length] = i;
                city->array_rides_city_length ++;

                // insere a nova struct cidade na hashtable
                g_hash_table_insert (catalog_cities->cities_hash, key, city); 
            }

            // A cidade já se encontra na hashtable
            else {

                // Procura a cidade na hashtable e incrementa os valores num_rides e total_gasto
                City *city = g_hash_table_lookup (catalog_cities->cities_hash,city_to_check);
                city->num_rides++;
                city->total_gasto += total_gasto_sem_tips;
                
                // Preenche o array das avaliações médias para o driver encontrado
                city->array_avaliacao[array_driver_index].id_driver = driver_id; 
                city->array_avaliacao[array_driver_index].score_driver += ride_score_driver;
                city->array_avaliacao[array_driver_index].num_rides ++;
                
                // Preenche o array dos ids das rides para o driver encontrado
                city->array_rides_city[city->array_rides_city_length] = i;
                city->array_rides_city_length++;
                if (city->array_rides_city_length % 100 == 0) city->array_rides_city = realloc(city->array_rides_city, sizeof(uint) * (city->array_rides_city_length + 100)); 
            // if (driver_id == 4214) printf ("%d",city->array_avaliacao[driver_id].score_driver), printf ("Score_added: %d\n",score_driver);
            }   
        free (city_to_check);
        }
    }
}
 

/**
 * @brief Liberta a memória associada a cada cidade (value) da hashtable
 * 
 * @param key chave (string cidade)
 * @param value struct city
 * @param user_data (não utilizado)
 */

void free_city_data(gpointer key, gpointer value, gpointer user_data) {
  City *city = (City *)value;
  free (city->array_rides_city);
  free (city->array_avaliacao);
  free (city);
  free (key);
  (void)(user_data); /* unused */   // flag que diz ao compilador para ignorar a não utiliação de uma variável.
}

/**
 * @brief Liberta toda a memória associada ao catálogo das cidades
 * 
 * @param catalog_cities Catálogo das cidades, que contém a referência para a hashtable das cidades
 */

void free_cities_catalog (Catalog_Cities * catalog_cities) {
    g_hash_table_foreach(catalog_cities->cities_hash, (GHFunc)free_city_data, NULL);
    g_hash_table_destroy (catalog_cities->cities_hash);
    free (catalog_cities);
}

/**
 * @brief Devolve o número de rides feitas por um driver na cidade
 * 
 * @param catalog_cities  Catálogo das cidades, que contém a referência para a hashtable das cidades
 * @param city Cidade na qual queremos procurar (key)
 * @return Nnúmero de rides feitas por um driver na cidade 
 */

uint get_num_rides_city (Catalog_Cities * catalog_cities, char * city) {
    City* aux = g_hash_table_lookup (catalog_cities->cities_hash,city);
     return aux->num_rides;
}


/**
 * @brief Devolve total gasto por um driver na cidade
 * 
 * @param catalog_cities Catálogo das cidades, que contém a referência para a hashtable das cidades 
 * @param city Cidade na qual queremos procurar (key)
 * @return double 
 */

double get_total_gasto_city (Catalog_Cities* catalog_cities, char * city) {
    City* aux = g_hash_table_lookup (catalog_cities->cities_hash,city);
    return aux->total_gasto;
}

/**
 * @brief Verifica se uma string cidade é uma chave da hashtable das cidades
 * 
 * @param catalog_cities  Catálogo das cidades, que contém a referência para a hashtable das cidades
 * @param city Cidade na qual queremos procurar (key)
 * @return true Se a cidade for uma chave válida
 * @return false Se não for
 */

bool is_in_hash_cities (Catalog_Cities * catalog_cities, char* city) {
    City* aux = g_hash_table_lookup (catalog_cities->cities_hash,city);
    if (!aux) return false;
    else return true;
}

/**
 * @brief Calcula a distância média percorrida numa cidade entre duas datas
 * 
 * @param catalog_cities  Catálogo das cidades, que contém a referência para a hashtable das cidades
 * @param catalog_rides Catálogo das rides 
 * @param city Cidade na qual queremos procurar (chave)
 * @param dateInf Data limite inferior
 * @param dateSup Data limite superior
 * @return distância média percorrida numa cidade entre duas datas 
 */

double get_average_distance (Catalog_Cities* catalog_cities, Catalog_Rides* catalog_rides,char * city, unsigned short int dateInf, unsigned short int dateSup) {
      unsigned int cont=0;
      unsigned short int distance = 0;
      double distancia_media = 0;
      City * aux = g_hash_table_lookup (catalog_cities->cities_hash, city);

      unsigned short int date = 0;
      for (uint i = 0; i < aux->array_rides_city_length; i++) {
        
        unsigned int id = aux->array_rides_city[i];
        date = get_ride_date (catalog_rides,id);
        
        if (date >= dateInf && date <= dateSup) {
        
            distance = get_ride_distance (catalog_rides,id);
            distancia_media += distance;
            cont++;
        }
      }
    if (cont != 0) distancia_media = distancia_media / cont;   
    return distancia_media;
}


