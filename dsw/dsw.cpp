#include <iostream>
using namespace std;


struct node
{
    int key;
    node* left;
    node* right;
    node* parent;
};

node* dummy;



void rotacja(node* B)
{
    if (!B || B == dummy || B->parent == dummy) return;
    node* A = B->parent;
    node* P = A->parent;
    if (A->left == B) 
    {
        node* Beta = B->right;
        if (P->left == A)
            P->left = B;
        else
            P->right = B;
        B->parent = P;
        A->parent = B;
        B->right = A;
        A->left = Beta;
        if (Beta)
            Beta->parent = A;
    }
    else
    {
        node* Beta = B->left;
        if (P->right == A)
            P->right = B;
        else
            P->left = B;
        B->parent = P;
        A->parent = B;
        B->left = A;
        A->right = Beta;
        if (Beta)
            Beta->parent = A;
    }

}



node* Add(node*& r, int k, node* par = dummy)
{
    if (!r)
    {
        r = new node;
        r->key = k;
        r->left = r->right = nullptr;
        r->parent = par;
        return r;
    }
    if (r->key == k) return r;
    if (r->key > k) return Add(r->left, k, r);
    return Add(r->right, k, r);
}

void PrintInOrder(node* r)
{
    if (!r) return;
    PrintInOrder(r->left);
    cout << r->key << ",";
    PrintInOrder(r->right);
}




void Myk(node* r, int depth = 0)
{
    if (!r) return;
    Myk(r->right, depth + 1);
    for (int i = 0; i < depth; i++)
    {
        cout << "    ";
    }
    cout << r->key << endl;
    Myk(r->left, depth + 1);
}



void DSW()
{
    int n = 0;
    node* w = dummy;
    while (w->right)
    {
        if (w->right->left)
        {
            node* temp = w->right->left;
            rotacja(temp);
        }
        else
        {
            w = w->right;
            n++;
        }
    }
    int m = n;
    while (m > 1)
    {
        m /= 2;
        w = dummy;
        for (int i = 0; i < m; i++)
        {
            w = w->right->right;
            rotacja(w);
        }
    }
}



int main()
{
    node* root = nullptr;
    
    dummy = new node;
    dummy->right = nullptr;
    for (int i = 0; i < 50; i++)
    {  
        cout << "- - - - - - - - - - -" << endl;
        Add(dummy->right,rand()%100 );
        Myk(dummy->right);
        cout << "- - - - - - - - - - -" << endl;
        if (i % 10 == 0)
        {
            cout << "dsw: " << endl;
            DSW();
            Myk(dummy->right);
        }
    }
    cout << endl;
    Myk(dummy->right);
    cout << endl << endl;

    DSW();
    Myk(dummy->right);
    return 0;
}
