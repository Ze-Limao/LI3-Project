#include "../includes/query1.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h>
#include  "../includes/drivers.h"
#include  "../includes/users.h"


double calcula_total_gasto(char car_class, unsigned short int distance, double tip) {
  double total = 0.000;
  if (car_class =='b' || car_class == 'B') {
    total = total + 3.250 + (0.620 * distance) + tip;
  } else if (car_class == 'g'|| car_class == 'G') {
    total = total + 4.000 + (0.790 * distance) + tip;
  } else if (car_class == 'p' || car_class  == 'P') {
    total = total + 5.200 + (0.94 * distance) + tip;
    }
  return total;
}




void query1_driver (int index, Catalog_Drivers * catalog_drivers, int n) {
  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);

  if (!get_driver_acc_Status(catalog_drivers, index - 1)) {
    FILE * output = fopen(buffer, "w");
    fclose(output);
  } else {
    //double r = (float) getAvaliacaoMediaDriver(catalog_drivers, id) / (float) getNviagensDriver(catalog_drivers, id);
    //avaliacaoMediaDriver(catalog_drivers, id, r);

    short int age = get_driver_age (catalog_drivers, index - 1);
    char * name = get_driver_name (catalog_drivers, index -1 );

    FILE * output = fopen(buffer, "w");
    fprintf(output, "%s;"
      "%c;"
      "%d;"
      "%.3f;"
      "%d;"
      "%.3f\n", name, get_driver_gender(catalog_drivers, index - 1), age, get_driver_avalMedia(catalog_drivers, index - 1), get_driver_Nviagens (catalog_drivers, index - 1), get_driver_total_auferido (catalog_drivers, index - 1));
    fclose(output);
    free (name);
  }
}

void query1_user(char * id, Catalog_Users * catalog_users, int n) {
  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
  if  (!getAccountStatusUser(catalog_users, id)) {
    FILE * output = fopen(buffer, "w");
    fclose(output);
  } else {
    double avaliacao_media = get_aval_media_user (catalog_users, id);

    char * name = getNameUser(catalog_users, id);
    short int age = get_age_user(catalog_users,id);
    FILE * output = fopen(buffer, "w");
    fprintf(output, "%s;"
      "%c;"
      "%d;"
      "%.3f;"
      "%d;"
      "%.3f\n", name, getGenderUser(catalog_users, id), age, avaliacao_media, getNviagensUser(catalog_users, id), getTotalGastoUser(catalog_users, id));
    fclose(output);
    free (name);
  }
}

void query1_main(char * id, Catalog_Users * catalog_users, Catalog_Drivers * catalog_drivers, int n) {
  //printf ("%d\n",n);
  if (isdigit(id[0]) == 0) {
    query1_user(id, catalog_users, n);
  } else {
    int index = atoi(id);
    query1_driver(index, catalog_drivers, n);
  }
}