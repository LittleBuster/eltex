#ifndef AVLTREE_H_
#define AVLTREE_H_


struct AVLNode {
    int key;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
};


unsigned char Height(struct AVLNode* p);

int Bfactor(struct AVLNode* p);

void Fixheight(struct AVLNode* p);

struct AVLNode* RotateRightAVL(struct AVLNode* p);

struct AVLNode* RotateLeftAVL(struct AVLNode* q);

struct AVLNode* Balance(struct AVLNode* p);

struct AVLNode* Insert(struct AVLNode* p, int k);

struct AVLNode* FindMin(struct AVLNode* p);

struct AVLNode* RemoveMin(struct AVLNode* p);

struct AVLNode* remove(struct AVLNode* p, int k);


#endif
