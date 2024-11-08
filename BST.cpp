#include <iostream>
#include <string>

struct Node {
    std::string isbn;
    std::string book_data;
    Node* left;
    Node* right;

    Node(std::string i, std::string data) : isbn(i), book_data(data), left(nullptr), right(nullptr) {}
};

class BookBST {
public:
    BookBST() : root(nullptr) {}

    void insert(std::string isbn, std::string book_data) {
        if (root == nullptr) {
            root = new Node(isbn, book_data);
        } else {
            insert(root, isbn, book_data);
        }
    }

    std::string search(std::string isbn) {
        Node* result = search(root, isbn);
        return result ? result->book_data : "Not found";
    }

    void deleteNode(std::string isbn) {
        root = deleteNode(root, isbn);
    }

private:
    Node* root;

    void insert(Node* node, std::string isbn, std::string book_data) {
        if (isbn < node->isbn) {
            if (node->left == nullptr) {
                node->left = new Node(isbn, book_data);
            } else {
                insert(node->left, isbn, book_data);
            }
        } else if (isbn > node->isbn) {
            if (node->right == nullptr) {
                node->right = new Node(isbn, book_data);
            } else {
                insert(node->right, isbn, book_data);
            }
        } else {
            node->book_data = book_data;
        }
    }

    Node* search(Node* node, std::string isbn) {
        if (node == nullptr || node->isbn == isbn) {
            return node;
        }
        if (isbn < node->isbn) {
            return search(node->left, isbn);
        } else {
            return search(node->right, isbn);
        }
    }

    Node* deleteNode(Node* node, std::string isbn) {
        if (node == nullptr) {
            return node;
        }
        if (isbn < node->isbn) {
            node->left = deleteNode(node->left, isbn);
        } else if (isbn > node->isbn) {
            node->right = deleteNode(node->right, isbn);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->isbn = temp->isbn;
            node->book_data = temp->book_data;
            node->right = deleteNode(node->right, temp->isbn);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
};