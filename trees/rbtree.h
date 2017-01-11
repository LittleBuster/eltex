#ifndef RBTREE_H_
#define RBTREE_H_

#include <stdio.h>
#include <stdlib.h>


enum NodeColor {
    CLR_BLACK,
    CLR_RED
};


struct Node {
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int color;
    void *data;
} Node;


void RotateLeft(struct Node *x);

void RotateRight(struct Node *x);

void InsertFixup(struct Node *x);

struct Node *InsertNode(void *data);

void DeleteFixup(struct Node *x);

void DeleteNode(struct Node *z);

struct Node *FindNode(void *data);


#endif
