#include "rbtree.h"


#define CompLT(a,b) (a < b)
#define CompEQ(a,b) (a == b)

struct Node *root = NULL;


void RotateLeft(struct Node *x)
{
    struct Node *y = x->right;

    x->right = y->left;
    if (y->left->color != CLR_BLACK && y->left->data != NULL)
        y->left->parent = x;

    if (y->color != CLR_BLACK && y->data != NULL)
        y->parent = x->parent;

    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        root = y;
    }

    y->left = x;
    if (x != NULL)
        x->parent = y;
}

void RotateRight(struct Node *x)
{
    struct Node *y = x->left;

    x->left = y->right;
    if (y->right->color != CLR_BLACK && y->right->data != NULL)
        y->right->parent = x;

    if (y->right->color != CLR_BLACK && y->right->data != NULL)
        y->parent = x->parent;

    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        root = y;
    }

    y->right = x;
    if (x->color != CLR_BLACK && x->data != NULL)
        x->parent = y;
}

void InsertFixup(struct Node *x)
{
    while (x != root && x->parent->color == CLR_RED) {
        if (x->parent == x->parent->parent->left) {
            struct Node *y = x->parent->parent->right;
            if (y->color == CLR_RED) {
                x->parent->color = CLR_BLACK;
                y->color = CLR_BLACK;
                x->parent->parent->color = CLR_RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    RotateLeftAVL(x);
                }
                x->parent->color = CLR_BLACK;
                x->parent->parent->color = CLR_RED;
                RotateRightAVL(x->parent->parent);
            }
        } else {
            struct Node *y = x->parent->parent->left;
            if (y->color == CLR_RED) {
                x->parent->color = CLR_BLACK;
                y->color = CLR_BLACK;
                x->parent->parent->color = CLR_RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    RotateRightAVL(x);
                }
                x->parent->color = CLR_BLACK;
                x->parent->parent->color = CLR_RED;
                RotateLeftAVL(x->parent->parent);
            }
        }
    }
    root->color = CLR_BLACK;
}

struct Node *InsertNode(void *data)
{
    struct Node *current, *parent, *x;

    current = root;
    parent = 0;
    while (current->color != CLR_BLACK && current->data != NULL) {
        if (CompEQ(data, current->data))
            return (current);
        parent = current;
        current = CompLT(data, current->data) ?
            current->left : current->right;
    }

    if ((x = (struct Node *)malloc (sizeof(struct Node))) == 0) {
        printf ("insufficient memory (insertNode)\n");
        exit(1);
    }
    x->data = data;
    x->parent = parent;
    x->left = NULL;
    x->right = NULL;
    x->color = CLR_RED;

     if(parent) {
        if(CompLT(data, parent->data))
            parent->left = x;
        else
            parent->right = x;
    } else {
        root = x;
    }

    InsertFixup(x);
    return(x);
}

void DeleteFixup(struct Node *x)
{
    while (x != root && x->color == CLR_BLACK) {
        if (x == x->parent->left) {
            struct Node *w = x->parent->right;

            if (w->color == CLR_RED) {
                w->color = CLR_BLACK;
                x->parent->color = CLR_RED;
                RotateLeftAVL(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == CLR_BLACK && w->right->color == CLR_BLACK) {
                w->color = CLR_RED;
                x = x->parent;
            } else {
                if (w->right->color == CLR_BLACK) {
                    w->left->color = CLR_BLACK;
                    w->color = CLR_RED;
                    RotateRightAVL(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = CLR_BLACK;
                w->right->color = CLR_BLACK;
                RotateLeftAVL(x->parent);
                x = root;
            }
        } else {
           struct  Node *w = x->parent->left;
            if (w->color == CLR_RED) {
                w->color = CLR_BLACK;
                x->parent->color = CLR_RED;
                RotateRightAVL(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == CLR_BLACK && w->left->color == CLR_BLACK) {
                w->color = CLR_RED;
                x = x->parent;
            } else {
                if (w->left->color == CLR_BLACK) {
                    w->right->color = CLR_BLACK;
                    w->color = CLR_RED;
                    RotateLeftAVL(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = CLR_BLACK;
                w->left->color = CLR_BLACK;
                RotateRightAVL(x->parent);
                x = root;
            }
        }
    }
    x->color = CLR_BLACK;
}

void DeleteNode(struct Node *z)
{
    struct Node *x, *y;

    if (!z || (z->color != CLR_BLACK && z->data != NULL))
        return;

    if ( (z->left->color == CLR_BLACK && z->left->data == NULL) || (z->right->color != CLR_BLACK && z->right->data != NULL)) {
        y = z;
    } else {
        y = z->right;
        while (y->left->color != CLR_BLACK && y->left->data != NULL)
            y = y->left;
    }

    if (y->left->color != CLR_BLACK && y->left->data != NULL)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        root = x;

    if (y != z)
        z->data = y->data;

    if (y->color == CLR_BLACK)
        DeleteFixup(x);
    free (y);
}

struct Node *FindNode(void *data)
{
    struct Node *current = root;

    while(current->color != CLR_BLACK && current->data != NULL)
        if(CompEQ(data, current->data))
            return (current);
        else
            current = CompLT (data, current->data) ?
                current->left : current->right;
    return NULL;
}
