#include "ft_ls.h"

t_data* sorted_list(t_data *first, t_data *element, unsigned char *flags) 
{
    if(element == NULL) 
        abort();

    if(first == NULL 
        || ((*flags & FLAG_t) == FLAG_t && first->mtime < element->mtime)
        || ((*flags & FLAG_t) != FLAG_t && strcmp(element->name, first->name) < 0))
    {
        element->next = first;
        return element;
    } 
    else 
    {
        t_data *cur = first;

        while ((cur->next != NULL && (*flags & FLAG_t) == FLAG_t && element->mtime < cur->next->mtime)
            || (cur->next != NULL && (*flags & FLAG_t) != FLAG_t && strcmp(element->name, cur->next->name) >= 0))
            cur = cur->next;
        
        element->next = cur->next;
        cur->next = element;
        return first;
    }
}

t_data* list_get_at(t_data *first, unsigned int position)
{
    t_data *current = first;
    unsigned int i = 0;

    while(i < position && current != NULL)
    {
        current = current->next;
        i++;
    }

    return current;
}

t_data* reverse_list(t_data* first)
{
    t_data *current = first;
    t_data *prev = NULL, *next = NULL;

    while(current != NULL)
    {
        next = current->next;
        current->next = prev;

        prev = current;
        current = next;
    }

    return prev;
}

void free_list(t_data* first)
{
    t_data* toDelete = first;
    while(toDelete != NULL)
    {
        first = toDelete->next;
        free(toDelete);
        
        toDelete = first;
    }
}