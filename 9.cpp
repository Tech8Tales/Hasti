#include <iostream>
#include <string>
using namespace std;
struct Node {
    string keyword, meaning;
    Node *left, *right;
    int height;
    Node(string k, string m) : keyword(k), meaning(m), left(NULL), right(NULL), height(1) {}
};
int height(Node* n) {
    return n ? n->height : 0;
}
int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}
Node* insert(Node* root, string key, string meaning) {
    if (!root) return new Node(key, meaning);
    if (key < root->keyword)
        root->left = insert(root->left, key, meaning);
    else if (key > root->keyword)
        root->right = insert(root->right, key, meaning);
    else {
        cout << "Keyword already exists. Use update instead.\n";
        return root;
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && key < root->left->keyword)
        return rightRotate(root);
    if (balance < -1 && key > root->right->keyword)
        return leftRotate(root);
    if (balance > 1 && key > root->left->keyword) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->keyword) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}
Node* deleteNode(Node* root, string key) {
    if (!root) return root;
    if (key < root->keyword)
        root->left = deleteNode(root->left, key);
    else if (key > root->keyword)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->keyword = temp->keyword;
        root->meaning = temp->meaning;
        root->right = deleteNode(root->right, temp->keyword);
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->keyword << " : " << root->meaning << endl;
        inOrder(root->right);
    }
}
void reverseInOrder(Node* root) {
    if (root) {
        reverseInOrder(root->right);
        cout << root->keyword << " : " << root->meaning << endl;
        reverseInOrder(root->left);
    }
}
void update(Node* root, string key, string newMeaning) {
    if (!root) {
        cout << "Keyword not found.\n";
        return;
    }
    if (key == root->keyword) {
        root->meaning = newMeaning;
        cout << "Updated successfully.\n";
    }
    else if (key < root->keyword)
        update(root->left, key, newMeaning);
    else
        update(root->right, key, newMeaning);
}
int search(Node* root, string key, int& comparisons) {
    comparisons++;
    if (!root) return 0;
    if (root->keyword == key) return 1;
    if (key < root->keyword) return search(root->left, key, comparisons);
    return search(root->right, key, comparisons);
}
int main() {
    Node* root = NULL;
    int choice;
    string key, meaning;
    do {
        cout << "\n---- Dictionary Menu ----\n";
        cout << "1. Add Keyword\n2. Delete Keyword\n3. Update Meaning\n4. Display Ascending\n";
        cout << "5. Display Descending\n6. Search Keyword (with comparisons)\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            cout << "Enter keyword: ";
            getline(cin, key);
            cout << "Enter meaning: ";
            getline(cin, meaning);
            root = insert(root, key, meaning);
            break;
        case 2:
            cout << "Enter keyword to delete: ";
            getline(cin, key);
            root = deleteNode(root, key);
            break;
        case 3:
            cout << "Enter keyword to update: ";
            getline(cin, key);
            cout << "Enter new meaning: ";
            getline(cin, meaning);
            update(root, key, meaning);
            break;
        case 4:
            cout << "--- Dictionary (Ascending Order) ---\n";
            inOrder(root);
            break;
        case 5:
            cout << "--- Dictionary (Descending Order) ---\n";
            reverseInOrder(root);
            break;
        case 6:
            cout << "Enter keyword to search: ";
            getline(cin, key);{
                int comparisons = 0;
                if (search(root, key, comparisons))
                    cout << "Keyword found in " << comparisons << " comparisons.\n";
                else
                    cout << "Keyword not found. Comparisons made: " << comparisons << "\n";
            }
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 7);
    return 0;
}
