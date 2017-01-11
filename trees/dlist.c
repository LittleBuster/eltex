#include "dlist.h"
#include <string.h>


static inline struct dlist *DlistRemoveLink(struct Dlist *list, struct Dlist *link)
{
    if (link == NULL)
        return list;

    if (link->prev) {
        if (link->prev->next == link)
            link->prev->next = link->next;
        else
            puts("Corrupted double-linked list");
    }

    if (link->next) {
        if (link->next->prev == link)
            link->next->prev = link->prev;
        else
            puts("Corrupted double-linked list");
    }

    if (link == list)
        list = list->next;

    link->next = NULL;
    link->prev = NULL;

    return list;
}

struct Dlist *DlistAppend(struct Dlist *list, void *data)
{
    struct Dlist *new_list;
    struct Dlist *last;

    new_list = (struct Dlist *)malloc(sizeof(new_list));
    new_list->data = data;
    new_list->next = NULL;

    if (list) {
        last = DlistLast(list);
        last->next = new_list;
        new_list->prev = last;
        return list;
    } else {
        new_list->prev = NULL;
        return new_list;
    }
}

struct Dlist *DlistPrepend(struct Dlist *list, void *data)
{
    struct Dlist *new_list;

    new_list = (struct Dlist *)malloc(sizeof(new_list));
    new_list->data = data;
    new_list->next = list;

    if (list) {
        new_list->prev = list->prev;
        if (list->prev)
            list->prev->next = new_list;
        list->prev = new_list;
    } else
        new_list->prev = NULL;
    return new_list;
}

size_t DlistLen(struct Dlist *restrict list)
{
    size_t len = 0;

    while (list) {
        len++;
        list = list->next;
    }
    return len;
}

struct Dlist *DlistNth(struct Dlist *list, size_t n)
{
    while ((n-- > 0) && list)
        list = list->next;
    return list;
}

void *DlistNthData(struct Dlist *list, size_t n)
{
    while ((n-- > 0) && list)
        list = list->next;
    return list ? list->data : NULL;
}

struct Dlist *DlistFirst(struct Dlist *restrict list)
{
    if (list)
        while (list->prev)
            list = list->prev;
    return list;
}

struct Dlist *DlistLast(struct Dlist *restrict list)
{
    if (list)
        while (list->next)
            list = list->next;
    return list;
}

struct Dlist *DlistRemove(struct Dlist *list, const void *data)
{
    struct Dlist *tmp;

    tmp = list;
    while (list)
        if (tmp->data != data)
            tmp = tmp->next;
        else {
            list = DlistRemoveLink(list, tmp);
            free(tmp);
            break;
        }
    return list;
}

void DlistFreeAll(struct Dlist *list)
{
    struct Dlist *tmp;

    if (!list)
        return;

    while (list) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
    free(list);
}

void DlistFree(struct Dlist *list)
{
    free(list);
}
