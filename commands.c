#include <stdio.h>
#include <unistd.h>

int shell_cd(char **args);
int shell_exit(char **args);

char *builtin_str[]={
    "cd",
    "exit"
};

int (*builtin_func[])(char **)={
    &shell_cd,
    &shell_exit
};

int shell_num_builtins(){
    return sizeof(builtin_str)/sizeof(char *);
}

int shell_cd(char **args)
{
    if(args[1]==NULL){
        fprintf(stderr, "shell: expected argument to \"cd\"\n");
    }else{
        if(chdir(args[1])!=0){
            perror("shell");
        }
    }
    return 1;
}
int shell_exit(char **args)
{
    return 0;
}
