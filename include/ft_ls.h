#ifndef FT_LS_H
#define FT_LS_H

/*
**	INCLUDES
*/
#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

/*
**	FLAGS
*/
#define FLAG_l 0b10000000
#define FLAG_R 0b01000000
#define FLAG_a 0b00100000
#define FLAG_r 0b00010000
#define FLAG_t 0b00001000

#define UNIX_MAX_PATH 4096
#define UNIX_MAX_FILE_NAME 255

/*
**	STRUCTURES
*/
typedef struct s_data
{
	char			name[256];
	char			mode[11];
	nlink_t			nlink;
	char*			uid;
	char*			gid;
	off_t			size;
	time_t			mtime;

	struct s_data*	next;
} t_data;

/*
**	flags functions
*/
void get_flags(int argc, char **argv, unsigned char *flags, char* path);

/*
**	print functions
*/
void print_columns(t_data *head, unsigned int *columns, unsigned int *rows, int *padding);
void print_inline(t_data *head, int *padding);
void print_long_format(t_data *head);
void print(t_data *head, unsigned char *flags, unsigned int *slonger, unsigned int *ltotal);

/*
**	dir functions
*/
void read_long_format(t_data *data, char* path);
void read_time(t_data *data, char *path);
void read_recursively(t_data *data, char *path);

void read_dir_recursively(char *path, t_data *head, unsigned char *flags);
void read_dir(char *path, unsigned char *flags);

/*
**	list functions
*/
t_data* sorted_list(t_data *first, t_data *element, unsigned char *flags);
t_data* list_get_at(t_data *first, unsigned int position);
t_data* reverse_list(t_data *first);
void free_list(t_data *first);

#endif