int shell_cd(char **args);
int shell_exit(char **args);


extern char *builtin_str[];




extern int (*builtin_func[])(char **);
int shell_num_builtins();

