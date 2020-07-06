#include "ft_ls.h"

int main(int argc, char *argv[])
{
    unsigned char flags = 0b00000000;
    char path[UNIX_MAX_PATH];
    path[0] = '\0';

    get_flags(argc, argv, &flags, path);
    read_dir(path, &flags);

    return 0;
}