// C++ code for an interactive Binary Search Tree (BST) implementation

#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int value) : key(value), left(nullptr), right(nullptr){}
};

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }
    if(key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    return root;
}

bool search(Node* root, int key) {
    if (root == nullptr) {
        return false;
    }
    if (key == root->key) {
        return true;
    } else if (key < root->key) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr) {
        return root;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = root->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void printPreorder(Node* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    cout << "Initial Tree (Preorder): ";
    printPreorder(root);
    cout << endl;
    int choice, value;
    do{
        cout << "\nOptions:\n";
        cout << "1. Search for a key\n";
        cout << "2. Insert a new key\n";
        cout << "3. Delete a key\n";
        cout << "4. Print the tree in preorder\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter the key to search: ";
                cin >> value;
                if (search(root, value)) {
                    cout << "Key " << value << " found in the tree.\n";
                } else {
                    cout << "Key " << value << " not found in the tree.\n";
                }
                break;
            case 2:
                cout << "Enter the key to insert: ";
                cin >> value;
                root = insert(root, value);
                cout << "Key " << value << " inserted.\n";
                break;
            case 3:
                cout << "Enter the key to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                cout << "Key " << value << " deleted.\n";
                break;
            case 4:
                cout << "Tree in preorder: ";
                printPreorder(root);
                cout << endl;
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
    return 0;
}
