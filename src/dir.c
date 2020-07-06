#include "ft_ls.h"

void read_long_format(t_data* data, char* path)
{
    // Permission
    struct stat fileStat;

    char str[4096]; // unix max path characters
    str[0] = '\0';
    strcpy(str, (strcmp(path, ".") == 0 ? "./" : path));
    strcat(str, data->name);

    stat(str, &fileStat);   

    char tempMode[11];
    tempMode[0] = ((S_ISDIR(fileStat.st_mode)) ? 'd' : '-');
    tempMode[1] = ((fileStat.st_mode & S_IRUSR) ? 'r' : '-');
    tempMode[2] = ((fileStat.st_mode & S_IWUSR) ? 'w' : '-');
    tempMode[3] = ((fileStat.st_mode & S_IXUSR) ? 'x' : '-');
    tempMode[4] = ((fileStat.st_mode & S_IRGRP) ? 'r' : '-');
    tempMode[5] = ((fileStat.st_mode & S_IWGRP) ? 'w' : '-');
    tempMode[6] = ((fileStat.st_mode & S_IXGRP) ? 'x' : '-');
    tempMode[7] = ((fileStat.st_mode & S_IROTH) ? 'r' : '-');
    tempMode[8] = ((fileStat.st_mode & S_IWOTH) ? 'w' : '-');
    tempMode[9] = ((fileStat.st_mode & S_IXOTH) ? 'x' : '-');
    tempMode[10] = '\0';

    strcpy(data->mode, tempMode);

    // Link
    data->nlink = fileStat.st_nlink;

    // Owner name
    struct passwd *pw = getpwuid(fileStat.st_uid);
    if(pw != NULL) 
        data->uid = pw->pw_name;
    else
        data->uid = "NULL";

    // Group
    struct group  *gr = getgrgid(fileStat.st_gid);
    data->gid = gr->gr_name;

    // Size
    data->size = fileStat.st_size;

    // Modification time
    data->mtime = fileStat.st_mtime;
}

void read_time(t_data* data, char* path)
{
    // Permission
    struct stat fileStat;

    char str[UNIX_MAX_PATH]; // unix max path characters
    strcpy(str, (strcmp(path, ".") == 0  ? "./" : path));
    strcat(str, data->name);

    stat(str, &fileStat); 

    // Modification time
    data->mtime = fileStat.st_mtime;
}

void read_recursively(t_data* data, char* path)
{
    // Permission
    struct stat fileStat;

    char str[UNIX_MAX_PATH]; // unix max path characters
    strcpy(str, (strcmp(path, ".") == 0 ? "./" : path));
    strcat(str, data->name);

    stat(str, &fileStat); 

    char tempMode[2];
    tempMode[0] = ((S_ISDIR(fileStat.st_mode)) ? 'd' : '-');
    tempMode[1] = '\0';

    strcpy(data->mode, tempMode);
}

void read_dir_recursively(char *path, t_data *head, unsigned char *flags)
{
    t_data *current = head;
        
    while(current != NULL)
    {
        if(current->mode[0] == 'd' && strcmp(current->name, ".") != 0 && strcmp(current->name, "..") != 0)
        {
            printf("\n%s%s:\n", path, current->name);

            char str[UNIX_MAX_FILE_NAME];
            str[0] = '\0';
            strcpy(str, path);

            strcat(str, current->name);
            strcat(str, "/");
            read_dir(str, flags);
        }

        current = current->next;
    }
}

void read_dir(char* path, unsigned char *flags)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);

    t_data *head = NULL;
    unsigned int slonger = 0;
    unsigned int ltotal = 0;

    // Read
    if(d) 
    {
        while((dir = readdir(d)) != NULL) 
        {
            if(dir->d_type == DT_REG || dir->d_type == DT_DIR)
            {
                if((((*flags & FLAG_a) == FLAG_a) 
                    && (dir->d_name[0] == '.'))
                    || (dir->d_name[0] != '.'))
                {
                    t_data *element = malloc(sizeof(*element));
                    strcpy(element->name, dir->d_name);
                    element->next = NULL;
                    
                    if((*flags & FLAG_l) == FLAG_l)
                        read_long_format(element, path);
                    else if((*flags & FLAG_R) == FLAG_R)
                        read_recursively(element, path);
                    else if((*flags & FLAG_t) == FLAG_t)
                        read_time(element, path);

                    ltotal++;
                    if(slonger < strlen(element->name))
                        slonger = strlen(element->name);
                    
                    head = sorted_list(head, element, flags);
                }
            }
        }

        closedir(d);
    }
    else
    {
        printf("ls: %s: No such file or directory\n", path);
        exit(-1);
    }

    // Print
    print(head, flags, &slonger, &ltotal);

    // Recursive
    if((*flags & FLAG_R) == FLAG_R) 
        read_dir_recursively(path, head, flags);

    // Clean
    free_list(head);
}