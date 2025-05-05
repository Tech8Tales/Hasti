#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

/*
 * Node Declaration
 */
struct node
{
    char label[10];            // Store the name of the node (Book/Chapter/Section/Subsection)
    int ch_count;              // Count of children (chapters, sections, subsections)
    struct node *child[10];   // Pointer to child nodes (for chapters, sections, subsections)
} *root;

/*
 * Class Declaration
 */
class GT
{
public:
    void create_tree();  
    void display(node *r1);
    int findHeight(node *r1);  // Function to find height of the tree

    GT()
    
    {
        root = NULL;
    }
};

void GT::create_tree()
{
    int tchapters, tsections, tsubsections, i, j, k;
    root = new node;
    cout << "Enter name of book: ";
    cin >> root->label;
    cout << "Enter number of chapters in book: ";
    cin >> tchapters; 
    root->ch_count = tchapters;
    
    // Create chapters
    for (i = 0; i < tchapters; i++)
    {
        root->child[i] = new node;
        cout << "Enter Chapter name: ";
        cin >> root->child[i]->label;   
        cout << "Enter number of sections in Chapter " << root->child[i]->label << ": ";
        cin >> tsections;
        root->child[i]->ch_count = tsections;
        
        // Create sections for each chapter
        for (j = 0; j < tsections; j++)
        {
            root->child[i]->child[j] = new node;
            cout << "Enter Section " << j + 1 << " name: ";
            cin >> root->child[i]->child[j]->label;

            // Create subsections for each section
            cout << "Enter number of subsections in Section " << root->child[i]->child[j]->label << ": ";
            cin >> tsubsections;
            root->child[i]->child[j]->ch_count = tsubsections;

            for (k = 0; k < tsubsections; k++)
            {
                root->child[i]->child[j]->child[k] = new node;
                cout << "Enter Subsection " << k + 1 << " name: ";
                cin >> root->child[i]->child[j]->child[k]->label;   
            }  
        }  
    }
}

void GT::display(node *r1)
{
    int i, j, k, tchapters;
    if (r1 != NULL)
    { 
        cout << "\n-----Book Hierarchy---";
        cout << "\n Book title: " << r1->label;
        tchapters = r1->ch_count;
        
        // Display chapters
        for (i = 0; i < tchapters; i++)
        {
            cout << "\n  Chapter " << i + 1 << ": " << r1->child[i]->label;   
            cout << "\n Sections: ";
            
            // Display sections under each chapter
            for (j = 0; j < r1->child[i]->ch_count; j++)
            {
                cout << "\n    Section " << j + 1 << ": " << r1->child[i]->child[j]->label;
                
                // Display subsections under each section
                cout << "\n      Subsections: ";
                for (k = 0; k < r1->child[i]->child[j]->ch_count; k++)
                {
                    cout << "\n        " << r1->child[i]->child[j]->child[k]->label;
                }  
            }
        }
    }
}

// Function to find the height of the tree
int GT::findHeight(node *r1)
{
    // Base case: if the node is NULL, return -1
    if (r1 == NULL)
        return -1;

    int maxHeight = -1;
    
    // For each child, recursively find the height and track the maximum height
    for (int i = 0; i < r1->ch_count; i++)
    {
        maxHeight = max(maxHeight, findHeight(r1->child[i]));
        
        
    }

    // Return the height: 1 + the maximum height of the children
    return 1 + maxHeight;
}

/*
 * Main Contains Menu
 */
int main()
{
    int choice;
    GT gt;
    while (1)
    {
        cout << "-----------------" << endl;
        cout << "Book Tree Creation" << endl;
        cout << "-----------------" << endl;
        cout << "1. Create" << endl;
        cout << "2. Display" << endl;
        cout << "3. Find Height" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            gt.create_tree();
            break;
        case 2:
            gt.display(root);
            break;
        case 3:
            cout << "Height of the tree: " << gt.findHeight(root) << endl;
            break;
        case 4:
            exit(1);
        default:
            cout << "Wrong choice" << endl;
        }
    }
}


