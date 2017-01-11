#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <stdio.h>


struct Dlist {
    /* user's data */
    void *data;

    /* next element */
    struct Dlist *next;

    /* prev. element */
    struct Dlist *prev;
};

/**
 * Add new element in end of list
 * @list: double-linked list struct
 * @data: user's data
 *
 * returns double-linked list with added element
 */
struct Dlist *DlistAppend(struct Dlist *list, void *data);

/**
 * Add new element in start of list
 * @list: double-linked list struct
 * @data: user's data
 *
 * returns double-linked list with added element
 */
struct Dlist *DlistPrepend(struct Dlist *list, void *data);

/*
 * Get size of list
 */
size_t DlistLen(struct Dlist *restrict list);

/**
 * Get element from list by number
 * @list: double-linked list
 * @n: number of element
 *
 * returns double-list structure
 */
struct Dlist *DlistNth(struct Dlist *list, size_t n);

/**
 * Get user data from list by number
 * @list: double-linked list
 * @n: number of element
 *
 * returns user data
 */
void *DlistNthData(struct Dlist *list, size_t n);

/*
 * Get first element of list
 */
struct Dlist *DlistFirst(struct Dlist *restrict list);

/*
 * Get last element from list
 */
struct Dlist *DlistLast(struct Dlist *restrict list);

/**
 * Remove element from list by data
 * @list: double-linked list
 * @data: user data
 *
 * returns double-linked list without element
 */
struct Dlist *DlistRemove(struct Dlist *list, const void *data);

/*
 * Free list elements
 */
void DlistFreeAll(struct Dlist *list);

/*
 * Free memory
 */
void DlistFree(struct Dlist *list);


#endif
