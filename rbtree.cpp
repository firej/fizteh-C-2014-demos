#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>    // std::max
#include <string>
using std::cout;
using std::cin;
using std::setw;
using std::setfill;
using std::endl;
using std::max;
using std::vector;
using std::string;

#define RED 0
#define BLACK 1
const string NC = "\E[0m";
const string CLEAR_SCREEN = "\E[2J";

class node{
public:
int value;
unsigned char color;
node* left;
node* right;
node* parent;
node(){
    left = right = parent = NULL;
    color = RED;
}
node(int val){
    value = val;
    left = right = parent = NULL;
    color = RED;
}
};

class RBTree{
private:
    node*   root;
    void    rprint(node* root);
    void    case1(node*);
    void    case2(node*);
    void    case3(node*);
    void    case4(node*);
    void    case5(node*);
    void    radd(node* r, node* n);
    node*   uncle(node *n);
    node*   grandpa(node* n);
    // int     count_seeds(node* r);
    int     count_depth(node* r);
    void    left_rotate (node *n);
    void    right_rotate (node *n);
public:     
    RBTree();
    int     get_depth();
    void    print();
    void    add(int val);
    void    remove(int val);
};

RBTree::RBTree(){     
    root = NULL; 
}

// int RBTree::count_seeds(node* r){
//     int res = 0;    
//     // while (r == r->left)     
//     //     res++; 
//     while (r){         
//         r = r->left;         
//         res++;     
//     }
//     return res; 
// }

int RBTree::count_depth(node *r){
    if (r == NULL)
        return 0;
    return 1 + max(count_depth(r->left), count_depth(r->right));
}

int RBTree::get_depth(){
    return count_depth(root);
}

int pow(int base, int power){
    int res = 1;
    for (int i = 0 ; i < power; i++ )
        res *= base;
    return res;
}
void print_slice(int shift, vector<node*> v){
    bool odd = true;
    if (v.size() > 1){
        for (int i = 0; i < pow(2, shift - 1) * 2 - 2; i++ ) cout << " ";
        for (int j = 1; j <= v.size(); j++ ){
            cout << (odd ? "  /-" : "--\\ ");
            if (j != v.size())
                for (int i = 0; i < pow(2, shift - 1) * 2 - 2; i++ ) cout << (odd ? "--" : "  " );
            odd = !odd;
        }
        cout << endl;
    }

    for (int i = 0; i < pow(2, shift - 1) * 2 - 2; i++ ) cout << " ";
    for (auto n: v){
        if (n)
            cout << ((n->color == RED) ? "\E[1;31m " : "\E[1;34m ")  << setfill('0') << setw(2) << n->value << NC << " ";
        else
            cout << " ** ";
        for (int i = 0; i < pow(2, shift - 1) * 2 - 2; i++ ) cout << "  ";
    }
    cout << endl;
}
void RBTree::print(){
    vector<node*> v;
    int depth = get_depth();
    v.push_back(root);      // Инициализиуем наше очередь
    print_slice(depth, v);
    for (int i = 1; i < depth; i++){
        vector<node*> v_tmp;
        for (auto n : v){
            if (n != NULL){
                v_tmp.push_back(n->left);
                v_tmp.push_back(n->right);
            }
            else{
                v_tmp.push_back(NULL), v_tmp.push_back(NULL);
            }
        }
        v = v_tmp;
        print_slice(depth - i, v);
    }
}

node* RBTree::grandpa(node *n){
    if(n->parent)
        return n->parent->parent;
    else
        return NULL;
}

node* RBTree::uncle(node *n){
    if(n->parent && n->parent->parent)
        return (n->parent == n->parent->parent->left) ? n->parent->parent->right : n->parent->parent->left;
    else
        return NULL;
}

void RBTree::case1(node *n){
    if (n->parent == NULL)
        n->color = BLACK;
    else
        case2(n);
}

void RBTree::case2(node* n){
    if (n->parent->color == BLACK)
        return;
    else
        case3(n);
}

// Третий случай - родительский элемент - КРАСНЫЙ
void RBTree::case3(node* n){
    if (n->parent->color == RED && uncle(n) && uncle(n)->color == RED){
        n->parent->color = BLACK;
        uncle(n)->color = BLACK;
        grandpa(n)->color = RED;
        case1(grandpa(n));
    }    
    else 
        case4(n);
}

void RBTree::left_rotate(node *a){
    // http://upload.wikimedia.org/wikipedia/ru/b/bc/AVL_LR.GIF
    // cout << "Делаем левый поворот: " << a->value << " и " << a->right->value << endl;
    node * grand = a->parent;
    node * b = a->right;
    node * c = b->left;

    if (grand && grand->left == a)
        grand->left = b;
    if (grand && grand->right == a)
        grand->right = b;
    if (a == root)
        root = b;

    a->right = c; if (c) c->parent = a;
    if (b) b->parent = grand;
    a->parent = b;
    b->left = a;
}

void RBTree::right_rotate(node *a){
    // http://upload.wikimedia.org/wikipedia/ru/e/e8/AVL_LL.GIF
    // cout << "Делаем правый поворот: " << a->value << " и " << a->left->value << endl;
    node * grand = a->parent;
    node * b = a->left;
    node * c = b->right;

    if (grand && grand->left == a)
        grand->left = b;
    if (grand && grand->right == a)
        grand->right = b;
    if (a == root)
        root = b;

    a->left = c; if (c) c->parent = a;
    if (b) b->parent = grand;
    a->parent = b;
    b->right = a;
}

void RBTree::case4(node* n){
    if ((n == n->parent->right) && (n->parent == grandpa(n)->left)){
        left_rotate(n->parent);
        n = n->left;
    }
    if ((n == n->parent->left) && (n->parent == grandpa(n)->right)){
        right_rotate(n->parent);
        n = n->right;
    }
    case5(n);
}

void RBTree::case5(node* n){
    n->parent->color = BLACK;
    grandpa(n)->color = RED;
    if ((n == n->parent->left) && (n->parent == grandpa(n)->left)){
        right_rotate(n->parent->parent);
    }
    else{
        left_rotate(n->parent->parent);
    }
}

// r = root, n = элемент, который добавляем
void RBTree::radd(node* r, node *n){
    if (n->value < r->value){         
        if (r->left == NULL){
            r->left = n;
            n->parent = r;
        }
        else{
            return radd(r->left, n);
        }
    }
    else{
        if (r->right == NULL){
            r->right = n;
            n->parent = r;
        }
        else{
            radd(r->right, n);
            return;
        }
    }
}

void RBTree::add(int val){
    node * n = new node(val);
 // Случай 1
    if (root == NULL){
        root = n;
    }
    else{
        radd(root, n);
    }
    case1(n);
}

int main(){
    cout << NC << endl;
    RBTree rbt;

    vector<int> values = {10, 5, 2, 1, 3, 7, 15, 25, 30};

    for (auto v : values) rbt.add(v);

    values = {45, 36, 67, 90, 04, 23, 52, 11};

    for (auto v : values){
        rbt.add(v);
        rbt.print();
        cin.ignore(1);
    }
    return 0;
} 
