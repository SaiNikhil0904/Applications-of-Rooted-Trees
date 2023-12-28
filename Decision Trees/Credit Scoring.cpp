#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    int studentNumber;
    int marks;
    Node* left;
    Node* right;

    Node(int studentNumber, int marks) : studentNumber(studentNumber), marks(marks), left(nullptr), right(nullptr) {}
};

class DecisionTree {
private:
    Node* root;

    Node* insert(Node* node, int studentNumber, int marks) {
        if (node == nullptr) {
            return new Node(studentNumber, marks);
        }

        if (marks <= node->marks) {
            node->left = insert(node->left, studentNumber, marks);
        } else {
            node->right = insert(node->right, studentNumber, marks);
        }

        return node;
    }

    void displayTree(Node* node, int depth) {
        if (node != nullptr) {
            displayTree(node->right, depth + 1);
            for (int i = 0; i < depth; ++i) {
                std::cout << "   ";
            }
            std::cout << node->studentNumber << "." << node->marks << "\n";
            displayTree(node->left, depth + 1);
        }
    }

    void inOrderTraversal(Node* node, std::vector<Node*>& sortedList) {
        if (node != nullptr) {
            inOrderTraversal(node->left, sortedList);
            sortedList.push_back(node);
            inOrderTraversal(node->right, sortedList);
        }
    }

    Node* buildTreeFromSorted(std::vector<Node*>& sortedList, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        Node* node = sortedList[mid];

        node->left = buildTreeFromSorted(sortedList, start, mid - 1);
        node->right = buildTreeFromSorted(sortedList, mid + 1, end);

        return node;
    }

public:
    DecisionTree() : root(nullptr) {}

    void insert(int studentNumber, int marks) {
        root = insert(root, studentNumber, marks);
    }

    void displayTree() {
        displayTree(root, 0);
    }

    void displaySortedList() {
        std::vector<Node*> sortedList;
        inOrderTraversal(root, sortedList);

        std::cout << "Sorted List of Students:\n";
        for (const auto& node : sortedList) {
            std::cout << node->studentNumber << "." << node->marks << " ";
        }
        std::cout << "\n";
    }

    void buildTreeFromSorted() {
        std::vector<Node*> sortedList;
        inOrderTraversal(root, sortedList);
        int size = sortedList.size();

        root = buildTreeFromSorted(sortedList, 0, size - 1);
    }
};

int main() {
    int numStudents;

    std::cout << "Enter the number of students: ";
    std::cin >> numStudents;

    DecisionTree tree;

    for (int i = 0; i < numStudents; ++i) {
        int marks;
        std::cout << "Enter marks for student " << i + 1 << ": ";
        std::cin >> marks;
        tree.insert(i + 1, marks);
    }

    tree.buildTreeFromSorted();

    std::cout << "\nDecision Tree for Sorting Students by Marks:\n";
    tree.displayTree();

    tree.displaySortedList();

    return 0;
}
