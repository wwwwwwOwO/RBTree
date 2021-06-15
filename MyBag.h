#include "Bag.h"
enum COLOR
{
    RED,
    BLACK
};

class MyBag : public Bag {
    struct RBNode{
        int weight;//
        COLOR color;
        RBNode *left, *right, *father;
        T value;
        RBNode(COLOR c, T v, RBNode *l = NULL, RBNode *r = NULL, RBNode *f = NULL, int w = 1) : color(c), value(v), left(l), right(r), father(f), weight(w) {}
        void rRotate(RBNode* axis){
            if(axis){
                RBNode *pFather = axis->father;
                axis->left = right;
                if (right->right != right)
                    right->father = axis;
                right = axis;
                father = pFather;
                axis->father = this;
                if (pFather->left == axis)
                    pFather->left = this;
                else
                    pFather->right = this;    
            }
        }
        void lRotate(RBNode* axis){
            if(axis){
                RBNode *pFather = axis->father;
                axis->right = left;
                if (right->right != right)
                    left->father = axis;
                left = axis;
                father = pFather;
                axis->father = this;
                if (pFather->left == axis)
                    pFather->left = this;
                else
                    pFather->right = this;    
            }
        }
    };

private:
    RBNode *ROOT;
    RBNode *NIL;
    size_t SIZE;

    void insertRed(RBNode* newNode){
        RBNode *prev = newNode->father;
        if (prev->color == BLACK){
            if (prev == ROOT)
                newNode->color = BLACK;
            return;
        }
        RBNode *prevprev = prev->father;
        if(prevprev->left->color == RED && prevprev->right->color == RED){
            prevprev->left->color = BLACK;
            prevprev->right->color = BLACK;
            prevprev->color = RED;
            insertRed(prevprev);
        }
        else{
            if (prev == prevprev->left)
            {
                if (newNode == prev->left)
                {
                    prev->color = BLACK;
                    prev->rRotate(prevprev);                    
                }
                else
                {
                    newNode->color = BLACK;                   
                    newNode->lRotate(prev);
                    newNode->rRotate(prevprev);
                }
                
            }
            else
            {
                if (newNode == prev->right)
                {
                    prev->color = BLACK;
                    prev->lRotate(prevprev);                    
                }
                else
                {
                    newNode->color = BLACK;
                    newNode->rRotate(prev);
                    newNode->lRotate(prevprev);                    
                }
            }
            prevprev->color = RED;            
        }
        return;
    }

    void eraseBlack(RBNode* oldNode){
        RBNode *prev = oldNode->father;
        if(prev==ROOT)
            return;
        if (prev->left == oldNode){
            RBNode *pBrother = prev->right;
            if (pBrother->color == BLACK)
            {
                if (pBrother->right->color == RED)
                {
                    pBrother->right->color = BLACK;
                    pBrother->color = prev->color;
                    prev->color = BLACK;
                    pBrother->lRotate(prev);
                }
                else if (pBrother->left->color == RED)
                {
                    pBrother->left->color = prev->color;
                    prev->color = BLACK;
                    pBrother->left->rRotate(pBrother);
                    prev->right->lRotate(prev);
                }
                else
                {
                    if (prev->color == RED)
                    {
                        prev->color = BLACK;
                        pBrother->color = RED;
                    }
                    else
                    {
                        pBrother->color = RED;
                        eraseBlack(prev);
                    }
                }    
            }
            else
            {
                prev->color = RED;
                pBrother->color = BLACK;
                pBrother->lRotate(prev);
                eraseBlack(oldNode);
            }
        }
        else
        {
            RBNode *pBrother = prev->left;
            if (pBrother->color == BLACK ){
                if(pBrother->left->color == RED){
                    pBrother->left->color = BLACK;
                    pBrother->color = prev->color;
                    prev->color = BLACK;
                    pBrother->rRotate(prev);
                }
                else if (pBrother->right->color == RED)
                {
                    pBrother->right->color = prev->color;
                    prev->color = BLACK;
                    pBrother->right->lRotate(pBrother);
                    prev->left->rRotate(prev);
                }
                else
                {
                    if (prev->color == RED){
                        prev->color = BLACK;
                        pBrother->color=RED;
                    }
                    else
                    {
                        pBrother->color = RED;
                        eraseBlack(prev);
                    }    
                }    
            }
            else
            {
                prev->color = RED;
                pBrother->color = BLACK;
                pBrother->rRotate(prev);
                eraseBlack(oldNode);
            }            
        }
    }    

    void printNode(RBNode *p) const{
        if (p == NIL)
            return;
        printNode(p->left);
        for (int i = 0; i < p->weight; ++i)
            cout << p->value << " ";
        printNode(p->right);
    }

    void deleteNode(RBNode *p)
    {
        if (p == NIL)
            return;
        deleteNode(p->left);
        deleteNode(p->right);
        delete p;
        SIZE--;
    }

public:

    MyBag() : SIZE(0){
        NIL = new RBNode(BLACK, 0, NULL, NULL, NULL, 0);
        NIL->left = NIL;
        NIL->right = NIL;
        ROOT = new RBNode(BLACK, 0, NIL, NIL, NULL, 0);
        NIL->father = ROOT;
    }

    ~MyBag(){
        clear();
        delete ROOT;
        delete NIL;
    }

    size_t size() const { return SIZE; }

    bool empty() const { return SIZE == 0; }

    bool contains(const T &x) const{
        const RBNode *p = ROOT->right;
        while (p != NIL)
        {
            if (p->value == x)
                return true;
            if (p->value > x)
                p = p->left;
            else
                p = p->right;
        }
        return false;
    }

    void insert(const T &x){
        RBNode *p = ROOT->right;
        RBNode *prev = ROOT;
        while (p != NIL)
        {
            if (p->value == x){
                p->weight++;
                SIZE++;
                return;
            }
            prev = p;
            if (x < p->value)
                p = p->left;
            else
                p = p->right;
        }
        RBNode *newNode = new RBNode(RED, x, NIL, NIL, prev, 1);
        if (prev == ROOT || x > prev->value)
            prev->right = newNode;
        else
            prev->left = newNode;
        insertRed(newNode);
        SIZE++;
    }

    void erase(const T &x){
        RBNode *p = ROOT->right;
        while (p != NIL)
        {
            if (p->value == x){
                if (p->weight > 1)
                {
                    p->weight--;
                    SIZE--;
                    return;
                }
                break;
            }
            if (x < p->value)
                p = p->left;
            else
                p = p->right;
        }
        if (p != NIL)
        {
            RBNode *realp = p;
            if (p->left != NIL && p->right != NIL)
            {
                p = p->right;
                while (p->left != NIL)
                    p = p->left;
            }
            realp->value = p->value;
            realp->weight = p->weight;

            RBNode *prev = p->father;
            if (p->color == RED)
            {
                if (p == prev->left)
                    prev->left = NIL;
                else
                    prev->right = NIL;
            }
            else if (p->left != NIL || p->right != NIL){
                if (p == prev->left)
                {
                    if (p->left != NIL){
                        prev->left = p->left;
                        p->left->father = prev;
                    }
                    else{
                        prev->left = p->right;
                        p->right->father = prev;
                    }
                }
                else
                {
                    if (p->left != NIL){
                        prev->right = p->left;
                        p->left->father = prev;
                    }
                    else{
                        prev->right = p->right;
                        p->right->father = prev;
                    }
                }               
            }
            else
            {
                eraseBlack(p);
                if (prev->left == p)
                    prev->left = NIL;
                else
                    prev->right = NIL;
            }
            delete p;
            SIZE--;
            return;
        }                    
    }

    void display() const{
        printNode(ROOT->right);
    }

    T min() const{
        if (SIZE){
            RBNode *p = ROOT->right;
            RBNode *prev = ROOT;
            while (p != NIL)
            {
                prev = p;
                p = p->left;
            }
            return prev->value;
        }        
    }

    T max() const{
        if (SIZE){
            RBNode *p = ROOT->right;
            RBNode *prev = ROOT;
            while (p != NIL)
            {
                prev = p;
                p = p->right;
            }
            return prev->value;
        }        
    }
    
    void clear(){
        deleteNode(ROOT->right);
        ROOT->right = NIL;
    }
};
