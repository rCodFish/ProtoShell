/*
   execute . cria um processo prog�nito e executa um programa
*/
#include "shell.h"

int ultimo(int* numargs, char** args);

//are forks really needed man
//funtion to execute unknown builtin commands using the OS
void execute(int numargs, char** args) {
  int pid, status;

  //ultimo is to check whether the last char is &
  //it then sets the command to run either on the background or the foreground ence the fork
  int code = ultimo(&numargs, args);

  if ((pid = fork()) < 0) { /* cria um processo progenito */
    perror("forks");/* NOTE: perror() produz uma pequema mensagem de erro para o stream */
    exit(1);/* estandardizado de erros que descreve o ultimo erro encontrado */
    /* durante uma chamada ao sistema ou funcao duma biblioteca */
  }

  // (pid = 0) = child
  if (pid == 0) {

    //tratar dos > < >> 2>
    //dont actually know if it works but hey we ball
    int nArgs = redirects(numargs, args);

    //if redirects -1 error
    if (nArgs == -1) {
      exit(1);
    }

    /* NOTE: as versoes execv() e execvp() de execl() sao uteis
    quando o numero de argumentos nao e conhecido.
    Os argumentos de execv() e execvp() sao o nome do ficheiro
    a ser executado e um vector de strings que contem os argumentos.
    Faltava mais frase aqui mas n sei onde foi parar. RIP*/

    //run the actual command on the OS
    execvp(*args, args);
    perror(*args);
    exit(1);
  }

  //well if its on the foreground keep the father running in the loop, if not just let it continue 
  //basically only let the father end if the child ends (in the case of FG)
  if (FG == code) {
    while (wait(&status) != pid)
      /*spin fazer nada */;
  }

  return;
}

int ultimo(int* numargs, char** args) {

  if (args[*numargs - 1][0] == '&') {

    *numargs = *numargs - 1;
    args[*numargs] = NULL;

    return BG;
  }

  return FG;
}