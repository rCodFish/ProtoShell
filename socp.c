#include "shell.h"

#define BUFFSIZE 4096

//byte reading and writing the hard way because masochism
void ioCopy(int IN, int OUT) {
    int n;
    char buf[BUFFSIZE];

    while ((n = read(IN, buf, BUFFSIZE)) > 0) {
        if (write(OUT, buf, n) != n)
            perror("Erro de escrita!\n");
    }
    if (n < 0)
        perror("Erro de leitura!\n");
}

//copy src contents to dest (dest comes first for whatever reason ig)
void socp(char* dest, char* src) {
    int fdIn, fdOut;

    //open in
    fdIn = open(src, FILE_MODE);
    if (fdIn < 0) {
        perror("Erro de abertura in");
        close(fdIn);
        exit(EXIT_FAILURE);
    }

    //open out
    fdOut = creat(dest, FILE_MODE);
    if (fdOut < 0) {
        perror("Erro de abertura out\n");
        close(fdOut);
        exit(EXIT_FAILURE);
    }

    //do the copying
    ioCopy(fdIn, fdOut);

    //close && close
    close(fdIn);
    close(fdOut);
}