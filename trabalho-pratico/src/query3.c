#include <stdio.h>

#include <glib.h>

#include "../includes/query3.h"

#include "../includes/rides.h"

#include "../includes/users.h"

#include "../includes/drivers.h"


struct query3{
  char * id;
  int distance;
  char* name;
  unsigned short int data;
};


int compare_users(const void * a, const void * b) {
  Query3 * ia = (struct query3 * ) a;
  Query3 * ib = (struct query3 * ) b;

  if (ia -> distance < ib -> distance) return 1;

  if (ia -> distance > ib -> distance) return -1;

  if (ia -> distance == ib -> distance) {
    if (ia -> data < ib -> data) return 1; //se id for igual retorna a data + recente
    if (ia -> data > ib -> data) return -1;
    else if (ia -> data == ib -> data) { // se for para trocar é este
      if (strcmp (ia -> id , ib -> id) > 0) return 1;
      if (strcmp (ia -> id, ib -> id) < 0) return -1;
    }
    return -1; // se datas também forem iguais retorna 
  } else {
    return 0;
  }
}


//   if (strcmp (ia -> id, ib -> id) < 0) return 1;
//    if (strcmp (ia -> id , ib -> id) > 0) return -1;
void query3(Catalog_Users * hash_users, char * info, int n) {
  int numb = atoi(info);
  uint size = get_hash_size_users (hash_users);

  Query3 * query3 = malloc(size * sizeof(struct query3));
  gpointer * keys = get_hash_keys_as_array_users(hash_users,size);
  for (uint i = 0; i < size; i++) {
    (query3 + i) -> id = getUsernameUser(hash_users, keys[i]);
    (query3 + i) -> distance = getDistanceUser(hash_users, keys[i]);
    (query3 + i) -> data = getDateUser(hash_users, keys[i]);
    (query3 + i) -> name = getNameUser(hash_users, keys[i]);

  }
  free (keys);
  qsort((void * ) query3, size, sizeof(struct query3), compare_users);

  char buffer[256];
  snprintf(buffer, 256, "Resultados/command%d_output.txt", n);
  FILE * output = fopen(buffer, "w");
  for (int i = 0; i < numb; i++) {
    if (getAccountStatusUser(hash_users, (query3 + i) -> id)) {     //(!u -> account_status)
      fprintf(output, "%s;"
        "%s;"
        "%d\n", (query3 + i) -> id, (query3 + i) -> name, (query3 + i) -> distance);

    } else {
      numb++;
    }
  }
  for (uint i = 0; i < size; i++) {
    free ((query3 + i) -> id);
    free ((query3 + i) -> name);
  }
  free (query3);
  fclose(output);
}