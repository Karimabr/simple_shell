#ifndef XYSHELL_H
#define XYSHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>

/*constants*/
#define EXTL_CMD 1
#define INTL_CMD 2
#define PTH_CMD 3
#define INVLD_CMD -1

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 *struct map - Structure to map a command name to a function
 *@cmd_name: Command's name
 *@funcy: the function that executes the command
 */

typedef struct map
{
	char *cmd_name;
	void (*funcy)(char **cmd);
} function_map;

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

/*xymakers*/
void print(char *, int);
char **tokenizer(char *, char *);
void remove_newline(char *);
int _strlen(char *);
void _strcpy(char *, char *);

/*xymakers2*/
int _strcmp(char *, char *);
char *_strcat(char *, char *);
int _strspn(char *, char *);
int _strcspn(char *, char *);
char *_strchr(char *, char);

/*xymakers3*/
char *_strtok_r(char *, char *, char **);
int _atoi(char *);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void ctrl_c_handler(int);
void remove_comment(char *);

/*utils*/
int parse_command(char *);
void execute_command(char **, int);
char *check_path(char *);
void (*get_func(char *))(char **);
char *_getenv(char *);

/*built_in*/
void env(char **);
void quit(char **);

/*main*/
extern void xy_function(void);
extern void initializer(char **current_command, int type_command);

#endif /*XYSHELL_H*/

