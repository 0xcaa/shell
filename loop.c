#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "commands.h"
#define SHELL_RL_SIZE 1024
#define SHELL_TOK_SIZE 64
#define SHELL_TOK_DELIM "\t\r\n\a"

char *shell_read_line(void);
char **shell_split_line(char *line);
int shell_launch(char **args);
int shell_execute(char **args);

void shell_loop(void)
{
    char *line;
    char **args;
    int status;
    
    do{
        printf("> ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);

        free(line);
        free(args);
    }while(status);

}

char *shell_read_line(void)
{

    char *line = NULL;
    ssize_t bufsize = 0;

    if(getline(&line, &bufsize, stdin)==-1){
        if(feof(stdin))
            exit(EXIT_SUCCESS);
        }else {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    return line;

    
    /*
    int bufsize = SHELL_RL_SIZE;
    int position = 0, c;
    char *buffer = malloc(sizeof(char)*bufsize);

    if(!buffer){
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        c = gerchar();

        if(c==EOF||c=='\n'){
            buffer[position] = '\0';
            return buffer;
        }else{
            buffer[position] = c;
        }
        position++;

        if(position >= bufsize){
            bufsize += SHELL_RL_SIZE;
            buffer = realloc(buffer, bufsize);
            if(!buffer){
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    */
}

char **shell_split_line(char *line)
{
    int bufsize = SHELL_TOK_SIZE, position = 0;
    char **tokens = malloc(bufsize*sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SHELL_TOK_DELIM);
    while(token!=NULL){
        tokens[position] = token;
        position++;

        if(position >=bufsize){
            bufsize += SHELL_TOK_SIZE;
            tokens = realloc(tokens, bufsize*sizeof(char*));
            if(!tokens){
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, SHELL_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int shell_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid == 0){
        if(execvp(args[0], args) ==-1){
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }else if(pid<0){
        perror("shell");
    }else{
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
        }while(!WIFEXITED(status)&&!WIFSIGNALED(status));
    }

    return 1;
}

int shell_execute(char **args)
{
    int i;

    if(args[0] == NULL){
        return 1;
    }

    for(i=0;i<shell_num_builtins();i++){
        if(strcmp(args[0], builtin_str[i])==0){
            return (*builtin_func[i])(args);
        }
    }

    return shell_launch(args);
}

