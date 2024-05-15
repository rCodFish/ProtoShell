#include "shell.h"

int dupandclose(int fd, int fdnew, int numargs, char* args[]) {
    if (fd < 0) {
        perror(NULL);
        exit(1); /*indicar um erro*/
    }
    dup2(fd, fdnew);
    close(fd);
    args[numargs - 2] = NULL;
    return (numargs - 2);
}

// redirects tratamento dos simbolos por ordem inversa: i) 2> ii) > OU >> iii) <
//should work? havent tested
int redirects(int argc, char *args[]) {

    // i tratar do redirect do 2>
    if (argc < 3) return argc; // Guard the following section

    if (strcmp(args[argc - 2], "2>") == 0) {
        int fd = creat(args[argc - 1], FILE_MODE);
        argc = dupandclose(fd, STDERR_FILENO, argc, args);
    }

    if (strcmp(args[argc - 2], ">") == 0) {
        int fd = creat(args[argc - 1], O_CREAT | O_WRONLY | FILE_MODE);
        argc = dupandclose(fd, STDOUT_FILENO, argc, args);
    }

    if (strcmp(args[argc - 2], ">>") == 0) {
        int fd = creat(args[argc - 1], O_CREAT | O_APPEND | FILE_MODE);
        argc = dupandclose(fd, STDOUT_FILENO, argc, args);
    }

    if (strcmp(args[argc - 2], "<") == 0) {
        int fd = creat(args[argc - 1], O_RDONLY | FILE_MODE);
        argc = dupandclose(fd, STDIN_FILENO, argc, args);
    }

    return argc; // devolver o numero de argumentos a passar para execvp
}