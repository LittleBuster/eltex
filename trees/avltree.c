#include "avltree.h"


unsigned char Height(struct AVLNode *p)
{
    return p?p->height:0;
}

int Bfactor(struct AVLNode* p)
{
    return Height(p->right)-Height(p->left);
}

void Fixheight(struct AVLNode* p)
{
    unsigned char hl = Height(p->left);
    unsigned char hr = Height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

struct AVLNode* RotateRightAVL(struct AVLNode* p)
{
    struct AVLNode* q = p->left;
    p->left = q->right;
    q->right = p;
    Fixheight(p);
    Fixheight(q);
    return q;
}

struct AVLNode* RotateLeftAVL(struct AVLNode* q)
{
    struct AVLNode* p = q->right;
    q->right = p->left;
    p->left = q;
    Fixheight(q);
    Fixheight(p);
    return p;
}

struct AVLNode* Balance(struct AVLNode* p)
{
    Fixheight(p);
    if( Bfactor(p)==2 )
    {
        if( Bfactor(p->right) < 0 )
            p->right = RotateRightAVL(p->right);
        return RotateLeftAVL(p);
    }
    if( Bfactor(p)==-2 )
    {
        if( Bfactor(p->left) > 0  )
            p->left = RotateLeftAVL(p->left);
        return RotateRightAVL(p);
    }
    return p;
}

struct AVLNode* Insert(struct AVLNode* p, int k)
{
    if( !p ) {
        struct AVLNode *new_node = (struct AVLNode *)malloc(sizeof(new_node));
        new_node->key = k;
        return new_node;
    }
    if( k<p->key )
        p->left = Insert(p->left,k);
    else
        p->right = Insert(p->right,k);
    return Balance(p);
}

struct AVLNode* FindMin(struct AVLNode* p)
{
    return p->left ? FindMin(p->left):p;
}

struct AVLNode* RemoveMin(struct AVLNode* p)
{
    if(p->left == 0)
        return p->right;
    p->left = RemoveMin(p->left);
    return Balance(p);
}

struct AVLNode* remove(struct AVLNode* p, int k)
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = remove(p->left,k);
    else if( k > p->key )
        p->right = remove(p->right,k);
    else {
        struct AVLNode* q = p->left;
        struct AVLNode* r = p->right;
        free(p);
        if( !r )
            return q;

        struct AVLNode* min = FindMin(r);
        min->right = RemoveMin(r);
        min->left = q;
        return Balance(min);
    }
    return Balance(p);
}
