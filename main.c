#include "shell.h"

char prompt[100];

int main() {
  int len;
  char linha[1024]; /* um comando */
  char* args[64];   /*just an array with pointers to char arrays(the arguments) com um maximo de 64 argumentos */

  //set prompt
  strcpy(prompt, "SOSHELL$prompt>");

  while (1) {
    printf("%s", prompt);

    //read stdin (1023 because of the termination char \0, i think?)
    if (fgets(linha, 1023, stdin) == NULL) {
      printf("\n");
      exit(0);
    }

    len = strlen(linha);
    if (1 == len)
      continue; /* linha é apenas \n */

    //if the end is a newline change it for a termination char \0
    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';

    //parse explained in the .c file, just returns the num of args found and sets the args array with pointers to each arg
    int numArgs = parse(linha, args); /* particiona a string em argumentos */

    //args is just args[0], its the same mem location(syntax suggar ofc)
    //if there is a builtin arg available do that, otherwise call execute(just a function to execute the actual command on the OS i believe)
    if (!builtin(args)) {
      execute(numArgs, args); /* executa o comando */
    }
  }
  //bye bye
  return 0;
}

//builtin commands (come from pratical classes and whatnot innit)
int builtin(char** args) {
  /* Toda a funcionalidade embutida deverá devolver 1*/

  //leave the shell
  if (strcmp(args[0], "sair") == 0) {
    exit(0);
    return 1; /* funcionalidade embutida */
  }

  //funny reference to giant head
  if (strncmp(args[0], "42", 2) == 0) {
    printf("42 is the answer to life the universe and everything\n");
    printf("https://pt.wikipedia.org/wiki/The_Hitchhiker's_Guide_to_the_Galaxy\n");
    return 1; /* funcionalidade embutida */
  }

  //basic info ig
  if (strcmp(args[0], "obterinfo") == 0) {
    printf("SoShell 2024 Version 1.0\n");
    return 1;
  }

  //bunch of logic just to set the prompt differently
  //if first arg is bigger than 4 && shorter than 102 && equal to PS1= set the prompt from what comes next
  //102 comes from the 2 addicional chars, whitespace and the \0 (100 + 2 = 102) Calc 3 level math trust me \O~O/
  if (strlen(args[0]) > 4 && strlen(args[0]) < 102 && strncmp(args[0], "PS1=", 4) == 0) {
    strcpy(prompt, args[0] + 4); //increment 4 to jump the PS1=
    prompt[strlen(args[0] + 4)] = ' '; //add the whitespace
    prompt[strlen(args[0] + 4) + 1] = '\0'; //add the termination char
    return 1;
  }

  //batman
  if (0 == strcmp(args[0], "quemsoueu")) {
    system("id");
    return 1; // comando embutido
  }

  //just a cd 
  if (0 == strcmp(args[0], "cd")) {
    int err;

    //if second arg is or NULL or ~ or $HOME change to Home dir ("HOME")
    if (NULL == args[1] || (strcmp(args[1], "~") == 0 || strcmp(args[1], "$HOME") == 0)) {
      err = chdir(getenv("HOME"));
    }
    else {
      //else just change it to whatever it is in the arg
      err = chdir(args[1]);
    }

    //if chdir returned <0 it got an error somewhere so perror the path inputed
    if (err < 0) {
      perror(args[1]);
    }
    return 1; // comando embutido
  }

  //command to copy a file contents to another file depending on the destination
  //if set try there, if not spawn a new output file
  if (0 == strcmp(args[0], "socp")) {
    //if either source or destination are NULL complain to the user
    if (args[1] == NULL || args[2] == NULL) {
      printf("Usage: socp <source> <destination>\n");
      return 1;
    }
    else {
      //the actual function call (with paths turned around because who cares of readability right?)
      socp(args[2], args[1]);
    }
    return 1; //comando embutido
  }

  //ooh big scary math :O
  if (0 == strcmp(args[0], "calc")) {
    //if either a or operation or b are NULL complain 
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
      printf("Usage: calc <value a> <operator> <value b>\n");
      return 1;
    }
    //calc just does a calculation based on operation and first and second values
    calc(args[1], args[2], args[3]);
    return 1; //comando embutido
  }

  //i do enjoy cat bulldozers yes
  //command to concatenate 
  if (strcmp(args[0], "cat") == 0) {
    printf("%s\n", args[1]);
    if (args[1] == NULL) {
      printf("Usage: cat <file>\n");
      return 1;
    }
    cat(args[1]);
    return 1; //comando embutido
  }

  if (strcmp(args[0], "avisoTeste") == 0) {
    if (args[1] == NULL) {
      printf("Usage: avisoTeste <mensagem> <tempo>\n");
      return 1;
    }
    aviso(args[1], atoi(args[2]));
    return 1; //comando embutido
  }

  if (strcmp(args[0], "aviso") == 0) {
    pthread_t th;
    aviso_t* ptr = (aviso_t*)malloc(sizeof(aviso_t));
    strcpy(ptr->msg, args[1]);
    ptr->tempo = atoi(args[2]);
    pthread_create(&th, NULL, avisowrapper, (void*)ptr);
    return 1;
  }


  /* IMPORTANTE :
   Devolver 0 para indicar que não existe comando embutido e que
   será executado usando exec() na função execute.c
  */
  return 0;
}
