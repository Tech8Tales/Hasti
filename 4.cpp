#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// Node structure for expression tree
struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to check if character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to get precedence of operators
int precedence(char op) {
    if (op == '^') return 4;
    if (op == '*' || op == '/') return 3;
    if (op == '+' || op == '-') return 2;
    return 0;
}

// Function to construct expression tree from infix expression
Node* constructTree(string infix) {
    stack<Node*> nodeStack;
    stack<char> opStack;
    
    for (char c : infix) {
        if (isalnum(c)) {
            nodeStack.push(new Node(c));
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                Node* opNode = new Node(opStack.top());
                opStack.pop();
                
                opNode->right = nodeStack.top();
                nodeStack.pop();
                
                opNode->left = nodeStack.top();
                nodeStack.pop();
                
                nodeStack.push(opNode);
            }
            opStack.pop(); // Remove '(' from stack
        } else if (isOperator(c)) {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)) {
                Node* opNode = new Node(opStack.top());
                opStack.pop();
                
                opNode->right = nodeStack.top();
                nodeStack.pop();
                
                opNode->left = nodeStack.top();
                nodeStack.pop();
                
                nodeStack.push(opNode);
            }
            opStack.push(c);
        }
    }
    
    // Process remaining operators
    while (!opStack.empty()) {
        Node* opNode = new Node(opStack.top());
        opStack.pop();
        
        opNode->right = nodeStack.top();
        nodeStack.pop();
        
        opNode->left = nodeStack.top();
        nodeStack.pop();
        
        nodeStack.push(opNode);
    }
    
    return nodeStack.top();
}

// Non-recursive postorder traversal
void postorderTraversal(Node* root) {
    if (!root) return;
    
    stack<Node*> s1, s2;
    s1.push(root);
    
    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();
        s2.push(current);
        
        if (current->left) s1.push(current->left);
        if (current->right) s1.push(current->right);
    }
    
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
    cout << endl;
}

// Function to delete the tree using postorder traversal
void deleteTree(Node* root) {
    if (!root) return;
    
    stack<Node*> s;
    Node* current = root;
    Node* lastVisited = nullptr;
    
    while (current || !s.empty()) {
        if (current) {
            s.push(current);
            current = current->left;
        } else {
            Node* topNode = s.top();
            if (topNode->right && lastVisited != topNode->right) {
                current = topNode->right;
            } else {
                delete topNode;
                lastVisited = topNode;
                s.pop();
            }
        }
    }
}

void printMenu() {
    cout << "\nMenu:\n";
    cout << "1. Enter infix expression\n";
    cout << "2. Perform postorder traversal\n";
    cout << "3. Delete the expression tree\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Node* root = nullptr;
    string expression;
    int choice;
    
    do {
        printMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter infix expression (without spaces): ";
                cin >> expression;
                if (root) {
                    deleteTree(root);
                    root = nullptr;
                }
                root = constructTree(expression);
                cout << "Expression tree constructed.\n";
                break;
                
            case 2:
                if (root) {
                    cout << "Postorder traversal: ";
                    postorderTraversal(root);
                } else {
                    cout << "No expression tree exists. Please enter an expression first.\n";
                }
                break;
                
            case 3:
                if (root) {
                    deleteTree(root);
                    root = nullptr;
                    cout << "Expression tree deleted.\n";
                } else {
                    cout << "No expression tree to delete.\n";
                }
                break;
                
            case 4:
                if (root) {
                    deleteTree(root);
                }
                cout << "Exiting program.\n";
                break;
                
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
    
    return 0;
}