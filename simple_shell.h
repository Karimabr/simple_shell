#ifndef _SIMPLE_SHELL_H
#define _SIMPLE_SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
/**
 * struct ls_t - struct type defining a linked list
 * @drc: A directory path
 * @next: A pointer to another struct list_t
 */
typedef struct list_t
{
	char *drc;
	struct list_t *next;
} ls_t;
char **copy_environ(void);
void _freeenviron(void);
char **get_env(const char *variable);
int _crterr(char **arg, int error);
char *_err_env(char **arg);
char *_err1(char **arg);
char *_errorexit(char **arg);
char *_errorcd(char **arg);
char *_errorsyn(char **arg);
char *err_3(char **arg);
char *err_4(char **arg);
/**
 * struct alias_a - struct defining aliases
 * @value: name of the alias
 * @name: value of the alias
 * @next: pointer to another struct alias_n
 */
typedef struct alias_a
{
	char *value;
	char *name;
	struct alias_a *next;
} alias_n;
extern char **envron;
char *nm;
int hst;
alias_n *aliases;

char *_getenval_(char *start, int length);
ssize_t _getline(char **lnpointr, size_t *num, FILE *strm);
void *_realloc_(void *p, unsigned int old_s, unsigned int size_new);
char **_strtok_(char *input, char *separator);
char *_getlocal(char *cmd);
ls_t *_path_drc(char *p);
void _freethelist(ls_t *hd);
char *_atoi(int number);
void _handline(char **str, ssize_t rd);
void _var_rep(char **arg, int *exert);
char *_getarg(char *ln, int *exert);
int _callarg(char **arg, char **fnt, int *exert);
int _exearg(char **arg, char **fnt, int *exert);
int _handleargmnt(int *exert);
int _checkonarg(char **arg);
void _freearg(char **arg, char **fnt);
char **_switchaliases(char **arg);
int _numlength(int number);
char *_getpid_(void);
/**
 * struct build_s - struct type defining builtin commands.
 * @nm: name of the builtin command.
 * @f: function pointer to the build command's function.
 */
typedef struct build_s
{
	char *nm;
	int (*f)(char **argv, char **fnt);
} build_t;
int str_length(const char *str);
char *stringconcat(char *dst, const char *source);
char *strnconcat(char *dst, const char *source, size_t num);
char *stringcopy(char *dst, const char *source);
char *stringchr(char *str, char chars);
int stringspn(char *str, char *take);
int strcompare(char *str, char *str1);
int strncompare(const char *str, const char *str1, size_t num);
char *_pathfilled(char *pt);
int (*_getbuilt(char *comnd))(char **arg, char **fnt);
int _shellexit(char **arg, char **fnt);
int _shellenv(char **arg, char **fnt);
int _shellsetenv(char **arg, char **fnt);
int _shellunsetenv(char **arg, char **fnt);
int _shellcd(char **arg, char **fnt);
int _shellalias(char **arg, char **fnt);
alias_n *_addaliasfin(alias_n **hd, char *nm, char *val);
void _freealiasfin(alias_n *hd);
ls_t *_addnodefin(ls_t **hd, char *drc);
void seg_fault(char a);
ssize_t _getnew_str(char *string);
void _operators(char *str, ssize_t *nlength);

void lnptr_assignment(char **linep, size_t *num, char *buf, size_t size);
void aliassetting(char *variable, char *value);
void aliasprinted(alias_n *als);
int file_cmnds(char *fpath, int *exert);
#endif
