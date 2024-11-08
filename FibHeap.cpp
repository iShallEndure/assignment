#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

class FibNode {
public:
    int key;
    int degree;
    FibNode* parent;
    FibNode* child;
    FibNode* left;
    FibNode* right;
    bool mark;

    FibNode(int value) : key(value), degree(0), parent(nullptr), child(nullptr),
                         left(this), right(this), mark(false) {}
};

class FibHeap {
public:
    FibHeap() : min(nullptr), n(0) {}

    FibNode* insert(int key) {
        FibNode* newNode = new FibNode(key);
        if (!min) {
            min = newNode;
        } else {
            addToRootList(newNode);
            if (newNode->key < min->key) {
                min = newNode;
            }
        }
        n++;
        return newNode;
    }

    int extract_min() {
        if (!min) return -1; 

        FibNode* z = min;
        if (z) {
            if (z->child) {
                FibNode* child = z->child;
                do {
                    FibNode* nextChild = child->right;
                    addToRootList(child);
                    child->parent = nullptr;
                    child = nextChild;
                } while (child != z->child);
            }
            removeNodeFromRootList(z);
            if (z == z->right) {
                min = nullptr;
            } else {
                min = z->right;
                consolidate();
            }
            n--;
        }
        int minValue = z->key;
        delete z;
        return minValue;
    }

    void decrease_key(FibNode* x, int new_key) {
        if (new_key > x->key) {
            std::cerr << "New key is greater than current key." << std::endl;
            return;
        }
        x->key = new_key;
        FibNode* y = x->parent;
        if (y && x->key < y->key) {
            cut(x, y);
            cascading_cut(y);
        }
        if (x->key < min->key) {
            min = x;
        }
    }

private:
    FibNode* min; 
    int n;        

    void addToRootList(FibNode* node) {
        if (!min) {
            min = node;
            node->left = node->right = node;
        } else {
            node->left = min;
            node->right = min->right;
            min->right->left = node;
            min->right = node;
        }
    }

    void removeNodeFromRootList(FibNode* node) {
        node->left->right = node->right;
        node->right->left = node->left;
    }

    void consolidate() {
        int max_degree = static_cast<int>(std::log2(n)) + 1;
        std::vector<FibNode*> A(max_degree, nullptr);

        std::vector<FibNode*> rootList;
        FibNode* x = min;
        if (x) {
            do {
                rootList.push_back(x);
                x = x->right;
            } while (x != min);
        }

        for (FibNode* w : rootList) {
            FibNode* x = w;
            int d = x->degree;
            while (A[d]) {
                FibNode* y = A[d];
                if (x->key > y->key) std::swap(x, y);
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }

        min = nullptr;
        for (FibNode* node : A) {
            if (node) {
                if (!min || node->key < min->key) {
                    min = node;
                }
            }
        }
    }

    void link(FibNode* y, FibNode* x) {
        removeNodeFromRootList(y);
        y->left = y->right = y;
        if (!x->child) {
            x->child = y;
        } else {
            y->right = x->child;
            y->left = x->child->left;
            x->child->left->right = y;
            x->child->left = y;
        }
        y->parent = x;
        x->degree++;
        y->mark = false;
    }

    void cut(FibNode* x, FibNode* y) {
        if (y->child == x) {
            y->child = (x->right == x) ? nullptr : x->right;
        }
        y->degree--;
        x->right->left = x->left;
        x->left->right = x->right;
        addToRootList(x);
        x->parent = nullptr;
        x->mark = false;
    }

    void cascading_cut(FibNode* y) {
        FibNode* z = y->parent;
        if (z) {
            if (!y->mark) {
                y->mark = true;
            } else {
                cut(y, z);
                cascading_cut(z);
            }
        }
    }
};

int main() {
    FibHeap fibHeap;
    
    
    FibNode* node1 = fibHeap.insert(10);
    FibNode* node2 = fibHeap.insert(20);
    FibNode* node3 = fibHeap.insert(30);

    std::cout << "Min after inserts: " << fibHeap.extract_min() << std::endl;  

    
    fibHeap.decrease_key(node3, 5);
    std::cout << "Min after decrease_key: " << fibHeap.extract_min() << std::endl;  

    return 0;
}
