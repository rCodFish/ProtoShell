#include "shell.h"

//concatenates the files content into another file
//the dup calls are to redirect STDIN and STDOUT temporarily to the fd (both the STD's were to the terminal needing redirection to the file for a moment)
int cat(char* fileName) {
    char* args[] = {"cat",fileName,"-n", NULL };

    int fd = open(fileName, O_RDONLY);
    if (fd < 0) { perror("open error"); return (1); }

    //dup2 is just a dup and close STDIN_FILENO
    //kinda like redirects the STDIN to the fd and closes it in the process (the STDIN)
    dup2(fd, STDIN_FILENO);
    close(fd);

    //creat the output file
    fd = creat("output.txt", FILE_MODE);
    if (fd < 0) { perror("creat error"); return (1); }

    //do the same shenanigans as above
    //redirect the STDOUT to fd and close it
    dup2(fd, STDOUT_FILENO);    //<----erro
    close(fd);

    //all that just to call the OS funtion 
    execvp("cat", args);    
    return(0);
}