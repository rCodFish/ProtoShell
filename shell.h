#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/wait.h>

#define BUFFIZE 128
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

typedef struct { char msg[100] ; int tempo;} aviso_t;

int parse(char *buf, char **args);

void execute(int numargs, char **args);

int builtin (char **args);

void ioCopy(int IN, int OUT);

void socp(char* dest, char* src);

void calc(char *value1, char *op, char *value2);

int cat(char *nome);

void aviso(char* mesg, int tempo);

int redirects(int argc, char *args[]);

void* avisowrapper(void* args);

/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1
