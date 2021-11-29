#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

struct List {
    struct Element {
        int value;
        Element* next;
        Element();
    };
    Element* first;
    List();
    void Print();
    void Add(int x);
    bool Remove(int x);
    bool Find(int x);
};
struct BST {
    struct Element {
        int value;
        Element* left;
        Element* right;
        Element();

    };
    Element* root;
    BST();
    void Print();
    void PrintElement(Element* e);
    void Add(int x);
    void Remove(int x);
    Element* RemoveElement(Element* e, int x);
    bool Find(int x);
    void PrintTree(Element *r, string indent, bool last);
};
struct AVL {
    struct Element {
        int value;
        int height;
        Element* left;
        Element* right;
        Element();
    };
    Element* root;
    AVL();
    int Height(Element* x);
    int Max(int a, int b);
    Element* NewElement(int value);
    Element* RightRotate(Element* x);
    Element* LeftRotate(Element* x);
    int GetBalanceFactor(Element* x);
    void Add(int value);
    Element* AddElement(Element* root, int value);
    Element* ElementWithMinValue(Element* x);
    void Remove(int value);
    Element* RemoveElement(Element* root, int value);
    void Print();
    void PrintElement(Element* e);
    bool Find(int x);
    void PrintTree(Element* r, string indent, bool last);
};

int* randomArray(int n, int min, int max);
int* sortedArray(int n);
int* invertedArray(int n);
int* AArray(int n);
int* VArray(int n);

int main() {
    srand(time(NULL));
    int s = 10, start, stop;
    fstream results;
    results.open("results.txt", ios::out);
    while (s <= 100000) {
        results << s << endl;
        cout << s << endl;
        for (int t = 0; t < 14; t++) {
            int* data = new int[s];
            switch(t) {
            case 0:
                data = sortedArray(s);
                break;
            case 1:
                data = invertedArray(s);
                break;
            case 2:
                data = AArray(s);
                break;
            case 3:
                data = VArray(s);
                break;
            default:
                data = randomArray(s, 0, RAND_MAX);
            }
            List* l = new List();
            BST* bst = new BST();
            AVL* avl = new AVL();
            start = clock();
            for (int i = 0; i < s; i++) {
                l->Add(i);
            }
            stop = clock();
            results << double(stop - start) / CLOCKS_PER_SEC << " ";
            cout << double(stop - start) / CLOCKS_PER_SEC << " ";
            start = clock();
            for (int i = 0; i < s; i++) {
                l->Find(i);
            }
            stop = clock();
            results << double(stop - start) / CLOCKS_PER_SEC << " ";
            cout << double(stop - start) / CLOCKS_PER_SEC << " ";
            start = clock();
            for (int i = 0; i < s; i++) {
                bst->Add(i);
            }
            stop = clock();
            results << double(stop - start) / CLOCKS_PER_SEC << " ";
            cout << double(stop - start) / CLOCKS_PER_SEC << " ";
            start = clock();
            for (int i = 0; i < s; i++) {
                bst->Find(i);
            }
            stop = clock();
            results << double(stop - start) / CLOCKS_PER_SEC << " ";
            cout << double(stop - start) / CLOCKS_PER_SEC << " ";
            start = clock();
            for (int i = 0; i < s; i++) {
                avl->Add(i);
            }
            stop = clock();
            results << double(stop - start) / CLOCKS_PER_SEC << " ";
            cout << double(stop - start) / CLOCKS_PER_SEC << " ";
            start = clock();
            for (int i = 0; i < s; i++) {
                avl->Find(i);
            }
            stop = clock();
            results << double(stop - start) / CLOCKS_PER_SEC << " ";
            cout << double(stop - start) / CLOCKS_PER_SEC << " ";
            results << endl;
            cout << endl;
        }
        s *= 10;
    }
    return 0;
}

int* randomArray(int n, int min, int max) {
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        a[i] = rand()%(max - min + 1) + min;
    }
    return a;
}
int* sortedArray(int n) {
    int* a = new int[n];
    for (int i = 0; i < n; i++){
        a[i] = i;
    }
    return a;
}
int* invertedArray(int n) {
    int* a = new int[n];
    for (int i = 0; i < n; i++){
        a[i] = n - i;
    }
    return a;
}
int* AArray(int n) {
    int* a = new int[n];
    for (int i = 0; i < n / 2; i++) {
        a[i] = i * 2;
        a[n - i - 1] = i * 2 + 1;
    }
    return a;
}
int* VArray(int n) {
    int* a = new int[n];
    for (int i = 0; i < n / 2; i++) {
        a[i] = n - i * 2;
        a[n - i - 1] = n - i * 2 - 1;
    }
    return a;
}

List::List() {
    first = 0;
}
List::Element::Element() {
    next = 0;
}
void List::Print() {
    Element* e = first;
    while (e) {
        cout << e->value << " ";
        e = e->next;
    }
    cout << "\n";
}
void List::Add(int x) {
    Element* n = new Element;
    n->value = x;
    if (!first){
        first = n;
        return;
    }
    if (first->value == x){
        return;
    }
    if (first->value > x){
        n->next = first;
        first = n;
        return;
    }
    Element* e = first;
    while (e->next) {
        if (e->next->value == x) {
            return;
        }
        if (e->next->value > x) {
            n->next = e->next;
            e->next = n;
            return;
        }
        e = e->next;
    }
    e->next = n;
}
bool List::Remove(int x) {
    if (!first) {
        return false;
    }
    if (first->value == x) {
        first = first->next;
        return true;
    }
    Element* e = first;
    while (e->next) {
        if (e->next->value == x) {
            e->next = e->next->next;
            return true;
        }
        if (e->next->value > x) {
            return false;
        }
        e = e->next;
    }
    return false;
}
bool List::Find(int x) {
    Element* e = first;
    while(e) {
        if (e->value == x){
            return true;
        }
        if (e->value > x) {
            return false;
        }
        e = e->next;
    }
    return false;
}

BST::BST() {
    root = 0;
}
BST::Element::Element() {
    left = 0;
    right = 0;
}
void BST::Print() {
    PrintElement(root);
    cout << "\n";
}
void BST::PrintElement(Element* e) {
    if (e) {
        PrintElement(e->left);
        cout << e->value << " ";
        PrintElement(e->right);
    }
}
void BST::Add(int x) {
    Element* n = new Element();
    n->value = x;
    if (!root) {
        root = n;
        return;
    }
    Element* e = root;
    while (true) {
        if (e->value > x) {
            if (!e->left) {
                e->left = n;
                return;
            }
            e = e->left;
        }
        else if (e->value < x) {
            if (!e->right) {
                e->right = n;
                return;
            }
            e = e->right;
        }
        else {
            return;
        }
    }
}
void BST::Remove(int x) {
    root = RemoveElement(root, x);
}
BST::Element* BST::RemoveElement(Element* e, int x) {
    if (!e) {
        return e;
    }
    if (e->value > x) {
        e->left = RemoveElement(e->left, x);
        return e;
    }
    if (e->value < x) {
        e-> right = RemoveElement(e->right, x);
        return e;
    }
    if (!e->left) {
        return e->right;
    }
    if (!e->right) {
        return e->left;
    }
    Element* m = e->right;
    while(m->left) {
        m = m->left;
    }
    e->value = m->value;
    e->right = RemoveElement(e->right, m->value);
    return e;
}
bool BST::Find(int x) {
    Element* e = root;
    while (e != 0) {
        if (e->value == x) {
            return true;
        }
        if (e->value < x) {
            e = e->right;
        }
        else {
            e = e->left;
        }
    }
    return false;
}
void BST::PrintTree(Element *r, string indent, bool last) {
  if (r != 0) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "   ";
    } else {
      cout << "L----";
      indent += "|  ";
    }
    cout << r->value << endl;
    PrintTree(r->left, indent, false);
    PrintTree(r->right, indent, true);
  }
}


AVL::AVL() {
    root = 0;
}
AVL::Element::Element() {
    right = 0;
    left = 0;
    height = 1;
}
int AVL::Height(Element* x) {
    if(x == 0){
        return 0;
    }
    return x->height;
}
int AVL::Max(int a, int b) {
    return (a > b) ? a : b;
}
AVL::Element* AVL::NewElement(int value) {
    Element* e = new Element();
    e->value = value;
    return e;
}
AVL::Element* AVL::RightRotate(Element* x) {
    Element* y = x->left;
    Element* z = y->right;
    y->right = x;
    x->left = z;
    x->height = Max(Height(x->left), Height(x->right)) + 1;
    y->height = Max(Height(y->left), Height(y->right)) + 1;
    return y;
}
AVL::Element* AVL::LeftRotate(Element* x) {
    Element* y = x->right;
    Element* z = y->left;
    y->left = x;
    x->right = z;
    x->height = Max(Height(x->left), Height(x->right)) + 1;
    y->height = Max(Height(y->left), Height(y->right)) + 1;
    return y;
}
int AVL::GetBalanceFactor(Element* x) {
    if (x == 0) {
        return 0;
    }
    return Height(x->left) - Height(x->right);
}
void AVL::Add(int value) {
    root = AddElement(root, value);
}
AVL::Element* AVL::AddElement(Element* r, int value) {
    if (r == 0) {
        return NewElement(value);
    }
    if (value < r->value) {
        r->left = AddElement(r->left, value);
    }
    else if (value > r->value) {
        r->right = AddElement(r->right, value);
    }
    else {
        return r;
    }
    r->height = Max(Height(r->left), Height(r->right)) + 1;
    int balanceFactor = GetBalanceFactor(r);
    if (balanceFactor > 1) {
        if (value < r->left->value) {
            return RightRotate(r);
        }
        else if (value > r->left->value) {
            r->left = LeftRotate(r->left);
            return RightRotate(r);
        }
    }
    if (balanceFactor < -1) {
        if (value > r->right->value) {
            return LeftRotate(r);
        }
        if (value < r->right->value) {
            r->right = RightRotate(r->right);
            return LeftRotate(r);
        }
    }
    return r;
}
AVL::Element* AVL::ElementWithMinValue(Element* x) {
    Element* e = x;
    while (e->left != 0) {
        e = e->left;
    }
    return e;
}
void AVL::Remove(int value) {
    root = RemoveElement(root, value);
}
AVL::Element* AVL::RemoveElement(Element* root, int value) {
    if (root == 0) {
        return root;
    }
    if (value < root->value) {
        root->left = RemoveElement(root->left, value);
    }
    else if (value > root->value) {
        root->right = RemoveElement(root->right, value);
    }
    else {
        if (root->left == 0 || root->right == 0) {
            Element* e = (root->left == 0) ? root->left : root->right;
            if (e == 0) {
                e = root;
                root = 0;
            }
            else {
                *root = *e;
            }
        }
        else {
            Element* e = ElementWithMinValue(root->right);
            root->value = e->value;
            root->right = RemoveElement(root->right, e->value);
        }
    }
    if (root == 0) {
        return root;
    }
    root->height = Max(Height(root->left), Height(root->right)) + 1;
    int balanceFactor = GetBalanceFactor(root);
    if (balanceFactor > 1) {
        if (GetBalanceFactor(root->left) >= 0) {
            return RightRotate(root);
        }
        else {
            root->left = LeftRotate(root->left);
            return RightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (GetBalanceFactor(root->right) <= 0) {
            return LeftRotate(root);
        }
        else {
            root->right = RightRotate(root->right);
            return LeftRotate(root);
        }
    }
    return root;
}
void AVL::Print() {
    PrintElement(root);
    cout << "\n";
}
void AVL::PrintElement(Element* e) {
    if (e) {
        PrintElement(e->left);
        cout << e->value << " ";
        PrintElement(e->right);
    }
}
bool AVL::Find(int x) {
    Element* e = root;
    while (e != 0) {
        if (e->value == x) {
            return true;
        }
        if (e->value < x) {
            e = e->right;
        }
        else {
            e = e->left;
        }
    }
    return false;
}
void AVL::PrintTree(Element *r, string indent, bool last) {
  if (r != 0) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "   ";
    } else {
      cout << "L----";
      indent += "|  ";
    }
    cout << r->value << endl;
    PrintTree(r->left, indent, false);
    PrintTree(r->right, indent, true);
  }
}