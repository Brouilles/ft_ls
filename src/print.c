#include "ft_ls.h"

void print_columns(t_data *head, unsigned int *columns, unsigned int *rows, int *padding)
{
    unsigned int i = 0;
    unsigned int j = 0;

    t_data *current;
    current = head;

    while(current != NULL) 
    {
        while(j <= *columns)
        {
            t_data *tempElement = list_get_at(head, i + *rows * j);

            if(tempElement != NULL)
                printf("%*s", *padding, tempElement->name);

            j++;
        }

        printf("\n");
        current = current->next;

        if(i == *rows - 1)
            break;

        j = 0;
        i++;
    }
}

void print_inline(t_data *head, int *padding)
{
    t_data *current;
    current = head;

    while(current != NULL)
    {
        printf("%*s", *padding, current->name);
        current = current->next;
    }
    printf("\n");
}

void print_long_format(t_data *head)
{
    t_data *current;
    current = head;

    while(current != NULL)
    {
        struct tm* timeinfo;
        char tempBuffer[26];

        timeinfo = localtime(&current->mtime);
        strftime(tempBuffer, 26, "%d %B %H:%M", timeinfo);

        printf("%s  %d %s  %s    %lld  %s %s\n", current->mode, current->nlink, current->uid, current->gid, current->size, tempBuffer, current->name);
        
        current = current->next;
    }
}

void print(t_data *head, unsigned char *flags, unsigned int *slonger, unsigned int *ltotal)
{
    if((*flags & FLAG_r) == FLAG_r)
        head = reverse_list(head);
    
    if((*flags & FLAG_l) == FLAG_l)
        print_long_format(head);
    else 
    {
        int padding = -(*slonger + 4);

        // Terminal size
        struct winsize terminalSize;
        ioctl(0, TIOCGWINSZ, &terminalSize);

        unsigned int columns = terminalSize.ws_col / (padding == 0 ? 1 : -padding);
        unsigned int rows = *ltotal / (columns == 0 ? 1 : columns);

        if(*ltotal * -padding <= terminalSize.ws_col)
            print_inline(head, &padding);
        else
            print_columns(head, &columns, &rows, &padding);
    }
}