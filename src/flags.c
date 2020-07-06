#include "ft_ls.h"

void get_flags(int argc, char **argv, unsigned char *flags, char *path)
{
    int cursor = 1;
    unsigned int flagCursor = 1;
    
    while(cursor < argc)
    {
        if(argv[cursor][0] == '-')
        {
            while(argv[cursor][flagCursor] != '\0')
            {
                if(argv[cursor][flagCursor] == 'l')
                    *flags = *flags | FLAG_l;
                else if(argv[cursor][flagCursor] == 'a')
                    *flags = *flags | FLAG_a;
                else if(argv[cursor][flagCursor] == 'R')
                    *flags = *flags | FLAG_R;
                else if(argv[cursor][flagCursor] == 'r')
                    *flags = *flags | FLAG_r;
                else if(argv[cursor][flagCursor] == 't')
                    *flags = *flags | FLAG_t;
                else
                {
                    printf("ft_ls: illegal option -- %c\n", argv[cursor][flagCursor]);
                    printf("usage: ls [-Ralrt] [file ...]\n");
                    exit(-1);
                }

                flagCursor++;
            }
            flagCursor = 1;
        }
        else 
        {
            strcpy(path, argv[cursor]);
            if(path[(strlen(path)-1)] != '/')
                strcat(path, "/");
            break;
        }

        cursor++;
    }

    if((path != NULL) && (path[0] == '\0'))
        strcpy(path, "./");
}