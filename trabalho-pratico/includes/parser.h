#ifndef PARSER_H
#define PARSER_H

#include "users.h"
#include "drivers.h"

void parser_input(char* pathfiles, char* input);
char* substr(const char *str, int m, int n);
char* fixstring(char* info);

#endif