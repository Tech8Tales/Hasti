#include <iostream>
#include <string>
using namespace std;
struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    Node(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = nullptr;
    }
};
class Dictionary {
private:
    Node* root;
    Node* insert(Node* node, string k, string m) {
        if (!node) return new Node(k, m);
        if (k < node->keyword)
            node->left = insert(node->left, k, m);
        else if (k > node->keyword)
            node->right = insert(node->right, k, m);
        else
            cout << "Keyword already exists.\n";
        return node;
    }
    Node* findMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }
    Node* deleteNode(Node* node, string k) {
        if (!node) return nullptr;
        if (k < node->keyword)
            node->left = deleteNode(node->left, k);
        else if (k > node->keyword)
            node->right = deleteNode(node->right, k);
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            } else if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* temp = findMin(node->right);
                node->keyword = temp->keyword;
                node->meaning = temp->meaning;
                node->right = deleteNode(node->right, temp->keyword);
            }
        }
        return node;
    }
    void update(Node* node, string k, string newMeaning) {
        if (!node) {
            cout << "Keyword not found.\n";
            return;
        }
        if (k < node->keyword)
            update(node->left, k, newMeaning);
        else if (k > node->keyword)
            update(node->right, k, newMeaning);
        else {
            node->meaning = newMeaning;
            cout << "Meaning updated.\n";
        }
    }
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->keyword << " : " << node->meaning << endl;
        inorder(node->right);
    }
    void reverseInorder(Node* node) {
        if (!node) return;
        reverseInorder(node->right);
        cout << node->keyword << " : " << node->meaning << endl;
        reverseInorder(node->left);
    }
    int maxDepth(Node* node) {
        if (!node) return 0;
        return 1 + max(maxDepth(node->left), maxDepth(node->right));
    }
public:
    Dictionary() {
        root = nullptr;
    }
    void addKeyword(string k, string m) {
        root = insert(root, k, m);
    }
    void deleteKeyword(string k) {
        root = deleteNode(root, k);
    }
    void updateMeaning(string k, string newMeaning) {
        update(root, k, newMeaning);
    }
    void displayAscending() {
        cout << "\nDictionary in Ascending Order:\n";
        inorder(root);
    }
    void displayDescending() {
        cout << "\nDictionary in Descending Order:\n";
        reverseInorder(root);
    }
    void showMaxComparisons() {
        cout << "\nMaximum comparisons needed in worst case: " << maxDepth(root) << endl;
    }
};
int main() {
    Dictionary dict;
    int choice;
    string keyword, meaning;
    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Meaning\n";
        cout << "4. Display Ascending\n";
        cout << "5. Display Descending\n";
        cout << "6. Show Max Comparisons (Height of BST)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, keyword);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dict.addKeyword(keyword, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, keyword);
                dict.deleteKeyword(keyword);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, keyword);
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                dict.updateMeaning(keyword, meaning);
                break;
            case 4:
                dict.displayAscending();
                break;
            case 5:
                dict.displayDescending();
                break;
            case 6:
                dict.showMaxComparisons();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
    } while (choice != 0);
    return 0;
}